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
#elif N810
    showMaximized();
    map->setPixmap(aImage.scaled(QSize(400,300),Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation));
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

