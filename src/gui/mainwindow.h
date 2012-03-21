/*
 * Copyright (C) 2010 Ixonos Plc.
 * Copyright (C) 2011-2012 Philipp Spitzer, gregor herrmann
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
    void on_conferencesAction_triggered();
    void on_settingsAction_triggered();
    void on_aboutAction_triggered();
    void on_reloadAction_triggered();
    void on_nowAction_triggered();
    void on_searchAction_triggered();
    void on_expandAllAction_triggered();
    void on_collapseAllAction_triggered();

    void onEventChanged(int aEventId, bool favouriteChanged);
    void onSearchResultChanged();
    // TODO: remove
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

