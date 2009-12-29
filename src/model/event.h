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

class Event : public OrmRecord <Event>
{
public:
    // column definition
    enum Column
    {
        Id = 0,
        Conference,
        Start,
        Duration,
        Activity,
        Type,
        Language
    };

    static QStringList const sColNames;

    static QString const sTableName;

public:
    static Event getById(int id, int conferenceId) { return Event(); } //EventTable::selectOne("id=1"); }

public:
    int id() const { return value(Id).toInt(); }
    int conferenceId() const { return value(Conference).toInt(); }
    QDateTime start() const { return value(Start).toDateTime(); }
    int duration() const { return value(Duration).toInt(); }
    int activityId() const { return value(Activity).toInt(); }
    int typeId() const { return value(Type).toInt(); }
    int languageId() const { return value(Language).toInt(); }

    void setId(int id) { setValue(Id, id); }
    void setConferenceId(int conferenceId) { setValue(Conference, conferenceId); }
    void setStart(const QDateTime& start) { setValue(Start, start); }
    void setDuration(int duration) { setValue(Duration, duration); }
    void setActivityId(int activityId) { setValue(Activity, activityId); }
    void setTypeId(int typeId) { setValue(Type, typeId); }
    void setLanguageId(int languageId) { setValue(Language, languageId); }
};



#endif // EVENT_H
