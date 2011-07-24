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
#ifndef DAYNAVIGATORWIDGET_H
#define DAYNAVIGATORWIDGET_H

#include "ui_daynavigatorwidget.h"
#include <QObject>
#include <QDate>

/*#include <QPainter>*/
/*#include <QLabel>*/

/*class QFontMetrics;*/

/*class VerticalLabel : public QWidget*/
/*{*/

/*public:*/
/*VerticalLabel(QWidget *aParent = NULL)*/
/*: QWidget(aParent)*/
/*, mText("")*/
/*{*/
/*mFont = QLabel().font();*/
/*}   */

/*void paintEvent(QPaintEvent *)*/
/*{   */
/*QPainter p(this);*/
/*drawRotatedText(&p, 270, width()/2, height()/2, mText);*/
/*}   */

/*void drawRotatedText(QPainter *aPainter, qreal aDegrees, int x, int y, const QString &aText)*/
/*{   */

/*aPainter->save();*/
/*aPainter->setFont(mFont);*/
/*aPainter->translate(x, y); */
/*aPainter->rotate(aDegrees);*/
/*QFontMetrics fm(mFont);*/
/*QRect r = fm.boundingRect(aText);*/
/*aPainter->drawText(-r.width()/2, fm.descent()/2, aText);*/
/*aPainter->restore();*/
/*}   */

/*void setText(const QString &aText)*/
/*{*/
/*mText = aText;*/
/*update();*/
/*}*/

/*private:*/
/*QString mText;*/
/*QFont mFont;*/
/*};*/

class DayNavigatorWidget : public QWidget, private Ui::DayNavigatorWidget
{
    Q_OBJECT
    public:
        DayNavigatorWidget(QWidget *aParent = NULL);
        ~DayNavigatorWidget() {}
        void setDates(const QDate &aStartDate, const QDate &aEndDate);
    protected:
        void paintEvent(QPaintEvent *);
        void configureNavigation();
    private slots:
        void todayButtonClicked();
        void prevDayButtonClicked();
        void nextDayButtonClicked();
    signals:
        void dateChanged(const QDate &aDate);
    private:
        QDate mStartDate;
        QDate mEndDate;
        QDate mCurDate;
        QFontMetrics *mFontMetrics;
};

#endif /* DAYNAVIGATORWIDGET_H */

