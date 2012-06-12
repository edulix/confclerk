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

#include "room.h"

QString const Room::sTableName = QString("room");
int const Room::sTableColCount = 2;
const QString Room::NAME = "name";

QSqlRecord const Room::sColumns = Room::toRecord(QList<QSqlField>()
    << QSqlField("id", QVariant::Int)
    << QSqlField(NAME, QVariant::String));

Room Room::retrieveByName(QString name)
{
    QSqlQuery query;
    query.prepare(
            selectQuery()
            + QString("WHERE %1.name = :name").arg(sTableName));
    query.bindValue(":name", name);
    return loadOne(query);
}

QList<Room> Room::getAll()
{
    QSqlQuery query;
    query.prepare(selectQuery());
    return load(query);
}

Room Room::retrieve(int id)
{
    QSqlQuery query;
    query.prepare(selectQuery()
            + QString("WHERE %1.id = :id").arg(sTableName));
    query.bindValue(":id", id);
    return loadOne(query);
}

QString Room::retrieveRoomName(int id)
{
    Room room = retrieve(id);
    return room.name();
}

