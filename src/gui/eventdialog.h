#ifndef EVENTDIALOG_H
#define EVENTDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "ui_eventdialog.h"
#include <event.h>

class EventDialog : public QDialog, Ui::EventDialog
{ 
public:
    EventDialog(const QModelIndex &aIndex, QWidget *aParent = NULL);
    ~EventDialog() {}
private:
    QModelIndex mIndex;
};

#endif /* EVENTDIALOG_H */

