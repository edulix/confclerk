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

#include "dayviewtabcontainer.h"

DayViewTabContainer::DayViewTabContainer(QWidget *aParent): TabContainer(aParent) {
}


void DayViewTabContainer::expandTimeGroup(QTime time, int conferenceId) {
    EventModel* eventModel = static_cast<EventModel*>(treeView->model());

    // iterate over the time groups
    for (int g = 0; g != eventModel->rowCount(); ++g) {
        QModelIndex groupIdx = eventModel->index(g, 0);
        // iterate over the events in the group
        for (int e = 0; e != eventModel->rowCount(groupIdx); ++e) {
            QModelIndex eventIdx = eventModel->index(e, 0, groupIdx);
            int eventId = eventIdx.data().toInt();
            Event event = Event::getById(eventId, conferenceId);
            if (time < event.start().time().addSecs(event.duration())) { // if time < end
                // expand this group
                treeView->expand(groupIdx);
                treeView->scrollTo(eventIdx, QAbstractItemView::PositionAtTop);
                return;
            }
        }
    }
}


void DayViewTabContainer::loadEvents( const QDate &aDate, const int aConferenceId ) {
    static_cast<EventModel*>(treeView->model())->loadEvents( aDate, aConferenceId );
}
