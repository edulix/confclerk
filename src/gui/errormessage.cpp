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
#include "errormessage.h"

#include <cstdio>

#include <QTextStream>
#ifdef QT_MAEMO5_LIB
#include <QMaemo5InformationBox>
#else
#include <QMessageBox>
#endif

void error_message(const QString& message)
{
#ifdef QT_MAEMO5_LIB
    // by default the message is white on yellow, which is unusable
    // but some html here works
    // remove it as soon as they fix the colors
    QMaemo5InformationBox::information(0, "<font color=\"black\">" + message + "</font>");
#else
    QMessageBox::warning(0, "Error", message);
#endif
}
