/*
 * Copyright (C) 2010 Ixonos Plc.
 * Copyright (C) 2011-2012 Philipp Spitzer, gregor herrmann, Stefan Stahl
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
#ifndef DAYNAVIGATORWIDGET_H
#define DAYNAVIGATORWIDGET_H

#include "ui_daynavigatorwidget.h"
#include <QObject>
#include <QDate>

/** The DayNavigator widget manages three dates, the startDate, curDate and endDate.
Either startDate, curDate and endDate all have to be valid and startDate <= curDate <= endDate,
OR all three dates are invalid (representing "no date range", e.g. no conference). */
class DayNavigatorWidget : public QWidget, private Ui::DayNavigatorWidget {
    Q_OBJECT
    public:
        DayNavigatorWidget(QWidget *aParent = NULL);
        ~DayNavigatorWidget() {}
        void setDates(const QDate &aStartDate, const QDate &aEndDate);
        void setCurDate(const QDate& curDate);
        QDate startDate() const {return mStartDate;}
        QDate curDate() const {return mCurDate;}
        QDate endDate() const {return mEndDate;}
        void unsetDates();
    protected:
        void paintEvent(QPaintEvent *);
        void configureNavigation();
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

