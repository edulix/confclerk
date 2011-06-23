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
#include "appsettings.h"

const QString PROXY_ADDRESS_SETTING ("proxyAddress"); 
const QString PROXY_PORT_SETTING ("proxyPort"); 
const QString PROXY_ISDIRECT_SETTING ("proxyIsDirectConnection"); 

QSettings AppSettings::mSettings("Ixonos", "FOSDEM");

QString AppSettings::proxyAddress()
{
    return mSettings.value(PROXY_ADDRESS_SETTING).toString();
}

quint16 AppSettings::proxyPort()
{
    return mSettings.value(PROXY_PORT_SETTING).toUInt();
}

bool AppSettings::isDirectConnection()
{
    return mSettings.value(PROXY_ISDIRECT_SETTING).toBool();
}

void AppSettings::setProxyAddress(const QString &aAddress)
{
    mSettings.setValue(PROXY_ADDRESS_SETTING, aAddress);
}

void AppSettings::setProxyPort(const quint16 aPort)
{
    mSettings.setValue(PROXY_PORT_SETTING, aPort);
}

void AppSettings::setDirectConnection(bool aDirectConnection)
{
    mSettings.setValue(PROXY_ISDIRECT_SETTING, aDirectConnection);
}

bool AppSettings::contains(const QString &aKey)
{
    return mSettings.contains(aKey);
}

