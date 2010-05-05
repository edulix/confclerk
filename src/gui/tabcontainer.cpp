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
#include "tabcontainer.h"

#include <QFile>
#include <QMessageBox>
#include <QTimer>

#include <treeview.h>
#include <delegate.h>

#include "eventdialog.h"
#include "mapwindow.h"
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

    connect(dayNavigator, SIGNAL(dateChanged(const QDate &)), SLOT(updateTreeView(const QDate &)));

    connect(treeView, SIGNAL(eventHasChanged(int,bool)), SIGNAL(eventHasChanged(int,bool)));
    connect(treeView, SIGNAL(clicked(const QModelIndex &)), SLOT(itemClicked(const QModelIndex &)));
    connect(treeView, SIGNAL(requestForMap(const QModelIndex &)), SLOT(displayMap(const QModelIndex &)));
    connect(treeView, SIGNAL(requestForConflicts(const QModelIndex &)), SLOT(displayConflicts(const QModelIndex &)));

    // day navigator is hidden by default
    dayNavigator->hide();
}

void TabContainer::updateTreeView(const QDate &aDate)
{
    int active_id = Conference::activeConference();
    dayNavigator->show();
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
    connect(&dialog, SIGNAL(eventHasChanged(int,bool)), this, SIGNAL(eventHasChanged(int,bool)));
    dialog.exec();
    disconnect(&dialog, SIGNAL(eventHasChanged(int,bool)), this, SIGNAL(eventHasChanged(int,bool)));
}

void TabContainer::displayMap(const QModelIndex &aIndex)
{
    Event *event = static_cast<Event*>(aIndex.internalPointer());

    QVariant mapPathV = event->room()->map();
    QString mapPath;
    if (!mapPathV.isValid()) {
        error_message("No map for this room");
        return;
    } else {
        mapPath = mapPathV.toString();
        if (!QFile::exists(mapPath)) {
            error_message("Map for this room not found: " + mapPath);
            return;
        }
    }

    QPixmap map(mapPath);
    MapWindow window(map, event->room()->name(),this);
    window.exec();
}

void TabContainer::displayConflicts(const QModelIndex &aIndex)
{
    ConflictsDialog dialog(static_cast<Event*>(aIndex.internalPointer())->id(),this);
#ifdef N810
    dialog.setFixedWidth(static_cast<QWidget*>(parent())->width());
#endif
    connect(&dialog, SIGNAL(eventHasChanged(int,bool)), this, SIGNAL(eventHasChanged(int,bool)));
    dialog.exec();
    disconnect(&dialog, SIGNAL(eventHasChanged(int,bool)), this, SIGNAL(eventHasChanged(int,bool)));
}

void TabContainer::updateTreeViewModel(int aEventId, bool aReloadModel)
{
    if(aReloadModel)
    {
        // requires special handling
        // eg. in case of favourities - some favourities may have changed
        // and so we need to reload them
        int confId = Conference::activeConference();
        QDate startDate = Conference::getById(confId).start();
        QDate endDate = Conference::getById(confId).end();
        dayNavigator->setDates(startDate, endDate);
        updateTreeView( Conference::getById(confId).start() );
    }
    else
    {
        // just update event in the question
        static_cast<EventModel*>(treeView->model())->updateModel(aEventId);
    }
}

void TabContainer::setDates(const QDate &aStart, const QDate &aEnd)
{
    dayNavigator->setDates(aStart, aEnd);
}

void TabContainer::clearModel()
{
    static_cast<EventModel*>(treeView->model())->clearModel();
}

