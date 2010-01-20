#include <mainwindow.h>

#include <QtGui/QApplication>
#ifdef MAEMO
#include <alarmdialog.h>
#endif /* MAEMO */

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(icons);
    Q_INIT_RESOURCE(maps);
    Q_INIT_RESOURCE(schedule);

    QApplication a(argc, argv);
    QApplication::setWindowIcon(QIcon(":/icons/fosdem.png"));

    QWidget *window;
#ifdef MAEMO
    // if the app is run with two cmd-line arguments
    // an alarm dialog is to be displayed
    // Usage: $ ./fosdem eventId alarmId
    // Example: $ ./fosdem 521 13
    if(argc==3) 
        window = new AlarmDialog(argc,argv);
    else if(argc==2) // display Event dialog automatically
        window = new MainWindow(atoi(argv[1])); // eventId = argv[1]
    else
        window = new MainWindow;
#else
    window = new MainWindow;
#endif /* MAEMO */
    window->show();
    return a.exec();
}

