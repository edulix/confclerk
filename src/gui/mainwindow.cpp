/*
 * Copyright (C) 2010 Ixonos Plc.
 *
 * This file is part of fosdem-schedule.
 *
 * fosdem-schedule is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 2 of the License, or (at your option)
 * any later version.
 *
 * fosdem-schedule is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * fosdem-schedule.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "mainwindow.h"

#include <QTreeView>
#include <QFile>
#include <QNetworkProxy>
#include <QNetworkAccessManager>
#include <QNetworkReply>

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
#include "mapwindow.h"
#include "settingsdialog.h"
#include "conferenceeditor.h"
#include "schedulexmlparser.h"
#include "errormessage.h"

#include <tabcontainer.h>
#include <appsettings.h>

const QString PROXY_USERNAME;
const QString PROXY_PASSWD;

MainWindow::MainWindow(int aEventId, QWidget *aParent)
    : QMainWindow(aParent)
    , conferenceModel(new ConferenceModel(this))
    , mXmlParser(new ScheduleXmlParser(this))
    , mNetworkAccessManager(new QNetworkAccessManager(this))
{
    setupUi(this);

    saved_title = windowTitle();

#ifdef N810
    tabWidget->setTabText(1,"Favs");
    //tabWidget->setTabText(2,"Day");
#endif

    // first time run aplication: -> let's have it direct connection in this case
    if(!AppSettings::contains("proxyIsDirectConnection"))
        AppSettings::setDirectConnection(true);

    if(AppSettings::isDirectConnection())
    {
        qDebug() << "Setting-up proxy: " << AppSettings::proxyAddress() << ":" << AppSettings::proxyPort();
    }
    QNetworkProxy proxy(
            AppSettings::isDirectConnection() ? QNetworkProxy::NoProxy : QNetworkProxy::HttpProxy,
            AppSettings::proxyAddress(),
            AppSettings::proxyPort(),
            PROXY_USERNAME,
            PROXY_PASSWD);
    QNetworkProxy::setApplicationProxy(proxy);

    #if 0
    // list of conferences must be maintained by ConferenceEditor
    // here must be one of the signals from the closing ConferenceEditor (or model):
    // selectedConf(conference), noConf()
    connect(importScheduleWidget, SIGNAL(scheduleImported(int)), SLOT(scheduleImported(int)));
    connect(importScheduleWidget, SIGNAL(scheduleDeleted(const QString&)), SLOT(scheduleDeleted(const QString&)));
    #endif

    // event details have changed
    connect(dayTabContainer, SIGNAL(eventHasChanged(int,bool)), SLOT(eventHasChanged(int,bool)));
    connect(favsTabContainer, SIGNAL(eventHasChanged(int,bool)), SLOT(eventHasChanged(int,bool)));
    connect(tracksTabContainer, SIGNAL(eventHasChanged(int,bool)), SLOT(eventHasChanged(int,bool)));
    connect(roomsTabContainer, SIGNAL(eventHasChanged(int,bool)), SLOT(eventHasChanged(int,bool)));
    connect(nowTabContainer, SIGNAL(eventHasChanged(int,bool)), SLOT(eventHasChanged(int,bool)));
    connect(searchTabContainer, SIGNAL(eventHasChanged(int,bool)), SLOT(eventHasChanged(int,bool)));

    // event conference map button clicked
    #if 0
    // TODO: think about it when return to maps
    connect(showMapButton, SIGNAL(clicked()), SLOT(conferenceMapClicked()));
    #endif

    connect(aboutAction, SIGNAL(triggered()), SLOT(aboutApp()));
    connect(settingsAction, SIGNAL(triggered()), SLOT(setup()));
    connect(conferencesAction, SIGNAL(triggered()), SLOT(showConferences()));

    useConference(Conference::activeConference());

    #if 0
    // TODO: remove GUI
    // initialisation of model and pick active conference from there and call conferenceChanged()
    // selectConference->setDuplicatesEnabled(false);
    int confCount = Conference::getAll().count();
    if(confCount)
    {
        initTabs();
        // fillAndShowConferenceHeader();
        setWindowTitle(Conference::getById(confId).title());

        QList<Conference> confs = Conference::getAll();
        QListIterator<Conference> i(confs);
        while(i.hasNext())
        {
            Conference conf = i.next();
            // TODO: remove GUI
            // selectConference->addItem(conf.title(),conf.id());
        }
        // TODO: remove GUI
        // int idx = selectConference->findText(Conference::getById(Conference::activeConference()).title());
        // selectConference->setCurrentIndex(idx);
        // connect(selectConference, SIGNAL(currentIndexChanged(int)), SLOT(conferenceChanged(int)));
        // conferenceChanged(idx);
    }
    else
    {
        // TODO: remove GUI
        // conferenceHeader->hide();
        // selectConferenceWidget->hide();
        // // go to the 'conferenceTab', so the user can import the schedule
        // tabWidget->setCurrentIndex(6); // 6 - conference tab
    }
    #endif

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

    connect(mNetworkAccessManager, SIGNAL(finished(QNetworkReply*)), SLOT(networkQueryFinished(QNetworkReply*)));

    connect(mXmlParser, SIGNAL(parsingScheduleBegin()), conferenceModel, SLOT(newConferenceBegin()));
    connect(mXmlParser, SIGNAL(parsingScheduleEnd(const QString&)), conferenceModel, SLOT(newConferenceEnd(const QString&)));
}

void MainWindow::scheduleImported(int aConfId)
{
    Q_UNUSED(aConfId);

    // TODO: this all goes to ConferenceEditor and model of conferences
    #if 0

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

        selectConferenceWidget->show();

        conferenceChanged(idx);
    }
    #endif
}

void MainWindow::scheduleDeleted(const QString& title)
{
    Q_UNUSED(title);
    // TODO: this all goes to ConferenceEditor and model of conferences
    #if 0
    int idx = selectConference->findText(title);

    if (idx == -1) {
        // should not happen
        qWarning() << __PRETTY_FUNCTION__ << "removed non-existent item:" << title;
        // this happens when you remove the only conference (the list is not ptoperly inited in this case)
        // now make sure that conferencet
        if (selectConference->count() > 0) {
            selectConference->setCurrentIndex(0);
            conferenceChanged(0);
        } else {
            conferenceChanged(-1);
        }
    } else {
        // will it signal "changed"?
        selectConference->removeItem(idx);
    }
    #endif
}

void MainWindow::aboutApp()
{
    QDialog dialog(this);
    Ui::AboutDialog ui;
    ui.setupUi(&dialog);
#ifdef N810
    dialog.setFixedWidth(width());
#endif
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

void MainWindow::useConference(int id)
{
    try {
        Conference::getById(Conference::activeConference()).update("active",0);
        Conference::getById(id).update("active",1);

        initTabs();
    } catch (OrmException& e) {
        // cannon set an active conference
        unsetConference();
        return;
    }

}

void MainWindow::initTabs()
{
    int confId = Conference::activeConference();
    Conference active = Conference::getById(confId);
    QDate startDate = active.start();
    QDate endDate = active.end();
    setWindowTitle(active.title());

    // 'dayNavigator' emits signal 'dateChanged' after setting valid START:END dates
    dayTabContainer->setDates(startDate, endDate);
    tracksTabContainer->setDates(startDate, endDate);
    roomsTabContainer->setDates(startDate, endDate);
    favsTabContainer->setDates(startDate, endDate);
    searchTabContainer->setDates(startDate, endDate);
    searchTabContainer->searchAgainClicked();
    nowTabContainer->updateTreeView(QDate::currentDate());
}

void MainWindow::unsetConference()
{
    dayTabContainer->clearModel();
    tracksTabContainer->clearModel();
    roomsTabContainer->clearModel();
    favsTabContainer->clearModel();
    searchTabContainer->clearModel();
    searchTabContainer->searchAgainClicked();
    nowTabContainer->clearModel();

    // TODO:  remove
    // conferenceHeader->hide();
    setWindowTitle(saved_title);
}

void MainWindow::setup()
{
    SettingsDialog dialog;
    dialog.exec();

    qDebug() << "Setting-up proxy: " << AppSettings::proxyAddress() << ":" << AppSettings::proxyPort();
    QNetworkProxy proxy(
            AppSettings::isDirectConnection() ? QNetworkProxy::NoProxy : QNetworkProxy::HttpProxy,
            AppSettings::proxyAddress(),
            AppSettings::proxyPort(),
            PROXY_USERNAME,
            PROXY_PASSWD);
    QNetworkProxy::setApplicationProxy(proxy);
}

/** Create and run ConferenceEditor dialog, making required connections for it.

This method manages, which classes actually perform changes in conference list.

There are several classes that modify the conferences:
this:
 deletion and URL update.
this, mXmlParser and mNetworkAccessManager:
 addition and refresh.
*/
void MainWindow::showConferences()
{
    ConferenceEditor dialog(conferenceModel, this);

    // TODO: connect signals about progress of network and parsing

    connect(&dialog, SIGNAL(haveConferenceUrl(const QString&)), SLOT(importFromNetwork(const QString&)));
    connect(&dialog, SIGNAL(haveConferenceFile(const QString&)), SLOT(importFromFile(const QString&)));
    connect(&dialog, SIGNAL(removeConferenceRequested(int)), SLOT(removeConference(int)));
    connect(&dialog, SIGNAL(changeUrlRequested(int, const QString&)),
                    SLOT(changeConferenceUrl(int, const QString&)));

    connect(&dialog, SIGNAL(haveConferenceSelected(int)), SLOT(useConference(int)));
    connect(&dialog, SIGNAL(noneConferenceSelected()), SLOT(unsetConference()));

    connect(mXmlParser, SIGNAL(parsingScheduleBegin()), &dialog, SLOT(importStarted()));
    connect(mXmlParser, SIGNAL(progressStatus(int)), &dialog, SLOT(showParsingProgress(int)));
    connect(mXmlParser, SIGNAL(parsingScheduleEnd(const QString&)), &dialog, SLOT(importFinished(const QString&)));

    connect(this, SIGNAL(conferenceRemoved()), &dialog, SLOT(conferenceRemoved()));

    dialog.exec();
}

