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

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDateTime>

#include <QDir>
#include <QDesktopServices>
#include "sqlengine.h"
#include "track.h"
#include "conference.h"

#include <QDebug>

const QString DATE_FORMAT ("yyyy-MM-dd");
const QString TIME_FORMAT ("hh:mm");

SqlEngine::SqlEngine(QObject *aParent): QObject(aParent) {
    QDir dbPath(QDesktopServices::storageLocation(QDesktopServices::DataLocation));
    dbFilename = dbPath.absoluteFilePath("ConfClerk.sqlite");
}


SqlEngine::~SqlEngine() {
}


void SqlEngine::open() {
    // we may have to create the directory of the database
    QFileInfo dbFilenameInfo(dbFilename);
    QDir cwd;
    cwd.mkpath(dbFilenameInfo.absolutePath());
    // We don't have to handle errors because in worst case, opening the database will fail
    // and db.isOpen() returns false.
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbFilename);
    db.open();
}


int SqlEngine::dbSchemaVersion() {
    QSqlQuery query(db);
    if (!query.exec("PRAGMA user_version")) {
        emitSqlQueryError(query);
        return -2;
    }
    query.first();
    int version = query.value(0).toInt();
    if (version == 0) {
        // check whether the tables are existing
        if (!query.exec("select count(*) from sqlite_master where name='CONFERENCE'")) {
            emitSqlQueryError(query);
            return -2;
        }
        query.first();
        if (query.value(0).toInt() == 1) return 0; // tables are existing
        return -1; // database seems to be empty (or has other tables)
    }
    return version;
}


bool SqlEngine::updateDbSchemaVersion000To001() {
    emit dbError("Upgrade 0 -> 1 not implemented yet");
    return false;
}


bool SqlEngine::createCurrentDbSchema() {
    QFile file(":/dbschema001.sql");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString allSqlStatements = file.readAll();
    QSqlQuery query(db);
    foreach(QString sql, allSqlStatements.split(";")) {
        if (sql.trimmed().isEmpty())  // do not execute empty queries like the last character from create_tables.sql
            continue;
        if (!query.exec(sql)) {
            emitSqlQueryError(query);
            return false;
        }
    }
    return true;
}


bool SqlEngine::createOrUpdateDbSchema() {
    int version = dbSchemaVersion();
    switch (version) {
    case -2:
        // the error has already been emitted by the previous function
        return false;
    case -1:
        // empty database
        return createCurrentDbSchema();
    case 0:
        // db schema version 0
        return updateDbSchemaVersion000To001();
    case 1:
        // current schema
        return true;
    default:
        // unsupported schema
        emit dbError(tr("Unsupported database schema version %1.").arg(version));
    }
    return false;
}


void SqlEngine::addConferenceToDB(QHash<QString,QString> &aConference, int conferenceId) {
    QSqlQuery query(db);
    if (conferenceId <= 0) // insert conference
    {
        query.prepare("INSERT INTO CONFERENCE (title,url,subtitle,venue,city,start,end,"
                                                "day_change,timeslot_duration,active) "
                        " VALUES (:title,:url,:subtitle,:venue,:city,:start,:end,"
                                                ":day_change,:timeslot_duration,:active)");
        foreach (QString prop_name, (QList<QString>() << "title" << "url" << "subtitle" << "venue" << "city")) {
            query.bindValue(QString(":") + prop_name, aConference[prop_name]);
        }
        query.bindValue(":start", QDateTime(QDate::fromString(aConference["start"],DATE_FORMAT),QTime(0,0),Qt::UTC).toTime_t());
        query.bindValue(":end", QDateTime(QDate::fromString(aConference["end"],DATE_FORMAT),QTime(0,0),Qt::UTC).toTime_t());
        query.bindValue(":day_change", -QTime::fromString(aConference["day_change"],TIME_FORMAT).secsTo(QTime(0,0)));
        query.bindValue(":timeslot_duration", -QTime::fromString(aConference["timeslot_duration"],TIME_FORMAT).secsTo(QTime(0,0)));
        query.bindValue(":active", 1);
        emitSqlQueryError(query);
        aConference["id"] = query.lastInsertId().toString(); // 'id' is assigned automatically
    }
    else // update conference
    {
        query.prepare("UPDATE CONFERENCE set title=:title, url=:url, subtitle=:subtitle, venue=:venue, city=:city, start=:start, end=:end,"
                                            "day_change=:day_change, timeslot_duration=:timeslot_duration, active=:active "
                      "WHERE id=:id");
        foreach (QString prop_name, (QList<QString>() << "title" << "url" << "subtitle" << "venue" << "city")) {
            query.bindValue(QString(":") + prop_name, aConference[prop_name]);
        }
        query.bindValue(":start", QDateTime(QDate::fromString(aConference["start"],DATE_FORMAT),QTime(0,0),Qt::UTC).toTime_t());
        query.bindValue(":end", QDateTime(QDate::fromString(aConference["end"],DATE_FORMAT),QTime(0,0),Qt::UTC).toTime_t());
        query.bindValue(":day_change", -QTime::fromString(aConference["day_change"],TIME_FORMAT).secsTo(QTime(0,0)));
        query.bindValue(":timeslot_duration", -QTime::fromString(aConference["timeslot_duration"],TIME_FORMAT).secsTo(QTime(0,0)));
        query.bindValue(":active", 1);
        query.bindValue(":id", conferenceId);
        emitSqlQueryError(query);
        aConference["id"] = conferenceId;
    }
}


