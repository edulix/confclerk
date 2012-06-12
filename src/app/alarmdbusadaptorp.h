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
#ifndef ALARM_DBUS_ADAPTOR_P_H
#define ALARM_DBUS_ADAPTOR_P_H

#include <QtCore/QObject>
#include <QtDBus/QtDBus>

QT_BEGIN_NAMESPACE
class QByteArray;
template<class T> class QList;
template<class Key, class Value> class QMap;
class QString;
class QStringList;
class QVariant;
QT_END_NAMESPACE


class AlarmDBusAdaptor: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "at.priv.toastfreeware.confclerk.AlarmInterface")
    Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"at.priv.toastfreeware.confclerk.AlarmInterface\" >\n"
"  <method name=\"Alarm\">\n"
"	  <arg name=\"aEventId\" type=\"i\" direction=\"in\"/>\n"
"  </method>\n"
"  </interface>\n"
        "")
public:
	AlarmDBusAdaptor(QObject *parent);
    virtual ~AlarmDBusAdaptor();

public: // PROPERTIES
public Q_SLOTS: // METHODS
	void Alarm(int aEventId);
};

#endif
