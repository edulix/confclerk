/*
 * Copyright (C) 2010 Ixonos Plc.
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
#ifndef DELEGATE_H
#define DELEGATE_H

#include <QItemDelegate>
#include <QTreeView>
#include <QPointer>

class Delegate : public QItemDelegate
{
    Q_OBJECT

    public:

        enum ControlId
        {
            ControlNone = 0,
            FavouriteControlOn,
            FavouriteControlOff,
            AlarmControlOn,
            AlarmControlOff,
            MapControl,
            WarningControl
        };

        class Control
        {
            public:
                Control(ControlId aControlId, const QString &aImageName, const Control* prev_control);

                inline QImage *image() const { return mImage; }
                inline void setDrawPoint(const QPoint &aPoint) { mDrawPoint = aPoint; }
                inline QRect drawRect(const QRect &aRect) const // helper for determining if Control was clicked
                {
                    return QRect(drawPoint(aRect), drawPoint(aRect)+QPoint(mImage->size().width(),mImage->size().height()));
                }
                void paint(QPainter* painter, const QRect rect);

                bool enabled() const { return mEnabled; }
                void setEnabled(bool v) { mEnabled = v; }
            private:
                inline QPoint drawPoint(const QRect &aRect = QRect()) const // for painter to draw Control
                {
                    if(aRect == QRect()) // null rectangle
                        return mDrawPoint; // returns relative drawing point
                    else
                        return QPoint(aRect.x()+aRect.width(),aRect.y()) + mDrawPoint; // returns absolute drawing point
                }

                ControlId mId;
                QImage *mImage;
                QPoint mDrawPoint; // relative 'start-drawing' position (may hold negative values)
                bool mEnabled;
        };

        Delegate(QTreeView *aParent); // the delegate 'owner' has to be specified in the constructor - it's used to obtain visualRect of selected item/index
        ~Delegate();

        void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
        //
        Delegate::ControlId whichControlClicked(const QModelIndex &aIndex, const QPoint &aPoint) const;
        bool isPointFromRect(const QPoint &aPoint, const QRect &aRect) const;

    private:
        bool hasParent( const QModelIndex &index ) const;
        bool isLast( const QModelIndex &index ) const;
        bool isExpanded( const QModelIndex &index ) const;
        void defineControls();
        // TODO: the better place for these methods would be 'eventmodel'
        // they are used in 'paint' method and so it's better to obtain number of
        // favourities/alarms once when the data has changed and not to call
        // these methods which iterate over all Events in corresponding group
        // every time it requires them
        int numberOfFavourities(const QModelIndex &index) const;
        int numberOfAlarms(const QModelIndex &index) const;

    private:
        QPointer<QTreeView> mViewPtr;
        QMap<ControlId,Control*> mControls;
};

#endif /* DELEGATE_H */

