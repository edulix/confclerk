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
    << QSqlField("timeslot_duration", QVariant::Int)
    << QSqlField("active", QVariant::Bool)
    << QSqlField("url", QVariant::String));

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

int Conference::activeConference()
{
    QSqlQuery query("SELECT id FROM conference WHERE active = 1");
    query.exec();

    QList<int> activeConfs;
    while(query.next())
        activeConfs.append(query.record().value("id").toInt());

    qDebug() << __PRETTY_FUNCTION__
        << "activeConfs.count()" << activeConfs.count()
        ;

    if(activeConfs.count()==0) // no active DB
        return 1;
    else // even if there are more active confs, the first from the list is confidered active
        return activeConfs[0];
}

