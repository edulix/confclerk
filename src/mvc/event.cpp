/*
 * Copyright (C) 2010 Ixonos Plc.
 *
 * This file is part of fosdem-schedule.
 *
 * fosdem-schedule is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 2 of the License, or (at your option)
 * any later version.
 *
 * fosdem-schedule is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * fosdem-schedule.  If not, see <http://www.gnu.org/licenses/>.
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
    mRoomId( 0 )
{
}

Event Event::getById(int id, int conferenceId)
{
    QSqlQuery query;
    query.prepare(selectQuery() + "WHERE id = :id AND xid_conference = :conf");
    query.bindValue(":id", id);
    query.bindValue(":conf", conferenceId);
    return loadOne(query);
}

QList<Event> Event::getByDate(const QDate& date, int conferenceId, QString orderBy)
{
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
    query.prepare(QString("SELECT %1 FROM %2 %3, %4 %5 WHERE %3.xid_conference = :conf AND %3.start >= :start AND %3.start < :end AND %3.id = R.xid_event ORDER BY %5.xid_room, %3.start").arg(
                    columnsForSelect(aliasEvent), Event::sTableName, aliasEvent, "EVENT_ROOM", aliasEventRoom));
    query.bindValue(":conf", conferenceId);
    query.bindValue(":start", convertToDb(date, QVariant::DateTime));
    query.bindValue(":end", convertToDb(date.addDays(1), QVariant::DateTime));

    return load(query);
}

QList<Event> Event::nowEvents(int conferenceId, QString orderBy)
{
    uint curTime_t =  QDateTime(QDate::currentDate(),QTime::currentTime(),Qt::UTC).toTime_t();
    //uint curTime_t = 1265457610; // for testing

    QSqlQuery query;
    query.prepare(selectQuery() + QString("WHERE xid_conference = :conf AND start <= :now1 AND ( start + duration ) > :now2 ORDER BY %1").arg(orderBy));
    query.bindValue(":conf", conferenceId);
    query.bindValue(":now1", convertToDb(curTime_t, QVariant::DateTime));
    query.bindValue(":now2", convertToDb(curTime_t, QVariant::DateTime));

    return load(query);
}

QList<Event> Event::conflictEvents(int aEventId, int conferenceId)
{
    QSqlQuery query;
    Event event = Event::getById(aEventId,conferenceId);
    query.prepare(selectQuery() + "WHERE xid_conference = :conf AND ( \
           ( start >= :s1 AND ( start + duration ) < :e1 ) \
        OR ( ( start + duration ) > :s2 AND start < :e2 ) ) \
        AND favourite = 1 AND NOT id = :id ORDER BY start");
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
    query.prepare(selectQuery() + QString("WHERE xid_conference = :conf AND start >= :start AND start < :end AND favourite = 1 ORDER BY start"));
    query.bindValue(":conf", conferenceId);
    query.bindValue(":start", convertToDb(date, QVariant::DateTime));
    query.bindValue(":end", convertToDb(date.addDays(1), QVariant::DateTime));

    return load(query);
}

QString Event::room()
{
    if ( mRoomName.isEmpty() )
    {
        QSqlQuery query;
        // TODO: conference ID isn't used here
        query.prepare("SELECT name FROM room WHERE id = :roomId");
        query.bindValue(":roomId", roomId());
        query.exec();
        // TODO: handle qeury error
        //qDebug() << query.lastError();
        if(query.next())
            mRoomName = query.record().value("name").toString();
        else
            mRoomName = QString("not-available");
    }
    return mRoomName;
}

int Event::roomId()
{
    if ( mRoomId == 0 )
    {
        QSqlQuery query;
        query.prepare("SELECT xid_room FROM event_room WHERE xid_event = :id");
        query.bindValue(":id", id());
        if (!query.isActive())
            if (!query.exec())
                throw OrmSqlException(query.lastError().text());
        if (!query.next())
        {
            qDebug() << "No room found for event id: " << id();
            throw OrmNoObjectException();
        }
        mRoomId = query.record().value("xid_room").toInt();
    }
    return mRoomId;
}

QStringList Event::persons()
{
    if( mPersonsList.isEmpty() )
    {
        QSqlQuery query;
        // TODO: conference ID isn't used here
        query.prepare("SELECT person.name FROM person INNER JOIN event_person ON person.id = event_person.xid_person AND event_person.xid_event = :id");
        query.bindValue(":id", id());
        query.exec();
        // TODO: handle qeury error
        //qDebug() << query.lastError();

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

QList<Event> Event::getSearchResultByDate(const QDate& date, int conferenceId, QString orderBy)
{
    QString strQuery = QString("SELECT %1 FROM EVENT INNER JOIN SEARCH_EVENT USING (xid_conference, id) ").arg(columnsForSelect());
    strQuery += QString("WHERE xid_conference = :conf AND start >= :start AND start < :end ORDER BY %1").arg(orderBy);
    //qDebug() << strQuery;
    QList<Event> list;
    QSqlQuery query;
    try{
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

