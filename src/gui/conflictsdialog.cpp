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
#include "conflictsdialog.h"

ConflictsDialog::ConflictsDialog(int aEventId, QWidget *aParent)
    : QDialog(aParent)
{
    setupUi(this);
    connect(container, SIGNAL(eventHasChanged(int,bool)), this, SIGNAL(eventHasChanged(int,bool)));
    connect(container, SIGNAL(eventHasChanged(int,bool)), container, SLOT(updateTreeViewModel(int,bool)));

    container->setEventId(aEventId);

    int confId = Conference::activeConference();
    QDate startDate = Conference::getById(confId).start();
    QDate endDate = Conference::getById(confId).end();
    container->setDates(startDate, endDate);
}

ConflictsDialog::~ConflictsDialog()
{
    disconnect(container, SIGNAL(eventHasChanged(int,bool)), this, SIGNAL(eventHasChanged(int,bool)));
}

