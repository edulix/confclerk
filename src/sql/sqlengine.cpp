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

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDateTime>

#include <QDir>
#include <QDesktopServices>
#include "sqlengine.h"
#include <track.h>
#include <conference.h>

#include <QDebug>

const QString DATE_FORMAT ("yyyy-MM-dd");
const QString TIME_FORMAT ("hh:mm");

SqlEngine::SqlEngine(QObject *aParent)
    : QObject(aParent)
{
}

SqlEngine::~SqlEngine()
{
}

QString SqlEngine::login(const QString &aDatabaseType, const QString &aDatabaseName)
{
    QSqlDatabase database = QSqlDatabase::addDatabase(aDatabaseType);
    database.setDatabaseName(aDatabaseName);

    bool result = false;
    if(!QFile::exists(aDatabaseName)) // the DB (tables) doesn't exists, and so we have to create one
    {
        // create Db
        if (!database.open()) qDebug() << "Could not open database" << database.lastError();
        QFile file(":/create_tables.sql");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString allSqlStatements = file.readAll();
        foreach(QString sql, allSqlStatements.split(";")) {
            QSqlQuery query(database);
            if (!query.exec(sql)) qDebug() << "Could not execute query" << query.lastError();
        }
    }
    else
    {
        database.open();
    }

    //LOG_INFO(QString("Opening '%1' database '%2'").arg(aDatabaseType).arg(aDatabaseName));

    return result ? QString() : database.lastError().text();
}

void SqlEngine::initialize()
{
    QString databaseName;
    QString dataDirName;
    dataDirName = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
    QDir dataDir = QDir(dataDirName).absolutePath();
    if(!dataDir.exists())
        dataDir.mkpath(dataDirName);
    databaseName = dataDirName + "/ConfClerk.sqlite";
    login("QSQLITE",databaseName);
}

void SqlEngine::addConferenceToDB(QHash<QString,QString> &aConference)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (db.isValid() && db.isOpen())
    {
        int confId = 0;
        QList<Conference> confsList = Conference::getAll();
        if(confsList.count())
        {
            QListIterator<Conference> i(confsList);
            while (i.hasNext())
            {
                Conference conf = i.next();
                if( aConference["title"] == conf.title() )
                {
                    confId = conf.id();
                    aConference["id"] = QString::number(confId);
                    break;
                }
            }
        }

        if(!confId) // conference 'aConference' isn't in the table => insert
        {
            QSqlQuery query(db);
            query.prepare("INSERT INTO CONFERENCE (title,url,subtitle,venue,city,start,end,days,"
                                                    "day_change,timeslot_duration,active) "
                            " VALUES (:title,:url,:subtitle,:venue,:city,:start,:end,:days,"
                                                    ":day_change,:timeslot_duration,:active)");
            foreach (QString prop_name, (QList<QString>() << "title" << "url" << "subtitle" << "venue" << "city" << "days")) {
                query.bindValue(QString(":") + prop_name, aConference[prop_name]);
            }
            query.bindValue(":start", QDateTime(QDate::fromString(aConference["start"],DATE_FORMAT),QTime(0,0),Qt::UTC).toTime_t());
            query.bindValue(":end", QDateTime(QDate::fromString(aConference["end"],DATE_FORMAT),QTime(0,0),Qt::UTC).toTime_t());
            query.bindValue(":day_change", -QTime::fromString(aConference["day_change"],TIME_FORMAT).secsTo(QTime(0,0)));
            query.bindValue(":day_change", -QTime::fromString(aConference["timeslot_duration"],TIME_FORMAT).secsTo(QTime(0,0)));
            query.bindValue(":active", confsList.count() > 0 ? 0 : 1);
            if (!query.exec()) qDebug() << "Could not execute query to insert a conference:" << query.lastError();
            aConference["id"] = query.lastInsertId().toString(); // 'id' is assigned automatically
        }
    }
}

void SqlEngine::addEventToDB(QHash<QString,QString> &aEvent)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (db.isValid() && db.isOpen())
    {
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
}

