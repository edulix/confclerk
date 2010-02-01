#include <mainwindow.h>

#include <QtGui/QApplication>
#include <sqlengine.h>

#include "eventdialog.h"

#ifdef MAEMO
//#include <alarmdialog.h>
#include <alarmdbus.h>
#include <alarmdbusadaptorp.h>
#endif /* MAEMO */


int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(icons);
    Q_INIT_RESOURCE(maps);
    Q_INIT_RESOURCE(db);

    QApplication a(argc, argv);
    QApplication::setWindowIcon(QIcon(":/icons/fosdem.png"));

    SqlEngine::initialize(); // creates "SQLITE" DB connection

    QWidget *window;

    window = new MainWindow;


#ifdef MAEMO
    // Alarm Dbus
    CAlarmDBus *alarmDBus = new CAlarmDBus(window);
    new AlarmDBusAdaptor(alarmDBus);
    QDBusConnection connection = QDBusConnection::sessionBus();

    if(connection.registerObject("/Fosdem", alarmDBus) == true)
    {
    	if( connection.registerService("org.fosdem.schedule") == false)
    	{
    		if(argc>1)
    		{
        		QDBusInterface *interface = new QDBusInterface("org.fosdem.schedule",
        		                                               "/Fosdem",
        		                                               "org.fosdem.schedule.AlarmInterface",
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

