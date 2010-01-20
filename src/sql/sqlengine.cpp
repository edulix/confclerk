
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDateTime>

#include <QDir>
#include "sqlengine.h"

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

    database.open();

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
        QString values = QString("'%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9', '%10'") \
                         .arg(aConference["id"]) \
                         .arg(aConference["title"]) \
                         .arg(aConference["subtitle"]) \
                         .arg(aConference["venue"]) \
                         .arg(aConference["city"]) \
                         .arg(QDateTime(QDate::fromString(aConference["start"],DATE_FORMAT),QTime(0,0),Qt::UTC).toTime_t()) \
                         .arg(QDateTime(QDate::fromString(aConference["end"],DATE_FORMAT),QTime(0,0),Qt::UTC).toTime_t()) \
                         .arg(aConference["days"]) \
                         .arg(-QTime::fromString(aConference["day_change"],TIME_FORMAT).secsTo(QTime(0,0))) \
                         .arg(-QTime::fromString(aConference["timeslot_duration"],TIME_FORMAT).secsTo(QTime(0,0)));

        QString query = QString("INSERT INTO CONFERENCE (id,title,subtitle,venue,city,start,end,days,day_change,timeslot_duration) VALUES (%1)").arg(values);
        QSqlQuery result (query, db);
        //LOG_AUTOTEST(query);
    }
}

void SqlEngine::addEventToDB(QHash<QString,QString> &aEvent)
{
    //LOG_DEBUG(QString("Adding event '%1' to DB").arg(*aEvent));

    QSqlDatabase db = QSqlDatabase::database();

    if (db.isValid() && db.isOpen())
    {
        // The items of the Event are divided into the two tables EVENT and VIRTUAL_EVENT
        // VIRTUAL_EVENT is for Full-Text-Serach Support
        QDateTime startDateTime = QDateTime(QDate::fromString(aEvent["date"],DATE_FORMAT),QTime::fromString(aEvent["start"],TIME_FORMAT));
        QString values = QString("'%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9'") \
                         .arg(aEvent["conference_id"]) \
                         .arg(aEvent["id"]) \
                         .arg(QString::number(startDateTime.toTime_t())) \
                         .arg(-QTime::fromString(aEvent["duration"],TIME_FORMAT).secsTo(QTime(0,0))) \
                         .arg("123456") \
                         .arg(aEvent["type"]) \
                         .arg(aEvent["language"]) \
                         .arg("0") \
                         .arg("0");

        QString query = QString("INSERT INTO EVENT (xid_conference, id, start, duration, xid_activity, type, language, favourite, alarm) VALUES (%1)").arg(values);
        QSqlQuery result (query, db);
        //LOG_AUTOTEST(query);

        // add some(text related) Event's items to VIRTUAL_EVENT table
        QString values2 = QString("'%1', '%2', '%3', ? , ? , ? , ? ") \
                          .arg(aEvent["conference_id"]) \
                          .arg(aEvent["id"]) \
                          .arg(aEvent["tag"]);

        QString query2 = QString("INSERT INTO VIRTUAL_EVENT (xid_conference, id, tag, title, subtitle, abstract, description) VALUES (%1)").arg(values2);

        QSqlQuery result2;
        result2.prepare(query2);
        result2.bindValue(0,aEvent["title"]);
        result2.bindValue(1,aEvent["subtitle"]);
        result2.bindValue(2,aEvent["abstract"]);
        result2.bindValue(3,aEvent["description"]);
        result2.exec();
        //LOG_AUTOTEST(query2);
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

        query.exec("CREATE TABLE CONFERENCE ( \
            id INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , \
            title VARCHAR NOT NULL , \
            subtitle VARCHAR, \
            venue VARCHAR, \
            city VARCHAR NOT NULL , \
            start INTEGER NOT NULL , \
            end INTEGER NOT NULL , \
            days INTEGER, \
            day_change INTEGER, \
            timeslot_duration INTEGER)");

        query.exec("CREATE TABLE ACTIVITY ( \
            id INTEGER  PRIMARY KEY AUTOINCREMENT  NOT NULL , \
            name VARCHAR NOT NULL )");

        query.exec("CREATE TABLE ROOM ( \
            id INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , \
            name VARCHAR NOT NULL , \
            picture VARCHAR NOT NULL)");

        query.exec("CREATE TABLE PERSON ( \
            id INTEGER PRIMARY KEY  NOT NULL , \
            name VARCHAR NOT NULL)");

        query.exec("CREATE TABLE EVENT ( \
            xid_conference INTEGER  NOT NULL, \
            id INTEGER NOT NULL , \
            start INTEGER NOT NULL , \
            duration INTEGER NOT NULL , \
            xid_activity INTEGER NOT NULL REFERENCES ACTIVITY(id), \
            type VARCHAR, \
            language VARCHAR, \
            favourite INTEGER DEFAULT 0, \
            alarm INTEGER DEFAULT 0, \
            PRIMARY KEY (xid_conference,id), \
            FOREIGN KEY(xid_conference) REFERENCES CONFERENCE(id) \
            FOREIGN KEY(xid_activity) REFERENCES ACTIVITY(id))");

#ifdef MAEMO
        // TBD: MAEMO Virtual tables compatibility (waiting for Marek).
        // MAEMO sqlite Qt driver doesn't provide FTS support by default - use the following HACK
        query.exec("CREATE TABLE VIRTUAL_EVENT ( \
            xid_conference INTEGER  NOT NULL, \
            id INTEGER NOT NULL , \
            tag VARCHAR,title VARCHAR NOT NULL , \
            subtitle VARCHAR, \
            abstract VARCHAR, \
            description VARCHAR, \
            PRIMARY KEY (xid_conference,id))");
#else
        query.exec("CREATE VIRTUAL TABLE VIRTUAL_EVENT using fts3 ( \
            xid_conference INTEGER  NOT NULL, \
            id INTEGER NOT NULL , \
            tag VARCHAR,title VARCHAR NOT NULL , \
            subtitle VARCHAR, \
            abstract VARCHAR, \
            description VARCHAR, \
            PRIMARY KEY (xid_conference,id))");
#endif

        query.exec("CREATE TABLE EVENT_PERSON ( \
            xid_conference INTEGER NOT NULL , \
            xid_event INTEGER NOT NULL , \
            xid_person INTEGER NOT NULL, \
            FOREIGN KEY(xid_conference, xid_event) REFERENCES EVENT(xid_conference, id), \
            FOREIGN KEY(xid_person) REFERENCES PERSON(id))");

        query.exec("CREATE TABLE EVENT_ROOM ( \
            xid_conference INTEGER NOT NULL , \
            xid_event INTEGER NOT NULL , \
            xid_room INTEGER NOT NULL, \
            FOREIGN KEY(xid_conference, xid_event) REFERENCES EVENT(xid_conference, id), \
            FOREIGN KEY(xid_room) REFERENCES ROOM(id))");

        query.exec("CREATE TABLE LINK ( \
            id INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL, \
            xid_conference INTEGER NOT NULL, \
            xid_event INTEGER NOT NULL, \
            name VARCHAR, \
            url VARCHAR NOT NULL, \
            FOREIGN KEY(xid_conference, xid_event) REFERENCES EVENT(xid_conference, id))");
    }
    else
    {
        //LOG_WARNING("Database is not opened");
    }

    return result;
}

