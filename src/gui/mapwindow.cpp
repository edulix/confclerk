#include "mapwindow.h"

MapWindow::MapWindow(const QPixmap &aImage, const QString &aName, QWidget *aParent)
    : QDialog(aParent)
{
    setupUi(this);
    setMouseTracking(true); // to receive mouse events
    setWindowTitle(aName);
    map->setPixmap(aImage);
}

void MapWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    close();
}

