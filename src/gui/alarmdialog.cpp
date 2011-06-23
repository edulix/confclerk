/*
 * Copyright (C) 2010 Ixonos Plc.
 *
 * This file is part of ConfClerk.
 *
 * ConfClerk is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 2 of the License, or (at your option)
 * any later version.
 *
 * ConfClerk is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * ConfClerk.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "alarmdialog.h"
#include <conference.h>

#include <QApplication>
#include <alarm.h>
#include <event.h>

#include <QDir>
#include <QProcess>

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

    connect(stopPB, SIGNAL(clicked()), SLOT(closeDialog()));
    connect(appPB, SIGNAL(clicked()), SLOT(runApp()));
    connect(snoozePB, SIGNAL(clicked()), SLOT(snooze()));

    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(QDir::homePath() + "/.fosdem/fosdem.sqlite");
    database.open();

    QString titleStr;
    QString messageStr;
    QString timeStr;
    QString personsStr;
    QString roomStr;
    try
    {
        Event event = Event::getById(mEventId,Conference::activeConference());
        titleStr = "Event alarm";
        messageStr = event.title();
        timeStr = event.start().toString("hh:mm") + "-" + event.start().addSecs(event.duration()).toString("hh:mm");
        personsStr = event.persons().join(" and ");
        roomStr = event.room();
    }
    catch(OrmNoObjectException&)
    {
        titleStr = QString("ERROR");
        messageStr = QString("No such event in the DB: %1").arg(QString::number(mEventId));
    }
    catch(...) {} // TODO: implement
    message->setText(messageStr);
    setWindowTitle(titleStr);
    time->setText(timeStr);
    persons->setText(personsStr);
    room->setText(roomStr);
}

void AlarmDialog::runApp()
{
    QString program = QDir::currentPath() + "/" + *qApp->argv();
    QProcess::startDetached(program,QStringList()<<QString::number(mEventId));
    closeDialog();
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
        Event event = Event::getById(mEventId,Conference::activeConference());
        event.setHasAlarm(false);
        event.update("alarm");
    }
    catch(OrmNoObjectException &) {} // TODO: implement
    catch(...) {} // just close dialog
    qApp->quit();
}

