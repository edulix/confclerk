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
#include "eventdialog.h"
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
    connect(activityDayNavigator, SIGNAL(dateChanged(const QDate &)), SLOT(updateActivitiesDayView(const QDate &)));
    //connect(tabWidget, SIGNAL(currentChanged(int)), SLOT(updateView(int)));

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

    //ACTIVITIES View
    actTreeView->setHeaderHidden(true);
    actTreeView->setRootIsDecorated(false);
    actTreeView->setIndentation(0);
    actTreeView->setAnimated(true);
    actTreeView->setModel(new EventModel());
    actTreeView->setItemDelegate(new Delegate(actTreeView));

    connect(dayTreeView, SIGNAL(doubleClicked(const QModelIndex &)), SLOT(itemDoubleClicked(const QModelIndex &)));
    connect(favTreeView, SIGNAL(doubleClicked(const QModelIndex &)), SLOT(itemDoubleClicked(const QModelIndex &)));
    connect(actTreeView, SIGNAL(doubleClicked(const QModelIndex &)), SLOT(itemDoubleClicked(const QModelIndex &)));

    // TESTING: load some 'fav' data
    if(Conference::getAll().count()) // no conference(s) in the DB
    {
        int confId = 1;
        static_cast<EventModel*>(favTreeView->model())->loadFavEvents(Conference::getById(confId).start(),confId);
        favTreeView->reset();
    }

    if(!Conference::getAll().count()) // no conference(s) in the DB
    {
        dayNavigator->hide(); // hide DayNavigatorWidget
        activityDayNavigator->hide();
    }
    else
    {
        int confId = 1;
        QDate aStartDate = Conference::getById(confId).start();
        QDate aEndDate = Conference::getById(confId).end();
        dayNavigator->setDates(aStartDate, aEndDate);
        activityDayNavigator->setDates(aStartDate, aEndDate);
    }
    connect(static_cast<EventModel*>(dayTreeView->model()), SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), SLOT(updateFavView()));
    connect(static_cast<EventModel*>(favTreeView->model()), SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), SLOT(updateFavView()));
/*    connect(static_cast<EventModel*>(favTreeView->model()), SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)), SLOT(updateFavViewComplete()));*/
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
        QString currPath = QDir::currentPath();
        qDebug() << "current path: " << currPath;
        qDebug() << "can't open " << file.fileName();
        return;
    }

    QByteArray data = file.readAll();
    mXmlParser->parseData(data,mSqlEngine);

    if(Conference::getAll().count())
    {
        int confId = 1;
        // 'dayNavigator' emits signal 'dateChanged' after setting valid START:END dates
        QDate aStartDate = Conference::getById(confId).start();
        QDate aEndDate = Conference::getById(confId).end();
        dayNavigator->setDates(aStartDate, aEndDate);
        activityDayNavigator->setDates(aStartDate, aEndDate);
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

void MainWindow::updateFavView()
{
    int confId = 1;
    static_cast<EventModel*>(favTreeView->model())->loadFavEvents(Conference::getById(confId).start(),confId);
    favTreeView->reset(); //Necessary reset:
                        //  if favourite event unselected as favourite is the only one in its time, and reset is not produced, crashed

    dayNavigator->show();
}

/*
void MainWindow::updateFavViewComplete()
{
    int confId = 1;
    updateFavView();
    updateDayView(Conference::getById(confId).start());
}
*/

void MainWindow::updateActivitiesDayView(const QDate &aDate)
{
    int confId = 1;
    static_cast<EventModel*>(actTreeView->model())->loadEventsByActivities(aDate,confId);
    actTreeView->reset();
    activityDayNavigator->show();
}

void MainWindow::itemDoubleClicked(const QModelIndex &aIndex)
{
    // have to handle only events, not time-groups
    if(!aIndex.parent().isValid()) // time-group
        return;

    EventDialog dialog(aIndex,this);
    dialog.exec();
}

