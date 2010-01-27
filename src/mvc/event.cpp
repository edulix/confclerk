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
    //uint curTime_t =  QDateTime(QDate::currentDate(),QTime::currentTime(),Qt::UTC).toTime_t();
    uint curTime_t = 1265457610; // for testing

    QSqlQuery query;
    query.prepare(selectQuery() + QString("WHERE xid_conference = :conf AND start <= :now1 AND ( start + duration ) > :now2 ORDER BY %1").arg(orderBy));
    query.bindValue(":conf", conferenceId);
    query.bindValue(":now1", convertToDb(curTime_t, QVariant::DateTime));
    query.bindValue(":now2", convertToDb(curTime_t, QVariant::DateTime));

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

QString Event::room() const
{
    QSqlQuery query;
    // TODO: conference ID isn't used here
    query.prepare("SELECT name FROM room WHERE id = (SELECT xid_room FROM event_room WHERE xid_event = :id)");
    query.bindValue(":id", id());
    query.exec();
    // TODO: handle qeury error
    //qDebug() << query.lastError();
    if(query.next())
        return query.record().value("name").toString();
    else
        return QString("not-available");
}

int Event::roomId() const
{
    QSqlQuery query;
    query.prepare("SELECT xid_room FROM event_room WHERE xid_event = :id");
    query.bindValue(":id", id());
    if (!query.isActive())
        if (!query.exec())
            throw OrmSqlException(query.lastError().text());
    if (!query.next())
        throw OrmNoObjectException();
    return query.record().value("xid_room").toInt();
}

QStringList Event::persons() const
{
    QSqlQuery query;
    // TODO: conference ID isn't used here
    query.prepare("SELECT person.name FROM person INNER JOIN event_person ON person.id = event_person.xid_person AND event_person.xid_event = :id");
    query.bindValue(":id", id());
    query.exec();
    // TODO: handle qeury error
    //qDebug() << query.lastError();

    QStringList persons;
    while(query.next())
        persons.append(query.record().value("name").toString());

    return persons;
}

QMap<QString,QString> Event::links() const
{
    QSqlQuery query;
    query.prepare("SELECT name,url FROM link WHERE xid_event = :id AND xid_conference = :conf");
    query.bindValue(":id", id());
    query.bindValue(":conf", conferenceId());
    query.exec();
    // TODO: handle qeury error
    //qDebug() << query.lastError();

    QMap<QString,QString> links;
    while(query.next())
        links.insert(query.record().value("name").toString(), query.record().value("url").toString());

    return links;
}

QList<int> Event::conflicts() const
{
    QSqlQuery query;
    // TODO: conference ID isn't used here
    query.prepare("SELECT conflict_event FROM event_conflict WHERE xid_event = :id AND xid_conference = :conf");
    query.bindValue(":id", id());
    query.bindValue(":conf", conferenceId());
    query.exec();
    // TODO: handle qeury error
    //qDebug() << query.lastError();

    QList<int> conflicts;
    while(query.next())
        conflicts.append(query.record().value("conflict_event").toInt());

    return conflicts;
}

bool Event::hasTimeConflict() const
{
    return conflicts().count() > 0 ? true : false;
}

void Event::updateConflicts()
{
    qDebug() << "updating conflicts";
    QSqlQuery query;
    query.prepare("SELECT id FROM event WHERE xid_conference = :conf AND ( \
           ( start <= :start1 AND ( start + duration ) >= :start2 ) \
        OR ( start >= :start3 AND ( start + duration ) <= :end1 ) \
        OR ( start <= :end2  AND ( start + duration ) >= :end3 ) ) AND favourite = 1 ORDER BY start");
    query.bindValue(":conf", conferenceId());
    query.bindValue(":start1", convertToDb(start(), QVariant::DateTime));
    query.bindValue(":start2", convertToDb(start(), QVariant::DateTime));
    query.bindValue(":start3", convertToDb(start(), QVariant::DateTime));
    query.bindValue(":end1", convertToDb(start().toTime_t()+duration(), QVariant::DateTime));
    query.bindValue(":end2", convertToDb(start().toTime_t()+duration(), QVariant::DateTime));
    query.bindValue(":end3", convertToDb(start().toTime_t()+duration(), QVariant::DateTime));
    query.exec();

    QList<int> conflicts;
    while(query.next())
    {
        int idx = query.record().value("id").toInt();
        if(idx != id())
            conflicts.append(idx);
    }

    if(isFavourite()) // event became favourite
    {
        for(int i=0; i<conflicts.count(); i++)
        {
            QSqlQuery query;
            query.prepare("INSERT INTO event_conflict (xid_conference, xid_event, conflict_event) VALUES ( ? , ? , ? )");
            query.bindValue(0, conferenceId());
            query.bindValue(1, id());
            query.bindValue(2, conflicts[i]);
            query.exec();

            QSqlQuery query2;
            query2.prepare("INSERT INTO event_conflict (xid_conference, xid_event, conflict_event) VALUES ( ? , ? , ? )");
            query2.bindValue(0, conferenceId());
            query2.bindValue(1, conflicts[i]);
            query2.bindValue(2, id());
            query2.exec();
        }
    }
    else // event removed from favourities
    {
        qDebug() << "removing";

        QSqlQuery queryRemove;
        queryRemove.prepare("DELETE FROM event_conflict WHERE xid_event = :id AND xid_conference = :conf");
        queryRemove.bindValue(":id",id());
        queryRemove.bindValue(":conf",conferenceId());
        queryRemove.exec();

        for(int i=0; i<conflicts.count(); i++)
        {
            qDebug() << "removing: " << id() << " -> " << conflicts[i];

            QSqlQuery queryRemove;
            queryRemove.prepare("DELETE FROM event_conflict WHERE xid_event = :id1 AND xid_conference = :conf AND conflict_event = :id2");
            queryRemove.bindValue(":id1",conflicts[i]);
            queryRemove.bindValue(":conf",conferenceId());
            queryRemove.bindValue(":id2",id());
            queryRemove.exec();
        }
    }
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
    qDebug() << strQuery;
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

