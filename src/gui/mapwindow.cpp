#include "mapwindow.h"

MapWindow::MapWindow(const QPixmap &aImage, const QString &aName, QWidget *aParent)
    : QDialog(aParent)
{
    setupUi(this);
#ifdef MAEMO
    showFullScreen();
    //map->setScaledContents(true);
    //map->setPixmap(aImage.scaled(QSize(800,480),Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation));
    map->setPixmap(aImage.scaled(QSize(640,480),Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation));
#else
    map->setPixmap(aImage);
#endif
    setMouseTracking(true); // to receive mouse events
    setWindowTitle(aName);
}

// it is enough to handle mouseReleaseEvent, instead of
// getting/creating mouseClikEvent, since the whole window
// is occupied by only-one widget/label (image/map)
void MapWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    close();
}

