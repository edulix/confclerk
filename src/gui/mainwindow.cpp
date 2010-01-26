#include "mainwindow.h"
#include <appsettings.h>

#include <QTreeView>
#include <QFile>

#include <sqlengine.h>

#include <track.h>
#include <eventmodel.h>
#include <delegate.h>

#include <conference.h>

#include <QDialog>
#include <QMessageBox>
#include "ui_about.h"
#include <eventdialog.h>
#include "daynavigatorwidget.h"
#include "importschedulewidget.h"
#include "mapwindow.h"

#include <tabcontainer.h>

MainWindow::MainWindow(int aEventId, QWidget *aParent)
    : QMainWindow(aParent)
{
    setupUi(this);

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

        setWindowTitle(confs[0].title());
    }

    dayTabContainer->setType(TabContainer::EContainerTypeDay);
    favsTabContainer->setType(TabContainer::EContainerTypeFavs);
    tracksTabContainer->setType(TabContainer::EContainerTypeTracks);
    nowTabContainer->setType(TabContainer::EContainerTypeNow);
    roomsTabContainer->setType(TabContainer::EContainerTypeRooms);

    connect(importScheduleWidget, SIGNAL(scheduleImported(int)), SLOT(scheduleImported(int)));

    connect(searchDayNavigator, SIGNAL(dateChanged(const QDate &)), SLOT(updateSearchView(const QDate &)));

    // SEARCH EVENTS View
	searchTreeView->setHeaderHidden(true);
	searchTreeView->setRootIsDecorated(false);
	searchTreeView->setIndentation(0);
	searchTreeView->setAnimated(true);
	searchTreeView->setModel(new EventModel());
	searchTreeView->setItemDelegate(new Delegate(searchTreeView));

    // event details have changed
    connect(dayTabContainer, SIGNAL(eventHasChanged(int)), SLOT(eventHasChanged(int)));
    connect(favsTabContainer, SIGNAL(eventHasChanged(int)), SLOT(eventHasChanged(int)));
    connect(favsTabContainer, SIGNAL(eventHasChanged(int)), SLOT(eventHasChanged(int)));
    connect(roomsTabContainer, SIGNAL(eventHasChanged(int)), SLOT(eventHasChanged(int)));
    connect(nowTabContainer, SIGNAL(eventHasChanged(int)), SLOT(eventHasChanged(int)));

    connect(searchTreeView, SIGNAL(eventHasChanged(int)), SLOT(eventHasChanged(int)));

    // event clicked
    connect(searchTreeView, SIGNAL(clicked(const QModelIndex &)), SLOT(itemClicked(const QModelIndex &)));

    // event search button clicked
    connect(searchButton, SIGNAL(clicked()), SLOT(searchClicked()));
    connect(searchAgainButton, SIGNAL(clicked()), SLOT(searchAgainClicked()));

    // event conference map button clicked
    connect(showMapButton, SIGNAL(clicked()), SLOT(conferenceMapClicked()));
    //
    connect(tabWidget, SIGNAL(infoIconClicked()), SLOT(aboutApp()));

    if(Conference::getAll().count()) // no conference(s) in the DB
    {
        QDate aStartDate = Conference::getById(AppSettings::confId()).start();
        QDate aEndDate = Conference::getById(AppSettings::confId()).end();
        searchDayNavigator->setDates(aStartDate, aEndDate);
        //
        dayTabContainer->setDates(aStartDate, aEndDate);
        tracksTabContainer->setDates(aStartDate, aEndDate);
        roomsTabContainer->setDates(aStartDate, aEndDate);
        favsTabContainer->setDates(aStartDate, aEndDate);
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
    searchVerticalWidget->hide();
    searchHead->show();

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

void MainWindow::scheduleImported(int aConfId)
{
    Q_UNUSED(aConfId);

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
        QDate startDate = Conference::getById(AppSettings::confId()).start();
        QDate endDate = Conference::getById(AppSettings::confId()).end();
        dayTabContainer->setDates(startDate, endDate);
        tracksTabContainer->setDates(startDate, endDate);
        roomsTabContainer->setDates(startDate, endDate);
        favsTabContainer->setDates(startDate, endDate);
    }
}

void MainWindow::aboutApp()
{
    QDialog dialog(this);
    Ui::AboutDialog ui;
    ui.setupUi(&dialog);
    dialog.exec();
}

void MainWindow::updateSearchView(const QDate &aDate)
{
    qDebug() << "MainWindow::updateSearchView(), aDate: " << aDate.toString() ;
    searchTreeView->reset();
    int eventsCount = static_cast<EventModel*>(searchTreeView->model())->loadSearchResultEvents(aDate,AppSettings::confId());
    if( eventsCount ||
            searchDayNavigator->getCurrentDate() != Conference::getById(AppSettings::confId()).start() ){
        searchVerticalWidget->show();
        //searchAgainButton->show();
        searchTreeView->show();
        searchHead->hide();
    }
    else{
        searchTreeView->hide();
        searchVerticalWidget->hide();
        searchHead->show();
    }
}

void MainWindow::searchClicked()
{
    QHash<QString,QString> columns;

    if( searchTitle->isChecked() )
        columns.insertMulti("EVENT", "title");
    if( searchAbstract->isChecked() )
        columns.insertMulti("EVENT", "abstract");
    if( searchTag->isChecked() )
        columns.insertMulti("EVENT", "tag");
    if( searchSpeaker->isChecked() )
        columns["PERSON"] = "name";
    if( searchRoom->isChecked() )
        columns["ROOM"] = "name";

    QString keyword = searchEdit->text().replace( QString("%"), QString("\\%") );
    qDebug() << "\nKeyword to search: " << keyword;
    SqlEngine::searchEvent( AppSettings::confId(), columns, keyword );

    QDate aStartDate = Conference::getById(AppSettings::confId()).start();
    QDate aEndDate = Conference::getById(AppSettings::confId()).end();
    searchDayNavigator->setDates(aStartDate, aEndDate);
    updateSearchView( Conference::getById(AppSettings::confId()).start() );
}

void MainWindow::searchAgainClicked()
{
    searchHead->show();
    //searchAgainButton->hide();
    searchVerticalWidget->hide();
    searchTreeView->hide();
}

void MainWindow::conferenceMapClicked()
{
    QString mapPath = QString(":/maps/campus.png");
    if(!QFile::exists(mapPath))
        mapPath = QString(":/maps/rooms/not-available.png");

    QString roomName;

    QPixmap map(mapPath);
    MapWindow window(map,roomName,this);
    window.exec();
}

void MainWindow::eventHasChanged(int aEventId)
{
    dayTabContainer->updateTreeViewModel(aEventId);
    favsTabContainer->updateTreeViewModel(aEventId);
    tracksTabContainer->updateTreeViewModel(aEventId);
    nowTabContainer->updateTreeViewModel(aEventId);
    roomsTabContainer->updateTreeViewModel(aEventId);

    static_cast<EventModel*>(searchTreeView->model())->updateModel(aEventId);
}

