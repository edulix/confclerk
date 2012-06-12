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
#include "event.h"
#include "room.h"

QString const Event::sTableName = QString("event");

QSqlRecord const Event::sColumns = Event::toRecord(QList<QSqlField>()
    << QSqlField("id", QVariant::Int)
    << QSqlField("xid_conference", QVariant::Int)
    << QSqlField("start", QVariant::DateTime)
    << QSqlField("duration", QVariant::Int)
    << QSqlField("xid_track", QVariant::Int)
    << QSqlField("type", QVariant::String)
    << QSqlField("language", QVariant::String)
    << QSqlField("favourite", QVariant::Bool)
    << QSqlField("alarm", QVariant::Bool)
    << QSqlField("tag", QVariant::String)
    << QSqlField("title", QVariant::String)
    << QSqlField("subtitle", QVariant::String)
    << QSqlField("abstract", QVariant::String)
    << QSqlField("description", QVariant::String));

Event::Event() :
    room_(NULL)
{
}

Event Event::getById(int id, int conferenceId) {
    QSqlQuery query;
    query.prepare(selectQuery() + "WHERE id = :id AND xid_conference = :conf");
    query.bindValue(":id", id);
    query.bindValue(":conf", conferenceId);
    return loadOne(query);
}


QList<Event> Event::getByDate(const QDate& date, int conferenceId, QString orderBy) {
    QSqlQuery query;
    query.prepare(selectQuery() + QString("WHERE xid_conference = :conf AND start >= :start AND start < :end ORDER BY %1").arg(orderBy));
    query.bindValue(":conf", conferenceId);
    query.bindValue(":start", convertToDb(date, QVariant::DateTime));
    query.bindValue(":end", convertToDb(date.addDays(1), QVariant::DateTime));
    return load(query);
}

QList<Event> Event::getByDateAndRoom(const QDate& date, int conferenceId)
{
    QSqlQuery query;
    QString aliasEvent("E");
    QString aliasEventRoom("R");
    query.prepare(QString("SELECT %1 FROM %2 %3, %4 %5 WHERE %3.xid_conference = :conf AND %3.start >= :start AND %3.start < :end AND %3.id = R.xid_event ORDER BY %5.xid_room, %3.start, %3.duration").arg(
                    columnsForSelect(aliasEvent), Event::sTableName, aliasEvent, "EVENT_ROOM", aliasEventRoom));
    query.bindValue(":conf", conferenceId);
    query.bindValue(":start", convertToDb(date, QVariant::DateTime));
    query.bindValue(":end", convertToDb(date.addDays(1), QVariant::DateTime));

    return load(query);
}


QList<Event> Event::conflictEvents(int aEventId, int conferenceId) {
    QSqlQuery query;
    Event event = Event::getById(aEventId,conferenceId);
    query.prepare(selectQuery() + "WHERE xid_conference = :conf AND ( \
           ( start >= :s1 AND ( start + duration ) < :e1 ) \
        OR ( ( start + duration ) > :s2 AND start < :e2 ) ) \
        AND favourite = 1 AND NOT id = :id ORDER BY start, duration");
    query.bindValue(":conf", event.conferenceId());
    query.bindValue(":s1", convertToDb(event.start(), QVariant::DateTime));
    query.bindValue(":e1", convertToDb(event.start().toTime_t()+event.duration(), QVariant::DateTime));
    query.bindValue(":s2", convertToDb(event.start(), QVariant::DateTime));
    query.bindValue(":e2", convertToDb(event.start().toTime_t()+event.duration(), QVariant::DateTime));
    query.bindValue(":id", event.id());

    return load(query);
}


QList<Event> Event::getFavByDate(const QDate& date, int conferenceId)
{
    QSqlQuery query;
    query.prepare(selectQuery() + QString("WHERE xid_conference = :conf AND start >= :start AND start < :end AND favourite = 1 ORDER BY start, duration"));
    query.bindValue(":conf", conferenceId);
    query.bindValue(":start", convertToDb(date, QVariant::DateTime));
    query.bindValue(":end", convertToDb(date.addDays(1), QVariant::DateTime));

    return load(query);
}

