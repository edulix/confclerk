#include "eventtest.h"

#include <QtTest>
#include <QSqlDatabase>

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
