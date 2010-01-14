#include "delegate.h"
#include "eventmodel.h"

#include <QDebug>
#include <QPainter>

const int RADIUS = 10;
const int SPACER = RADIUS;

Delegate::Delegate(QTreeView *aParent)
    : QItemDelegate(aParent)
    , mViewPtr(aParent)
{
    mControls.clear();
    defineControls();
}

Delegate::~Delegate()
{
    QListIterator<ControlId> i(mControls.keys());
    while (i.hasNext())
    {
        delete mControls[i.next()]->image();
    }
}

void Delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(!mViewPtr)
        return;

    painter->save();

    QColor bkgrColor = Qt::cyan;
    QPen borderPen(bkgrColor.darker());
    if(hasParent(index))
    {
        if(isLast(index))
        {
            QLinearGradient lastGradient(option.rect.topLeft(), option.rect.bottomLeft());
            lastGradient.setColorAt(0.0, Qt::white);
            lastGradient.setColorAt(0.5, bkgrColor);
            lastGradient.setColorAt(1.0, Qt::white);

            QPainterPath endPath;
            endPath.moveTo(option.rect.topLeft());
            endPath.lineTo(option.rect.bottomLeft()-QPoint(0, RADIUS));
            endPath.arcTo(option.rect.left(), option.rect.bottom()-2*RADIUS, 2*RADIUS, 2*RADIUS, 180, 90);
            endPath.lineTo(option.rect.bottomRight()-QPoint(RADIUS, 0));
            endPath.arcTo(option.rect.right()-2*RADIUS, option.rect.bottom()-2*RADIUS, 2*RADIUS, 2*RADIUS, 270, 90);
            endPath.lineTo(option.rect.topRight());

            //painter->setBrush( bkgrColor );
            painter->setBrush(lastGradient);
            painter->setPen(borderPen);
            painter->drawPath(endPath);

            painter->setFont(option.font);
        }
        else // middle elements
        {

            QLinearGradient middleGradient(option.rect.topLeft(), option.rect.bottomLeft());
            middleGradient.setColorAt(0.0, Qt::white);
            middleGradient.setColorAt(0.25, bkgrColor);
            middleGradient.setColorAt(0.5, Qt::white);
            middleGradient.setColorAt(0.75, bkgrColor);
            middleGradient.setColorAt(1.0, Qt::white);

            //painter->setBrush( bkgrColor );
            painter->setBrush(middleGradient);
            painter->setPen(Qt::NoPen);
            painter->drawRect(option.rect);

            painter->setPen(borderPen);
            // vertical lines
            painter->drawLine(option.rect.topLeft(), option.rect.bottomLeft());
            painter->drawLine(option.rect.topRight(), option.rect.bottomRight());
            // horizontal lines
            painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());

            painter->setFont(option.font);
        }

        // draw Controls
        painter->drawImage(mControls[FavouriteControl]->drawPoint(option.rect),*mControls[FavouriteControl]->image());
        painter->drawImage(mControls[AlarmControl]->drawPoint(option.rect),*mControls[AlarmControl]->image());
    }
    else // doesn't have parent - time-groups' elements (top items)
    {
        QLinearGradient titleGradient(option.rect.topLeft(), option.rect.topRight());
        //titleGradient.setColorAt(0.0, Qt::white);
        titleGradient.setColorAt(0.0, bkgrColor);
        titleGradient.setColorAt(0.5, Qt::white);
        titleGradient.setColorAt(1.0, bkgrColor);

        QPainterPath titlePath;
        if(isExpanded(index))
        {
            titlePath.moveTo(option.rect.bottomLeft());
            titlePath.lineTo(option.rect.topLeft()+QPoint(0, RADIUS));
            titlePath.arcTo(option.rect.left(), option.rect.top(), 2*RADIUS, 2*RADIUS, 180, -90);
            titlePath.lineTo(option.rect.topRight()-QPoint(RADIUS, 0));
            titlePath.arcTo(option.rect.right()-2*RADIUS, option.rect.top(), 2*RADIUS, 2*RADIUS, 90, -90);
            titlePath.lineTo(option.rect.bottomRight());
            titlePath.closeSubpath();
        }
        else
        {
            titlePath.lineTo(option.rect.topLeft()+QPoint(0, RADIUS));
            titlePath.arcTo(option.rect.left(), option.rect.top(), 2*RADIUS, 2*RADIUS, 180, -90);
            titlePath.lineTo(option.rect.topRight()-QPoint(RADIUS, 0));
            titlePath.arcTo(option.rect.right()-2*RADIUS, option.rect.top(), 2*RADIUS, 2*RADIUS, 90, -90);
            titlePath.lineTo(option.rect.bottomRight()-QPoint(0, RADIUS));
            titlePath.arcTo(option.rect.right()-2*RADIUS, option.rect.bottom()-2*RADIUS, 2*RADIUS, 2*RADIUS, 0, -90);
            titlePath.lineTo(option.rect.bottomLeft()+QPoint(RADIUS, 0));
            titlePath.arcTo(option.rect.left(), option.rect.bottom()-2*RADIUS, 2*RADIUS, 2*RADIUS, 270, -90);      
            titlePath.closeSubpath();
        }

        painter->setBrush(titleGradient);
        painter->setPen(borderPen);
        painter->drawPath(titlePath);

        QFont font = option.font;
        font.setBold(true);
        painter->setFont(font);
    }

    //// HIGHLIGHTING SELECTED ITEM
    //if (option.state & QStyle::State_Selected)
        //painter->fillRect(option.rect, option.palette.highlight());

    // draw title
    QPointF titlePointF(option.rect.x(),option.rect.y()+option.rect.height()-10);
    QString text = qVariantValue<QString>(index.data());
    painter->drawText(titlePointF,text);

    painter->restore();
}

