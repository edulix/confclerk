/*
 * track.cpp
 *
 *  Created on: Dec 27, 2009
 *      Author: Pavol Korinek
 */

#include "track.h"

QString const Track::sTableName = QString("track");
int const Track::sTableColCount = 2;

QSqlRecord const Track::sColumns = Track::toRecord(QList<QSqlField>()
    << QSqlField("id", QVariant::Int)
    << QSqlField("name", QVariant::String));

QMap<int, Track> Track::mIdToTrack;

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
        qDebug() << QString("Error: undefined track name for id %1").arg(id);
    }
    return name;
}
