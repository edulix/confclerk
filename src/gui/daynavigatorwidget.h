#ifndef DAYNAVIGATORWIDGET_H
#define DAYNAVIGATORWIDGET_H

#include "ui_daynavigatorwidget.h"
#include <QObject>
#include <QDate>

class DayNavigatorWidget : public QWidget, private Ui::DayNavigatorWidget
{
    Q_OBJECT
    public:
        DayNavigatorWidget(QWidget *aParent = NULL);
        ~DayNavigatorWidget() {}
        void setDates(const QDate &aStartDate, const QDate &aEndDate);
        QDate getCurrentDate();
    private slots:
        void prevDayButtonClicked();
        void nextDayButtonClicked();
    signals:
        void dateChanged(const QDate &aDate);
    private:
        QDate mStartDate;
        QDate mEndDate;
        QDate mCurDate;
};

#endif /* DAYNAVIGATORWIDGET_H */

