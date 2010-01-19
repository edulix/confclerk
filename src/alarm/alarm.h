#ifndef ALARM_H
#define ALARM_H

#include <QObject>
#include <QDateTime>

extern "C"
{
#include <alarmd/libalarm.h>
}

#define APPID "fosdem-alarm"

class Alarm : public QObject
{
    Q_OBJECT
    public:
        Alarm() {}
        ~Alarm() {}
        int addAlarm(int aEventId, const QDateTime &aDateTime); 
        void deleteAlarm(int aEventId);
        static bool hasEventAlarm(int aEventId);
    signals:
        void alarmAdded(int aEventId);
        void addAlarmFailed(int aEventId);
        void alarmDeleted(int aEventId);
        void deleteAlarmFailed(int aEventId);
};

#endif /* ALARM_H */

