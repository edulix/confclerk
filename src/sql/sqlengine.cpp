
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDateTime>

#include <QDir>
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
        // creating empty DB + tables
        // ??? what is the best way of creating new empty DB ???
        // we can either:
        //  - create new DB + tables by issuing corresponding queries (used solution)
        //  - create new DB from resource, which contains empty DB with tables
        result = createTables(database);
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
    if(!QDir::home().exists(".fosdem"))
        QDir::home().mkdir(".fosdem");
    databaseName = QDir::homePath() + "/.fosdem/" + "fosdem.sqlite";
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
            QString values = QString("'%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9'") \
                             .arg(aConference["title"]) \
                             .arg(aConference["subtitle"]) \
                             .arg(aConference["venue"]) \
                             .arg(aConference["city"]) \
                             .arg(QDateTime(QDate::fromString(aConference["start"],DATE_FORMAT),QTime(0,0),Qt::UTC).toTime_t()) \
                             .arg(QDateTime(QDate::fromString(aConference["end"],DATE_FORMAT),QTime(0,0),Qt::UTC).toTime_t()) \
                             .arg(aConference["days"]) \
                             .arg(-QTime::fromString(aConference["day_change"],TIME_FORMAT).secsTo(QTime(0,0))) \
                             .arg(-QTime::fromString(aConference["timeslot_duration"],TIME_FORMAT).secsTo(QTime(0,0)));
                             values.append(QString(", '%1'").arg(confsList.count()>0?"0":"1"));

            QString query = QString("INSERT INTO CONFERENCE (title,subtitle,venue,city,start,end,days,day_change,timeslot_duration,active) VALUES (%1)").arg(values);
            QSqlQuery result (query, db);
            aConference["id"] = result.lastInsertId().toString(); // 'id' is assigned automatically
        }
    }
}

void SqlEngine::addEventToDB(QHash<QString,QString> &aEvent)
{
    //LOG_DEBUG(QString("Adding event '%1' to DB").arg(*aEvent));

    QSqlDatabase db = QSqlDatabase::database();

    if (db.isValid() && db.isOpen())
    {
        //insert event track to table and get track id
        QString name = aEvent["track"];
        Track track;
        int trackId;
        try
        {
            track = Track::retrieveByName(name);
            trackId = track.id();
            /*qDebug() << QString("DEBUG: Track %1 in DB").arg(name);*/
        }
        catch (OrmNoObjectException &e) {
            track.setName(name);
            trackId = track.insert();
            /*qDebug() << QString("DEBUG: Track %1 added to DB").arg(name);*/
        }
        QDateTime startDateTime = QDateTime(QDate::fromString(aEvent["date"],DATE_FORMAT),QTime::fromString(aEvent["start"],TIME_FORMAT));
        QString values = QString("'%1', '%2', '%3', '%4', '%5', '%6', '%7', ? , ? , ? , ? , ? , '%8', '%9'") \
                         .arg(aEvent["conference_id"]) \
                         .arg(aEvent["id"]) \
                         .arg(QString::number(startDateTime.toTime_t())) \
                         .arg(-QTime::fromString(aEvent["duration"],TIME_FORMAT).secsTo(QTime(0,0))) \
                         .arg(trackId) \
                         .arg(aEvent["type"]) \
                         .arg(aEvent["language"]) \
                         .arg("0") \
                         .arg("0");

        QString query =
            QString("INSERT INTO EVENT (xid_conference, id, start, duration, xid_track, type, language, tag, title, subtitle, abstract, description, favourite, alarm) VALUES (%1)")
            .arg(values);

        QSqlQuery result;
        result.prepare(query);
        result.bindValue(0,aEvent["tag"]);
        result.bindValue(1,aEvent["title"]);
        result.bindValue(2,aEvent["subtitle"]);
        result.bindValue(3,aEvent["abstract"]);
        result.bindValue(4,aEvent["description"]);
        result.exec();
    }
}


void SqlEngine::addPersonToDB(QHash<QString,QString> &aPerson)
{
    QSqlDatabase db = QSqlDatabase::database();

    //TODO: check if the person doesn't exist before inserting
    if (db.isValid() && db.isOpen())
    {
        QString values = QString("'%1', '%2'").arg(aPerson["id"],aPerson["name"]);
        QString query = QString("INSERT INTO PERSON (id,name) VALUES (%1)").arg(values);
        QSqlQuery result (query, db);
        //LOG_AUTOTEST(query);

        values = QString("'%1', '%2', '%3'").arg(aPerson["conference_id"],aPerson["event_id"],aPerson["id"]);
        query = QString("INSERT INTO EVENT_PERSON (xid_conference,xid_event,xid_person) VALUES (%1)").arg(values);
        QSqlQuery resultEventPerson (query, db);
        //LOG_AUTOTEST(query);
    }
}

