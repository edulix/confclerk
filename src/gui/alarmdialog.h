#ifndef ALARMDIALOG_H
#define ALARMDIALOG_H

#include <QDialog>
#include "ui_alarmdialog.h"

class AlarmDialog : public QDialog, Ui::AlarmDialog
{
    Q_OBJECT
    public:
        AlarmDialog(int argc, char *argv[], QWidget *aParent = NULL);
        ~AlarmDialog() {}
    private slots:
        void runApp();
        void snooze();
    private:
        int mEventId; // event ID obtained from 'schedule'
        int mAlarmId; // cookie assigned by alarmd
};

#endif /* ALARMDIALOG_H */

