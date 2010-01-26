#ifndef CALENDAR_H
#define CALENDAR_H

#include <QObject>
#include <QDateTime>

class CMulticalendar;
class CCalendar;

class Calendar : public QObject
{
    Q_OBJECT
    public:
    	Calendar();
        ~Calendar();
        int addCalendarEvent(QString summary, QString description, QString location, uint dateStart, uint dateEnd, int eventId);
        void deleteCalendarEvent(uint dateStart, uint dateEnd, int eventId);
        bool hasCalendarEvent(int eventId);

        CMulticalendar * m_pMultiCalendar;
        CCalendar * m_pCalendar;
//    signals:
//        void alarmAdded(int aEventId);
//        void addAlarmFailed(int aEventId);
//        void alarmDeleted(int aEventId);
//        void deleteAlarmFailed(int aEventId);
};

#endif /* CALENDAR_H */
