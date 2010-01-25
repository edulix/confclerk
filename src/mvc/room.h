/*
 * room.h
 *
 *  Created on: Dec 27, 2009
 *      Author: Pavol Korinek
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
    int insert();
public:
    static QList<Room> getAll();
    static Room retrieve(int id);
    static QString retrieveRoomName(int id);
    static Room retrieveByName(QString name);
};

#endif /* ROOM_H_ */
