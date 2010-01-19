#include "mapwindow.h"

MapWindow::MapWindow(const QPixmap &aImage, const QString &aName, QWidget *aParent)
    : QDialog(aParent)
{
    setupUi(this);
    setMouseTracking(true); // to receive mouse events
    setWindowTitle(aName);
    map->setPixmap(aImage);
}

// it is enough to handle mouseReleaseEvent, instead of
// getting/creating mouseClikEvent, since the whole window
// is occupied by only-one widget/label (image/map)
void MapWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    close();
}

