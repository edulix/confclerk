#include "eventtest.h"

#include <QtTest>
#include <QSqlDatabase>

#include <QDebug>

#include <event.h>

void EventTest::initTestCase()
{
    // Connect to the test database. Ask Mr. Pavelka to generate one for you :)
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("fosdem-test.sqlite");
    QVERIFY(db.open());
}

void EventTest::getById()
{
    Event event = Event::getById(500, 1);
    QCOMPARE(event.id(), 500);
    QCOMPARE(event.start(), QDateTime::fromString("Sat Feb 7 11:30:00 2009"));
    QCOMPARE(event.activityId(), 123);

    // !!! TODO: typeId and languageId
    QCOMPARE(event.typeId(), 0);
    QCOMPARE(event.languageId(), 0);
}

void EventTest::storingValues()
{
    Event event;

    event.setId(10);
    event.setConferenceId(20);
    event.setStart(QDateTime::fromString("Sat Feb 7 11:30:00 2009"));
    event.setDuration(30);
    event.setActivityId(40);
    event.setTypeId(50);
    event.setLanguageId(60);

    QCOMPARE(event.id(), 10);
    QCOMPARE(event.conferenceId(), 20);
    QCOMPARE(event.start(), QDateTime::fromString("Sat Feb 7 11:30:00 2009"));
    QCOMPARE(event.duration(), 30);
    QCOMPARE(event.activityId(), 40);
    QCOMPARE(event.typeId(), 50);
    QCOMPARE(event.languageId(), 60);
}


void EventTest::hydrate()
{
    QSqlRecord record;
    record.append(QSqlField("duration", QVariant::Int));
    record.append(QSqlField("id", QVariant::Int));
    record.setValue(0, 10);
    record.setValue(1, 20);

    Event event = Event::hydrate(record);
    QCOMPARE(event.id(), 20);
    QCOMPARE(event.duration(), 10);
}

void EventTest::columnsForSelect()
{
    QCOMPARE(Event::columnsForSelect(), QString("id,xid_conference,start,duration,xid_activity,type,language"));
    QCOMPARE(Event::columnsForSelect("t0"),
             QString("t0.id,t0.xid_conference,t0.start,t0.duration,t0.xid_activity,t0.type,t0.language"));
}

void EventTest::selectQuery()
{
    QCOMPARE(Event::selectQuery(), QString("SELECT id,xid_conference,start,duration,xid_activity,type,language FROM event "));
}
