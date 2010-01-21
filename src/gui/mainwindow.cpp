#include "mainwindow.h"

#include <QTreeView>
#include <QDirModel>

#include <sqlengine.h>
#include <schedulexmlparser.h>

#include <track.h>
#include <eventmodel.h>
#include <delegate.h>

#include <conference.h>

#include <QDialog>
#include "ui_about.h"
#include "eventdialog.h"
#include "daynavigatorwidget.h"
#include "mapwindow.h"

const int confId = 1;

MainWindow::MainWindow(int aEventId, QWidget *aParent)
    : QMainWindow(aParent)
{
    setupUi(this);

    // connect Menu actions
    connect(actionImportSchedule, SIGNAL(triggered()), SLOT(importSchedule()));
    connect(actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(actionAboutApplication, SIGNAL(triggered()), SLOT(aboutApp()));

    // create "SQLITE" DB instance/connection
    // opens DB connection (needed for EventModel)
    mSqlEngine = new SqlEngine(this);
    mSqlEngine->initialize();

    mXmlParser = new ScheduleXmlParser(this);
    connect(mXmlParser, SIGNAL(progressStatus(int)), this, SLOT(showParsingProgress(int)));
    statusBar()->showMessage(tr("Ready"));

    //update track map
    Track::updateTrackMap();

    connect(dayNavigator, SIGNAL(dateChanged(const QDate &)), SLOT(updateDayView(const QDate &)));
    connect(trackDayNavigator, SIGNAL(dateChanged(const QDate &)), SLOT(updateTracksView(const QDate &)));
    connect(favouriteDayNavigator, SIGNAL(dateChanged(const QDate &)), SLOT(updateFavouritesView(const QDate &)));

    // DAY EVENTS View
    dayTreeView->setHeaderHidden(true);
    dayTreeView->setRootIsDecorated(false);
    dayTreeView->setIndentation(0);
    dayTreeView->setAnimated(true);
    dayTreeView->setModel(new EventModel());
    dayTreeView->setItemDelegate(new Delegate(dayTreeView));

    // FAVOURITIES View
    favTreeView->setHeaderHidden(true);
    favTreeView->setRootIsDecorated(false);
    favTreeView->setIndentation(0);
    favTreeView->setAnimated(true);
    favTreeView->setModel(new EventModel());
    favTreeView->setItemDelegate(new Delegate(favTreeView));

    //ACTIVITIES View
    trackTreeView->setHeaderHidden(true);
    trackTreeView->setRootIsDecorated(false);
    trackTreeView->setIndentation(0);
    trackTreeView->setAnimated(true);
    trackTreeView->setModel(new EventModel());
    trackTreeView->setItemDelegate(new Delegate(trackTreeView));

    // SEARCH EVENTS View
	searchTreeView->setHeaderHidden(true);
	searchTreeView->setRootIsDecorated(false);
	searchTreeView->setIndentation(0);
	searchTreeView->setAnimated(true);
	searchTreeView->setModel(new EventModel());
	searchTreeView->setItemDelegate(new Delegate(searchTreeView));
	searchTreeView->setVisible(false);
	searchDayNavigator->setVisible(false);
    // event clicked
    connect(dayTreeView, SIGNAL(clicked(const QModelIndex &)), SLOT(itemClicked(const QModelIndex &)));
    connect(favTreeView, SIGNAL(clicked(const QModelIndex &)), SLOT(itemClicked(const QModelIndex &)));
    connect(trackTreeView, SIGNAL(clicked(const QModelIndex &)), SLOT(itemClicked(const QModelIndex &)));
    connect(searchTreeView, SIGNAL(clicked(const QModelIndex &)), SLOT(itemClicked(const QModelIndex &)));
    // request for map to be displayed
    connect(dayTreeView, SIGNAL(requestForMap(const QModelIndex &)), SLOT(displayMap(const QModelIndex &)));
    connect(favTreeView, SIGNAL(requestForMap(const QModelIndex &)), SLOT(displayMap(const QModelIndex &)));
    connect(trackTreeView, SIGNAL(requestForMap(const QModelIndex &)), SLOT(displayMap(const QModelIndex &)));
    connect(searchTreeView, SIGNAL(requestForMap(const QModelIndex &)), SLOT(displayMap(const QModelIndex &)));
    // event search button clicked
    connect(searchButton, SIGNAL(clicked()), SLOT(searchClicked()));

    // TESTING: load some 'fav' data
    if(Conference::getAll().count()) // no conference(s) in the DB
    {
        static_cast<EventModel*>(favTreeView->model())->loadFavEvents(Conference::getById(confId).start(),confId);
        favTreeView->reset();
    }

    if(!Conference::getAll().count()) // no conference(s) in the DB
    {
        dayNavigator->hide(); // hide DayNavigatorWidget
        trackDayNavigator->hide();
    }
    else
    {
        QDate aStartDate = Conference::getById(confId).start();
        QDate aEndDate = Conference::getById(confId).end();
        dayNavigator->setDates(aStartDate, aEndDate);
        trackDayNavigator->setDates(aStartDate, aEndDate);
        favouriteDayNavigator->setDates(aStartDate, aEndDate);
        searchDayNavigator->setDates(aStartDate, aEndDate);
    }

    connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(updateTab(int)));

    // open dialog for given Event ID
    // this is used in case Alarm Dialog request application to start
    if(aEventId)
    {
        try
        {
            EventDialog dialog(aEventId,this);
            dialog.exec();
        }
        catch(OrmNoObjectException*) {} // just start application
        catch(...) {} // just start application
    }
}

