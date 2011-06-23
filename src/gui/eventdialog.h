/*
 * Copyright (C) 2010 Ixonos Plc.
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
#ifndef EVENTDIALOG_H
#define EVENTDIALOG_H

#include <QDialog>
#include "ui_eventdialog.h"
#include <event.h>

class EventDialog : public QDialog, Ui::EventDialog
{ 
    Q_OBJECT
public:
    EventDialog(const int &aEventId, QWidget *aParent = NULL);
    ~EventDialog() {}
private slots:
    void favouriteClicked();
    void alarmClicked();
signals:
    void eventHasChanged(int aEventId, bool aReloadModel = false); // emited when user changes some event details, eg. sets it Favourite
private:
    int mEventId;
};

#endif /* EVENTDIALOG_H */

