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
#ifndef EVENTMODEL_H
#define EVENTMODEL_H

#include <QAbstractItemModel>

#include "event.h"

class EventModel : public QAbstractItemModel
{
public:
    static const QString COMMA_SEPARATOR; // ", "
public:
    EventModel();
    QVariant data(const QModelIndex& index, int role) const;
    QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;
    QModelIndex parent ( const QModelIndex & index ) const;
    int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
    int rowCount ( const QModelIndex & parent = QModelIndex() ) const;
    void loadEvents(const QDate &aDate, int aConferenceId); // loads Events from the DB
    void loadFavEvents(const QDate &aDate, int aConferenceId); // loads Favourite events from the DB
    void loadEventsByTrack(const QDate &aDate, int aConferenceId); // loads Events sorted by Track id and Event start from the DB
    int loadSearchResultEvents(const QDate &aDate, int aConferenceId);
    void loadEventsByRoom(const QDate &aDate, int aConferenceId);
    void loadConflictEvents(int aEventId, int aConferenceId); // loads events in conflict
    void clearModel();

private:
    struct Group
    {
        Group(const QString & title,
              int firstEventIndex) :

            mTitle(title),                     // e.g. "16:00 - 17:30"
            mFirstEventIndex(firstEventIndex), // first index within mEvents
            mChildCount(0)                     // number of events in mEvents
        {}

        QString mTitle;
        int mFirstEventIndex;
        int mChildCount;

        void setTitle(const QList<Event>& mEvents);
    };

private:
    void createTimeGroups();
    void createTrackGroups();
    void createTrackGroupsNew();
    void createRoomGroups();

public slots:
    void updateModel(int aEventId);

private:
    QList<Event> mEvents;
    QList<Group> mGroups;
    QHash<int, int> mParents; ///< eventId, groupId
};

#endif // EVENTMODEL_H

