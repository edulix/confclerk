#include "eventtest.h"

#include <QtTest>
#include <QSqlDatabase>

#include <QDebug>

#include <event.h>

void EventTest::initTestCase()
{
    // Connect to the test database. Ask Mr. Pavelka to generate one for you :)
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("fostem-test.sqlite");
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

void EventTest::colNames()
{
    QCOMPARE(Event::colName(Event::Id), QString("id"));
    QCOMPARE(Event::colName(Event::Conference), QString("xid_conference"));
    QCOMPARE(Event::colName(Event::Start), QString("start"));
    QCOMPARE(Event::colName(Event::Duration), QString("duration"));
    QCOMPARE(Event::colName(Event::Activity), QString("xid_activity"));
    QCOMPARE(Event::colName(Event::Type), QString("type"));
    QCOMPARE(Event::colName(Event::Language), QString("language"));
}

void EventTest::storingValues()
{
    Event event;
    QCOMPARE(event.id(), 0);

    event.setId(10);
    QCOMPARE(event.id(), 10);

    event.setConferenceId(20);
    QCOMPARE(event.conferenceId(), 20);

    event.setStart(QDateTime::fromString("Sat Feb 7 11:30:00 2009"));
    QCOMPARE(event.start(), QDateTime::fromString("Sat Feb 7 11:30:00 2009"));

    event.setDuration(30);
    QCOMPARE(event.duration(), 30);

    event.setActivityId(40);
    QCOMPARE(event.activityId(), 40);

    event.setTypeId(50);
    QCOMPARE(event.typeId(), 50);

    event.setLanguageId(60);
    QCOMPARE(event.languageId(), 60);
}
