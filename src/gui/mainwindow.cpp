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

    connect(importScheduleWidget, SIGNAL(scheduleImported(int)), SLOT(scheduleImported(int)));

    // event details have changed
    connect(dayTabContainer, SIGNAL(eventHasChanged(int)), SLOT(eventHasChanged(int)));
    connect(favsTabContainer, SIGNAL(eventHasChanged(int)), SLOT(eventHasChanged(int)));
    connect(favsTabContainer, SIGNAL(eventHasChanged(int)), SLOT(eventHasChanged(int)));
    connect(roomsTabContainer, SIGNAL(eventHasChanged(int)), SLOT(eventHasChanged(int)));
    connect(nowTabContainer, SIGNAL(eventHasChanged(int)), SLOT(eventHasChanged(int)));
    connect(searchTabContainer, SIGNAL(eventHasChanged(int)), SLOT(eventHasChanged(int)));


    // event conference map button clicked
    connect(showMapButton, SIGNAL(clicked()), SLOT(conferenceMapClicked()));

    connect(tabWidget, SIGNAL(infoIconClicked()), SLOT(aboutApp()));

    if(Conference::getAll().count()) // no conference(s) in the DB
    {
        QDate startDate = Conference::getById(AppSettings::confId()).start();
        QDate endDate = Conference::getById(AppSettings::confId()).end();
        //
        dayTabContainer->setDates(startDate, endDate);
        tracksTabContainer->setDates(startDate, endDate);
        roomsTabContainer->setDates(startDate, endDate);
        favsTabContainer->setDates(startDate, endDate);
        searchTabContainer->setDates(startDate, endDate);
        //
        conferenceTitle->setText(Conference::getById(AppSettings::confId()).title());
        conferenceSubtitle->setText(Conference::getById(AppSettings::confId()).subtitle());
        conferenceWhere->setText(Conference::getById(AppSettings::confId()).city() + ", " + Conference::getById(AppSettings::confId()).venue());
        conferenceWhen->setText(
                Conference::getById(AppSettings::confId()).start().toString("dd-MM-yyyy")
                + ", " +
                Conference::getById(AppSettings::confId()).end().toString("dd-MM-yyyy"));
    }

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
    searchTabContainer->updateTreeViewModel(aEventId);
}

