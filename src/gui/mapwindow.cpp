#include "mapwindow.h"

MapWindow::MapWindow(const QPixmap &aImage, QWidget *aParent)
    : QDialog(aParent)
{
    setupUi(this);
    setMouseTracking(true); // to receive mouse events
    map->setPixmap(aImage);
}

void MapWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    close();
}

