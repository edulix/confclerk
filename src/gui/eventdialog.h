#ifndef EVENTDIALOG_H
#define EVENTDIALOG_H

#include <QDialog>
#include "ui_eventdialog.h"
#include <event.h>

class DetailsContainer : public QWidget
{
public:
    DetailsContainer(QWidget *aParent = NULL);
    void setPersons(const QStringList &aPersons);
    void setAbstract(const QString &aAbstract);
    void setDescription(const QString &aDescription);
private:
    QBoxLayout *mMainLayout;
    QLabel mPersons;
    QLabel mAbstract;
    QLabel mDescription;
};


class EventDialog : public QDialog, Ui::EventDialog
{ 
public:
    EventDialog(const int &aEventId, QWidget *aParent = NULL);
    ~EventDialog() {}
private:
    int mEventId;
    DetailsContainer mDetails;
};

#endif /* EVENTDIALOG_H */