Room* Event::room()
{
    if (room_ == NULL)
    {
        QSqlQuery query;
        query.prepare("SELECT xid_room FROM event_room WHERE xid_event = :id AND xid_conference = :conf");
        query.bindValue(":id", id());
        query.bindValue(":conf", conferenceId());
        if (!query.isActive())
            if (!query.exec())
                throw OrmSqlException(query.lastError().text());
        if (!query.next())
        {
            qDebug() << "No room found for event id: " << id();
            throw OrmNoObjectException();
        }
        int id = query.record().value("xid_room").toInt();
        room_ = new Room(Room::retrieve(id));
    }
    return room_;
}

QString Event::roomName()
{
    return room()->name();
}

int Event::roomId()
{
    return room()->id();
}

QStringList Event::persons()
{
    if( mPersonsList.isEmpty() )
    {
        QSqlQuery query;
        query.prepare("SELECT person.name FROM person INNER JOIN event_person ON person.id = event_person.xid_person AND event_person.xid_event = :id AND event_person.xid_conference = :conf1 AND person.xid_conference = :conf2");
        query.bindValue(":id", id());
        query.bindValue(":conf1", conferenceId());
        query.bindValue(":conf2", conferenceId());
        if (!query.exec())  qDebug() << query.lastError();

        while(query.next())
            mPersonsList.append(query.record().value("name").toString());
    }

    return mPersonsList;
}

QMap<QString,QString> Event::links()
{
    if ( mLinksList.isEmpty() )
    {
        QSqlQuery query;
        query.prepare("SELECT name,url FROM link WHERE xid_event = :id AND xid_conference = :conf");
        query.bindValue(":id", id());
        query.bindValue(":conf", conferenceId());
        query.exec();
        // TODO: handle qeury error
        //qDebug() << query.lastError();

        while(query.next())
            mLinksList.insert(query.record().value("name").toString(), query.record().value("url").toString());
    }
    return mLinksList;
}

bool Event::hasTimeConflict() const
{
    if(!isFavourite()) // if it's not favourite, it can't have time-conflict
        return false;

    return conflictEvents(id(),conferenceId()).count() > 0 ? true : false;
}

void Event::setRoom(const QString &room)
{
    Q_UNUSED(room);

    qWarning("WARINING: setRoom() is NOT IMPLEMENTED YET");
    // TODO: implement
}

void Event::setPersons(const QStringList &persons)
{
    Q_UNUSED(persons);

    qWarning("WARINING: setPersons() is NOT IMPLEMENTED YET");
    // TODO: implement
}

void Event::setLinks(const QMap<QString,QString> &aLinks)
{
    Q_UNUSED(aLinks);

    qWarning("WARINING: setLinks() is NOT IMPLEMENTED YET");
    // TODO: implement
}

QList<Event> Event::getSearchResultByDate(const QDate& date, int conferenceId, QString orderBy) {
    QList<Event> list;

    // Check whether the temporary table SEARCH_EVENT exists (http://www.sqlite.org/faq.html#q7)
    QSqlQuery query("SELECT count(*) FROM sqlite_temp_master WHERE type='table' and name='SEARCH_EVENT'");
    if (!query.exec()) {
        qDebug() << "SQL Error: " << query.lastError().text();
        return list;
    }
    query.first();
    QVariant v = query.value(0);
    if (v.toInt() != 1) return list;

    QString strQuery = QString("SELECT %1 FROM EVENT INNER JOIN SEARCH_EVENT USING (xid_conference, id) ").arg(columnsForSelect());
    strQuery += QString("WHERE xid_conference = :conf AND start >= :start AND start < :end ORDER BY %1").arg(orderBy);
    query = QSqlQuery();
    try {
        if( !query.prepare( strQuery ) ){
            qDebug() << "QSqlQuery.prepare error";
            throw OrmSqlException( query.lastError().text() );
        }

        query.bindValue(":conf", conferenceId);
        query.bindValue(":start", convertToDb(date, QVariant::DateTime));
        query.bindValue(":end", convertToDb(date.addDays(1), QVariant::DateTime));

        list = load(query);
    }
    catch(OrmException &e)
    {
        qDebug() << "getSearchResultByDate error: " << e.text();
    }
    catch(...){
        qDebug() << "getSearchResultByDate failed ...";
    }
    return list;
}

