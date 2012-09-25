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
#ifndef SQLENGINE_H
#define SQLENGINE_H

#include <QObject>
#include <QHash>
#include <QSqlDatabase>


class SqlEngine : public QObject {
    Q_OBJECT
    public:
        QString dbFilename; ///< database filename including path
        QSqlDatabase db; ///< this may be private one day...

        SqlEngine(QObject *aParent = NULL);
        ~SqlEngine();

        // Open/Close
        void open(); ///< emits a database error if failed.
        bool isOpen() const {return db.isOpen();}
        void close() {db.close();}

        // Schema version
        /// returns the "user_version" of the database schema
        /// we return -1 for an empty database
        /// the database has to be open
        /// returns -2 if an error occurs and emits the error message
        int dbSchemaVersion();
        /// called by createOrUpdateDbSchema. Do not use directly. true for success.
        bool updateDbSchemaVersion000To001();
        /// called by createOrUpdateDbSchma. Do not use directly. true for success.
        bool createCurrentDbSchema();
        /// creates the current database schema if an empty database is found,
        /// otherwise updates the schema if an old one is found. true for success.
        bool createOrUpdateDbSchema();
        /// Applies an SQL file
        bool applySqlFile(const QString sqlFile);

        // if a conferneceId != 0 is given, the confernce is updated instead of inserted.
        void addConferenceToDB(QHash<QString,QString> &aConference, int conferenceId);
        void addEventToDB(QHash<QString,QString> &aEvent);
        void addPersonToDB(QHash<QString,QString> &aPerson);
        void addLinkToDB(QHash<QString,QString> &aLink);
        void addRoomToDB(QHash<QString,QString> &aRoom);
        bool deleteConference(int id);

        bool beginTransaction();
        bool commitTransaction();

        /// search Events for .... returns true if success
        bool searchEvent(int conferenceId, const QHash<QString,QString> &columns, const QString &keyword);
    private:
        static QString login(const QString &aDatabaseType, const QString &aDatabaseName);
        /// emits a possible error message as signal. Does nothing if there was not last error
        void emitSqlQueryError(const QSqlQuery& query);

    signals:
        /// emitted when a database errors occur
        void dbError(const QString& message);
};

#endif /* SQLENGINE_H */

