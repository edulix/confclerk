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
#include <QLabel>


DayNavigatorWidget::DayNavigatorWidget(QWidget *aParent): QWidget(aParent) {
    setupUi(this);    

    connect(prevDayButton, SIGNAL(clicked()), SLOT(prevDayButtonClicked()));
    connect(nextDayButton, SIGNAL(clicked()), SLOT(nextDayButtonClicked()));

    configureNavigation();
}


void DayNavigatorWidget::setDates(const QDate &aStartDate, const QDate &aEndDate) {
    Q_ASSERT(aStartDate.isValid() && aEndDate.isValid() && aStartDate<=aEndDate);

    mStartDate = aStartDate;
    mEndDate = aEndDate;

    if (!mCurDate.isValid()) mCurDate = mStartDate;
    // if mCurDate is out of range, set it to mstartDate
    else if (mCurDate < mStartDate || mCurDate > mEndDate) mCurDate = mStartDate;

    configureNavigation();
    emit(dateChanged(mCurDate));
    this->update();
}


void DayNavigatorWidget::setCurDate(const QDate& curDate) {
    Q_ASSERT(curDate.isValid());
    if (curDate == mCurDate) return;

    if (!mStartDate.isValid()) {
        // the start and end date have not been set
        mStartDate = curDate;
        mEndDate = curDate;
        mCurDate = curDate;
    }

    else if (curDate < mStartDate) mCurDate = mStartDate;
    else if (curDate > mEndDate) mCurDate = mEndDate;
    else mCurDate = curDate;

    configureNavigation();
    emit(dateChanged(mCurDate));
    this->update();
}


void DayNavigatorWidget::unsetDates() {
    mStartDate= QDate();
    mEndDate = QDate();
    mCurDate = QDate();

    configureNavigation();
    emit(dateChanged(mCurDate));
    this->update();
}


void DayNavigatorWidget::configureNavigation() {
    prevDayButton->setDisabled(!mStartDate.isValid() || mCurDate == mStartDate);
    nextDayButton->setDisabled(!mEndDate.isValid() || mCurDate == mEndDate);
}


void DayNavigatorWidget::prevDayButtonClicked() {
    if(mCurDate <= mStartDate) return;
    mCurDate = mCurDate.addDays(-1);
    configureNavigation();
    emit(dateChanged(mCurDate));
    this->update();
}


void DayNavigatorWidget::nextDayButtonClicked() {
    if(mCurDate >= mEndDate) return;
    mCurDate = mCurDate.addDays(1);
    configureNavigation();
    emit(dateChanged(mCurDate));
    this->update();
}


void DayNavigatorWidget::paintEvent(QPaintEvent *aEvent) {
    Q_UNUSED(aEvent);

    QString selectedDateStr = mCurDate.isValid() ? mCurDate.toString("dddd\nyyyy-MM-dd") : tr("No date");
    QPainter painter(this);
    painter.save();

    // rectangle only for the text
    QRect q(-selectedDate->height()-selectedDate->y(), selectedDate->x(), selectedDate->height(), selectedDate->width());
    painter.rotate(270);

    // font size adjustion, static on maemo, dynamically otherwise
    QFont f = painter.font();
#ifdef MAEMO
    qreal factor = 0.8;
#else
    qreal factor = (qreal) 2 * q.width() / painter.fontMetrics().width(selectedDateStr);
#endif
    if (factor < 1) f.setPointSizeF(f.pointSizeF() * factor);
    painter.setFont(f);

    painter.drawText(q, Qt::AlignCenter, selectedDateStr);
    painter.restore();
}