void SqlEngine::addEventToDB(QHash<QString,QString> &aEvent) {
    //insert event track to table and get track id
    int conference = aEvent["conference_id"].toInt();
    QString name = aEvent["track"];
    Track track;
    int trackId;
    try
    {
        track = Track::retrieveByName(conference, name);
        trackId = track.id();
    }
    catch (OrmNoObjectException &e) {
        track.setConference(conference);
        track.setName(name);
        trackId = track.insert();
    }
    QDateTime startDateTime;
    startDateTime.setTimeSpec(Qt::UTC);
    startDateTime = QDateTime(QDate::fromString(aEvent["date"],DATE_FORMAT),QTime::fromString(aEvent["start"],TIME_FORMAT),Qt::UTC);

    bool event_exists = false;
    {
        QSqlQuery check_event_query;
        check_event_query.prepare("SELECT * FROM EVENT WHERE xid_conference = :xid_conference AND id = :id");
        check_event_query.bindValue(":xid_conference", aEvent["conference_id"]);
        check_event_query.bindValue(":id", aEvent["id"]);
        if (!check_event_query.exec()) {
            qWarning() << "check event failed, conference id:" << aEvent["xid_conference"]
                    << "event id:" << aEvent["id"]
                    << "error:" << check_event_query.lastError()
                    ;
            return;
        }
        if (check_event_query.isActive() and check_event_query.isSelect() and check_event_query.next()) {
            event_exists = true;
        }
    }

    QSqlQuery result;
    if (event_exists) {
        result.prepare("UPDATE EVENT SET"
                        " start = :start"
                        ", duration = :duration"
                        ", xid_track = :xid_track"
                        ", type = :type"
                        ", language = :language"
                        ", tag = :tag"
                        ", title = :title"
                        ", subtitle = :subtitle"
                        ", abstract = :abstract"
                        ", description = :description"
                            " WHERE id = :id AND xid_conference = :xid_conference");
    } else {
        result.prepare("INSERT INTO EVENT "
                        " (xid_conference, id, start, duration, xid_track, type, "
                            " language, tag, title, subtitle, abstract, description) "
                        " VALUES (:xid_conference, :id, :start, :duration, :xid_track, :type, "
                            ":language, :tag, :title, :subtitle, :abstract, :description)");
    }
    result.bindValue(":xid_conference", aEvent["conference_id"]);
    result.bindValue(":start", QString::number(startDateTime.toTime_t()));
    result.bindValue(":duration", -QTime::fromString(aEvent["duration"],TIME_FORMAT).secsTo(QTime(0,0)));
    result.bindValue(":xid_track", trackId);
    static const QList<QString> props = QList<QString>()
        << "id" << "type" << "language" << "tag" << "title" << "subtitle" << "abstract" << "description";
    foreach (QString prop_name, props) {
        result.bindValue(QString(":") + prop_name, aEvent[prop_name]);
    }
    if (!result.exec()) {
        qWarning() << "event insert/update failed:" << result.lastError();
    }
}


