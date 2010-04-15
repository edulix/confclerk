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
#include "importschedulewidget.h"

#include <schedulexmlparser.h>

#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QNetworkProxy>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMessageBox>
#include <QDebug>
#include <appsettings.h>

// TODO: this is temporary
#include <QInputDialog>

#include "conference.h"

// const QString SCHEDULE_URL = "http://fosdem.org/2010/schedule/xml";

const QString PROXY_USERNAME;
const QString PROXY_PASSWD;

ImportScheduleWidget::ImportScheduleWidget(QWidget *aParent)
    : QWidget(aParent)
{
    setupUi(this);

    mXmlParser = new ScheduleXmlParser(this);
    connect(mXmlParser, SIGNAL(progressStatus(int)), SLOT(showParsingProgress(int)));
    connect(mXmlParser, SIGNAL(parsingSchedule(const QString &)), SLOT(parsingSchedule(const QString &)));

    connect(browse, SIGNAL(clicked()), SLOT(browseSchedule()));
    progressBar->hide();

    cancel->hide();
    connect(online, SIGNAL(clicked()), SLOT(downloadSchedule()));

    connect(changeUrl, SIGNAL(clicked()), SLOT(on_changeUrl()));
    connect(newConfFromUrl, SIGNAL(clicked()), SLOT(on_newFromUrl()));
    connect(delConf, SIGNAL(clicked()), SLOT(on_delete()));

    mNetworkAccessManager = new QNetworkAccessManager(this);
    connect(mNetworkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(networkQueryFinished(QNetworkReply*)));
    mNetworkAccessManager->setProxy(QNetworkProxy::applicationProxy());
}

ImportScheduleWidget::~ImportScheduleWidget()
{
    if(mXmlParser)
    {
        delete mXmlParser;
        mXmlParser = NULL;
    }
    if(mNetworkAccessManager)
    {
        delete mNetworkAccessManager;
        mNetworkAccessManager = NULL;
    }
}

void ImportScheduleWidget::parsingSchedule(const QString &aTitle)
{
    importScheduleLabel->setText("Importing: " + aTitle);
}

void ImportScheduleWidget::showParsingProgress(int progress)
{
    progressBar->setValue(progress);
}

void ImportScheduleWidget::browseSchedule()
{
    QString scheduleFileName = QFileDialog::getOpenFileName(this, tr("Select Conference Schedule"), QDir::homePath(), tr("Schedule Files (*.xml)"));
    if(QFile::exists(scheduleFileName))
    {
        QFile file(scheduleFileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "can't open " << file.fileName();
            return;
        }

        importData(file.readAll(), QString());

    }
    else
    {
        progressBar->hide();
    }
}

void ImportScheduleWidget::networkQueryFinished(QNetworkReply *aReply)
{
    if ( aReply->error() != QNetworkReply::NoError )
    {
        qDebug() << "Error occured during download: " << aReply->errorString();
    }
    else
    {
        importData(aReply->readAll(), aReply->url().toEncoded());
    }
}

void ImportScheduleWidget::downloadSchedule()
{

    // TODO: make a nicer GUI
    // basically, you have to do the following things:
    // 1. store schedule URL for each conteferce
    // 2. allow refreshing of the current conference schedule with "1 button click"
    // 3. allow changing of the URL for a conference;
    //     run refresh together with it is ok and even justified by usability,
    //     but it must not loose this change if refresh not available.
    //     So it cannot be done as "do like #4 and rely on REPLACE".
    // 4. allow getting the new conference by URL

    // FIXME: it will throw
    // GUI should not show this button if there is no active conf
    importFromNetwork(Conference::getById(Conference::activeConference()).getUrl());
}

void ImportScheduleWidget::on_changeUrl()
{
    // FIXME: it will throw
    // GUI should not show this button if there is no active conf
    Conference active_conference = Conference::getById(Conference::activeConference());
    bool ok = false;
    QString new_url =
        QInputDialog::getText(this, "URL request", "Enter the new URL for conference schedule"
                                , QLineEdit::Normal
                                , active_conference.getUrl()
                                , &ok);
    if (ok) {
        active_conference.setUrl(new_url);
    }
}

void ImportScheduleWidget::on_newFromUrl()
{
    bool ok = false;
    QString url = QInputDialog::getText(this, "URL request", "Put the schedule URL", QLineEdit::Normal, "", &ok);
    if (ok) {
        importFromNetwork(url);
    }

}

void ImportScheduleWidget::on_delete()
{
    int active_id = Conference::activeConference();
    Conference active_conference = Conference::getById(active_id);

    QMessageBox::StandardButton answer = 
        QMessageBox::question(0
            , "Deletion confirmation"
            , QString("Really delete the %1 conference").arg(active_conference.title())
            , QMessageBox::Yes | QMessageBox::No
            , QMessageBox::No);

    if (answer == QMessageBox::Yes) {
        QString title = active_conference.title();
        Conference::deleteConference(active_id);
        emit(scheduleDeleted(title));
    }
}

void ImportScheduleWidget::importFromNetwork(const QString& url)
{
    QNetworkRequest request;
    request.setUrl(QUrl(url));

    mNetworkAccessManager->setProxy(QNetworkProxy::applicationProxy());
    mNetworkAccessManager->get(request);
}

void ImportScheduleWidget::importData(const QByteArray &aData, const QString& url)
{
    browse->hide();
    online->hide();
    progressBar->show();
    // proxySettings->hide();

    int confId = mXmlParser->parseData(aData, url);

    progressBar->hide();
    browse->show();
    online->show();
    // proxySettings->show();
    importScheduleLabel->setText("Schedule:");

    emit(scheduleImported(confId));
}

