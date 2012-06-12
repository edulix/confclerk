/*
 * Copyright (C) 2010 Ixonos Plc.
 * Copyright (C) 2011-2012 Philipp Spitzer, gregor herrmann, Stefan Stahl
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

#ifndef SEARCHTAB_H_
#define SEARCHTAB_H_

#include <QtGui>

#include "tabcontainer.h"
#include "searchhead.h"

class SearchTabContainer: public TabContainer {
    Q_OBJECT
public:
    SearchTabContainer(QWidget *aParent);
    virtual ~SearchTabContainer() {}
    bool searchDialogIsVisible() const;
    int searchResultCount(const QDate& date) const; ///< returns the number of events found on that specific date

protected:
    virtual void loadEvents( const QDate &aDate, const int aConferenceId );

signals:
    void searchResultChanged();

public slots:
    void showSearchDialog(bool show=true);

private slots:
    void searchButtonClicked();

private:
    SearchHead *header;
    QToolButton *searchAgainButton;
};

#endif /* SEARCHTAB_H_ */
