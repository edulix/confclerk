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
#include "eventdialog.h"
#include <conference.h>

#include <QScrollBar>

#ifdef MAEMO
#include <alarm.h>
#endif

EventDialog::EventDialog(const int &aEventId, QWidget *aParent)
    : QDialog(aParent)
    , mEventId(aEventId)
{
    setupUi(this);

#ifdef MAEMO
    showFullScreen();
#else
    alarmButton->hide();
#endif

    Event event = Event::getById(mEventId,Conference::activeConference());

    title->setText(event.title());
    persons->setText(event.persons().join(" and "));
    abstract->setText(event.abstract());
    description->setText(event.description());
    links->setText(static_cast<QStringList>(event.links().values()).join("\n"));

    connect(favouriteButton, SIGNAL(clicked()), SLOT(favouriteClicked()));
    connect(alarmButton, SIGNAL(clicked()), SLOT(alarmClicked()));

    if(event.isFavourite())
    {
        favouriteButton->setIcon(QIcon(":/icons/favourite-onBig.png"));
    }

    if(event.hasAlarm())
    {
        alarmButton->setIcon(QIcon(":/icons/alarm-onBig.png"));
    }
}

void EventDialog::favouriteClicked()
{
    Event event = Event::getById(mEventId,Conference::activeConference());

    QList<Event> conflicts = Event::conflictEvents(event.id(),Conference::activeConference());
    if(event.isFavourite())
    {
        event.setFavourite(false);
        favouriteButton->setIcon(QIcon(":/icons/favourite-offBig.png"));
    }
    else
    {
        event.setFavourite(true);
        favouriteButton->setIcon(QIcon(":/icons/favourite-onBig.png"));
    }
    event.update("favourite");

    if(event.isFavourite())
    {
        // event has became 'favourite' and so 'conflicts' list may have changed
        conflicts = Event::conflictEvents(event.id(),Conference::activeConference());
    }

    qDebug() << " FAVOURITE [" << event.id() << "] -> " << event.isFavourite();

    // have to emit 'eventHasChanged' signal on all events in conflict
    for(int i=0; i<conflicts.count(); i++)
        emit(eventHasChanged(conflicts[i].id()));

    // since the Favourite icon has changed, update TreeViews accordingly
    // all TreeViews have to listen on this signal
    emit(eventHasChanged(event.id(),true));
}

void EventDialog::alarmClicked()
{
    Event event = Event::getById(mEventId,Conference::activeConference());

    if(event.hasAlarm())
    {
        event.setHasAlarm(false); // update DB
        alarmButton->setIcon(QIcon(":/icons/alarm-offBig.png"));
#ifdef MAEMO
        // remove alarm from the 'alarmd' alrms list
        Alarm alarm;
        alarm.deleteAlarm(event.id());
        // TODO: test if removing was successfull
#endif /* MAEMO */
    }
    else
    {
        event.setHasAlarm(true);
        alarmButton->setIcon(QIcon(":/icons/alarm-onBig.png"));
#ifdef MAEMO
        // add alarm to the 'alarmd'
        Alarm alarm;
        int cookie = alarm.addAlarm(event.id(),QDateTime::currentDateTime().addSecs(10));
        qDebug() << "cookie: " << cookie;
#endif /* MAEMO */
    }
    event.update("alarm");
    qDebug() << " ALARM [" << event.id() << "] -> " << event.hasAlarm();
    // since the Alarm icon has changed, update TreeView accordingly
    // all TreeViews have to listen on this signal
    emit(eventHasChanged(event.id()));
}

