/*
 * Copyright (C) 2010 Ixonos Plc.
 * Copyright (C) 2011-2012 Philipp Spitzer, gregor herrmann, Stefan Stahl
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

#include "sqlengine.h"

#include "track.h"
#include "eventmodel.h"
#include "delegate.h"

#include "conference.h"

#include <QDialog>
#include <QMessageBox>

#include "ui_about.h"
#include "eventdialog.h"
#include "daynavigatorwidget.h"
#include "settingsdialog.h"
#include "conferenceeditor.h"
#include "schedulexmlparser.h"
#include "errormessage.h"

#include "tabcontainer.h"
#include "appsettings.h"

const QString PROXY_USERNAME;
const QString PROXY_PASSWD;

MainWindow::MainWindow(int aEventId, QWidget *aParent): QMainWindow(aParent) {
    setupUi(this);

    // Open database
    sqlEngine = new SqlEngine(this);
    searchTabContainer->setSqlEngine(sqlEngine);
    connect(sqlEngine, SIGNAL(dbError(QString)), this, SLOT(showError(QString)));
    sqlEngine->open();
    sqlEngine->createOrUpdateDbSchema();

    conferenceModel = new ConferenceModel(this);
    mXmlParser = new ScheduleXmlParser(sqlEngine, this);
    mNetworkAccessManager = new QNetworkAccessManager(this);

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
    connect(dayTabContainer, SIGNAL(eventChanged(int,bool)), SLOT(onEventChanged(int,bool)));
    connect(favsTabContainer, SIGNAL(eventChanged(int,bool)), SLOT(onEventChanged(int,bool)));
    connect(tracksTabContainer, SIGNAL(eventChanged(int,bool)), SLOT(onEventChanged(int,bool)));
    connect(roomsTabContainer, SIGNAL(eventChanged(int,bool)), SLOT(onEventChanged(int,bool)));
    connect(searchTabContainer, SIGNAL(eventChanged(int,bool)), SLOT(onEventChanged(int,bool)));

    // date has changed
    connect(dayNavigator, SIGNAL(dateChanged(QDate)), dayTabContainer, SLOT(redisplayDate(QDate)));
    connect(dayNavigator, SIGNAL(dateChanged(QDate)), favsTabContainer, SLOT(redisplayDate(QDate)));
    connect(dayNavigator, SIGNAL(dateChanged(QDate)), tracksTabContainer, SLOT(redisplayDate(QDate)));
    connect(dayNavigator, SIGNAL(dateChanged(QDate)), roomsTabContainer, SLOT(redisplayDate(QDate)));
    connect(dayNavigator, SIGNAL(dateChanged(QDate)), searchTabContainer, SLOT(redisplayDate(QDate)));

    // search result has changed
    connect(searchTabContainer, SIGNAL(searchResultChanged()), SLOT(onSearchResultChanged()));


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
    connect(mXmlParser, SIGNAL(parsingScheduleEnd(int)), conferenceModel, SLOT(newConferenceEnd(int)));
}

void MainWindow::on_aboutAction_triggered()
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


void MainWindow::on_reloadAction_triggered() {
    int confId = Conference::activeConference();
    if (confId== -1) return;
    Conference active = Conference::getById(confId);
    if (active.url().isEmpty()) return;
    importFromNetwork(active.url(), confId);
    setEnabled(false);
}


void MainWindow::on_nowAction_triggered() {
    int confId = Conference::activeConference();
    if (confId== -1) return;
    dayNavigator->setCurDate(QDate::currentDate());
    dayTabContainer->expandTimeGroup(QTime::currentTime(), confId);
}


void MainWindow::on_searchAction_triggered() {
    if (tabWidget->currentWidget() == searchTab)
        searchTabContainer->showSearchDialog(!searchTabContainer->searchDialogIsVisible());
    else {
        tabWidget->setCurrentWidget(searchTab);
        searchTabContainer->showSearchDialog();
    }
}


void MainWindow::on_expandAllAction_triggered() {
    if (tabWidget->currentWidget() == favouritesTab) favsTabContainer->treeView->expandAll();
    if (tabWidget->currentWidget() == dayViewTab) dayTabContainer->treeView->expandAll();
    if (tabWidget->currentWidget() == tracksTab) tracksTabContainer->treeView->expandAll();
    if (tabWidget->currentWidget() == roomsTab) roomsTabContainer->treeView->expandAll();
    if (tabWidget->currentWidget() == searchTab) searchTabContainer->treeView->expandAll();
}


void MainWindow::on_collapseAllAction_triggered() {
    if (tabWidget->currentWidget() == favouritesTab) favsTabContainer->treeView->collapseAll();
    if (tabWidget->currentWidget() == dayViewTab) dayTabContainer->treeView->collapseAll();
    if (tabWidget->currentWidget() == tracksTab) tracksTabContainer->treeView->collapseAll();
    if (tabWidget->currentWidget() == roomsTab) roomsTabContainer->treeView->collapseAll();
    if (tabWidget->currentWidget() == searchTab) searchTabContainer->treeView->collapseAll();
}


void MainWindow::onEventChanged(int aEventId, bool favouriteChanged) {
    dayTabContainer->redisplayEvent(aEventId);
    if (favouriteChanged) favsTabContainer->redisplayDate(dayNavigator->curDate());
    else favsTabContainer->redisplayEvent(aEventId);
    tracksTabContainer->redisplayEvent(aEventId);
    roomsTabContainer->redisplayEvent(aEventId);
    searchTabContainer->redisplayEvent(aEventId);
}


void MainWindow::onSearchResultChanged() {
    // Are results found on the current date?
    QDate date = dayNavigator->curDate();
    int count = searchTabContainer->searchResultCount(date);
    if (count > 0) {searchTabContainer->redisplayDate(date); return;}

    // Are results found in the future?
    for (date = date.addDays(1); date <= dayNavigator->endDate(); date = date.addDays(1)) {
        int count = searchTabContainer->searchResultCount(date);
        if (count > 0) {dayNavigator->setCurDate(date); return;}
    }

    // Are results found in the past?
    for (date = dayNavigator->startDate(); date < dayNavigator->curDate(); date = date.addDays(1)) {
        int count = searchTabContainer->searchResultCount(date);
        if (count > 0) {dayNavigator->setCurDate(date); return;}
    }
    // No results were found
    searchTabContainer->redisplayDate(dayNavigator->curDate());
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
}

void MainWindow::unsetConference()
{
    clearTabs();
    dayNavigator->unsetDates();
    setWindowTitle(saved_title);
}


void MainWindow::showError(const QString& message) {
    error_message(message);
}


void MainWindow::on_settingsAction_triggered()
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
void MainWindow::on_conferencesAction_triggered()
{
    ConferenceEditor dialog(conferenceModel, this);

    connect(&dialog, SIGNAL(haveConferenceUrl(const QString&, int)), SLOT(importFromNetwork(const QString&, int)));
    connect(&dialog, SIGNAL(haveConferenceFile(const QString&, int)), SLOT(importFromFile(const QString&, int)));
    connect(&dialog, SIGNAL(removeConferenceRequested(int)), SLOT(removeConference(int)));
    connect(&dialog, SIGNAL(changeUrlRequested(int, const QString&)),
                    SLOT(changeConferenceUrl(int, const QString&)));

    connect(&dialog, SIGNAL(haveConferenceSelected(int)), SLOT(useConference(int)));
    connect(&dialog, SIGNAL(noneConferenceSelected()), SLOT(unsetConference()));

    connect(mXmlParser, SIGNAL(parsingScheduleBegin()), &dialog, SLOT(importStarted()));
    connect(mXmlParser, SIGNAL(progressStatus(int)), &dialog, SLOT(showParsingProgress(int)));
    connect(mXmlParser, SIGNAL(parsingScheduleEnd(int)), &dialog, SLOT(importFinished(int)));

    connect(this, SIGNAL(conferenceRemoved()), &dialog, SLOT(conferenceRemoved()));

    dialog.exec();

    // optimization, see useConference() code
    try {
        initTabs();
    } catch (OrmException) {
        clearTabs();
    }
}

void MainWindow::networkQueryFinished(QNetworkReply *aReply) {
    if (aReply->error() != QNetworkReply::NoError) {
        error_message(QString("Error occured during download: ") + aReply->errorString());
    } else {
        QUrl redirectUrl = aReply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
        if (!redirectUrl.isEmpty()) {
            if (redirectUrl != aReply->request().url()) {
                importFromNetwork(redirectUrl.toString(), aReply->request().attribute(QNetworkRequest::User).toInt());
                return; // don't enable controls
            } else {
                error_message(QString("Error: Cyclic redirection from %1 to itself.").arg(redirectUrl.toString()));
            }
        } else {
            importData(aReply->readAll(), aReply->url().toEncoded(), aReply->request().attribute(QNetworkRequest::User).toInt());
        }
    }
    setEnabled(true);
}

void MainWindow::importData(const QByteArray &aData, const QString& url, int conferenceId)
{
    mXmlParser->parseData(aData, url, conferenceId);
}

void MainWindow::importFromNetwork(const QString& url, int conferenceId)
{
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setAttribute(QNetworkRequest::User, conferenceId);

    mNetworkAccessManager->setProxy(QNetworkProxy::applicationProxy());
    mNetworkAccessManager->get(request);
}

void MainWindow::importFromFile(const QString& filename, int conferenceId)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {    
        static const QString format("Cannot read \"%1\": error %2");
        error_message(format.arg(filename, QString::number(file.error())));
    }

    importData(file.readAll(), "", conferenceId);
}


void MainWindow::removeConference(int id) {
    sqlEngine->deleteConference(id);
    conferenceModel->conferenceRemoved();
    emit conferenceRemoved();
}


void MainWindow::changeConferenceUrl(int id, const QString& url) {
    Conference::getById(id).setUrl(url);
}

