/*
 * Copyright (C) 2010 Ixonos Plc.
 * Copyright (C) 2011-2012 Philipp Spitzer, gregor herrmann
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
#include "eventmodel.h"
#include <conference.h>
#include <track.h>
#include <room.h>

const QString EventModel::COMMA_SEPARATOR = ", ";

EventModel::EventModel()
{ }


void EventModel::Group::setTitle(const QList<Event>& mEvents) {
    QTime startTime = mEvents.at(mFirstEventIndex).start().time();
    QTime endTime(0, 0);
    for (int i = mFirstEventIndex; i != mFirstEventIndex + mChildCount; ++i) {
        endTime = qMax(mEvents.at(i).start().time().addSecs(mEvents.at(i).duration()), endTime);
    }
    mTitle = QString("%1 - %2").arg(startTime.toString("HH:mm")).arg(endTime.toString("HH:mm"));
}


// We want to group the events into "time slots/time groups" that
// should start at full hours and have the duration of either
// one hour or (if less than 3 events are in one time slot)
// multiple of one hour.
void EventModel::createTimeGroups()
{
    mGroups.clear();
    mParents.clear();
    if (mEvents.empty()) return;

    const int minTimeSpan = 3600; // one hour // minimum duration of a group
    const int minChildCount = 3;  // minimum number of events in one group

    // Create the first time group. The events have to be sorted by start time at this point!
    //    Remarks for the following non-comment line:
    //    * As it is right now it could be written as
    //      QDateTime groupStartDateTime = mEvents.first().start();
    //    * Before r1444 the minutes were set to zero so that the time groups started at
    //      whole hours.

    // QDateTime groupStartDateTime(mEvents.first().start().date(), QTime(mEvents.first().start().time().hour(), 0));
    QDateTime groupStartDateTime = mEvents.first().start();
    QDateTime groupEndDateTime = groupStartDateTime.addSecs(mEvents.first().duration());
    mGroups << EventModel::Group("", 0);
    int timeSpan = minTimeSpan;

    for (int i = 0; i != mEvents.count(); ++i) {
        QDateTime eventStartDateTime = mEvents.at(i).start();
        QDateTime eventEndDateTime = eventStartDateTime.addSecs(mEvents.at(i).duration());

        if (eventStartDateTime >= groupStartDateTime.addSecs(timeSpan)) {
            // a new group could be necessary
            if (mGroups.last().mChildCount < minChildCount) {
                // too few events in the group => no new group
                // except a gap in time would occur that is longer than minTimeSpan
                QDateTime prevEventStartDateTime = mEvents.at(i).start();
                if (i > 0 && qMax(prevEventStartDateTime.addSecs(mEvents.at(i-1).duration()), groupEndDateTime).secsTo(eventStartDateTime) < minTimeSpan) {
                    timeSpan += minTimeSpan;
                    --i;
                    continue; // repeat with the same event
                }
            }

            // a new group is necessary
            mGroups.last().setTitle(mEvents);
            groupStartDateTime = groupStartDateTime.addSecs(timeSpan);
            groupEndDateTime = groupStartDateTime.addSecs(mEvents.at(i).duration());
            mGroups << EventModel::Group("", i);
            timeSpan = minTimeSpan;
        }

        // insert event into current group
        mParents[mEvents.at(i).id()] = mGroups.count() - 1;
        mGroups.last().mChildCount += 1;
        groupEndDateTime = qMax(eventEndDateTime, groupEndDateTime);
    }

    // the last group needs a title as well
    mGroups.last().setTitle(mEvents);

    reset();
}

void EventModel::createTrackGroups() {
    mGroups.clear();
    mParents.clear();
    if (mEvents.empty())
    {
        return;
    }
    int trackId = mEvents.first().trackId();

    mGroups << EventModel::Group(Track::retrieveTrackName(trackId), 0);
    int nextTrackId = trackId;

    for (int i=0; i<mEvents.count(); i++)
    {
        trackId = mEvents.at(i).trackId();
        if (nextTrackId != trackId)
        {
            mGroups.last().mChildCount = i - mGroups.last().mFirstEventIndex;
            mGroups << EventModel::Group(Track::retrieveTrackName(trackId), i);
            nextTrackId = trackId;
        }
        // add parent-child relation
        mParents[mEvents.at(i).id()] = mGroups.count() - 1;
    }
    mGroups.last().mChildCount = mEvents.count() - mGroups.last().mFirstEventIndex;
}

void EventModel::createRoomGroups()
{
    mGroups.clear();
    mParents.clear();
    if (mEvents.empty())
    {
        return;
    }
    int roomId = mEvents.first().roomId();

    mGroups << EventModel::Group(Room::retrieveRoomName(roomId), 0);
    int nextRoomId = roomId;

    QList<Event>::iterator event = mEvents.begin();
    int i = 0;
    while (event != mEvents.end())
    {
        roomId = event->roomId();
        if (nextRoomId != roomId)
        {
            mGroups.last().mChildCount = i - mGroups.last().mFirstEventIndex;
            mGroups << EventModel::Group(Room::retrieveRoomName(roomId), i);
            nextRoomId = roomId;
        }
        mParents[event->id()] = mGroups.count() - 1;
        event++;
        i++;
    }
    mGroups.last().mChildCount = mEvents.count() - mGroups.last().mFirstEventIndex;
}

QVariant EventModel::data(const QModelIndex& index, int role) const
{
    if (index.isValid() && role == Qt::DisplayRole)
    {
        if (index.internalId() == 0)
        {
            return mGroups.at(index.row()).mTitle;
        }
        else //event data
        {
            return static_cast<Event*>(index.internalPointer())->id();
        }
    }

    return QVariant();
}

QModelIndex EventModel::index(int row, int column, const QModelIndex& parent) const
{
    // TODO: add checks for out of range rows

    if (!parent.isValid())
    {
        return createIndex(row, column, 0);
    }
    else if (parent.internalId() == 0)
    {
        const Group& group = mGroups.at(parent.row());
        Event* event = const_cast<Event*>(&mEvents.at(row + group.mFirstEventIndex));
        return createIndex(row, column, reinterpret_cast<void*>(event));
    }
    else
    {
        return QModelIndex();
    }
}

QModelIndex EventModel::parent(const QModelIndex & index) const
{
    if (index.isValid())
    {
        if (index.internalId() == 0)
        {
            return QModelIndex();
        }

        Event * event = static_cast<Event*>(index.internalPointer());

        return createIndex(mParents[event->id()], 0, 0);
    }

    return QModelIndex();
}

int EventModel::columnCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return 1;
}

int EventModel::rowCount (const QModelIndex & parent) const
{
    if (!parent.isValid())
    {
        return mGroups.count();
    }

    if (parent.internalId() == 0)
    {
        return mGroups.at(parent.row()).mChildCount;
    }

    return 0;
}

void EventModel::clearModel()
{
    mGroups.clear();
    mEvents.clear();
    mParents.clear();

    reset();
}

void EventModel::loadEvents(const QDate &aDate, int aConferenceId)
{
    clearModel();
    // check for existence of the conference in the DB
    if(Conference::getAll().count())
    {
        mEvents = Event::getByDate(QDate(aDate.year(), aDate.month(), aDate.day()), aConferenceId, "start, duration");
    }
    createTimeGroups();
}

void EventModel::loadFavEvents(const QDate &aDate, int aConferenceId)
{
    clearModel();
    // check for existence of the conference in the DB
    if(Conference::getAll().count())
    {
        mEvents = Event::getFavByDate(QDate(aDate.year(), aDate.month(), aDate.day()), aConferenceId);
    }
    createTimeGroups();
}

int EventModel::loadSearchResultEvents(const QDate &aDate, int aConferenceId)
{
    clearModel();
    // check for existence of the conference in the DB
    if(Conference::getAll().count())
    {
        try{
            mEvents = Event::getSearchResultByDate(QDate(aDate.year(), aDate.month(), aDate.day()), aConferenceId, "start, duration");
        }
        catch( OrmException &e  ){
            qDebug() << "Event::getSearchResultByDate failed: " << e.text();
        }
        catch(...){
            qDebug() << "Event::getSearchResultByDate failed";
        }

    }

    createTimeGroups();

    return mEvents.count();
}

void EventModel::loadEventsByTrack(const QDate &aDate, int aConferenceId)
{
    clearModel();
    if (Conference::getAll().count())
    {
        mEvents = Event::getByDate(QDate(aDate.year(), aDate.month(), aDate.day()), aConferenceId, "xid_track, start, duration");
    }
    createTrackGroups();
}

void EventModel::loadEventsByRoom(const QDate &aDate, int aConferenceId)
{
    clearModel();
    if (Conference::getAll().count())
    {
        mEvents = Event::getByDateAndRoom(QDate(aDate.year(), aDate.month(), aDate.day()), aConferenceId);
    }
    createRoomGroups();
}


void EventModel::loadConflictEvents(int aEventId, int aConferenceId) {
    clearModel();
    // check for existence of the conference in the DB
    if(Conference::getAll().count())
    {
        mEvents = Event::conflictEvents(aEventId, aConferenceId);
    }
    createTimeGroups();
}

void EventModel::updateModel(int aEventId)
{
    for(int i=0; i<mEvents.count(); i++)
    {
        if(mEvents[i].id() == aEventId)
            mEvents[i] = Event::getById(aEventId,Conference::activeConference());
    }

    // find the ModelIndex for given aEventId
    for(int i=0; i<mGroups.count(); i++)
    {
        QModelIndex groupIndex = index(i,0,QModelIndex());
        for(int j=0; j<mGroups[i].mChildCount; j++)
        {
            QModelIndex eventIndex = index(j,0,groupIndex);
            if(static_cast<Event*>(eventIndex.internalPointer())->id() == aEventId)
            {
                emit(dataChanged(groupIndex,groupIndex));
                emit(dataChanged(eventIndex,eventIndex));
            }
        }
    }
}