void SqlEngine::addPersonToDB(QHash<QString,QString> &aPerson)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (db.isValid() && db.isOpen())
    {
        QSqlQuery query(db);
        query.prepare("INSERT INTO PERSON (xid_conference,id,name) VALUES (:xid_conference, :id, :name)");
        query.bindValue(":xid_conference", aPerson["conference_id"]);
        query.bindValue(":id", aPerson["id"]);
        query.bindValue(":name", aPerson["name"]);
        query.exec(); // some queries fail due to the unique key constraint
        // if (!query.exec()) qDebug() << "SQL query 'insert into person' failed: " << query.lastError();

        query = QSqlQuery(db);
        query.prepare("INSERT INTO EVENT_PERSON (xid_conference,xid_event,xid_person) VALUES (:xid_conference, :xid_event, :xid_person)");
        query.bindValue(":xid_conference", aPerson["conference_id"]);
        query.bindValue(":xid_event", aPerson["event_id"]);
        query.bindValue(":xid_person", aPerson["id"]);
        query.exec(); // some queries fail due to the unique key constraint
        // if (!query.exec()) qDebug() << "SQL query 'insert into event_person' failed: " << query.lastError();
    }
}

void SqlEngine::addRoomToDB(QHash<QString,QString> &aRoom)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (db.isValid() && db.isOpen())
    {
        QSqlQuery query(db);
        query.prepare("SELECT id FROM ROOM WHERE xid_conference=:conference_id and name=:name");
        query.bindValue(":conference_id", aRoom["conference_id"]);
        query.bindValue(":name", aRoom["name"]);
        if (!query.exec()) qDebug() << "Could not execute select room query: " << query.lastError();
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
            query.prepare("INSERT INTO ROOM (xid_conference,name,picture) VALUES (:xid_conference, :name, '')");
            query.bindValue(":xid_conference", aRoom["conference_id"]);
            query.bindValue(":xid_name", aRoom["name"]);
            if (!query.exec()) qDebug() << "Could not execute 'insert into room ...' query." << query.lastError();
            aRoom["id"]= query.lastInsertId().toString(); // 'id' is assigned automatically
            //LOG_AUTOTEST(query);
        }
        query = QSqlQuery(db);
        query.prepare("INSERT INTO EVENT_ROOM (xid_conference,xid_event,xid_room) VALUES (:conference_id, :event_id, :room_id)");
        query.bindValue(":conference_id", aRoom["conference_id"]);
        query.bindValue(":event_id", aRoom["event_id"]);
        query.bindValue(":room_id", aRoom["id"]);
        if (!query.exec()) qDebug() << "Could not 'execute insert into event_room' query:" << query.lastError();
    }
}

void SqlEngine::addLinkToDB(QHash<QString,QString> &aLink)
{
    QSqlDatabase db = QSqlDatabase::database();

    //TODO: check if the link doesn't exist before inserting
    if (db.isValid() && db.isOpen())
    {
        QSqlQuery query(db);
        query.prepare("INSERT INTO LINK (xid_event, xid_conference, name, url) VALUES (:xid_event, :xid_conference, :name, :url)");
        query.bindValue(":xid_event", aLink["event_id"]);
        query.bindValue(":xid_conference", aLink["conference_id"]);
        query.bindValue(":name", aLink["name"]);
        query.bindValue(":url", aLink["url"]);
        if (!query.exec()) qDebug() << "Error executing 'insert into link' query: " << query.lastError();
    }
}

