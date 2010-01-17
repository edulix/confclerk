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

    // DAY EVENTS View
    dayTreeView->setHeaderHidden(true);
    dayTreeView->setRootIsDecorated(false);
    dayTreeView->setIndentation(0);
    dayTreeView->setAnimated(true);
    dayTreeView->setModel(new EventModel());
    dayTreeView->setItemDelegate(new Delegate(dayTreeView));

    // FAVOURITIES View
    favTreeView->setHeaderHidden(true);
    favTreeView->setRootIsDecorated(false);
    favTreeView->setIndentation(0);
    favTreeView->setAnimated(true);
    favTreeView->setModel(new EventModel());
    favTreeView->setItemDelegate(new Delegate(favTreeView));
    // TESTING: load some 'fav' data
    if(Conference::getAll().count()) // no conference(s) in the DB
    {
        int confId = 1;
        static_cast<EventModel*>(favTreeView->model())->loadFavEvents(Conference::getById(confId).start(),confId);
        favTreeView->reset();
    }

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
    static_cast<EventModel*>(dayTreeView->model())->loadEvents(aDate,confId);
    dayTreeView->reset();
    dayNavigator->show();
}

