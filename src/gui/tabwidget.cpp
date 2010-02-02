/*
 * Copyright (C) 2010 Ixonos Plc.
 *
 * This file is part of fosdem-schedule.
 *
 * fosdem-schedule is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 2 of the License, or (at your option)
 * any later version.
 *
 * fosdem-schedule is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * fosdem-schedule.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "tabwidget.h"

#include <QMouseEvent>
#include <QPainter>
#include <QTabBar>

TabWidget::TabWidget(QWidget *aParent)
    : QTabWidget(aParent)
    , mPressPoint(0,0)
{
    mInfoImage = QImage(":/icons/info.png");
}

void TabWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    int height = tabBar()->tabRect(currentIndex()).height();
    QImage image = mInfoImage.scaled(QSize(height,height),Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);
    QPainter painter(this);
    painter.drawImage(rect().topRight()-QPoint(image.width(),0),image);
}

void TabWidget::mousePressEvent(QMouseEvent *event)
{
    mPressPoint = event->pos();
}

void TabWidget::mouseReleaseEvent(QMouseEvent *event)
{
    int height = tabBar()->tabRect(currentIndex()).height();
    QImage image = mInfoImage.scaled(QSize(height,height),Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);
    QPoint topLeft = rect().topRight()-QPoint(image.width(),0);
    QRect infoRect = QRect(topLeft, topLeft+QPoint(image.width(),image.height()));
    if( (infoRect.contains(event->pos())) && (infoRect.contains(mPressPoint)) )
    {
        emit(infoIconClicked());
    }
}

