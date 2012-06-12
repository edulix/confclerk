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
#ifndef ALARM_DBUS_H
#define ALARM_DBUS_H

#include <QObject>
#include <QtDBus/QtDBus>

class CAlarmDBus: public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "at.priv.toastfreeware.confclerk")

public:
	CAlarmDBus(QWidget * aParent);
    virtual ~CAlarmDBus();

public: // PROPERTIES
public Q_SLOTS: // METHODS
    void Alarm(int aEventId);
private:
	QWidget * mParent;
};


#endif // ALARM_DBUS_H
