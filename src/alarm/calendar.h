/*
 * Copyright (C) 2010 Ixonos Plc.
 *
 * This file is part of fosdem-schedule.
 *
 * fosdem-schedule is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 2 of the License, or (at your option)
 * any later version.
 *
 * fosdem-schedule is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * fosdem-schedule.  If not, see <http://www.gnu.org/licenses/>.
 */
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
