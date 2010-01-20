#include "alarmdialog.h"

#include <QApplication>
#include <alarm.h>
#include <event.h>

#include <QDir>
#include <QProcess>

const int SNOOZE_TIME = 5; // in minutes

const int confId = 1;

AlarmDialog::AlarmDialog(int argc, char *argv[], QWidget *aParent)
    : QDialog(aParent)
    , mEventId(0)
    , mAlarmId(0)
{
    setupUi(this);

    if(argc<3)
    {
        // not enough arguments passed to the dialog
        // Usage: $ ./dialog eventId alarmId
        // Example: $ ./dialog 521 13
        //
        // TODO: handle this case
    }
    else
    {
        mEventId = QString(argv[1]).toInt();
        mAlarmId = QString(argv[2]).toInt();
    }

    connect(stopPB, SIGNAL(clicked()), SLOT(closeDialog()));
    connect(appPB, SIGNAL(clicked()), SLOT(runApp()));
    connect(snoozePB, SIGNAL(clicked()), SLOT(snooze()));

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(QDir::homePath() + "/.fosdem/fosdem.sqlite");
    database.open();

    try
    {
        Event event = Event::getById(mEventId,confId);
        message->setText(event.title());
        setWindowTitle(event.title());
    }
    catch(OrmNoObjectException*)
    {
        message->setText(QString("No such event in the DB: %1").arg(QString::number(mEventId)));
        setWindowTitle("ERROR");
    }
    catch(...) {} // TODO: implement
}

void AlarmDialog::runApp()
{
    QString program = QDir::currentPath() + "/" + *qApp->argv();
    QProcess::startDetached(program,QStringList()<<QString::number(mEventId));
    qApp->quit();
}

void AlarmDialog::snooze()
{
    if(mEventId==0) // not valid event ID
        return;

    Alarm alarm;
    alarm.addAlarm(mEventId,QDateTime::currentDateTime().addSecs(60*SNOOZE_TIME));
    qApp->quit();
}

void AlarmDialog::closeDialog()
{
    // before closing the dialog, it is necessary to remove alarm flag from the DB
    try
    {
        Event event = Event::getById(mEventId,confId);
        event.setHasAlarm(false);
        event.update("alarm");
    }
    catch(OrmNoObjectException*) {} // TODO: implement
    catch(...) {} // just close dialog
    qApp->quit();
}

