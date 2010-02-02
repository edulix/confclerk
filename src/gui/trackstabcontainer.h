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

#ifndef TRACKSTABCONTAINER_H_
#define TRACKSTABCONTAINER_H_

#include "tabcontainer.h"

class TracksTabContainer: public TabContainer
{
    Q_OBJECT
public:
    TracksTabContainer( QWidget *aParent );
    virtual ~TracksTabContainer() {}

protected:
    virtual void loadEvents( const QDate &aDate, const int aConferenceId );

};

#endif /* TRACKSTABCONTAINER_H_ */
