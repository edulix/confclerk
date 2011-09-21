/*
 * Copyright (C) 2010 Ixonos Plc.
 * Copyright (C) 2011 Philipp Spitzer, gregor herrmann
 *
 * This file is part of ConfClerk.
 *
 * ConfClerk is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 2 of the License, or (at your option)
 * any later version.
 *
 * ConfClerk is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * ConfClerk.  If not, see <http://www.gnu.org/licenses/>.
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

    /*
    if(AppSettings::isDirectConnection())
    {
        qDebug() << "Setting-up proxy: " << AppSettings::proxyAddress() << ":" << AppSettings::proxyPort();
    }
    */
    QNetworkProxy proxy(
            AppSettings::isDirectConnection() ? QNetworkProxy::NoProxy : QNetworkProxy::HttpProxy,
            AppSettings::proxyAddress(),
            AppSettings::proxyPort(),
            PROXY_USERNAME,
            PROXY_PASSWD);
    QNetworkProxy::setApplicationProxy(proxy);

    // event details have changed
    connect(dayTabContainer, SIGNAL(eventHasChanged(int,bool)), SLOT(eventHasChanged(int,bool)));
    connect(favsTabContainer, SIGNAL(eventHasChanged(int,bool)), SLOT(eventHasChanged(int,bool)));
    connect(tracksTabContainer, SIGNAL(eventHasChanged(int,bool)), SLOT(eventHasChanged(int,bool)));
    connect(roomsTabContainer, SIGNAL(eventHasChanged(int,bool)), SLOT(eventHasChanged(int,bool)));
    connect(nowTabContainer, SIGNAL(eventHasChanged(int,bool)), SLOT(eventHasChanged(int,bool)));
    connect(searchTabContainer, SIGNAL(eventHasChanged(int,bool)), SLOT(eventHasChanged(int,bool)));

    // date has changed
    connect(dayNavigator, SIGNAL(dateChanged(QDate)), dayTabContainer, SLOT(setCurDate(QDate)));
    connect(dayNavigator, SIGNAL(dateChanged(QDate)), favsTabContainer, SLOT(setCurDate(QDate)));
    connect(dayNavigator, SIGNAL(dateChanged(QDate)), tracksTabContainer, SLOT(setCurDate(QDate)));
    connect(dayNavigator, SIGNAL(dateChanged(QDate)), roomsTabContainer, SLOT(setCurDate(QDate)));
    connect(dayNavigator, SIGNAL(dateChanged(QDate)), nowTabContainer, SLOT(setCurDate(QDate)));
    connect(dayNavigator, SIGNAL(dateChanged(QDate)), searchTabContainer, SLOT(setCurDate(QDate)));

    connect(aboutAction, SIGNAL(triggered()), SLOT(aboutApp()));
    connect(settingsAction, SIGNAL(triggered()), SLOT(setup()));
    connect(conferencesAction, SIGNAL(triggered()), SLOT(showConferences()));

    useConference(Conference::activeConference());
    // optimization, see useConference() code
    try {
        initTabs();
    } catch (const OrmException& e) {
        qDebug() << "OrmException:" << e.text();
        clearTabs();
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

    connect(mNetworkAccessManager, SIGNAL(finished(QNetworkReply*)), SLOT(networkQueryFinished(QNetworkReply*)));

    connect(mXmlParser, SIGNAL(parsingScheduleBegin()), conferenceModel, SLOT(newConferenceBegin()));
    connect(mXmlParser, SIGNAL(parsingScheduleEnd(const QString&)), conferenceModel, SLOT(newConferenceEnd(const QString&)));
}

void MainWindow::aboutApp()
{
    QDialog dialog(this);
    Ui::AboutDialog ui;
    ui.setupUi(&dialog);
    ui.labDescription->setText(ui.labDescription->text().arg(qApp->applicationVersion()));
#ifdef N810
    dialog.setFixedWidth(width());
#endif
    dialog.exec();
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
    if (id == -1)  // in case no conference is active
    {
        unsetConference();
        return;
    }
    try {
        Conference::getById(Conference::activeConference()).update("active",0);
        Conference new_active = Conference::getById(id);
        new_active.update("active",1);

        // looks like it does not work at n900
        setWindowTitle(new_active.title());

        // optimization.
        // dont run initTabs() here
        // it takes much CPU, making travelling between conferences in ConferenceEditor longer
        // and is not seen in maemo WM anyway
        // instead run it explicitly
        // 1. at startup
        // 2. when ConferenceEditor finished
        // dont forget to protect the calls by try-catch!

        // just in case, clear conference selection instead
        clearTabs();

        // end of optimization
        // initTabs();
    } catch (OrmException& e) {
        // cannon set an active conference
        unsetConference();   // TODO: as no active conference is now correctly managed this should be handled as a fatal error
        return;
    }

}

void MainWindow::initTabs()
{
    int confId = Conference::activeConference();
    if (confId != -1)   // only init tabs if a conference is active
    {
        Conference active = Conference::getById(confId);
        QDate startDate = active.start();
        QDate endDate = active.end();

        // 'dayNavigator' emits signal 'dateChanged' after setting valid START:END dates
        dayTabContainer->setDates(startDate, endDate);
        tracksTabContainer->setDates(startDate, endDate);
        roomsTabContainer->setDates(startDate, endDate);
        favsTabContainer->setDates(startDate, endDate);
        searchTabContainer->setDates(startDate, endDate);
        searchTabContainer->searchAgainClicked();
        nowTabContainer->updateTreeView(QDate::currentDate());
        dayNavigator->setDates(startDate, endDate);
    }
}

void MainWindow::clearTabs()
{
    dayTabContainer->clearModel();
    tracksTabContainer->clearModel();
    roomsTabContainer->clearModel();
    favsTabContainer->clearModel();
    searchTabContainer->clearModel();
    searchTabContainer->searchAgainClicked();
    nowTabContainer->clearModel();
}

void MainWindow::unsetConference()
{
    clearTabs();
    dayNavigator->unsetDates();
    setWindowTitle(saved_title);
}

void MainWindow::setup()
{
    SettingsDialog dialog;
    dialog.loadDialogData();
    if (dialog.exec() == QDialog::Accepted) {
        dialog.saveDialogData();
        QNetworkProxy proxy(
                AppSettings::isDirectConnection() ? QNetworkProxy::NoProxy : QNetworkProxy::HttpProxy,
                AppSettings::proxyAddress(),
                AppSettings::proxyPort(),
                PROXY_USERNAME,
                PROXY_PASSWD);
        QNetworkProxy::setApplicationProxy(proxy);
    }
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

    // optimization, see useConference() code
    try {
        initTabs();
    } catch (OrmException) {
        clearTabs();
    }
}

void MainWindow::networkQueryFinished(QNetworkReply *aReply)
{
    if ( aReply->error() != QNetworkReply::NoError )
    {
        error_message(QString("Error occured during download: ") + aReply->errorString());
    }
    else
    {
        importData(aReply->readAll(), aReply->url().toEncoded());
    }
}

void MainWindow::importData(const QByteArray &aData, const QString& url)
{
    mXmlParser->parseData(aData, url);
}

void MainWindow::importFromNetwork(const QString& url)
{
    QNetworkRequest request;
    request.setUrl(QUrl(url));

    mNetworkAccessManager->setProxy(QNetworkProxy::applicationProxy());
    mNetworkAccessManager->get(request);
}

void MainWindow::importFromFile(const QString& filename)
{
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

