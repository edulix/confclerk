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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

#include <ui_mainwindow.h>

#include "conferencemodel.h"

class ScheduleXmlParser;
class QNetworkAccessManager;
class QNetworkReply;

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT
public:
    // aEventId is used to inform widget to automatically open
    // Event dialog for given Event ID
    MainWindow(int aEventId = 0, QWidget *aParent = NULL);
    ~MainWindow() {}
signals:
    void conferenceRemoved();
private slots:
    void aboutApp();
    void eventHasChanged(int aEventId, bool aReloadModel);
    void setup();
    // TODO: remove
    void showConferences();
    void networkQueryFinished(QNetworkReply*);
    void importFromNetwork(const QString&);
    void importFromFile(const QString&);
    void removeConference(int);
    void changeConferenceUrl(int, const QString&);

    void useConference(int id);
    void unsetConference();
private:
    void fillAndShowConferenceHeader();
    void initTabs();
    void clearTabs();
    void importData(const QByteArray &aData, const QString& url);

    QString saved_title;
    ConferenceModel* conferenceModel;
    ScheduleXmlParser *mXmlParser;
    QNetworkAccessManager *mNetworkAccessManager;
};

#endif /* MAINWINDOW_H */

