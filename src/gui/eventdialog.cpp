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
#include "eventdialog.h"
#include "conference.h"

#include <QScrollBar>

#ifdef MAEMO
#include "alarm.h"
#endif

EventDialog::EventDialog(int conferenceId, int eventId, QWidget *parent): QDialog(parent), mConferenceId(conferenceId), mEventId(eventId) {
    setupUi(this);

#ifdef MAEMO
    showFullScreen();
#else
    alarmButton->hide();
#endif

    Event event = Event::getById(mEventId, mConferenceId);

    title->setText(event.title());
    persons->setText(event.persons().join(" and "));
    abstract->setText(event.abstract());
    description->setText(event.description());
    QStringList linksText = static_cast<QStringList>(event.links().values());
    for (QStringList::iterator linkIterator = linksText.begin(); linkIterator != linksText.end(); ++linkIterator)
        *linkIterator = QString("<a href=\"%1\">%1</a>").arg(*linkIterator);
    links->setText(linksText.join("<br/>"));

    connect(favouriteButton, SIGNAL(clicked()), SLOT(favouriteClicked()));
    connect(alarmButton, SIGNAL(clicked()), SLOT(alarmClicked()));

    if(event.isFavourite())
    {
        favouriteButton->setIcon(QIcon(":/icons/favourite-on.png"));
    }

    if(event.hasAlarm())
    {
        alarmButton->setIcon(QIcon(":/icons/alarm-on.png"));
    }
}

void EventDialog::favouriteClicked()
{
    Event event = Event::getById(mEventId, mConferenceId);

    QList<Event> conflicts = Event::conflictEvents(event.id(), mConferenceId);
    if(event.isFavourite())
    {
        event.setFavourite(false);
        favouriteButton->setIcon(QIcon(":/icons/favourite-off.png"));
    }
    else
    {
        event.setFavourite(true);
        favouriteButton->setIcon(QIcon(":/icons/favourite-on.png"));
    }
    event.update("favourite");

    if(event.isFavourite())
    {
        // event has became 'favourite' and so 'conflicts' list may have changed
        conflicts = Event::conflictEvents(event.id(), mConferenceId);
    }

    // have to emit 'eventChanged' signal on all events in conflict
    for(int i=0; i<conflicts.count(); i++)
        emit eventChanged(conflicts[i].id(), false);

    // since the Favourite icon has changed, update TreeViews accordingly
    // all TreeViews have to listen on this signal
    emit eventChanged(event.id(), true);
}

void EventDialog::alarmClicked()
{
    Event event = Event::getById(mEventId, mConferenceId);

    if(event.hasAlarm())
    {
        event.setHasAlarm(false); // update DB
        alarmButton->setIcon(QIcon(":/icons/alarm-off.png"));
#ifdef MAEMO
        // remove alarm from the 'alarmd' alrms list
        Alarm alarm;
        alarm.deleteAlarm(event.conferenceId(), event.id());
        // TODO: test if removing was successfull
#endif /* MAEMO */
    }
    else
    {
        event.setHasAlarm(true);
        alarmButton->setIcon(QIcon(":/icons/alarm-on.png"));
#ifdef MAEMO
        // add alarm to the 'alarmd'
        Alarm alarm;
        alarm.addAlarm(event.conferenceId(), event.id(), event.title(), event.start().addSecs(PRE_EVENT_ALARM_SEC));
#endif /* MAEMO */
    }
    event.update("alarm");
    // since the Alarm icon has changed, update TreeView accordingly
    // all TreeViews have to listen on this signal
    emit eventChanged(event.id(), false);
}