MainWindow::~MainWindow()
{
    if(mSqlEngine)
    {
        delete mSqlEngine;
        mSqlEngine = NULL;
    }
    if(mXmlParser)
    {
        delete mXmlParser;
        mXmlParser = NULL;
    }
}

void MainWindow::importSchedule()
{
    QFile file(":/schedule.en.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "can't open " << file.fileName();
        return;
    }

    QByteArray data = file.readAll();
    mXmlParser->parseData(data,mSqlEngine);

    if(Conference::getAll().count())
    {
        // 'dayNavigator' emits signal 'dateChanged' after setting valid START:END dates
        QDate aStartDate = Conference::getById(confId).start();
        QDate aEndDate = Conference::getById(confId).end();
        dayNavigator->setDates(aStartDate, aEndDate);
        trackDayNavigator->setDates(aStartDate, aEndDate);
    }
    //update track map
    Track::updateTrackMap();
}

void MainWindow::showParsingProgress(int aStatus)
{
    QString msg = QString("Parsing completed: %1\%").arg(aStatus);
    statusBar()->showMessage(msg,1000);
}

void MainWindow::aboutApp()
{
    QDialog dialog(this);
    Ui::AboutDialog ui;
    ui.setupUi(&dialog);
    dialog.exec();
}

void MainWindow::updateDayView(const QDate &aDate)
{
    static_cast<EventModel*>(dayTreeView->model())->loadEvents(aDate,confId);
    dayTreeView->reset();
    dayNavigator->show();
}

void MainWindow::updateTab(const int aIndex)
{
    switch(aIndex)
    {
    case 0://index 0 of tabWidget: dayViewTab
        {
            static_cast<EventModel*>(dayTreeView->model())->loadEvents(Conference::getById(confId).start(),confId);
            dayTreeView->reset();
            dayNavigator->show();
        }
        break;
    case 1: //index 1 of tabWidget: favouritesTab
        {
            static_cast<EventModel*>(favTreeView->model())->loadFavEvents(Conference::getById(confId).start(),confId);
            favTreeView->reset();
            favouriteDayNavigator->show();
        }
        break;
    case 2: //index 2 of tabWidget: trackTab
        {
            static_cast<EventModel*>(trackTreeView->model())->loadEventsByTrack(Conference::getById(confId).start(), confId);
            trackTreeView->reset();
            trackDayNavigator->show();
        }
        break;
    default:
        {

        }
    };
}

void MainWindow::updateTracksView(const QDate &aDate)
{
    static_cast<EventModel*>(trackTreeView->model())->loadEventsByTrack(aDate, confId);
    trackTreeView->reset();
    trackDayNavigator->show();
}

void MainWindow::updateFavouritesView(const QDate &aDate)
{
    static_cast<EventModel*>(favTreeView->model())->loadFavEvents(aDate,confId);
    favTreeView->reset();
    favouriteDayNavigator->show();
}

void MainWindow::itemClicked(const QModelIndex &aIndex)
{
    // have to handle only events, not time-groups
    if(!aIndex.parent().isValid()) // time-group
        return;

    EventDialog dialog(static_cast<Event*>(aIndex.internalPointer())->id(),this);
    dialog.exec();
}

void MainWindow::displayMap(const QModelIndex &aIndex)
{
    Event *event = static_cast<Event*>(aIndex.internalPointer());

    // room names are stored in lower-case format
    // room names are stored without dots in the name, eg. "aw.1124.png" -> "aw1124.png"
    QString mapPath = QString(":/maps/rooms/%1.png").arg(event->room().toLower().remove("."));
    if(!QFile::exists(mapPath))
        mapPath = QString(":/maps/rooms/not-available.png");

    QString roomName;
    if(mapPath.contains("not-available", Qt::CaseInsensitive))
        roomName = QString("Map is not available: %1").arg(event->room());
    else
        roomName = event->room();

    QPixmap map(mapPath);
    MapWindow window(map,roomName,this);
    window.exec();
}

void MainWindow::searchClicked()
{
    QList<QString> columns;

    if( searchTitle->isChecked() )
        columns.append( "title" );
    if( searchAbstract->isChecked() )
        columns.append( "abstract" );

    searchTreeView->reset();
    if( mSqlEngine->searchEvent( confId, columns, searchEdit->text() ) > 0 ){
        static_cast<EventModel*>(searchTreeView->model())->loadSearchResultEvents(Conference::getById(confId).start(),confId);
        searchDayNavigator->show();
        searchTreeView->show();
    }
}