void SqlEngine::addPersonToDB(QHash<QString,QString> &aPerson) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO PERSON (xid_conference,id,name) VALUES (:xid_conference, :id, :name)");
    query.bindValue(":xid_conference", aPerson["conference_id"]);
    query.bindValue(":id", aPerson["id"]);
    query.bindValue(":name", aPerson["name"]);
    query.exec(); // TODO some queries fail due to the unique key constraint
    // if (!query.exec()) qDebug() << "SQL query 'insert into person' failed: " << query.lastError();

    query = QSqlQuery(db);
    query.prepare("INSERT INTO EVENT_PERSON (xid_conference,xid_event,xid_person) VALUES (:xid_conference, :xid_event, :xid_person)");
    query.bindValue(":xid_conference", aPerson["conference_id"]);
    query.bindValue(":xid_event", aPerson["event_id"]);
    query.bindValue(":xid_person", aPerson["id"]);
    query.exec(); // TODO some queries fail due to the unique key constraint
    // if (!query.exec()) qDebug() << "SQL query 'insert into event_person' failed: " << query.lastError();
}


void SqlEngine::addRoomToDB(QHash<QString,QString> &aRoom) {
    QSqlQuery query(db);
    query.prepare("SELECT id FROM ROOM WHERE xid_conference=:conference_id and name=:name");
    query.bindValue(":conference_id", aRoom["conference_id"]);
    query.bindValue(":name", aRoom["name"]);
    emitSqlQueryError(query);
    // now we have to check whether ROOM record with 'name' exists or not,
    // - if it doesn't exist yet, then we have to add that record to 'ROOM' table
    //   and assign autoincremented 'id' to aRoom
    // - if it exists, then we need to get its 'id' and assign it to aRoom
    aRoom["id"] = "";
    if(query.next()) // ROOM record with 'name' already exists: we need to get its 'id'
    {
        aRoom["id"] = query.value(0).toString();
    }
    else // ROOM record doesn't exist yet, need to create it
    {
        query = QSqlQuery(db);
        query.prepare("INSERT INTO ROOM (xid_conference,name) VALUES (:xid_conference, :name)");
        query.bindValue(":xid_conference", aRoom["conference_id"]);
        query.bindValue(":xid_name", aRoom["name"]);
        emitSqlQueryError(query);
        aRoom["id"]= query.lastInsertId().toString(); // 'id' is assigned automatically
        //LOG_AUTOTEST(query);
    }

    // remove previous conference/room records; room names might have changed
    query = QSqlQuery(db);
    query.prepare("DELETE FROM EVENT_ROOM WHERE xid_conference=:conference_id AND xid_event=:event_id");
    query.bindValue(":conference_id", aRoom["conference_id"]);
    query.bindValue(":event_id", aRoom["event_id"]);
    emitSqlQueryError(query);
    // and insert new ones
    query = QSqlQuery(db);
    query.prepare("INSERT INTO EVENT_ROOM (xid_conference,xid_event,xid_room) VALUES (:conference_id, :event_id, :room_id)");
    query.bindValue(":conference_id", aRoom["conference_id"]);
    query.bindValue(":event_id", aRoom["event_id"]);
    query.bindValue(":room_id", aRoom["id"]);
    emitSqlQueryError(query);
}


void SqlEngine::addLinkToDB(QHash<QString,QString> &aLink) {
    //TODO: check if the link doesn't exist before inserting
    QSqlQuery query(db);
    query.prepare("INSERT INTO LINK (xid_event, xid_conference, name, url) VALUES (:xid_event, :xid_conference, :name, :url)");
    query.bindValue(":xid_event", aLink["event_id"]);
    query.bindValue(":xid_conference", aLink["conference_id"]);
    query.bindValue(":name", aLink["name"]);
    query.bindValue(":url", aLink["url"]);
    emitSqlQueryError(query);
}


