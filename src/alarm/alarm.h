/*
 * Copyright (C) 2010 Ixonos Plc.
 * Copyright (C) 2011-2012 Philipp Spitzer, gregor herrmann, Stefan Stahl
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

#define APPID "confclerk-alarm"
const int PRE_EVENT_ALARM_SEC = -15*60; // alarm goes off 15 minutes before start of event

class Alarm : public QObject
{
    Q_OBJECT
    public:
        Alarm() {}
        ~Alarm() {}
        int addAlarm(int conferenceId, int eventId, QString eventTitle, const QDateTime& alarmDateTime);
        void deleteAlarm(int conferenceId, int eventId);
};

#endif /* ALARM_H */

