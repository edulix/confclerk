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
#include "calendar.h"
#include <qdebug.h>
#include <qvariant.h>

#include <calendar-backend/CMulticalendar.h>
#include <calendar-backend/CCalendar.h>
#include <calendar-backend/CEvent.h>
#include <calendar-backend/CAlarm.h>

Calendar::Calendar():
m_pMultiCalendar(0),
m_pCalendar(0)
{
	m_pMultiCalendar = CMulticalendar::MCInstance();

	if(m_pMultiCalendar != NULL)
		m_pCalendar  = m_pMultiCalendar->getSynchronizedCalendar();

}

Calendar::~Calendar()
{
	delete m_pCalendar;
	delete m_pMultiCalendar;
}

int Calendar::addCalendarEvent(QString summary, QString description, QString location, uint dateStart, uint  dateEnd, int eventId)
{
	int errorCode = 0;

	if(m_pMultiCalendar == NULL)
		return 0;

	if(m_pCalendar == NULL)
		return 0;

	// create event
	CEvent event(summary.toStdString(), description.toStdString(), location.toStdString(),  dateStart, dateEnd);

	// create alarm
	CAlarm alarm;
	alarm.setTrigger(dateStart - 15 * 60);
	alarm.setRepeat(1);
	alarm.setDuration(3);
	alarm.setAction(0);
	alarm.setAttach(QString::number(eventId).toLocal8Bit().data());

	// add alarm to event
	event.setAlarm(&alarm);

	// register event into calendar
	m_pMultiCalendar->addEvent(&event,m_pCalendar->getCalendarId(),errorCode);

    return errorCode;
}

void Calendar::deleteCalendarEvent(uint dateStart, uint dateEnd, int eventId)
{
	int errorCode = 0;

	vector< CComponent * > components;

	// get all events
	components = m_pMultiCalendar->getComponents(m_pCalendar->getCalendarId(), 1, dateStart, dateEnd, errorCode);

	for (vector<CComponent *>::iterator it = components.begin();it!=components.end(); ++it)
	{
		// get alarm properties
		if( (*it)->getAlarmProperties() == true)
		{
			CAlarm * pAlarm = (*it)->getAlarm();

			bool converted = false;
			int tempId = QVariant(pAlarm->getAttach().data()).toInt(&converted);

			// check event id
			if(converted == true)
				if(tempId == eventId)
				{
					//delete event
					m_pCalendar->deleteComponent((*it)->getId(),errorCode);
					break;
				}
		}
	}
}

bool Calendar::hasCalendarEvent(int eventId)
{
	bool ret = false;
	int errorCode = 0;

	vector< CEvent * > events;

	// get all events
	events = m_pCalendar->getEvents(errorCode);

	if(events.size() > 0)
	{
		for (vector<CEvent *>::iterator it = events.begin(); it!=events.end(); ++it)
		{
			// get alarm properties
			if( (*it)->getAlarmProperties() == true)
			{
				CAlarm * pAlarm = (*it)->getAlarm();

				bool converted = false;
				int tempId = QVariant(pAlarm->getAttach().data()).toInt(&converted);

				// check event id
				if(converted == true)
					if(tempId == eventId)
					{
						ret = true;
						break;
					}
			}
		}
	}
}
