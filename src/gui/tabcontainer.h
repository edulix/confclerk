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
    virtual void loadEvents( const QDate &aDate, const int aConferenceId ) = 0;

signals:
    void eventChanged(int aEventId, bool aReloadModel);

public slots:
    virtual void redisplayEvent(int aEventId);
    void redisplayDate(const QDate& curDate);

protected slots:
    virtual void updateTreeView(const QDate &aDate);
    void itemClicked(const QModelIndex &aIndex);
    void displayConflicts(const QModelIndex &aIndex);
};

#endif /* TABCONTAINER_H */

