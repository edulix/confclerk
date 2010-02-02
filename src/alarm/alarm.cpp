#include "alarm.h"

#include <QDateTime>

#include <QApplication>
#include <QDir>
#include <QFileInfo>

//#include <dbus-1.0/dbus/dbus-protocol.h>

int Alarm::addAlarm(int aEventId, const QDateTime &aDateTime)
{
    cookie_t cookie = 0;
    alarm_event_t *eve = 0;
    alarm_action_t *act = 0;

    /* Create alarm event structure and set application identifier */
    eve = alarm_event_create();
    alarm_event_set_alarm_appid(eve, APPID);

    /* for Deleting purposes */
    alarm_event_set_message(eve, QString::number(aEventId).toLocal8Bit().data());

    /* Use absolute time triggering */
    eve->alarm_time = aDateTime.toTime_t();
    eve->flags = ALARM_EVENT_BOOT;

    /* Add exec command action */
    act = alarm_event_add_actions(eve, 1);
    alarm_action_set_label(act, "FOSDEM'10");

    QFileInfo fi(*qApp->argv());
    QString name(fi.fileName());

    QString command = QDir::currentPath() + "/" + name + QString(" %1").arg(QString::number(aEventId));
    //QString command =  *qApp->argv() + QString(" %1").arg(QString::number(aEventId));
    alarm_action_set_exec_command(act, command.toLocal8Bit().data());
    act->flags |= ALARM_ACTION_TYPE_EXEC;
    act->flags |= ALARM_ACTION_WHEN_RESPONDED;
    act->flags |= ALARM_ACTION_EXEC_ADD_COOKIE; // adds assigned cookie at the end of command string

//    // setup this action to be a "DBus command"
//    act->flags |= ALARM_ACTION_WHEN_RESPONDED;
//    act->flags |= ALARM_ACTION_TYPE_DBUS;
//
//    // DBus params for this action
//    alarm_action_set_dbus_interface(act, "org.fosdem.schedule.AlarmInterface");
//    alarm_action_set_dbus_service(act, "org.fosdem.schedule");
//    alarm_action_set_dbus_path(act, "/Fosdem");
//    alarm_action_set_dbus_name(act, "Alarm");
//
//    // DBus arguments for the action
//    alarm_action_set_dbus_args(act,  DBUS_TYPE_INT32, &aEventId, DBUS_TYPE_INVALID);

    //    act->flags |= ALARM_ACTION_TYPE_EXEC;
    //     alarm_action_set_exec_command(act, command.toLocal8Bit().data());
    //    alarm_event_set_icon(eve, "fosdem");
    //    alarm_event_set_title(eve, "FOSDEM'10");
    // adds assigned cookie at the end of command string
    //    act->flags |= ALARM_ACTION_EXEC_ADD_COOKIE;

    /* Add stop button action */
    /* TODO: send a DBus message to remove that alarm from database */
    act = alarm_event_add_actions(eve, 1);
    alarm_action_set_label(act, "Stop");
    act->flags |= ALARM_ACTION_WHEN_RESPONDED;
    act->flags |= ALARM_ACTION_TYPE_NOP;

    /* Add snooze button action */
    act = alarm_event_add_actions(eve, 1);
    alarm_action_set_label(act, "Snooze");
    act->flags |= ALARM_ACTION_WHEN_RESPONDED;
    act->flags |= ALARM_ACTION_TYPE_SNOOZE;

    /* Send the alarm to alarmd */
    cookie = alarmd_event_add(eve);

    // adding alarm failed
    if (cookie == 0)
        emit(addAlarmFailed(aEventId));
    else
        emit(alarmAdded(aEventId));

    /* Free all dynamic memory associated with the alarm event */
    alarm_event_delete(eve);

    return cookie;
}

void Alarm::deleteAlarm(int aEventId)
{
    cookie_t *list = 0;
    cookie_t cookie = 0;
    alarm_event_t *event = 0;

    // query the APPID's list of alarms
    if( (list = alarmd_event_query(0,0, 0,0, APPID)) != 0 ) // query OK
    {
        for( int i = 0; (cookie = list[i]) != 0; ++i )
        {
            alarm_event_delete(event);

            // get the event for specified alarm cookie (alarmId)
            if( (event = alarmd_event_get(cookie)) == 0 )
            {
                // should we inform user about it ???
                continue;
            }

            if(aEventId==atoi(alarm_event_get_message(event)))
            {
                // delete cookie
                if( alarmd_event_del(cookie) == -1 )
                {
                    // was not able to delete alarm for given aEventId
                    emit(deleteAlarmFailed(aEventId));
                    break;
                }
                else
                {
                    emit(alarmDeleted(aEventId));
                    break;
                }
            }
        }
    }
    else
    {
        // query failed
    }

    free(list);
    alarm_event_delete(event);
}

bool Alarm::hasEventAlarm(int aEventId)
{
    cookie_t *list = 0;
    cookie_t cookie = 0;
    alarm_event_t *event = 0;

    bool eventHasAlarm = false;

    // query the APPID's list of alarms
    if( (list = alarmd_event_query(0,0, 0,0, APPID)) != 0 ) // query OK
    {
        for( int i = 0; (cookie = list[i]) != 0; ++i )
        {
            alarm_event_delete(event);

            // get the event for specified alarm cookie (alarmId)
            if( (event = alarmd_event_get(cookie)) == 0 )
            {
                // should we inform user about it ???
                continue;
            }

            if(aEventId==atoi(alarm_event_get_message(event)))
            {
                eventHasAlarm = true;
                break;
            }
        }
    }
    else
    {
        // query failed
    }

    free(list);
    alarm_event_delete(event);

    return eventHasAlarm;
}

