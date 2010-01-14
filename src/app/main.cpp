#include <mainwindow.h>

#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(icons);

    QApplication a(argc, argv);
    QApplication::setWindowIcon(QIcon(":/icons/fosdem.png"));

    MainWindow w;
    w.show();
    return a.exec();
}
