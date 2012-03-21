/*
 * Copyright (C) 2010 Ixonos Plc.
 * Copyright (C) 2011 Philipp Spitzer, gregor herrmann
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
#include "alarm.h"

#include <QDateTime>

#include <QApplication>
#include <QDir>
#include <QFileInfo>

#include <QDebug>

//#include <dbus-1.0/dbus/dbus-protocol.h>

int Alarm::addAlarm(int conferenceId, int eventId, QString eventTitle, const QDateTime &alarmDateTime) {
    cookie_t alarmCookie = 0;
    alarm_event_t *alarmEvent = 0;
    alarm_action_t *alarmAction = 0;

    /* Create alarm event structure and set application identifier */
    alarmEvent = alarm_event_create();
    alarm_event_set_alarm_appid(alarmEvent, APPID);

    // message
    alarm_event_set_title(alarmEvent, "ConfClerk");
    alarm_event_set_message(alarmEvent, eventTitle.toLocal8Bit().data());

    // for deleting purposes
    alarm_event_set_attr_int(alarmEvent, "conferenceId", conferenceId);
    alarm_event_set_attr_int(alarmEvent, "eventId", eventId);

    /* Use absolute time triggering */
    QDateTime local(alarmDateTime);
    local.setTimeSpec(Qt::LocalTime);

    alarmEvent->alarm_time = local.toTime_t();
    alarmEvent->flags = ALARM_EVENT_BOOT;

    /* Add exec command action */
    alarmAction = alarm_event_add_actions(alarmEvent, 1);
    alarm_action_set_label(alarmAction, "ConfClerk");

    QString command = QFileInfo(*qApp->argv()).absoluteFilePath() + QString(" %1").arg(QString::number(eventId));
    qDebug() << "Setting alarm: " << command;
    alarm_action_set_exec_command(alarmAction, command.toLocal8Bit().data());
    alarmAction->flags |= ALARM_ACTION_TYPE_EXEC;
    alarmAction->flags |= ALARM_ACTION_WHEN_RESPONDED;
    alarmAction->flags |= ALARM_ACTION_EXEC_ADD_COOKIE; // adds assigned cookie at the end of command string

//    // setup this action to be a "DBus command"
//    act->flags |= ALARM_ACTION_WHEN_RESPONDED;
//    act->flags |= ALARM_ACTION_TYPE_DBUS;
//
//    // DBus params for this action
//    alarm_action_set_dbus_interface(act, "at.priv.toastfreeware.confclerk.AlarmInterface");
//    alarm_action_set_dbus_service(act, "at.priv.toastfreeware.confclerk");
//    alarm_action_set_dbus_path(act, "/ConfClerk");
//    alarm_action_set_dbus_name(act, "Alarm");
//
//    // DBus arguments for the action
//    alarm_action_set_dbus_args(act,  DBUS_TYPE_INT32, &aEventId, DBUS_TYPE_INVALID);

    //    act->flags |= ALARM_ACTION_TYPE_EXEC;
    //     alarm_action_set_exec_command(act, command.toLocal8Bit().data());
    //    alarm_event_set_icon(eve, "fosdem");
    //    alarm_event_set_title(eve, "ConfClerk");
    // adds assigned cookie at the end of command string
    //    act->flags |= ALARM_ACTION_EXEC_ADD_COOKIE;

    /* Add stop button action */
    /* TODO: send a DBus message to remove that alarm from database */
    alarmAction = alarm_event_add_actions(alarmEvent, 1);
    alarm_action_set_label(alarmAction, "Stop");
    alarmAction->flags |= ALARM_ACTION_WHEN_RESPONDED;
    alarmAction->flags |= ALARM_ACTION_TYPE_NOP;

    /* Add snooze button action */
    alarmAction = alarm_event_add_actions(alarmEvent, 1);
    alarm_action_set_label(alarmAction, "Snooze");
    alarmAction->flags |= ALARM_ACTION_WHEN_RESPONDED;
    alarmAction->flags |= ALARM_ACTION_TYPE_SNOOZE;

    /* Send the alarm to alarmd */
    alarmCookie = alarmd_event_add(alarmEvent);

    /* Free all dynamic memory associated with the alarm event */
    alarm_event_delete(alarmEvent);

    return alarmCookie;
}

void Alarm::deleteAlarm(int conferenceId, int eventId) {
    cookie_t *alarmList = 0;
    cookie_t alarmCookie = 0;
    alarm_event_t *alarmEvent = 0;

    // query the APPID's list of alarms
    if( (alarmList = alarmd_event_query(0,0, 0,0, APPID)) != 0) { // query OK
        for (int i = 0; (alarmCookie = alarmList[i]) != 0; ++i ) {
            // get the event for specified alarm cookie (alarmId)
            alarmEvent = alarmd_event_get(alarmCookie);
            Q_ASSERT(alarmEvent);

            bool found = (conferenceId == alarm_event_get_attr_int(alarmEvent, "conferenceId", -1) && eventId == alarm_event_get_attr_int(alarmEvent, "eventId", -1));
            if (found) alarmd_event_del(alarmCookie); // delete cookie
            alarm_event_delete(alarmEvent);
            if (found) break;
        }
    }
    free(alarmList);
}
