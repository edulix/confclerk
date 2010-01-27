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

