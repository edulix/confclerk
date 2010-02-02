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
#include "proxysettingsdialog.h"

#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QNetworkProxy>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <appsettings.h>

const QString SCHEDULE_URL = "http://fosdem.org/2010/schedule/xml";

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
    importAction->hide();
    connect(online, SIGNAL(clicked()), SLOT(downloadSchedule()));

    connect(proxySettings, SIGNAL(clicked()), SLOT(setupProxy()));
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

        importData(file.readAll());

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
        importData(aReply->readAll());
    }
}

void ImportScheduleWidget::downloadSchedule()
{
    QNetworkRequest request;
    request.setUrl(QUrl(SCHEDULE_URL));
    mNetworkAccessManager->get(request);
}

void ImportScheduleWidget::importData(const QByteArray &aData)
{
    browse->hide();
    online->hide();
    progressBar->show();
    proxySettings->hide();

    int confId = mXmlParser->parseData(aData);

    progressBar->hide();
    browse->show();
    online->show();
    proxySettings->show();
    importScheduleLabel->setText("Import schedule: ");

    emit(scheduleImported(confId));
}

void ImportScheduleWidget::setupProxy()
{
    ProxySettingsDialog dialog;
    dialog.exec();

    qDebug() << "Setting-up proxy: " << AppSettings::proxyAddress() << ":" << AppSettings::proxyPort();
    QNetworkProxy proxy(
            AppSettings::isDirectConnection() ? QNetworkProxy::NoProxy : QNetworkProxy::HttpProxy,
            AppSettings::proxyAddress(),
            AppSettings::proxyPort(),
            PROXY_USERNAME,
            PROXY_PASSWD);
    QNetworkProxy::setApplicationProxy(proxy);

    mNetworkAccessManager->setProxy(QNetworkProxy::applicationProxy());
}

