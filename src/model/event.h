#ifndef EVENT_H
#define EVENT_H

#include <QDateTime>

class Event
{
public:
    static Event getById(int id, int conferenceId);

public:
    int id() const { return mId; }
    int conferenceId() const { return mConferenceId; }
    QDateTime start() const { return mStart; }
    int duration() const { return mDuration; }
    int activityId() const { return mActivityId; }
    int typeId() const { return mTypeId; }
    int languageId() const { return mLanguageId; }

private:
    Event() {}; // private constructor, use static methods to access instances

private:
    int mId;
    int mConferenceId;
    QDateTime mStart;
    int mDuration;
    int mActivityId;
    int mTypeId;
    int mLanguageId;
};

#endif // EVENT_H
