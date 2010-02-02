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

#ifndef CONFLICTDIALOGCONTAINER_H
#define CONFLICTDIALOGCONTAINER_H

#include "tabcontainer.h"

class ConflictDialogContainer: public TabContainer
{
    Q_OBJECT
public:
    ConflictDialogContainer(QWidget *aParent);
    virtual ~ConflictDialogContainer(){}

    void setEventId(int aEventId) { mEventId = aEventId; }

protected:
    virtual void loadEvents( const QDate &aDate, const int aConferenceId );

protected slots:
    virtual void updateTreeView(const QDate &aDate);

private:
    int mEventId;
};

#endif /* CONFLICTDIALOGCONTAINER_H */

