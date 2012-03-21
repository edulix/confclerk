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
#include "tabcontainer.h"

#include <QFile>
#include <QMessageBox>
#include <QTimer>

#include <treeview.h>
#include <delegate.h>

#include "eventdialog.h"
#include "room.h"
#include "errormessage.h"

#include "conflictsdialog.h"

TabContainer::TabContainer(QWidget *aParent)
    : QWidget(aParent)
{
    setupUi(this);

    treeView->setHeaderHidden(true);
    treeView->setRootIsDecorated(false);
    treeView->setIndentation(0);
    treeView->setAnimated(true);
    treeView->setModel(new EventModel());
    treeView->setItemDelegate(new Delegate(treeView));

    connect(treeView, SIGNAL(eventChanged(int,bool)), SIGNAL(eventChanged(int,bool)));
    connect(treeView, SIGNAL(clicked(const QModelIndex &)), SLOT(itemClicked(const QModelIndex &)));
    connect(treeView, SIGNAL(requestForConflicts(const QModelIndex &)), SLOT(displayConflicts(const QModelIndex &)));
}

void TabContainer::updateTreeView(const QDate &aDate)
{
    int active_id = Conference::activeConference();
    if (active_id > 0) {
        loadEvents(aDate, active_id);
    } else {
        static_cast<EventModel*>(treeView->model())->clearModel();
    }
}

void TabContainer::itemClicked(const QModelIndex &aIndex)
{
    // have to handle only events, not time-groups
    if(!aIndex.parent().isValid()) // time-group
        return;

    EventDialog dialog(static_cast<Event*>(aIndex.internalPointer())->id(),this);
#ifdef N810
    dialog.setFixedWidth(static_cast<QWidget*>(parent())->width());
#endif
    connect(&dialog, SIGNAL(eventChanged(int,bool)), this, SIGNAL(eventChanged(int,bool)));
    dialog.exec();
    disconnect(&dialog, SIGNAL(eventChanged(int,bool)), this, SIGNAL(eventChanged(int,bool)));
}

void TabContainer::displayConflicts(const QModelIndex &aIndex)
{
    Event* event = static_cast<Event*>(aIndex.internalPointer());
    ConflictsDialog dialog(event->id(), event->conferenceId(), this);
#ifdef N810
    dialog.setFixedWidth(static_cast<QWidget*>(parent())->width());
#endif
    connect(&dialog, SIGNAL(eventChanged(int,bool)), this, SIGNAL(eventChanged(int,bool)));
    dialog.exec();
    disconnect(&dialog, SIGNAL(eventChanged(int,bool)), this, SIGNAL(eventChanged(int,bool)));
}


void TabContainer::redisplayEvent(int aEventId) {
    static_cast<EventModel*>(treeView->model())->updateModel(aEventId);
}


void TabContainer::redisplayDate(const QDate& curDate) {
    updateTreeView(curDate);
}


void TabContainer::clearModel()
{
    static_cast<EventModel*>(treeView->model())->clearModel();
}

