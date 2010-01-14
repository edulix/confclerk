#include "conference.h"

QSqlRecord const Conference::sColumns = Conference::toRecord(QList<QSqlField>()
    << QSqlField("id", QVariant::Int)
    << QSqlField("title", QVariant::String)
    << QSqlField("subtitle", QVariant::String)
    << QSqlField("venue", QVariant::String)
    << QSqlField("city", QVariant::String)
    << QSqlField("start", QVariant::DateTime)
    << QSqlField("end", QVariant::DateTime)
    << QSqlField("days", QVariant::Int)
    << QSqlField("day_change", QVariant::Int)
    << QSqlField("timeslot_duration", QVariant::Int));

QString const Conference::sTableName = QString("conference");

Conference Conference::getById(int id)
{
    QSqlQuery query;
    query.prepare(selectQuery() + "WHERE id = :id");
    query.bindValue(":id", id);
    return loadOne(query);
}

QList<Conference> Conference::getAll()
{
    QSqlQuery query;
    query.prepare(selectQuery());
    return load(query);
}

