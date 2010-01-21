#include "event.h"

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

QList<Event> Event::getSearchResultByDate(const QDate& date, int conferenceId, QString orderBy)
{

    QString strQuery = QString("SELECT %1 FROM EVENT INNER JOIN SEARCH_EVENT USING (xid_conference, id) ").arg(columnsForSelect());
    strQuery += QString("WHERE xid_conference = :conf AND start >= :start AND start < :end ORDER BY %1").arg(orderBy);
    qDebug() << strQuery;
    QSqlQuery query;
    query.prepare( strQuery );
    query.bindValue(":conf", conferenceId);
    query.bindValue(":start", convertToDb(date, QVariant::DateTime));
    query.bindValue(":end", convertToDb(date.addDays(1), QVariant::DateTime));

    return load(query);
}

