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

#ifndef FAVTABCONTAINER_H_
#define FAVTABCONTAINER_H_

#include "tabcontainer.h"

class FavTabContainer: public TabContainer
{
    Q_OBJECT
public:
    FavTabContainer(QWidget *aParent);
    virtual ~FavTabContainer(){}

protected:
    virtual void loadEvents( const QDate &aDate, const int aConferenceId );
};

#endif /* FAVTABCONTAINER_H_ */
