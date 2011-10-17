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
#include "conflictsdialog.h"

ConflictsDialog::ConflictsDialog(int aEventId, int aConferenceId, QWidget *aParent)
    : QDialog(aParent)
{
    setupUi(this);
    connect(container, SIGNAL(eventChanged(int,bool)), this, SIGNAL(eventChanged(int,bool)));
    connect(container, SIGNAL(eventChanged(int,bool)), container, SLOT(loadEvents()));

    container->setEventId(aEventId, aConferenceId);
}


ConflictsDialog::~ConflictsDialog()
{
    disconnect(container, SIGNAL(eventChanged(int,bool)), this, SIGNAL(eventChanged(int,bool)));
}

