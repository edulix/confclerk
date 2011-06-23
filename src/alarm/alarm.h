/*
 * Copyright (C) 2010 Ixonos Plc.
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

