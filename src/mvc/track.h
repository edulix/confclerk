/*
 * track.h
 *
 *  Created on: Dec 27, 2009
 *      Author: Pavol Korinek
 */

#ifndef TRACK_H_
#define TRACK_H_

#include <ormrecord.h>

class Track : public OrmRecord<Track>
{
public:
    static const QSqlRecord sColumns;
    static const QSqlRecord sInsertColumns;
    static QString const sTableName;
    static const int sTableColCount;
    static const QString NAME;
public:
    static QMap<int, Track> mIdToTrack;
public:
    int insert();
    int id() const { return value("id").toInt(); }
    void setId(int id) { setValue("id", id); }
    QString name() const { return value("name").toString(); }
    void setName(const QString & type) { setValue("name", type); }
public:
    static QList<Track> getAll();
    static Track retrieve(int id);
    static QString retrieveTrackName(int id);
    static Track retrieveByName(QString name);
};

#endif /* TRACK_H_ */
