#include "mainwindow.h"

#include <QTreeView>

#include <eventmodel.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // open database connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("fosdem-test.sqlite");
    db.open();

    QTreeView * view = new QTreeView(parent);
    this->setCentralWidget(view);

    view->setModel(new EventModel());
}
