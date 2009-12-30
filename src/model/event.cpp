#include "event.h"

QSqlRecord const Event::sColumns = Event::toRecord(QList<QSqlField>()
    << QSqlField("id", QVariant::Int)
    << QSqlField("xid_conference", QVariant::Int)
    << QSqlField("start", QVariant::DateTime)
    << QSqlField("duration", QVariant::Int)
    << QSqlField("xid_activity", QVariant::Int)
    << QSqlField("type", QVariant::String)
    << QSqlField("language", QVariant::String));

QString const Event::sTableName = QString("event");

Event Event::getById(int id, int conferenceId)
{
    QString query = selectQuery() + "WHERE id = :id AND xid_conference = :conf";

    QSqlQuery q;
    q.prepare(query);
    q.bindValue(":id", id);
    q.bindValue(":conf", conferenceId);
    return loadOne(q);
}
