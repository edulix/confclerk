#include "mainwindow.h"

#include <QTreeView>
#include <QDirModel>

#include <eventmodel.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // open database connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("fosdem-test.sqlite");
    db.open();

    setupUi(this);
    //TODO Palo: continue
    //treeView->setModel(new QDirModel);
    treeView->setModel(new EventModel());
}
