/*
 * Copyright (C) 2010 Ixonos Plc.
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

#ifndef ROOM_H_
#define ROOM_H_

#include <ormrecord.h>

class Room : public OrmRecord<Room>
{
public:
    static const QSqlRecord sColumns;
    static QString const sTableName;
    static const int sTableColCount;
    static const QString NAME;
public:
    int id() const { return value("id").toInt(); }
    void setId(int id) { setValue("id", id); }
    QString name() const { return value("name").toString(); }
    void setName(const QString & type) { setValue("name", type); }
    // TODO: make naming consistent - either "picture" or "map"
    QVariant map() const { return value("picture"); }
    bool hasMap() const
    {
        // empty strings also treasted as NULL,
        // as storing NULLs requires rewrite of storing code and DB scheme
        return !isNull("picture") and !value("picture").toString().isEmpty();
    }
    int insert();
public:
    static QList<Room> getAll();
    static Room retrieve(int id);
    static QString retrieveRoomName(int id);
    static Room retrieveByName(QString name);
};

#endif /* ROOM_H_ */
