/*
 * activity.cpp
 *
 *  Created on: Dec 27, 2009
 *      Author: Pavol Korinek
 */

#include "track.h"
#include <QSqlTableModel>

QString const Track::sTableName = QString("track");
int const Track::sTableColCount = 2;
const QString Track::NAME = "name";

QSqlRecord const Track::sColumns = Track::toRecord(QList<QSqlField>()
    << QSqlField("id", QVariant::Int)
    << QSqlField(NAME, QVariant::String));

QMap<int, Track> Track::mIdToTrack;

class TrackInsertException : OrmSqlException
{
public:
    TrackInsertException(const QString& text) : OrmSqlException(text) {}
};

int Track::insert()
{
    QSqlQuery query;
    query.prepare("INSERT INTO " + sTableName + " (" + NAME + ")" + " VALUES " + "(\"" + name() + "\")");
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

void Track::updateTrackMap()
{
    mIdToTrack.clear();
    QList<Track> trackList = Track::getAll();
    Track track;
    for (int id = 0; id < trackList.count(); ++id) {
        track = trackList.at(id);
        mIdToTrack.insert(track.id(), track);
    }
}

QString Track::getTrackName(int id)
{
    QString name = mIdToTrack.value(id).name();
    if (name == "") {
        qDebug() << QString("Error: undefined activity name for id %1").arg(id);
    }
    return name;
}
