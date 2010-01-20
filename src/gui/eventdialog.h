#ifndef EVENTDIALOG_H
#define EVENTDIALOG_H

#include <QDialog>
#include "ui_eventdialog.h"
#include <event.h>

class EventDialog : public QDialog, Ui::EventDialog
{ 
public:
    EventDialog(const int &aEventId, QWidget *aParent = NULL);
    ~EventDialog() {}
private:
    int mEventId;
};

#endif /* EVENTDIALOG_H */

