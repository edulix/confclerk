#include "mainwindow.h"

#include <QTreeView>
#include <QDirModel>

#include <eventmodel.h>
#include <delegate.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // open database connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("fosdem-test.sqlite");
    db.open();

    setupUi(this);
    //TODO Palo: continue
    treeView->setHeaderHidden(true);
    treeView->setRootIsDecorated(false);
    treeView->setIndentation(0);
    treeView->setAnimated(true);
    treeView->setModel(new EventModel());
    treeView->setItemDelegate(new Delegate(treeView));
}

