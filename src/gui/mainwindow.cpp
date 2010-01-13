#include "mainwindow.h"

#include <QTreeView>
#include <QDirModel>

#include <sqlengine.h>
#include <schedulexmlparser.h>

#include <eventmodel.h>
#include <delegate.h>

#include <conference.h>

#include <QDialog>
#include "ui_about.h"
#include "daynavigatorwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

    // connect Menu actions
    connect(actionImportSchedule, SIGNAL(triggered()), SLOT(importSchedule()));
    connect(actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(actionAboutApplication, SIGNAL(triggered()), SLOT(aboutApp()));

    // create "SQLITE" DB instance/connection
    // opens DB connection (needed for EventModel)
    mSqlEngine = new SqlEngine(this);
    mSqlEngine->initialize();

    mXmlParser = new ScheduleXmlParser(this);
    connect(mXmlParser, SIGNAL(progressStatus(int)), this, SLOT(showParsingProgress(int)));
    statusBar()->showMessage(tr("Ready"));

    connect(dayNavigator, SIGNAL(dateChanged(const QDate &)), SLOT(updateDayView(const QDate &)));

    treeView->setHeaderHidden(true);
    treeView->setRootIsDecorated(false);
    treeView->setIndentation(0);
    treeView->setAnimated(true);
    treeView->setModel(new EventModel());
    treeView->setItemDelegate(new Delegate(treeView));

    if(!Conference::getAll().count()) // no conference(s) in the DB
        dayNavigator->hide(); // hide DayNavigatorWidget
    else
    {
        int confId = 1;
        dayNavigator->setDates(Conference::getById(confId).start(),Conference::getById(confId).end());
    }
}

MainWindow::~MainWindow()
{
    if(mSqlEngine)
    {
        delete mSqlEngine;
        mSqlEngine = NULL;
    }
    if(mXmlParser)
    {
        delete mXmlParser;
        mXmlParser = NULL;
    }
}

void MainWindow::importSchedule()
{
    QFile file("../schedule.en.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "can't open " << file.fileName();
        return;
    }

    QByteArray data = file.readAll();
    mXmlParser->parseData(data,mSqlEngine);

    if(Conference::getAll().count())
    {
        int confId = 1;
        // 'dayNavigator' emits signal 'dateChanged' after setting valid START:END dates
        dayNavigator->setDates(Conference::getById(confId).start(),Conference::getById(confId).end());
    }
}

void MainWindow::showParsingProgress(int aStatus)
{
    QString msg = QString("Parsing completed: %1\%").arg(aStatus);
    statusBar()->showMessage(msg,1000);
}

void MainWindow::aboutApp()
{
    QDialog dialog(this);
    Ui::AboutDialog ui;
    ui.setupUi(&dialog);
    dialog.exec();
}

void MainWindow::updateDayView(const QDate &aDate)
{
    int confId = 1;
    static_cast<EventModel*>(treeView->model())->loadEvents(aDate,confId);
    treeView->reset();
    dayNavigator->show();
}