bool SqlEngine::searchEvent(int aConferenceId, const QHash<QString,QString> &aColumns, const QString &aKeyword) {
    if (aColumns.empty()) return false;

    // DROP
    QSqlQuery query(db);
    query.exec("DROP TABLE IF EXISTS SEARCH_EVENT");
    emitSqlQueryError(query);

    // CREATE
    query.exec("CREATE TEMP TABLE SEARCH_EVENT ( xid_conference INTEGER  NOT NULL, id INTEGER NOT NULL )");
    emitSqlQueryError(query);

    // INSERT
    QString sql = QString("INSERT INTO SEARCH_EVENT ( xid_conference, id ) "
                "SELECT DISTINCT EVENT.xid_conference, EVENT.id FROM EVENT ");
    if( aColumns.contains("ROOM") ){
        sql += "LEFT JOIN EVENT_ROOM ON ( EVENT.xid_conference = EVENT_ROOM.xid_conference AND EVENT.id = EVENT_ROOM.xid_event ) ";
        sql += "LEFT JOIN ROOM ON ( EVENT_ROOM.xid_room = ROOM.id ) ";
    }
    if( aColumns.contains("PERSON") ){
        sql += "LEFT JOIN EVENT_PERSON ON ( EVENT.xid_conference = EVENT_PERSON.xid_conference AND EVENT.id = EVENT_PERSON.xid_event ) ";
        sql += "LEFT JOIN PERSON ON ( EVENT_PERSON.xid_person = PERSON.id ) ";
    }
    sql += QString("WHERE EVENT.xid_conference = %1 AND (").arg( aConferenceId );

    QStringList searchKeywords = aKeyword.trimmed().split(QRegExp("\\s+"));
    QStringList whereAnd;
    for (int i=0; i < searchKeywords.count(); i++) {
        QStringList whereOr;
        foreach (QString table, aColumns.uniqueKeys()) {
            foreach (QString column, aColumns.values(table)){
                 whereOr.append(QString("%1.%2 LIKE '\%' || :%1%2%3 || '\%'").arg(table).arg(column).arg(i));
            }
        }
        whereAnd.append(whereOr.join(" OR "));
    }
    sql += whereAnd.join(") AND (");
    sql += QString(")");

    query.prepare(sql);
    for (int i = 0; i != searchKeywords.size(); ++i) {
        QString keyword = searchKeywords[i];
        foreach (QString table, aColumns.uniqueKeys()) {
            foreach (QString column, aColumns.values(table)) {
                query.bindValue(QString(":%1%2%3").arg(table).arg(column).arg(i), keyword );
            }
        }
    }

    bool success = query.exec();
    emitSqlQueryError(query);
    return success;
}


bool SqlEngine::beginTransaction() {
    QSqlQuery query(db);
    bool success = query.exec("BEGIN IMMEDIATE TRANSACTION");
    emitSqlQueryError(query);
    return success;
}


bool SqlEngine::commitTransaction() {
    QSqlQuery query(db);
    bool success = query.exec("COMMIT");
    emitSqlQueryError(query);
    return success;
}


bool SqlEngine::deleteConference(int id) {
    QSqlQuery query(db);
    bool success = query.exec("BEGIN IMMEDIATE TRANSACTION");
    emitSqlQueryError(query);

    QStringList sqlList;
    sqlList << "DELETE FROM LINK WHERE xid_conference = ?"
            << "DELETE FROM EVENT_ROOM WHERE xid_conference = ?"
            << "DELETE FROM EVENT_PERSON WHERE xid_conference = ?"
            << "DELETE FROM EVENT WHERE xid_conference = ?"
            << "DELETE FROM ROOM WHERE xid_conference = ?"
            << "DELETE FROM PERSON WHERE xid_conference = ?"
            << "DELETE FROM TRACK WHERE xid_conference = ?"
            << "DELETE FROM CONFERENCE WHERE id = ?";

    foreach (const QString& sql, sqlList) {
        query.prepare(sql);
        query.bindValue(0, id);
        success &= query.exec();
        emitSqlQueryError(query);
    }

    success &= query.exec("COMMIT");
    emitSqlQueryError(query);

    return success;
}


void SqlEngine::emitSqlQueryError(const QSqlQuery &query) {
    QSqlError error = query.lastError();
    if (error.type() == QSqlError::NoError) return;
    emit dbError(error.text());
}

