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
#ifndef ALARMDIALOG_H
#define ALARMDIALOG_H

#include <QDialog>
#include "ui_alarmdialog.h"

class AlarmDialog : public QDialog, Ui::AlarmDialog
{
    Q_OBJECT
    public:
        AlarmDialog(int argc, char *argv[], QWidget *aParent = NULL);
        ~AlarmDialog() {}
    private slots:
        void runApp();
        void snooze();
        void closeDialog();
    private:
        int mEventId; // event ID obtained from 'schedule'
        int mAlarmId; // cookie assigned by alarmd
};

#endif /* ALARMDIALOG_H */

