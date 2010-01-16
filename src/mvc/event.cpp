#include "event.h"

QSqlRecord const Event::sColumns = Event::toRecord(QList<QSqlField>()
    << QSqlField("id", QVariant::Int)
    << QSqlField("xid_conference", QVariant::Int)
    << QSqlField("start", QVariant::DateTime)
    << QSqlField("duration", QVariant::Int)
    << QSqlField("xid_activity", QVariant::Int)
    << QSqlField("type", QVariant::String)
    << QSqlField("language", QVariant::String)
    << QSqlField("favourite", QVariant::Bool));

QString const Event::sTableName = QString("event");

Event Event::getById(int id, int conferenceId)
{
    QSqlQuery query;
    query.prepare(selectQuery() + "WHERE id = :id AND xid_conference = :conf");
    query.bindValue(":id", id);
    query.bindValue(":conf", conferenceId);
    return loadOne(query);
}

QList<Event> Event::getByDate(const QDate& date, int conferenceId)
{
    QSqlQuery query;
    query.prepare(selectQuery() + "WHERE xid_conference = :conf AND start >= :start AND start < :end ORDER BY start");
    query.bindValue(":conf", conferenceId);
    query.bindValue(":start", convertToDb(date, QVariant::DateTime));
    query.bindValue(":end", convertToDb(date.addDays(1), QVariant::DateTime));

    return load(query);
}

