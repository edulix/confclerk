#include "alarmdialog.h"

#include <QApplication>
#include <alarm.h>

const int SNOOZE_TIME = 5; // in minutes

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

    connect(stopPB, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(appPB, SIGNAL(clicked()), SLOT(runApp()));
    connect(snoozePB, SIGNAL(clicked()), SLOT(snooze()));

    message->setText(QString(argv[1]).append("-").append(QString(argv[2])));
}

void AlarmDialog::runApp()
{
}

void AlarmDialog::snooze()
{
    if(mEventId==0) // not valid event ID
        return;

    Alarm alarm;
    alarm.addAlarm(mEventId,QDateTime::currentDateTime().addSecs(60*SNOOZE_TIME));
    qApp->quit();
}

