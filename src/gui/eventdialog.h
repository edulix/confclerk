#ifndef EVENTDIALOG_H
#define EVENTDIALOG_H

#include <QDialog>
#include "ui_eventdialog.h"
#include <event.h>

class EventDialog : public QDialog, Ui::EventDialog
{ 
    Q_OBJECT
public:
    EventDialog(const int &aEventId, QWidget *aParent = NULL);
    ~EventDialog() {}
private slots:
    void favouriteClicked();
    void alarmClicked();
signals:
    void eventHasChanged(int aEventId, bool aReloadModel = false); // emited when user changes some event details, eg. sets it Favourite
private:
    int mEventId;
};

#endif /* EVENTDIALOG_H */

