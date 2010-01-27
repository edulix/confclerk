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
};

#endif /* CONFERENCE_H */

