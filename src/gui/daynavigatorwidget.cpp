/*
 * Copyright (C) 2010 Ixonos Plc.
 * Copyright (C) 2011 Philipp Spitzer, gregor herrmann
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
#include "daynavigatorwidget.h"

#include <QPainter>
#include <QFontMetrics>
#include <QLabel>

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
    connect(todayButton, SIGNAL(clicked()), SLOT(todayButtonClicked()));

    mFontMetrics = new QFontMetrics(QLabel().font());
}

void DayNavigatorWidget::setDates(const QDate &aStartDate, const QDate &aEndDate)
{
    Q_ASSERT(aStartDate<=aEndDate);

    mStartDate = aStartDate;
    mEndDate = aEndDate;
    mCurDate = aStartDate;

    // QRect rect = mFontMetrics->boundingRect(mCurDate.toString("MMM dd yyyy"));

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

void DayNavigatorWidget::configureNavigation()
{
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
}

void DayNavigatorWidget::prevDayButtonClicked()
{
    if(mCurDate>mStartDate)
    {
        mCurDate = mCurDate.addDays(-1);
        configureNavigation();
        emit(dateChanged(mCurDate));
        selectedDate->update();
    }
}

void DayNavigatorWidget::nextDayButtonClicked()
{
    if(mCurDate<mEndDate)
    {
        mCurDate = mCurDate.addDays(1);
        configureNavigation();
        emit(dateChanged(mCurDate));
        selectedDate->update();
    }
}

void DayNavigatorWidget::todayButtonClicked()
{
    QDate targetDate = QDate::currentDate();
    if (targetDate>mStartDate && targetDate<mEndDate)
    {
        mCurDate = targetDate;
        configureNavigation();
        emit(dateChanged(mCurDate));
        selectedDate->update();
    }
}

void DayNavigatorWidget::paintEvent(QPaintEvent *aEvent)
{
    Q_UNUSED(aEvent);

    QString selectedDateStr = mCurDate.toString("dddd\nyyyy-MM-dd");
    QPainter painter(this);
    painter.save();
    QRect q(y()-height()+16, x(), height(), width()); // today icon size = 32x32
    painter.rotate(270);
    painter.drawText(q, Qt::AlignCenter, selectedDateStr);
    painter.restore();
}

