#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QDialog>
#include <QPixmap>
#include "ui_mapwindow.h"

class MapWindow : public QDialog, Ui::MapWindow
{
public:
    MapWindow(const QPixmap &aImage, const QString &aName, QWidget *aParent = NULL);
    ~MapWindow() {}
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif /* MAPWINDOW_H */

