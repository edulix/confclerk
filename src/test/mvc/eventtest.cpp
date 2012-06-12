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
#include "eventtest.h"

#include <QtTest>
#include <QSqlDatabase>

#include <QDebug>

#include <event.h>

void EventTest::initTestCase()
{
    // Connect to the test database. Ask Mr. Pavelka to generate one for you :)
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("ConfClerk-test.sqlite");
    QVERIFY(db.open());
}

void EventTest::getById()
{
    Event event = Event::getById(500, 1);

    QCOMPARE(event.id(), 500);
    QCOMPARE(event.start(), QDateTime(QDate(2009, 2, 7), QTime(11, 30, 0), Qt::UTC));
    QCOMPARE(event.trackId(), 123);

    // !!! TODO: typeId and languageId
    QCOMPARE(event.type(), QString("Podium"));
    QCOMPARE(event.language(), QString("English"));
}

void EventTest::getByDate()
{
    QCOMPARE(Event::getByDate(QDate(2009, 2, 7), 1).count(), 127);
    QCOMPARE(Event::getByDate(QDate(2009, 2, 8), 1).count(), 154);
}

void EventTest::storingValues()
{
    Event event;

    event.setId(10);
    event.setConferenceId(20);
    event.setStart(QDateTime::fromString("Sat Feb 7 11:30:00 2009"));
    event.setDuration(30);
    event.setTrackId(40);
    event.setType(QString("type"));
    event.setLanguage(QString("language"));

    QCOMPARE(event.id(), 10);
    QCOMPARE(event.conferenceId(), 20);
    QCOMPARE(event.start(), QDateTime::fromString("Sat Feb 7 11:30:00 2009"));
    QCOMPARE(event.duration(), 30);
    QCOMPARE(event.trackId(), 40);
    QCOMPARE(event.type(), QString("type"));
    QCOMPARE(event.language(), QString("language"));
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
    QCOMPARE(Event::columnsForSelect(), QString("id,xid_conference,start,duration,xid_track,type,language"));
    QCOMPARE(Event::columnsForSelect("t0"),
             QString("t0.id,t0.xid_conference,t0.start,t0.duration,t0.xid_track,t0.type,t0.language"));
}

void EventTest::selectQuery()
{
    QCOMPARE(Event::selectQuery(), QString("SELECT id,xid_conference,start,duration,xid_track,type,language FROM event "));
}
