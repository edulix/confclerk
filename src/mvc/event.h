#ifndef EVENT_H
#define EVENT_H

#include <QDateTime>
#include <QVector>
#include <QStringList>

#include <ormrecord.h>

/**
  NoSuchEventException is thrown when required event does not exist.
*/
class NoSuchEventException
{
};

class Event : public OrmRecord<Event>
{
public:
    static const QSqlRecord sColumns;
    //static QString const sTableName;
    static const QString sTable1Name;
    static const QString sTable2Name;
    static const int sTable1ColCount;
    static const int sTable2ColCount;
    static const QString XID_ACTIVITY;
    static const QString START;
public:
    static Event getById(int id, int conferenceId);
    static QList<Event> getByDate(const QDate & date, int conferenceId, QString orderBy);
    static QList<Event> getFavByDate(const QDate & date, int conferenceId); // get Favourities by Date
public:
    // Table 1
    int id() const { return value("id").toInt(); }
    int conferenceId() const { return value("xid_conference").toInt(); }
    QDateTime start() const { return value(START).toDateTime(); }
    int duration() const { return value("duration").toInt(); }
    int activityId() const { return value(XID_ACTIVITY).toInt(); }
    QString type() const { return value("type").toString(); }
    QString language() const { return value("language").toString(); }
    bool isFavourite() const { return value("favourite").toBool(); }
    bool hasAlarm() const { return value("alarm").toBool(); }
    // Table 2 : virtual table for FTS (Full Text Search)
    QString tag() const { return value("tag").toString(); }
    QString title() const { return value("title").toString(); }
    QString subtitle() const { return value("subtitle").toString(); }
    QString abstract() const { return value("abstract").toString(); }
    QString description() const { return value("description").toString(); }

    // Table 1
    void setId(int id) { setValue("id", id); }
    void setConferenceId(int conferenceId) { setValue("xid_conference", conferenceId); }
    void setStart(const QDateTime & start) { setValue(START, start); }
    void setDuration(int duration) { setValue("duration", duration); }
    void setActivityId(int activityId) { setValue(XID_ACTIVITY, activityId); }
    void setType(const QString & type) { setValue("type", type); }
    void setLanguage(const QString & language) { setValue("language", language); }
    void setFavourite(bool favourite) { setValue("favourite", (int)((favourite))); }
    void setHasAlarm(bool alarm) { setValue("alarm", (int)((alarm))); }
    // Table 2 : virtual table for FTS (Full Text Search)
    void setTag(const QString& tag) { setValue("tag", tag); }
    void setTitle(const QString& title) { setValue("title", title); }
    void setSubtitle(const QString& subtitle) { setValue("subtitle", subtitle); }
    void setAbstract(const QString& abstract) { setValue("abstract", abstract); }
    void setDescription(const QString& description) { setValue("description", description); }

friend class EventTest;
};

#endif // EVENT_H

