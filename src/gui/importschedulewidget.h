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
#ifndef IMPORTSCHEDULEWIDGET_H
#define IMPORTSCHEDULEWIDGET_H

#include <QWidget>
#include "ui_importschedulewidget.h"

class ScheduleXmlParser;
class QNetworkAccessManager;
class QNetworkReply;

class ImportScheduleWidget : public QWidget, Ui::ImportScheduleWidget
{
    Q_OBJECT
    public:
        ImportScheduleWidget(QWidget *aParent = NULL);
        ~ImportScheduleWidget();
    private slots:
        void browseSchedule();
        void parsingSchedule(const QString &aTitle);
        void showParsingProgress(int progress);
        void networkQueryFinished(QNetworkReply *aReply);
        void downloadSchedule();
    signals:
        void scheduleImported(int confId);
    private:
        void importData(const QByteArray &aData, const QString& url);
    private:
        ScheduleXmlParser *mXmlParser;
        QNetworkAccessManager *mNetworkAccessManager;
};

#endif /* IMPORTSCHEDULEWIDGET_H */

