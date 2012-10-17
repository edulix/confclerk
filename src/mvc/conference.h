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
#ifndef CONFERENCE_H
#define CONFERENCE_H

#include <QDateTime>
#include <QVector>
#include <QStringList>

#include "ormrecord.h"

class Conference : public OrmRecord<Conference>
{
public:
    static QSqlRecord const sColumns;
    static QString const sTableName;

public:
    static Conference getById(int id);
    static QList<Conference> getAll();

    /// Returns the active conference. If no active conference can be found, it returns the conference with the lowest id.
    /// If no conference exists or database errors occur, it returns -1.
    static int activeConference();

public:
    int id() const { return value("id").toInt(); }
    QString title() const { return value("title").toString(); }
    QString subtitle() const { return value("subtitle").toString(); }
    QString venue() const { return value("venue").toString(); }
    QString city() const { return value("city").toString(); }
    QDate start() const { return value("start").toDate(); }
    QDate end() const { return value("end").toDate(); }
    int dayChange() const { return value("day_change").toInt(); } // in seconds from 00:00
    int timeslotDuration() const { return value("timeslot_duration").toInt(); } // in seconds
    bool isActive() const { return value("active").toBool(); }
    QString url() const { return stringFromNullable(value("url")); }

    void setUrl(const QString& url)
    {
        setValue("url", url.isNull() ? QVariant() : url);
        update("url");
    }

private:
    static QString stringFromNullable(const QVariant& v)
    {
        if (v.isValid()) {
            return v.toString();
        } else {
            return QString();
        }
    }
};

#endif /* CONFERENCE_H */

