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
#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QTreeView>

class TreeView : public QTreeView
{
    Q_OBJECT
public:
    TreeView(QWidget *aParent = NULL);
    ~TreeView() {}
private:
    void mouseReleaseEvent(QMouseEvent *aEvent);
    bool testForControlClicked(const QModelIndex &aIndex, const QPoint &aPoint);
public slots:
    void setAllExpanded(bool aExpanded); // (aExpanded==true) => expanded; (aExpanded==false) => collapsed
private slots:
    void handleItemClicked(const QModelIndex &index);
signals:
    void requestForConflicts(const QModelIndex &aIndex);
    void eventHasChanged(int aEventId, bool aReloadModel = false); // emited when user changes some event details, eg. sets it Favourite
};

#endif /* TREEVIEW_H */

