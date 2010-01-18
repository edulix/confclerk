#include "event.h"

// 'event' record is splitted into two separate tables 'event' and 'virtual_event'
// for the FTS (Full-Text-Search) support and so, it is necessary to provide/use
// two table names + corresponding parameters/methods, see bellow
QString const Event::sTable1Name = QString("event");
QString const Event::sTable2Name = QString("virtual_event");
int const Event::sTable1ColCount = 8; // see 'toRecord()' for more details
int const Event::sTable2ColCount = 5; // see 'toRecord()' for more details

QSqlRecord const Event::sColumns = Event::toRecord(QList<QSqlField>()
    /* 'columns from Table 1 */
    << QSqlField("id", QVariant::Int)
    << QSqlField("xid_conference", QVariant::Int)
    << QSqlField("start", QVariant::DateTime)
    << QSqlField("duration", QVariant::Int)
    << QSqlField("xid_activity", QVariant::Int)
    << QSqlField("type", QVariant::String)
    << QSqlField("language", QVariant::String)
    << QSqlField("favourite", QVariant::Bool)
    /* 'columns' from Table2 */
    << QSqlField("tag", QVariant::String)
    << QSqlField("title", QVariant::String)
    << QSqlField("subtitle", QVariant::String)
    << QSqlField("abstract", QVariant::String)
    << QSqlField("description", QVariant::String));


Event Event::getById(int id, int conferenceId)
{
    QSqlQuery query;
    query.prepare(
            selectQueryJoin2T("id")
            + QString("WHERE %1.id = :id AND %1.xid_conference = :conf").arg(sTable1Name));
    query.bindValue(":id", id);
    query.bindValue(":conf", conferenceId);

    return loadOne(query);
}

QList<Event> Event::getByDate(const QDate& date, int conferenceId)
{
    QSqlQuery query;
    query.prepare(
            selectQueryJoin2T("id")
            + QString("WHERE %1.xid_conference = :conf AND %1.start >= :start AND %1.start < :end ORDER BY %1.start").arg(sTable1Name));
    query.bindValue(":conf", conferenceId);
    query.bindValue(":start", convertToDb(date, QVariant::DateTime));
    query.bindValue(":end", convertToDb(date.addDays(1), QVariant::DateTime));

    return load(query);
}

QList<Event> Event::getFavByDate(const QDate& date, int conferenceId)
{
    QSqlQuery query;
    query.prepare(
            selectQueryJoin2T("id")
            + QString("WHERE %1.xid_conference = :conf AND %1.start >= :start AND %1.start < :end AND %1.favourite = 1 ORDER BY %1.start").arg(sTable1Name));
    query.bindValue(":conf", conferenceId);
    query.bindValue(":start", convertToDb(date, QVariant::DateTime));
    query.bindValue(":end", convertToDb(date.addDays(1), QVariant::DateTime));

    return load(query);
}


