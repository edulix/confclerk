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
#ifndef CONFLICTSDIALOG_H
#define CONFLICTSDIALOG_H

#include "ui_conflictsdialog.h"
#include <QDialog>

class ConflictsDialog : public QDialog, Ui::ConflictsDialog
{
    Q_OBJECT
public:
    ConflictsDialog(int aEventId, int aConferenceId, QWidget *aParent = NULL);
    ~ConflictsDialog();
signals:
    void eventChanged(int aEventId, bool favouriteChanged);
};

#endif /* CONFLICTSDIALOG_H */ 

