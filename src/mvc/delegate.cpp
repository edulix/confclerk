#include "delegate.h"
#include "eventmodel.h"

#include <QDebug>
#include <QPainter>

const int RADIUS = 10;
const int SPACER = 15;

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
        // favourite
        if(static_cast<Event*>(index.internalPointer())->isFavourite())
            painter->drawImage(mControls[FavouriteControlOn]->drawPoint(option.rect),*mControls[FavouriteControlOn]->image());
        else
            painter->drawImage(mControls[FavouriteControlOff]->drawPoint(option.rect),*mControls[FavouriteControlOff]->image());
        // alarm
        if(static_cast<Event*>(index.internalPointer())->hasAlarm())
            painter->drawImage(mControls[AlarmControlOn]->drawPoint(option.rect),*mControls[AlarmControlOn]->image());
        else
            painter->drawImage(mControls[AlarmControlOff]->drawPoint(option.rect),*mControls[AlarmControlOff]->image());
        // map
        painter->drawImage(mControls[MapControl]->drawPoint(option.rect),*mControls[MapControl]->image());
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

        // draw icons 
        QPoint drawPoint =
            option.rect.topRight()
            - QPoint(
                    SPACER + mControls[FavouriteControlOn]->image()->width(),
                    - option.rect.height()/2 + mControls[FavouriteControlOn]->image()->height()/2);
        painter->drawImage(drawPoint,*mControls[FavouriteControlOn]->image());
        painter->drawText(drawPoint+QPoint(mControls[FavouriteControlOn]->image()->width()+2, option.rect.height()/2),
                QString::number(numberOfFavourities(index)));
        drawPoint.setX(drawPoint.x() - SPACER - mControls[FavouriteControlOn]->image()->width());
        painter->drawImage(drawPoint,*mControls[AlarmControlOn]->image());
        painter->drawText(drawPoint+QPoint(mControls[FavouriteControlOn]->image()->width()+2, option.rect.height()/2),
                QString::number(numberOfAlarms(index)));
        // draw texts
        drawPoint.setX(drawPoint.x() - SPACER -mControls[AlarmControlOn]->image()->width() - 20);
        drawPoint.setY(drawPoint.y() + option.rect.height()/2);
        painter->drawText(drawPoint,QString("Events: ") + QString::number(index.model()->rowCount(index)));
    }

    //// HIGHLIGHTING SELECTED ITEM
    //if (option.state & QStyle::State_Selected)
        //painter->fillRect(option.rect, option.palette.highlight());

    // draw title
    QPointF titlePointF(option.rect.x()+SPACER,option.rect.y()+option.rect.height()-10);
    QString text;
    if(index.parent().isValid()) // event
        text = qVariantValue<QString>(index.data()) + ": " + static_cast<Event*>(index.internalPointer())->title();
    else // group
        text = qVariantValue<QString>(index.data());
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
    QPoint p(0,0);
    // FAVOURITE ICONs
    // on
    control = new Control(FavouriteControlOn,QString(":icons/favourite-on.png"));
    p = QPoint(0,SPACER);
    p.setX(p.x()-control->image()->width()-SPACER);
    control->setDrawPoint(p);
    mControls.insert(FavouriteControlOn,control);
    // off
    control = new Control(FavouriteControlOff,QString(":icons/favourite-off.png"));
    p = QPoint(0,SPACER);
    p.setX(p.x()-control->image()->width()-SPACER);
    control->setDrawPoint(p);
    mControls.insert(FavouriteControlOff,control);

    // ALARM ICONs
    // on
    control = new Control(AlarmControlOn,QString(":icons/alarm-on.png"));
    p = mControls[FavouriteControlOn]->drawPoint();
    p.setX(p.x()-control->image()->width()-SPACER);
    control->setDrawPoint(p);
    mControls.insert(AlarmControlOn,control);
    // off
    control = new Control(AlarmControlOff,QString(":icons/alarm-off.png"));
    p = mControls[FavouriteControlOff]->drawPoint();
    p.setX(p.x()-control->image()->width()-SPACER);
    control->setDrawPoint(p);
    mControls.insert(AlarmControlOff,control);

    // MAP ICON
    control = new Control(MapControl,QString(":icons/compass.png"));
    p = mControls[AlarmControlOn]->drawPoint();
    p.setX(p.x()-control->image()->width()-SPACER);
    control->setDrawPoint(p);
    mControls.insert(MapControl,control);
}

bool Delegate::isPointFromRect(const QPoint &aPoint, const QRect &aRect) const
{
    if( (aPoint.x()>=aRect.left() && aPoint.x()<=aRect.right()) && (aPoint.y()>=aRect.top() && aPoint.y()<=aRect.bottom()) )
        return true;

    return false;
}

int Delegate::numberOfFavourities(const QModelIndex &index) const
{
    if(index.parent().isValid()) // it's event, not time-group
        return 0;

    int nrofFavs = 0;
    for(int i=0; i<index.model()->rowCount(index); i++)
        if(static_cast<Event*>(index.child(i,0).internalPointer())->isFavourite())
            nrofFavs++;

    return nrofFavs;
}

int Delegate::numberOfAlarms(const QModelIndex &index) const
{
    if(index.parent().isValid()) // it's event, not time-group
        return 0;

    int nrofAlarms = 0;
    for(int i=0; i<index.model()->rowCount(index); i++)
        if(static_cast<Event*>(index.child(i,0).internalPointer())->hasAlarm())
            nrofAlarms++;

    return nrofAlarms;
}

