/*
 * room.cpp
 *
 *  Created on: Dec 27, 2009
 *      Author: user
 */

#include "room.h"

QString const Room::sTableName = QString("room");
int const Room::sTableColCount = 3;
const QString Room::NAME = "name";

QSqlRecord const Room::sColumns = Room::toRecord(QList<QSqlField>()
    << QSqlField("id", QVariant::Int)
    << QSqlField(NAME, QVariant::String)
    << QSqlField("picture", QVariant::String));

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

