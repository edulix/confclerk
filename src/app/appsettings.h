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

#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QString>
#include <QSettings>

class AppSettings
{
    private:
        AppSettings() {}
        static QSettings mSettings;

    public:
        static bool contains(const QString &aKey);

        static QString proxyAddress();
        static quint16 proxyPort();
        static bool isDirectConnection();

        static void setProxyAddress(const QString &aAddress);
        static void setProxyPort(const quint16 aPort);
        static void setDirectConnection(bool aDirectConnection);
};

#endif /* APPSETTINGS_H */

