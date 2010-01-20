/*
 * track.h
 *
 *  Created on: Dec 27, 2009
 *      Author: Pavol Korinek
 */

#ifndef TRACK_H
#define TRACK_H

#include <ormrecord.h>

class Track : public OrmRecord<Track>
{
public:
    static const QSqlRecord sColumns;
    static QString const sTableName;
    static const int sTableColCount;
public:
    static QMap<int, Track> mIdToTrack;
public:
    static QList<Track> getAll();
    int id() const { return value("id").toInt(); }
    void setId(int id) { setValue("id", id); }
    QString name() const { return value("name").toString(); }
    void setName(const QString & type) { setValue("name", type); }
public:
    static void updateTrackMap();
    static QString getTrackName(int id);
};

#endif /* TRACK_H */

