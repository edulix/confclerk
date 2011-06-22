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

#include "track.h"

QString const Track::sTableName = QString("track");
int const Track::sTableColCount = 3;
const QString Track::CONFERENCEID = "xid_conference";
const QString Track::NAME = "name";

QSqlRecord const Track::sColumns = Track::toRecord(QList<QSqlField>()
    << QSqlField("id", QVariant::Int)
    << QSqlField(CONFERENCEID, QVariant::Int)
    << QSqlField(NAME, QVariant::String));

class TrackInsertException : OrmSqlException
{
public:
    TrackInsertException(const QString& text) : OrmSqlException(text) {}
};

int Track::insert()
{
    QSqlQuery query;
    query.prepare("INSERT INTO " + sTableName + " (" + CONFERENCEID + "," + NAME + ")" + " VALUES " + "(\"" + QString::number(conferenceid()) + "\",\"" + name() + "\")");
    if (!query.exec())
    {
        throw TrackInsertException("Exec Error");
    }
    QVariant variant = query.lastInsertId();
    if (variant.isValid())
        return variant.toInt();
    else
        throw TrackInsertException("Last Insert Id Error");
}

Track Track::retrieveByName(QString name)
{
    QSqlQuery query;
    query.prepare(
            selectQuery()
            + QString("WHERE %1.name = :name").arg(sTableName));
    query.bindValue(":name", name);
    return loadOne(query);
}

QList<Track> Track::getAll()
{
    QSqlQuery query;
    query.prepare(selectQuery());
    return load(query);
}

Track Track::retrieve(int id)
{
    QSqlQuery query;
    query.prepare(selectQuery()
            + QString("WHERE %1.id = :id").arg(sTableName));
    query.bindValue(":id", id);
    return loadOne(query);
}

QString Track::retrieveTrackName(int id)
{
    Track track = retrieve(id);
    return track.name();
}