int SqlEngine::searchEvent(int aConferenceId, const QList<QString> &aColumns, const QString &aKeyword)
{
    QSqlDatabase db = QSqlDatabase::database();

    if ( !db.isValid() || !db.isOpen())
        return -1;

    QString query = QString(
        "DROP TABLE IF EXISTS SEARCH_EVENT;"
        "CREATE TEMP TABLE SEARCH_EVENT ( xid_conference INTEGER  NOT NULL, id INTEGER NOT NULL );"
        "INSERT INTO SEARCH_EVENT ( xid_conference, id) "
            "SELECT xid_conference, id FROM EVENT AS e INNER JOIN VIRTUAL_EVENT AS ve USING (xid_conference, id) "
            "WHERE xid_conference = %1 AND (").arg( aConferenceId );

    int i = 0;
    foreach (QString str, aColumns){
        query += QString("%1 LIKE '\%%2\%' OR ").arg( aColumns.at(i++), aKeyword );
    }
    query.chop( QString(" OR ").length() );
    query += QString(");");

    qDebug() << "\nSQL: " << query;

    db.exec();

    if( db.lastError().isValid() && db.lastError().number() != 0 ){
        qDebug() << "SQL ERR: " << db.lastError().number() << ", " << db.lastError().text();
        return 0;
    }
    else{
        qDebug() << "SQL OK.\n";
        return 1;
    }

}
