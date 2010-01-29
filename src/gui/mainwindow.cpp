#include "mainwindow.h"

#include <QTreeView>
#include <QFile>
#include <QNetworkProxy>

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

const QString PROXY_URL("192.168.0.252");
const quint16 PROXY_PORT = 4040;
const QString PROXY_USERNAME;
const QString PROXY_PASSWD;
const bool DIRECT_CONNECTION = false;

MainWindow::MainWindow(int aEventId, QWidget *aParent)
    : QMainWindow(aParent)
{
    setupUi(this);

    qDebug() << "Setting-up proxy: " << PROXY_URL << ":" << PROXY_PORT;
    QNetworkProxy proxy(DIRECT_CONNECTION ? QNetworkProxy::NoProxy : QNetworkProxy::HttpProxy,
            PROXY_URL, PROXY_PORT, PROXY_USERNAME, PROXY_PASSWD);
    QNetworkProxy::setApplicationProxy(proxy);

    int confId = Conference::activeConference();

    connect(importScheduleWidget, SIGNAL(scheduleImported(int)), SLOT(scheduleImported(int)));

    // event details have changed
    connect(dayTabContainer, SIGNAL(eventHasChanged(int,bool)), SLOT(eventHasChanged(int,bool)));
    connect(favsTabContainer, SIGNAL(eventHasChanged(int,bool)), SLOT(eventHasChanged(int,bool)));
    connect(tracksTabContainer, SIGNAL(eventHasChanged(int,bool)), SLOT(eventHasChanged(int,bool)));
    connect(roomsTabContainer, SIGNAL(eventHasChanged(int,bool)), SLOT(eventHasChanged(int,bool)));
    connect(nowTabContainer, SIGNAL(eventHasChanged(int,bool)), SLOT(eventHasChanged(int,bool)));
    connect(searchTabContainer, SIGNAL(eventHasChanged(int,bool)), SLOT(eventHasChanged(int,bool)));

    // event conference map button clicked
    connect(showMapButton, SIGNAL(clicked()), SLOT(conferenceMapClicked()));

    connect(tabWidget, SIGNAL(infoIconClicked()), SLOT(aboutApp()));

    selectConference->setDuplicatesEnabled(false);
    int confCount = Conference::getAll().count();
    if(confCount)
    {
        initTabs();
        fillAndShowConferenceHeader();
        setWindowTitle(Conference::getById(confId).title());

        if(confCount==1) // don't have to show 'selectConference' widget, if there is only one conference in the DB
            selectConferenceWidget->hide();
        else
        {
            // have to fill comboBox with available conferences
            QList<Conference> confs = Conference::getAll();
            QListIterator<Conference> i(confs);
            while(i.hasNext())
            {
                Conference conf = i.next();
                selectConference->addItem(conf.title(),conf.id());
            }
            int idx = selectConference->findText(Conference::getById(Conference::activeConference()).title());
            selectConference->setCurrentIndex(idx);
        }
        connect(selectConference, SIGNAL(currentIndexChanged(int)), SLOT(conferenceChanged(int)));
    }
    else
    {
        conferenceHeader->hide();
        selectConferenceWidget->hide();
        // go to the 'conferenceTab', so the user can import the schedule
        tabWidget->setCurrentIndex(6); // 6 - conference tab
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

    Conference conf = Conference::getById(aConfId);
    if( selectConference->findText(conf.title()) < 0 ) // item doesn't exist
    {
        disconnect(selectConference, SIGNAL(currentIndexChanged(int)), this, SLOT(conferenceChanged(int)));
        selectConference->addItem(conf.title(),conf.id());
        connect(selectConference, SIGNAL(currentIndexChanged(int)), SLOT(conferenceChanged(int)));
    }
    int confCount = Conference::getAll().count();
    if(confCount)
    {
        int idx = selectConference->findText(conf.title());
        selectConference->setCurrentIndex(idx);

        if(confCount>1)
            selectConferenceWidget->show();

        conferenceChanged(idx);
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

void MainWindow::eventHasChanged(int aEventId, bool aReloadModel)
{
    dayTabContainer->updateTreeViewModel(aEventId);
    favsTabContainer->updateTreeViewModel(aEventId,aReloadModel);
    tracksTabContainer->updateTreeViewModel(aEventId);
    nowTabContainer->updateTreeViewModel(aEventId);
    roomsTabContainer->updateTreeViewModel(aEventId);
    searchTabContainer->updateTreeViewModel(aEventId);
}

void MainWindow::fillAndShowConferenceHeader()
{
    int confId = Conference::activeConference();
    conferenceTitle->setText(Conference::getById(confId).title());
    conferenceSubtitle->setText(Conference::getById(confId).subtitle());
    conferenceWhere->setText(Conference::getById(confId).city() + ", " + Conference::getById(confId).venue());
    conferenceWhen->setText(
            Conference::getById(confId).start().toString("dd-MM-yyyy")
            + ", " +
            Conference::getById(confId).end().toString("dd-MM-yyyy"));
    conferenceHeader->show();
}

void MainWindow::initTabs()
{
    int confId = Conference::activeConference();
    QDate startDate = Conference::getById(confId).start();
    QDate endDate = Conference::getById(confId).end();

    // 'dayNavigator' emits signal 'dateChanged' after setting valid START:END dates
    dayTabContainer->setDates(startDate, endDate);
    tracksTabContainer->setDates(startDate, endDate);
    roomsTabContainer->setDates(startDate, endDate);
    favsTabContainer->setDates(startDate, endDate);
    searchTabContainer->setDates(startDate, endDate);
    searchTabContainer->searchAgainClicked();
    nowTabContainer->updateTreeView(QDate::currentDate());
}

void MainWindow::conferenceChanged(int aIndex)
{
    Conference::getById(Conference::activeConference()).update("active",0);
    Conference::getById(selectConference->itemData(aIndex).toInt()).update("active",1);

    initTabs();
    fillAndShowConferenceHeader();
    setWindowTitle(Conference::getById(Conference::activeConference()).title());
}

