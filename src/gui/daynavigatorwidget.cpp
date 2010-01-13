#include "daynavigatorwidget.h"

#include <QDebug>

DayNavigatorWidget::DayNavigatorWidget(QWidget *aParent)
    : QWidget(aParent)
    , mStartDate(QDate())
    , mEndDate(QDate())
    , mCurDate(QDate())
{
    setupUi(this);
    connect(prevDayButton, SIGNAL(clicked()), SLOT(prevDayButtonClicked()));
    connect(nextDayButton, SIGNAL(clicked()), SLOT(nextDayButtonClicked()));
}

void DayNavigatorWidget::setDates(const QDate &aStartDate, const QDate &aEndDate)
{
    Q_ASSERT(aStartDate>=aEndDate);

    //qDebug() << "DayNavigatorWidget::setDates(): " << aStartDate << ", " << aEndDate;
    mStartDate = aStartDate;
    mEndDate = aEndDate;
    mCurDate = aStartDate;

    currentDateLabel->setText(mCurDate.toString());
    if(mStartDate==mEndDate) // only one day conference
    {
        prevDayButton->setDisabled(true);
        nextDayButton->setDisabled(true);
        emit(dateChanged(mCurDate));
    }
    else
    {
        // at least 2-days conference
        prevDayButton->setDisabled(true);
        nextDayButton->setDisabled(false);
        emit(dateChanged(mCurDate));
    }
}

void DayNavigatorWidget::prevDayButtonClicked()
{
    //qDebug() << mStartDate << ":" << mCurDate << ":" << mEndDate;
    if(mCurDate>mStartDate)
    {
        mCurDate = mCurDate.addDays(-1);
        currentDateLabel->setText(mCurDate.toString());
        // check start date
        if(mCurDate==mStartDate || mStartDate==mEndDate)
            prevDayButton->setDisabled(true);
        else
            prevDayButton->setDisabled(false);
        // check end date
        if(mCurDate==mEndDate || mStartDate==mEndDate)
            nextDayButton->setDisabled(true);
        else
            nextDayButton->setDisabled(false);

        emit(dateChanged(mCurDate));
    }
}

void DayNavigatorWidget::nextDayButtonClicked()
{
    //qDebug() << mStartDate << ":" << mCurDate << ":" << mEndDate;
    if(mCurDate<mEndDate)
    {
        mCurDate = mCurDate.addDays(1);
        currentDateLabel->setText(mCurDate.toString());
        // check start date
        if(mCurDate==mStartDate || mStartDate==mEndDate)
            prevDayButton->setDisabled(true);
        else
            prevDayButton->setDisabled(false);
        // check end date
        if(mCurDate==mEndDate || mStartDate==mEndDate)
            nextDayButton->setDisabled(true);
        else
            nextDayButton->setDisabled(false);

        emit(dateChanged(mCurDate));
    }
}

