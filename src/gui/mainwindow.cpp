#include "mainwindow.h"
#include <appsettings.h>

#include <QTreeView>
#include <QDirModel>

#include <sqlengine.h>

#include <track.h>
#include <eventmodel.h>
#include <delegate.h>

#include <conference.h>

#include <QDialog>
#include <QMessageBox>
#include "ui_about.h"
#include "eventdialog.h"
#include "daynavigatorwidget.h"
#include "importscheduledialog.h"
#include "mapwindow.h"

MainWindow::MainWindow(int aEventId, QWidget *aParent)
    : QMainWindow(aParent)
{
    setupUi(this);

    // create "SQLITE" DB instance/connection
    // opens DB connection (needed for EventModel)
    mSqlEngine = new SqlEngine(this);
    mSqlEngine->initialize();

    // Sanity check for existence of any Conference in the DB
    // it AppSettings::confId() is 0, but there are any Conference(s) in the DB
    // set the confId in the AppSettings for the ID of the first conference in the DB
    QList<Conference> confs = Conference::getAll();
    if(!confs.count()) // no conference(s) in the DB
    {
        AppSettings::setConfId(0); // no conference in the DB
    }
    else
    {
        if(AppSettings::confId() == 0)
            AppSettings::setConfId(confs[0].id());
    }

    // connect Menu actions
    connect(actionImportSchedule, SIGNAL(triggered()), SLOT(importSchedule()));
    connect(actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(actionAboutApplication, SIGNAL(triggered()), SLOT(aboutApp()));

    connect(dayNavigator, SIGNAL(dateChanged(const QDate &)), SLOT(updateDayView(const QDate &)));
    connect(trackDayNavigator, SIGNAL(dateChanged(const QDate &)), SLOT(updateTracksView(const QDate &)));
    connect(favouriteDayNavigator, SIGNAL(dateChanged(const QDate &)), SLOT(updateFavouritesView(const QDate &)));
    connect(searchDayNavigator, SIGNAL(dateChanged(const QDate &)), SLOT(updateSearchView(const QDate &)));

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

    // TRACKS View
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

    // NOW View
	nowTreeView->setHeaderHidden(true);
	nowTreeView->setRootIsDecorated(false);
	nowTreeView->setIndentation(0);
	nowTreeView->setAnimated(true);
	nowTreeView->setModel(new EventModel());
	nowTreeView->setItemDelegate(new Delegate(nowTreeView));

    // event details have changed
    connect(dayTreeView, SIGNAL(eventHasChanged(int)), SLOT(eventHasChanged(int)));
    connect(favTreeView, SIGNAL(eventHasChanged(int)), SLOT(eventHasChanged(int)));
    connect(trackTreeView, SIGNAL(eventHasChanged(int)), SLOT(eventHasChanged(int)));
    connect(searchTreeView, SIGNAL(eventHasChanged(int)), SLOT(eventHasChanged(int)));
    connect(nowTreeView, SIGNAL(eventHasChanged(int)), SLOT(eventHasChanged(int)));

    // event clicked
    connect(dayTreeView, SIGNAL(clicked(const QModelIndex &)), SLOT(itemClicked(const QModelIndex &)));
    connect(favTreeView, SIGNAL(clicked(const QModelIndex &)), SLOT(itemClicked(const QModelIndex &)));
    connect(trackTreeView, SIGNAL(clicked(const QModelIndex &)), SLOT(itemClicked(const QModelIndex &)));
    connect(searchTreeView, SIGNAL(clicked(const QModelIndex &)), SLOT(itemClicked(const QModelIndex &)));
    connect(nowTreeView, SIGNAL(clicked(const QModelIndex &)), SLOT(itemClicked(const QModelIndex &)));
    // request for map to be displayed
    connect(dayTreeView, SIGNAL(requestForMap(const QModelIndex &)), SLOT(displayMap(const QModelIndex &)));
    connect(favTreeView, SIGNAL(requestForMap(const QModelIndex &)), SLOT(displayMap(const QModelIndex &)));
    connect(trackTreeView, SIGNAL(requestForMap(const QModelIndex &)), SLOT(displayMap(const QModelIndex &)));
    connect(searchTreeView, SIGNAL(requestForMap(const QModelIndex &)), SLOT(displayMap(const QModelIndex &)));
    connect(nowTreeView, SIGNAL(requestForMap(const QModelIndex &)), SLOT(displayMap(const QModelIndex &)));
    // request for warning to be displayed
    connect(dayTreeView, SIGNAL(requestForWarning(const QModelIndex &)), SLOT(displayWarning(const QModelIndex &)));
    connect(favTreeView, SIGNAL(requestForWarning(const QModelIndex &)), SLOT(displayWarning(const QModelIndex &)));
    connect(trackTreeView, SIGNAL(requestForWarning(const QModelIndex &)), SLOT(displayWarning(const QModelIndex &)));
    connect(searchTreeView, SIGNAL(requestForWarning(const QModelIndex &)), SLOT(displayWarning(const QModelIndex &)));
    connect(nowTreeView, SIGNAL(requestForWarning(const QModelIndex &)), SLOT(displayWarning(const QModelIndex &)));
    // event search button clicked
    connect(searchButton, SIGNAL(clicked()), SLOT(searchClicked()));
    //
    connect(tabWidget, SIGNAL(currentChanged(int)), SLOT(tabHasChanged(int)));

    if(!Conference::getAll().count()) // no conference(s) in the DB
    {
        dayNavigator->hide(); // hide DayNavigatorWidget
        trackDayNavigator->hide();
    }
    else
    {
        QDate aStartDate = Conference::getById(AppSettings::confId()).start();
        QDate aEndDate = Conference::getById(AppSettings::confId()).end();
        dayNavigator->setDates(aStartDate, aEndDate);
        trackDayNavigator->setDates(aStartDate, aEndDate);
        favouriteDayNavigator->setDates(aStartDate, aEndDate);
        searchDayNavigator->setDates(aStartDate, aEndDate);
        //
        conferenceTitle->setText(Conference::getById(AppSettings::confId()).title());
        conferenceSubtitle->setText(Conference::getById(AppSettings::confId()).subtitle());
        conferenceWhere->setText(Conference::getById(AppSettings::confId()).city() + ", " + Conference::getById(AppSettings::confId()).venue());
        conferenceWhen->setText(
                Conference::getById(AppSettings::confId()).start().toString("dd-MM-yyyy")
                + ", " +
                Conference::getById(AppSettings::confId()).end().toString("dd-MM-yyyy"));
    }

    searchTreeView->hide();
    searchDayNavigator->hide();

    // open dialog for given Event ID
    // this is used in case Alarm Dialog request application to start
    if(aEventId)
    {
        try
        {
            EventDialog dialog(aEventId,this);
            dialog.exec();
        }
        catch(OrmNoObjectException&) {} // just start application
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
}

void MainWindow::importSchedule()
{
    ImportScheduleDialog dialog(mSqlEngine,this);
    dialog.exec();

    QList<Conference> confs = Conference::getAll();
    if(!confs.count()) // no conference(s) in the DB
    {
        AppSettings::setConfId(0); // no conference in the DB
    }
    else
    {
        if(AppSettings::confId() == 0)
            AppSettings::setConfId(confs[0].id());

        // 'dayNavigator' emits signal 'dateChanged' after setting valid START:END dates
        QDate aStartDate = Conference::getById(AppSettings::confId()).start();
        QDate aEndDate = Conference::getById(AppSettings::confId()).end();
        dayNavigator->setDates(aStartDate, aEndDate);
        trackDayNavigator->setDates(aStartDate, aEndDate);
    }
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
    static_cast<EventModel*>(dayTreeView->model())->loadEvents(aDate,AppSettings::confId());
    dayTreeView->reset();
    dayNavigator->show();
}

void MainWindow::updateTracksView(const QDate &aDate)
{
    static_cast<EventModel*>(trackTreeView->model())->loadEventsByTrack(aDate, AppSettings::confId());
    trackTreeView->reset();
    trackDayNavigator->show();
}

void MainWindow::updateFavouritesView(const QDate &aDate)
{
    static_cast<EventModel*>(favTreeView->model())->loadFavEvents(aDate,AppSettings::confId());
    favTreeView->reset();
    favouriteDayNavigator->show();
}

void MainWindow::updateSearchView(const QDate &aDate)
{
    searchTreeView->reset();
    int eventsCount = static_cast<EventModel*>(searchTreeView->model())->loadSearchResultEvents(aDate,AppSettings::confId());
    if( eventsCount ){
        searchDayNavigator->show();
        searchTreeView->show();
    }
    else{
        searchTreeView->hide();
        searchDayNavigator->hide();
    }
}

void MainWindow::updateNowView()
{
    EventModel *model = static_cast<EventModel*>(nowTreeView->model());
    model->loadNowEvents(AppSettings::confId());
    nowTreeView->reset();
    nowTreeView->setAllExpanded(true);
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

    mSqlEngine->searchEvent( AppSettings::confId(), columns, searchEdit->text() );
    updateSearchView( Conference::getById(AppSettings::confId()).start() );
}

void MainWindow::displayWarning(const QModelIndex &aIndex)
{
    Q_UNUSED(aIndex);

    QMessageBox::warning(
    this,
    tr("Time Conflict Warning"),
    tr("This event happens at the same time than another one of your favourites.") );
}

void MainWindow::eventHasChanged(int aEventId)
{
    static_cast<EventModel*>(dayTreeView->model())->updateModel(aEventId);
    static_cast<EventModel*>(favTreeView->model())->updateModel(aEventId);
    static_cast<EventModel*>(trackTreeView->model())->updateModel(aEventId);
    static_cast<EventModel*>(searchTreeView->model())->updateModel(aEventId);
    static_cast<EventModel*>(nowTreeView->model())->updateModel(aEventId);
}

void MainWindow::tabHasChanged(int aIndex)
{
    Q_UNUSED(aIndex);

    // TODO: only if it changed to favourities tab
    updateFavouritesView(favouriteDayNavigator->getCurrentDate());
    // TODO: only if it changed to now tab
    //updateNowView();
}