void SqlEngine::addRoomToDB(QHash<QString,QString> &aRoom)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (db.isValid() && db.isOpen())
    {
        QString queryExist = QString("SELECT id FROM ROOM WHERE name='%1'").arg(aRoom["name"]);
        QSqlQuery resultExist(queryExist,db);
        // now we have to check whether ROOM record with 'name' exists or not,
        // - if it doesn't exist yet, then we have to add that record to 'ROOM' table
        //   and assign autoincremented 'id' to aRoom
        // - if it exists, then we need to get its 'id' and assign it to aRoom
        int roomId = -1;
        if(resultExist.next()) // ROOM record with 'name' already exists: we need to get its 'id'
        {
            roomId = resultExist.value(0).toInt();
        }
        else // ROOM record doesn't exist yet, need to create it
        {
            QString values = QString("'%1', '%2'").arg(aRoom["name"],aRoom["picture"]);
            QString query = QString("INSERT INTO ROOM (name,picture) VALUES (%1)").arg(values);
            QSqlQuery result (query, db);
            roomId = result.lastInsertId().toInt(); // 'id' is assigned automatically
            //LOG_AUTOTEST(query);
        }

        QString values = QString("'%1', '%2', '%3'").arg(aRoom["conference_id"],aRoom["event_id"],QString::number(roomId));
        QString query = QString("INSERT INTO EVENT_ROOM (xid_conference,xid_event,xid_room) VALUES (%1)").arg(values);
        QSqlQuery result (query, db);
        //LOG_AUTOTEST(query);
    }
}

void SqlEngine::addLinkToDB(QHash<QString,QString> &aLink)
{
    QSqlDatabase db = QSqlDatabase::database();

    //TODO: check if the link doesn't exist before inserting
    if (db.isValid() && db.isOpen())
    {
        QString values = QString("'%1', '%2', '%3', '%4'").arg(aLink["event_id"],aLink["conference_id"],aLink["name"],aLink["url"]);
        QString query = QString("INSERT INTO LINK (xid_event, xid_conference, name, url) VALUES (%1)").arg(values);
        QSqlQuery result(query, db);
        //LOG_AUTOTEST(query);
    }
}

bool SqlEngine::createTables(QSqlDatabase &aDatabase)
{
    bool result = aDatabase.open();

    if (aDatabase.isValid() && aDatabase.isOpen())
    {
        QSqlQuery query(aDatabase);

        query.exec("CREATE TABLE CONFERENCE ( "
            "id INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL, "
            "title VARCHAR UNIQUE NOT NULL, "
            "subtitle VARCHAR, "
            "venue VARCHAR, "
            "city VARCHAR NOT NULL, "
            "start INTEGER NOT NULL, "
            "end INTEGER NOT NULL, "
            "days INTEGER, "
            "day_change INTEGER, "
            "timeslot_duration INTEGER, "
            "active INTEGER DEFAULT 0);");

        query.exec("CREATE TABLE TRACK ( "
            "id INTEGER  PRIMARY KEY AUTOINCREMENT  NOT NULL, "
            "name VARCHAR UNIQUE NOT NULL );");

        query.exec("CREATE TABLE ROOM ( "
            "id INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL, "
            "name VARCHAR UNIQUE NOT NULL, "
            "picture VARCHAR NOT NULL);");

        query.exec("CREATE TABLE PERSON ( "
            "id INTEGER PRIMARY KEY  NOT NULL, "
            "name VARCHAR UNIQUE NOT NULL);");

        query.exec("CREATE TABLE EVENT ( "
            "xid_conference INTEGER  NOT NULL, "
            "id INTEGER NOT NULL, "
            "start INTEGER NOT NULL, "
            "duration INTEGER NOT NULL, "
            "xid_track INTEGER NOT NULL REFERENCES TRACK(id), "
            "type VARCHAR, "
            "language VARCHAR, "
            "tag VARCHAR,title VARCHAR NOT NULL, "
            "subtitle VARCHAR, "
            "abstract VARCHAR, "
            "description VARCHAR, "
            "favourite INTEGER DEFAULT 0, "
            "alarm INTEGER DEFAULT 0, "
            "PRIMARY KEY (xid_conference,id), "
            "FOREIGN KEY(xid_conference) REFERENCES CONFERENCE(id), "
            "FOREIGN KEY(xid_track) REFERENCES TRACK(id));");

        query.exec("CREATE TABLE EVENT_PERSON ( "
            "xid_conference INTEGER NOT NULL, "
            "xid_event INTEGER NOT NULL, "
            "xid_person INTEGER NOT NULL, "
            "UNIQUE ( xid_conference, xid_event, xid_person ) ON CONFLICT IGNORE, "
            "FOREIGN KEY(xid_conference) REFERENCES CONFERENCE(id), "
            "FOREIGN KEY(xid_event) REFERENCES EVENT(id), "
            "FOREIGN KEY(xid_person) REFERENCES PERSON(id));");

        query.exec("CREATE TABLE EVENT_ROOM ( "
            "xid_conference INTEGER NOT NULL, "
            "xid_event INTEGER NOT NULL, "
            "xid_room INTEGER NOT NULL, "
            "UNIQUE ( xid_conference, xid_event, xid_room ) ON CONFLICT IGNORE, "
            "FOREIGN KEY(xid_conference) REFERENCES CONFERENCE(id), "
            "FOREIGN KEY(xid_event) REFERENCES EVENT(id), "
            "FOREIGN KEY(xid_room) REFERENCES ROOM(id));");

        query.exec("CREATE TABLE EVENT_CONFLICT ( "
            "xid_conference INTEGER NOT NULL, "
            "xid_event INTEGER NOT NULL, "
            "conflict_event INTEGER NOT NULL, "
            "UNIQUE ( xid_conference, xid_event, conflict_event ) ON CONFLICT IGNORE, "
            "FOREIGN KEY(xid_conference) REFERENCES CONFERENCE(id), "
            "FOREIGN KEY(xid_event) REFERENCES EVENT(id));");

        query.exec("CREATE TABLE LINK ( "
            "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "
            "xid_conference INTEGER NOT NULL, "
            "xid_event INTEGER NOT NULL, "
            "name VARCHAR, "
            "url VARCHAR NOT NULL, "
            "UNIQUE ( xid_conference, xid_event, url ) ON CONFLICT IGNORE, "
            "FOREIGN KEY(xid_conference) REFERENCES CONFERENCE(id), "
            "FOREIGN KEY(xid_event) REFERENCES EVENT(id));");
    }
    else
    {
        //LOG_WARNING("Database is not opened");
    }

    return result;
}

