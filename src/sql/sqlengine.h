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
#ifndef SQLENGINE_H
#define SQLENGINE_H

#include <QObject>
#include <QHash>

class QSqlDatabase;

class SqlEngine : public QObject
{
    Q_OBJECT
    public:
        SqlEngine(QObject *aParent = NULL);
        ~SqlEngine();
        static void initialize();
        static void addConferenceToDB(QHash<QString,QString> &aConference);
        static void addEventToDB(QHash<QString,QString> &aEvent);
        static void addPersonToDB(QHash<QString,QString> &aPerson);
        static void addLinkToDB(QHash<QString,QString> &aLink);
        static void addRoomToDB(QHash<QString,QString> &aRoom);
        static void deleteConference(int id);

        static bool beginTransaction();
        static bool commitTransaction();

        // search Events for ....
        static int searchEvent(int conferenceId, const QHash<QString,QString> &columns, const QString &keyword);
    private:
        static QString login(const QString &aDatabaseType, const QString &aDatabaseName);
        static bool execQuery(QSqlDatabase &aDatabase, const QString &aQuery);
        static bool execQueryWithParameter(QSqlDatabase &aDatabase, const QString &aQuery, const QHash<QString, QVariant>& params);

        static void checkConferenceMap(QSqlDatabase &aDatabase);
};

#endif /* SQLENGINE_H */

