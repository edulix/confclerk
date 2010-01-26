#include "tabwidget.h"

#include <QMouseEvent>
#include <QPainter>

#include <QDebug>

const int SPACER = 5;

TabWidget::TabWidget(QWidget *aParent)
    : QTabWidget(aParent)
    , mPressPoint(0,0)
{
    mInfoImage = QImage(":/icons/info.png");
}

void TabWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(rect().topRight()-QPoint(mInfoImage.width()+SPACER,-SPACER),mInfoImage);
}

void TabWidget::mousePressEvent(QMouseEvent *event)
{
    mPressPoint = event->pos();
}

void TabWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint topLeft = rect().topRight()-QPoint(mInfoImage.width()+SPACER,-SPACER);
    QRect infoRect = QRect(topLeft, topLeft+QPoint(mInfoImage.width(),mInfoImage.height()));
    if( (infoRect.contains(event->pos())) && (infoRect.contains(mPressPoint)) )
    {
        emit(infoIconClicked());
    }
}

