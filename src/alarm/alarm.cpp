#include "alarm.h"

#include <QDateTime>

int Alarm::addAlarm(int aEventId, const QDateTime &aDateTime)
{
    cookie_t cookie = 0;
    alarm_event_t *event = 0;
    alarm_action_t *action = 0;

    /* Create alarm event structure and set application identifier */
    event = alarm_event_create();
    alarm_event_set_alarm_appid(event, APPID);
    alarm_event_set_message(event, QString::number(aEventId).toLocal8Bit().data()); // for Deleting purposes

    /* Use absolute time triggering */
    event->alarm_time = aDateTime.toTime_t();

    /* Add exec command action */
    action = alarm_event_add_actions(event, 1);
    QString command = QString("/home/maemo/work/fosdem-maemo/bin/fosdem %1").arg(QString::number(aEventId));
    alarm_action_set_exec_command(action, command.toLocal8Bit().data());
    action->flags |= ALARM_ACTION_TYPE_EXEC;
    action->flags |= ALARM_ACTION_WHEN_TRIGGERED;
    action->flags |= ALARM_ACTION_EXEC_ADD_COOKIE; // adds assigned cookie at the end of command string

    /* Send the alarm to alarmd */
    cookie = alarmd_event_add(event);
    if(cookie==0) // adding alarm failed
        emit(addAlarmFailed(aEventId));
    else
        emit(alarmAdded(aEventId));

    /* Free all dynamic memory associated with the alarm event */
    alarm_event_delete(event);

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