int SqlEngine::searchEvent(int aConferenceId, const QHash<QString,QString> &aColumns, const QString &aKeyword)
{
    QSqlDatabase db = QSqlDatabase::database();

    if ( !db.isValid() || !db.isOpen())
        return -1;


    // DROP
    execQuery( db, "DROP TABLE IF EXISTS SEARCH_EVENT;");
    // CREATE
    execQuery( db, "CREATE TEMP TABLE SEARCH_EVENT ( xid_conference INTEGER  NOT NULL, id INTEGER NOT NULL );");
    // INSERT
    QString query = QString("INSERT INTO SEARCH_EVENT ( xid_conference, id) "
                "SELECT EVENT.xid_conference, EVENT.id FROM EVENT ");
    if( aColumns.contains("ROOM") ){
        query += "INNER JOIN EVENT_ROOM ON (EVENT.xid_conference = EVENT_ROOM.xid_conference AND EVENT.id = EVENT_ROOM.xid_event ) ";
        query += "INNER JOIN ROOM ON ( EVENT_ROOM.xid_room = ROOM.id ) ";
    }
    if( aColumns.contains("PERSON") ){
        query += "INNER JOIN EVENT_PERSON ON (EVENT.xid_conference = EVENT_PERSON.xid_conference AND EVENT.id = EVENT_PERSON.xid_event ) ";
        query += "INNER JOIN PERSON ON ( EVENT_PERSON.xid_person = PERSON.id ) ";
    }
    query += QString("WHERE EVENT.xid_conference = %1 AND (").arg( aConferenceId );

    foreach (QString table, aColumns.uniqueKeys()){
        foreach (QString column, aColumns.values(table)){
            query += QString("%1.%2 LIKE '\%%3\%' OR ").arg( table, column, aKeyword );
        }
    }
    query.chop( QString(" OR ").length() );
    query += QString(");");

    execQuery( db, query );

    //TODO: retun number of rows from SEARCH_EVENT
    return 1;
}

bool SqlEngine::execQuery(QSqlDatabase &aDatabase, const QString &aQuery)
{
    qDebug() << "\nSQL: " << aQuery;

    QSqlQuery sqlQuery(aDatabase);
    if( !sqlQuery.exec(aQuery) ){
       qDebug() << "SQL ERR: " << sqlQuery.lastError().number() << ", " << sqlQuery.lastError().text();
       return false;
    }
    else{
       qDebug() << "SQL OK.\n";
       return true;
    }
}