int SqlEngine::searchEvent(int aConferenceId, const QHash<QString,QString> &aColumns, const QString &aKeyword)
{
    QSqlDatabase db = QSqlDatabase::database();

    if ( !db.isValid() || !db.isOpen())
        return -1;

    if (aColumns.empty()) return -1;

    // DROP
    execQuery( db, "DROP TABLE IF EXISTS SEARCH_EVENT");
    // CREATE
    execQuery( db, "CREATE TEMP TABLE SEARCH_EVENT ( xid_conference INTEGER  NOT NULL, id INTEGER NOT NULL )");
    // INSERT
    QString sql = QString("INSERT INTO SEARCH_EVENT ( xid_conference, id ) "
                "SELECT DISTINCT EVENT.xid_conference, EVENT.id FROM EVENT ");
    if( aColumns.contains("ROOM") ){
        sql += "INNER JOIN EVENT_ROOM ON ( EVENT.xid_conference = EVENT_ROOM.xid_conference AND EVENT.id = EVENT_ROOM.xid_event ) ";
        sql += "INNER JOIN ROOM ON ( EVENT_ROOM.xid_room = ROOM.id ) ";
    }
    if( aColumns.contains("PERSON") ){
        sql += "INNER JOIN EVENT_PERSON ON ( EVENT.xid_conference = EVENT_PERSON.xid_conference AND EVENT.id = EVENT_PERSON.xid_event ) ";
        sql += "INNER JOIN PERSON ON ( EVENT_PERSON.xid_person = PERSON.id ) ";
    }
    sql += QString("WHERE EVENT.xid_conference = %1 AND (").arg( aConferenceId );

    QStringList searchKeywords = aKeyword.split(QRegExp("\\s+"));
    foreach (QString table, aColumns.uniqueKeys()){
        foreach (QString column, aColumns.values(table)){
            for (int i=0; i < searchKeywords.count(); i++){
                 sql += QString("%1.%2 LIKE '\%' || :%1%2%3 || '\%' OR ").arg(table).arg(column).arg(i);
            }
        }
    }
    sql.chop( QString(" OR ").length() );
    sql += QString(")");

    QSqlQuery query(db);
    query.prepare(sql);
    foreach (QString table, aColumns.uniqueKeys()){
        foreach (QString column, aColumns.values(table)){
            for (int i = 0; i != searchKeywords.size(); ++i) {
                QString keyword = searchKeywords[i];
                query.bindValue(QString(":%1%2%3").arg(table).arg(column).arg(i), keyword );
            }
        }
    }

    if( !query.exec() ){
       qDebug() << "Could not execute search query: " << query.lastError().text();
       return -1;
    }

    return 1;
}

bool SqlEngine::beginTransaction()
{
    QSqlDatabase db = QSqlDatabase::database();

    return execQuery(db, "BEGIN IMMEDIATE TRANSACTION");
}

bool SqlEngine::commitTransaction()
{
    QSqlDatabase db = QSqlDatabase::database();

    return execQuery(db, "COMMIT");
}

void SqlEngine::deleteConference(int id)
{
    QSqlDatabase db = QSqlDatabase::database();

    if ( !db.isValid() || !db.isOpen()) {
        return;
    }

    beginTransaction();

    QHash<QString, QVariant> params;
    params["xid_conference"] = id;
    execQueryWithParameter(db, "DELETE FROM LINK WHERE xid_conference = :xid_conference", params);
    execQueryWithParameter(db, "DELETE FROM EVENT_ROOM WHERE xid_conference = :xid_conference", params);
    execQueryWithParameter(db, "DELETE FROM EVENT_PERSON WHERE xid_conference = :xid_conference", params);
    execQueryWithParameter(db, "DELETE FROM EVENT WHERE xid_conference = :xid_conference", params);
    execQueryWithParameter(db, "DELETE FROM ROOM WHERE xid_conference = :xid_conference", params);
    execQueryWithParameter(db, "DELETE FROM PERSON WHERE xid_conference = :xid_conference", params);
    execQueryWithParameter(db, "DELETE FROM TRACK WHERE xid_conference = :xid_conference", params);
    execQueryWithParameter(db, "DELETE FROM CONFERENCE WHERE id = :xid_conference", params);

    commitTransaction();
}

bool SqlEngine::execQuery(QSqlDatabase &aDatabase, const QString &aQuery)
{
    QSqlQuery sqlQuery(aDatabase);
    if( !sqlQuery.exec(aQuery) ){
       qDebug() << "SQL ERR: " << sqlQuery.lastError().number() << ", " << sqlQuery.lastError().text();
       return false;
    }
    return true;
}

bool SqlEngine::execQueryWithParameter(QSqlDatabase &aDatabase, const QString &aQuery, const QHash<QString, QVariant>& params)
{
    QSqlQuery sqlQuery(aDatabase);
    sqlQuery.prepare(aQuery);
    foreach (QString param_key, params.keys()) {
        sqlQuery.bindValue(param_key, params[param_key]);
    }
    if( !sqlQuery.exec() ){
       qDebug() << "SQL ERR: " << sqlQuery.lastError().number() << ", " << sqlQuery.lastError().text();
       return false;
    }
    return true;
}
