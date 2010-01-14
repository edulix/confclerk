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
            FavouriteControl,
            AlarmControl
        };

        class Control
        {
            public:
                Control(ControlId aControlId, const QString &aImageName)
                    : mId(aControlId)
                    , mImage(new QImage(aImageName))
                    , mDrawPoint(QPoint(0,0))
                { }
                inline QImage *image() const { return mImage; }
                inline void setDrawPoint(const QPoint &aPoint) { mDrawPoint = aPoint; }
                inline QPoint drawPoint(const QRect &aRect) const // for painter to draw Control
                {
                    return QPoint(aRect.x()+aRect.width(),aRect.y()) + mDrawPoint;
                }
                inline QRect drawRect(const QRect &aRect) const // helper for determining if Control was clicked
                {
                    return QRect(drawPoint(aRect), drawPoint(aRect)+QPoint(mImage->size().width(),mImage->size().height()));
                }
            private:
                ControlId mId;
                QImage *mImage;
                QPoint mDrawPoint; // relative 'start-drawing' position (may hold negative values)
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

    private:
        QPointer<QTreeView> mViewPtr;
        QMap<ControlId,Control*> mControls;
};

#endif /* DELEGATE_H */
