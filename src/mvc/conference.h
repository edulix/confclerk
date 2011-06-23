/*
 * Copyright (C) 2010 Ixonos Plc.
 * Copyright (C) 2011 Philipp Spitzer, gregor herrmann
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

#include <ormrecord.h>

class Conference : public OrmRecord<Conference>
{
public:
    static QSqlRecord const sColumns;
    static QString const sTableName;

public:
    static Conference getById(int id);
    static QList<Conference> getAll();
    static int activeConference();
    static void deleteConference(int id);

public:
    int id() const { return value("id").toInt(); }
    QString title() const { return value("title").toString(); }
    QString subtitle() const { return value("subtitle").toString(); }
    QString venue() const { return value("venue").toString(); }
    QString city() const { return value("city").toString(); }
    QDate start() const { return value("start").toDate(); }
    QDate end() const { return value("end").toDate(); }
    int days() const { return value("days").toInt(); }
    int dayChange() const { return value("day_change").toInt(); } // in seconds from 00:00
    int timeslotDuration() const { return value("timeslot_duration").toInt(); } // in seconds
    bool isActive() const { return value("active").toBool(); }
    QString url() const { return stringFromNullable(value("url")); }
    QString map() const { return stringFromNullable(value("map")); }

    #if 0
    void setId(int id) { setValue("id", id); }
    void setTitle(const QString& title) { setValue("title", title); }
    void setSubtitle(const QString& subtitle) { setValue("subtitle", subtitle); }
    void setVenue(const QString& venue) { setValue("venue", venue); }
    void setCity(const QString& city) { setValue("city", city); }
    void setStart(const QDate& start) { setValue("start", start); }
    void setEnd(const QDate& end) { setValue("end", end); }
    void setDays(int days) { setValue("days", days); }
    void setDayChange(int dayChange) { setValue("day_change", dayChange); }
    void setTimeslotDuration(int timeslotDuration) { setValue("timeslot_duration", timeslotDuration); }
    void setActive(bool active) { setValue("active", (int)((active))); }
    #endif
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

