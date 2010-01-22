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
    static QString const sTableName;
public:
    static Event getById(int id, int conferenceId);
    static QList<Event> getByDate(const QDate & date, int conferenceId, QString orderBy);
    static QList<Event> getFavByDate(const QDate & date, int conferenceId); // get Favourities by Date
    static QList<Event> getSearchResultByDate(const QDate& date, int conferenceId, QString orderBy);
    static QList<Event> nowEvents(int conferenceId, QString orderBy); // get events scheduled NOW
public:
    int id() const { return value("id").toInt(); }
    int conferenceId() const { return value("xid_conference").toInt(); }
    QDateTime start() const { return value("start").toDateTime(); }
    int duration() const { return value("duration").toInt(); }
    int trackId() const { return value("xid_track").toInt(); }
    QString type() const { return value("type").toString(); }
    QString language() const { return value("language").toString(); }
    bool isFavourite() const { return value("favourite").toBool(); }
    bool hasAlarm() const { return value("alarm").toBool(); }
    bool hasTimeConflict() const { return true; /*return value("warning").toBool()*/; } //TODO
    QString tag() const { return value("tag").toString(); }
    QString title() const { return value("title").toString(); }
    QString subtitle() const { return value("subtitle").toString(); }
    QString abstract() const { return value("abstract").toString(); }
    QString description() const { return value("description").toString(); }
    // records from other tables associated with 'id'
    QString room() const;
    QStringList persons() const;

    void setId(int id) { setValue("id", id); }
    void setConferenceId(int conferenceId) { setValue("xid_conference", conferenceId); }
    void setStart(const QDateTime & start) { setValue("start", start); }
    void setDuration(int duration) { setValue("duration", duration); }
    void setTrackId(int trackId) { setValue("xid_track", trackId); }
    void setType(const QString & type) { setValue("type", type); }
    void setLanguage(const QString & language) { setValue("language", language); }
    void setFavourite(bool favourite) { setValue("favourite", (int)((favourite))); }
    void setHasAlarm(bool alarm) { setValue("alarm", (int)((alarm))); }
    void setTag(const QString& tag) { setValue("tag", tag); }
    void setTitle(const QString& title) { setValue("title", title); }
    void setSubtitle(const QString& subtitle) { setValue("subtitle", subtitle); }
    void setAbstract(const QString& abstract) { setValue("abstract", abstract); }
    void setDescription(const QString& description) { setValue("description", description); }
    // records from other tables associated with 'id'
    void setRoom(const QString& room);
    void setPersons(const QStringList &persons);

friend class EventTest;
};

#endif // EVENT_H

