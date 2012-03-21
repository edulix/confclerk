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

#include "conflictdialogcontainer.h"

ConflictDialogContainer::ConflictDialogContainer(QWidget *aParent)
    : TabContainer( aParent ), mEventId(-1), mConferenceId(-1)
{}


void ConflictDialogContainer::setEventId(int aEventId, int conferenceId) {
    mEventId = aEventId;
    mConferenceId = conferenceId;
    loadEvents();
}


void ConflictDialogContainer::loadEvents() {
    static_cast<EventModel*>(treeView->model())->loadConflictEvents(mEventId, mConferenceId);
    treeView->setAllExpanded(true);
}


void ConflictDialogContainer::loadEvents(const QDate &aDate, const int aConferenceId) {
    Q_UNUSED(aDate);
    Q_UNUSED(aConferenceId);
    Q_ASSERT(aConferenceId == mConferenceId);
    Q_ASSERT(mConferenceId > 0);
    Q_ASSERT(mEventId > 0);
    loadEvents();
}