void MainWindow::networkQueryFinished(QNetworkReply *aReply)
{
    if ( aReply->error() != QNetworkReply::NoError )
    {
        error_message(QString("Error occured during download: ") + aReply->errorString());
    }
    else
    {
        qDebug() << __PRETTY_FUNCTION__ << ": have data";
        importData(aReply->readAll(), aReply->url().toEncoded());
    }
}

void MainWindow::importData(const QByteArray &aData, const QString& url)
{
    // TODO: remove GUI
    // instead send signals to the child dialog
    #if 0
    browse->hide();
    online->hide();
    progressBar->show();
    // proxySettings->hide();
    #endif

    int confId = mXmlParser->parseData(aData, url);

    #if 0
    progressBar->hide();
    browse->show();
    online->show();
    // proxySettings->show();
    importScheduleLabel->setText("Schedule:");

    #endif
    if (confId > 0) {
        emit(scheduleImported(confId));
    }
}

void MainWindow::importFromNetwork(const QString& url)
{
    qDebug() << __PRETTY_FUNCTION__;
    QNetworkRequest request;
    request.setUrl(QUrl(url));

    mNetworkAccessManager->setProxy(QNetworkProxy::applicationProxy());
    mNetworkAccessManager->get(request);
}

void MainWindow::importFromFile(const QString& filename)
{
    qDebug() << __PRETTY_FUNCTION__;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {    
        static const QString format("Cannot read \"%1\": error %2");
        error_message(format.arg(filename, QString::number(file.error())));
    }

    importData(file.readAll(), "");
}

void MainWindow::removeConference(int id)
{
    Conference::deleteConference(id);
    conferenceModel->conferenceRemoved();

    emit conferenceRemoved();
}

void MainWindow::changeConferenceUrl(int id, const QString& url)
{
    Conference::getById(id).setUrl(url);
}

