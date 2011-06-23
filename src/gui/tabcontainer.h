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
#ifndef TABCONTAINER_H
#define TABCONTAINER_H

#include <QWidget>
#include "ui_tabcontainer.h"

#include <conference.h>
#include <sqlengine.h>
#include <conference.h>
#include <eventmodel.h>

class TabContainer : public QWidget, public Ui::TabContainer
{
    Q_OBJECT
public:

    TabContainer(QWidget *aParent = NULL);
    virtual ~TabContainer() {}

    void clearModel();
protected:
    virtual void loadEvents( const QDate &aDate, const int aConferenceId )
    {
        Q_UNUSED(aDate);
        Q_UNUSED(aConferenceId);
    }

signals:
    void eventHasChanged(int aEventId, bool aReloadModel);

public slots:
    virtual void updateTreeViewModel(int aEventId, bool aReloadModel = false);
    void setDates(const QDate &aStart, const QDate &aEnd);

protected slots:
    virtual void updateTreeView(const QDate &aDate);
    void itemClicked(const QModelIndex &aIndex);
    void displayMap(const QModelIndex &aIndex);
    void displayConflicts(const QModelIndex &aIndex);
};

#endif /* TABCONTAINER_H */

