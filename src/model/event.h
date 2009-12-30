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
    static QSqlRecord const sColumns;
    static QString const sTableName;

public:
    static Event getById(int id, int conferenceId);

public:
    int id() const { return value("id").toInt(); }
    int conferenceId() const { return value("xid_conference").toInt(); }
    QDateTime start() const { return value("start").toDateTime(); }
    int duration() const { return value("duration").toInt(); }
    int activityId() const { return value("xid_activity").toInt(); }
    int typeId() const { return value("type").toInt(); }
    int languageId() const { return value("language").toInt(); }

    void setId(int id) { setValue("id", id); }
    void setConferenceId(int conferenceId) { setValue("xid_conference", conferenceId); }
    void setStart(const QDateTime& start) { setValue("start", start); }
    void setDuration(int duration) { setValue("duration", duration); }
    void setActivityId(int activityId) { setValue("xid_activity", activityId); }
    void setTypeId(int typeId) { setValue("type", typeId); }
    void setLanguageId(int languageId) { setValue("language", languageId); }

friend class EventTest;
};



#endif // EVENT_H
