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

#ifndef TRACK_H_
#define TRACK_H_

#include "ormrecord.h"

class Track : public OrmRecord<Track>
{
public:
    static const QSqlRecord sColumns;
    static QString const sTableName;
    static const int sTableColCount;
    static const QString CONFERENCEID;
    static const QString NAME;
public:
    int id() const { return value("id").toInt(); }
    void setId(int id) { setValue("id", id); }
    int conferenceid() const { return value("xid_conference").toInt(); }
    void setConference(int conferenceid) { setValue("xid_conference", conferenceid); }
    QString name() const { return value("name").toString(); }
    void setName(const QString & type) { setValue("name", type); }
    int insert();
public:
    static QList<Track> getAll();
    static Track retrieve(int id);
    static QString retrieveTrackName(int id);
    static Track retrieveByName(int conferenceid, QString name);
};

#endif /* TRACK_H_ */
