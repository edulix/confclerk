#include <mainwindow.h>

#include <QtGui/QApplication>
#ifdef MAEMO
//#include <alarmdialog.h>
#include "alarmdbus.h"
#include "alarmdbusadaptorp.h"
#endif /* MAEMO */

#include <sqlengine.h>


int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(icons);
    Q_INIT_RESOURCE(maps);
    Q_INIT_RESOURCE(db);

    QApplication a(argc, argv);
    QApplication::setWindowIcon(QIcon(":/icons/fosdem.png"));

    SqlEngine::initialize(); // creates "SQLITE" DB connection

    QWidget *window;
#ifdef MAEMO
    // if the app is run with two cmd-line arguments
    // an alarm dialog is to be displayed
    // Usage: $ ./fosdem eventId alarmId
    // Example: $ ./fosdem 521 13
//    if(argc==3)
//        window = new AlarmDialog(argc,argv);
//    else if(argc==2) // display Event dialog automatically
//        window = new MainWindow(atoi(argv[1])); // eventId = argv[1]
//    else
        window = new MainWindow;
#else
    window = new MainWindow;
#endif /* MAEMO */
    window->show();

#ifdef MAEMO
    // Alarm Dbus
    CAlarmDBus *alarmDBus = new CAlarmDBus(window);
    new AlarmDBusAdaptor(alarmDBus);
    //QDBusConnection connection = QDBusConnection::sessionBus();
    QDBusConnection connection = QDBusConnection::sessionBus();

    if(connection.registerObject("/Fosdem", alarmDBus) == true)
    {
    	if( connection.registerService("org.fosdem.schedule") == false)
    	{
    		qDebug() << "dbus register service failed";
    	}
    }
#endif

    return a.exec();
}