QSize Delegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)

    if (index.internalId() == 0) // time group
    {
        return QSize(30,30);
    }
    else // event
    {
        return QSize(100,100);
    }
}

bool Delegate::hasParent( const QModelIndex &index ) const
{
    if( index.parent().isValid() )
        return true;
    else
        return false;
}
  
bool Delegate::isLast( const QModelIndex &index ) const
{
    if(!hasParent(index))
        return false; // what should be returned here?

    if(index.row() >= (index.model()->rowCount(index.parent())-1))
        return true;
    else
        return false;
}

bool Delegate::isExpanded( const QModelIndex &index ) const
{
    if( !mViewPtr )
        return false;
    else
        return mViewPtr->isExpanded( index );
}

Delegate::ControlId Delegate::whichControlClicked(const QModelIndex &aIndex, const QPoint &aPoint) const
{
    if(!hasParent(aIndex)) // time-group item (root item)
        return ControlNone;

    QListIterator<ControlId> i(mControls.keys());
    while (i.hasNext())
    {
        ControlId id = i.next();
        if(mControls[id]->drawRect(static_cast<QTreeView*>(parent())->visualRect(aIndex)).contains(aPoint))
            return id;
    }

    return ControlNone;
}

void Delegate::defineControls()
{
    Control *control;
    // FAVOURITE ICON
    control = new Control(FavouriteControl,QString(":icons/favourite-on.png"));
    control->setDrawPoint(QPoint(-control->image()->width()-SPACER,SPACER));
    mControls.insert(FavouriteControl,control);

    // ALARM ICON
    control = new Control(AlarmControl,QString(":icons/alarm-on.png"));
    control->setDrawPoint(QPoint(-mControls[FavouriteControl]->image()->width()-control->image()->width()-2*SPACER,SPACER));
    mControls.insert(AlarmControl,control);
}

bool Delegate::isPointFromRect(const QPoint &aPoint, const QRect &aRect) const
{
    if( (aPoint.x()>=aRect.left() && aPoint.x()<=aRect.right()) && (aPoint.y()>=aRect.top() && aPoint.y()<=aRect.bottom()) )
        return true;

    return false;
}

