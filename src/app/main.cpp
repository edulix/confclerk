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
#include <mainwindow.h>

#include <sqlengine.h>

#include "eventdialog.h"
#include "application.h"

#ifdef MAEMO
//#include <alarmdialog.h>
#include <alarmdbus.h>
#include <alarmdbusadaptorp.h>
#endif /* MAEMO */


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
 
    SqlEngine::initialize(); // creates "SQLITE" DB connection

    QWidget *window;

    window = new MainWindow;


#ifdef MAEMO
    // Alarm Dbus
    CAlarmDBus *alarmDBus = new CAlarmDBus(window);
    new AlarmDBusAdaptor(alarmDBus);
    QDBusConnection connection = QDBusConnection::sessionBus();

    if(connection.registerObject("/ConfClerk", alarmDBus) == true)
    {
    	if( connection.registerService("at.priv.toastfreeware.confclerk") == false)
    	{
    		if(argc>1)
    		{
        		QDBusInterface *interface = new QDBusInterface("at.priv.toastfreeware.confclerk",
        		                                               "/ConfClerk",
        		                                               "at.priv.toastfreeware.confclerk.AlarmInterface",
        		                                               connection);
        		interface->call("Alarm",atoi(argv[1]));
        		return 0;
    		}
    	}
    }

    if(argc > 1)
    {
        EventDialog dialog(atoi(argv[1]),window);
        dialog.exec();
    }
#endif

    window->show();

    return a.exec();
}

