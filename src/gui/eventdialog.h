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
    Q_OBJECT
public:
    EventDialog(const int &aEventId, QWidget *aParent = NULL);
    ~EventDialog() {}
private slots:
    void favouriteClicked();
    void alarmClicked();
signals:
    void eventHasChanged(int aEventId); // emited when user changes some event details, eg. sets it Favourite
private:
    int mEventId;
    DetailsContainer mDetails;
};

#endif /* EVENTDIALOG_H */

