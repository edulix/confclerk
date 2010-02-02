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
#include "eventmodel.h"
#include <conference.h>
#include <track.h>
#include <room.h>

const QString EventModel::COMMA_SEPARATOR = ", ";

EventModel::EventModel()
{
    mEvents.clear();
}

void EventModel::createTimeGroups()
{
    mGroups.clear();
    mParents.clear();

    if (mEvents.empty())
    {
        return;
    }

    const int timeSpan = 5400;

    QTime startTime = mEvents.first().start().time();
    mGroups << EventModel::Group(QString("%1 - %2").arg(startTime.toString("HH:mm"),
        startTime.addSecs(timeSpan).toString("HH:mm")), 0);
    QTime nextGroupTime = mEvents.first().start().time().addSecs(timeSpan);

    for (int i=0; i<mEvents.count(); i++)
    {
        QTime eventTime = mEvents.at(i).start().time();

        if (nextGroupTime <= eventTime)
        {
            mGroups.last().mChildCount = i - mGroups.last().mFirstEventIndex;
            mGroups << EventModel::Group(QString("%1 - %2").arg(nextGroupTime.toString("HH:mm"),
                nextGroupTime.addSecs(timeSpan).toString("HH:mm")), i);
            nextGroupTime = nextGroupTime.addSecs(timeSpan);
        }

        // add parent-child relation
        mParents[mEvents.at(i).id()] = mGroups.count() - 1;
    }

    mGroups.last().mChildCount = mEvents.count() - mGroups.last().mFirstEventIndex;
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
    for(int i = 0;i < mGroups.count();i++){
        QModelIndex idx = index(i, 0);
        Group group = mGroups[i];
        beginRemoveRows(idx, 0, group.mChildCount - 1);
        /*bool ok =*/ removeRows(0, group.mChildCount, idx);
        endRemoveRows();
        //qDebug() << "removing " << group.mChildCount << " events from group:" << i << idx.data() << ":" << ok;
    }
    mEvents.clear();
}

void EventModel::loadEvents(const QDate &aDate, int aConferenceId)
{
    clearModel();
    // check for existence of the conference in the DB
    if(Conference::getAll().count())
    {
        qDebug() << "Loading Conference Data: [" << Conference::getById(aConferenceId).title() << "] " << aDate;
        mEvents = Event::getByDate(QDate(aDate.year(), aDate.month(), aDate.day()), aConferenceId, "start");
    }
    createTimeGroups();
}

void EventModel::loadFavEvents(const QDate &aDate, int aConferenceId)
{
    clearModel();
    // check for existence of the conference in the DB
    if(Conference::getAll().count())
    {
        qDebug() << "Loading FAV Conference Data: [" << Conference::getById(aConferenceId).title() << "] " << aDate;
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
        qDebug() << "Loading search result Data: [" << Conference::getById(aConferenceId).title() << "] " << aDate;
        try{
            mEvents = Event::getSearchResultByDate(QDate(aDate.year(), aDate.month(), aDate.day()), aConferenceId, "start");
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
        qDebug() << "Loading Conference Data (by Track): [" << Conference::getById(aConferenceId).title() << "] " << aDate;
        mEvents = Event::getByDate(QDate(aDate.year(), aDate.month(), aDate.day()), aConferenceId, "xid_track, start");
    }
    createTrackGroups();
}

void EventModel::loadEventsByRoom(const QDate &aDate, int aConferenceId)
{
    clearModel();
    if (Conference::getAll().count())
    {
        qDebug() << "Loading Conference Data (by Room): [" << Conference::getById(aConferenceId).title() << "] " << aDate;
        mEvents = Event::getByDateAndRoom(QDate(aDate.year(), aDate.month(), aDate.day()), aConferenceId);
    }
    createRoomGroups();
}

void EventModel::loadNowEvents(int aConferenceId)
{
    clearModel();
    // check for existence of the conference in the DB
    if(Conference::getAll().count())
    {
        qDebug() << "Loading Conference Data: [" << Conference::getById(aConferenceId).title() << "] scheduled NOW";
        mEvents = Event::nowEvents(aConferenceId, "start");
    }
    createTimeGroups();
}

void EventModel::loadConflictEvents(int aEventId, int aConferenceId)
{
    clearModel();
    // check for existence of the conference in the DB
    if(Conference::getAll().count())
    {
        qDebug() << "Loading Conference Data: [" << Conference::getById(aConferenceId).title() << "] in conflict with " << aEventId;
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

