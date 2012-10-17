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
#include "mainwindow.h"

#include "sqlengine.h"

#include "eventdialog.h"
#include "application.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(icons);
    Q_INIT_RESOURCE(db);
    Q_INIT_RESOURCE(data);

    Application a(argc, argv);
    Application::setWindowIcon(QIcon(":/confclerk.svg"));

    // needed by QDesktopServices
    QCoreApplication::setOrganizationName("Toastfreeware");
    QCoreApplication::setApplicationName("ConfClerk");
    QCoreApplication::setApplicationVersion(VERSION);

    QWidget* window = new MainWindow;

    // If we were started with the parameters confernceid and eventid, show the corresponding event (alarm)
    if (argc == 3) {
        QString conferenceIdStr = argv[1];
        QString eventIdStr = argv[2];
        EventDialog dialog(conferenceIdStr.toInt(), eventIdStr.toInt(), window);
        dialog.exec();
    }
    window->show();

    return a.exec();
}

