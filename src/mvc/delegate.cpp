#include "delegate.h"
#include "eventmodel.h"
#include <track.h>

#include <QDebug>
#include <QPainter>

const int RADIUS = 10;
const int SPACER = 10;

const double scaleFactor1 = 0.4;
const double scaleFactor2 = 0.8;

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
    //QColor bkgrColor = QColor(0,0,113);
    //QPen borderPen(Qt::cyan);
    if(hasParent(index))
    {
        int aux = option.rect.height() - mControls[FavouriteControlOn]->drawPoint().y() - mControls[FavouriteControlOn]->image()->height();
        // font SMALL
        QFont fontSmall = option.font;
        fontSmall.setBold(false);
        fontSmall.setPixelSize(aux*0.2);
        QFontMetrics fmSmall(fontSmall);
        // font SMALL bold
        QFont fontSmallB = fontSmall;
        fontSmallB.setBold(true);
        QFontMetrics fmSmallB(fontSmallB);

        // font BIG
        QFont fontBig = option.font;
        fontBig.setBold(false);
        fontBig.setPixelSize(aux*0.33);
        QFontMetrics fmBig(fontBig);
        // font BIG bold
        QFont fontBigB = fontBig;
        fontBigB.setBold(true);
        QFontMetrics fmBigB(fontBigB);

        //int spacer = (fmSmall.boundingRect("999").width() < SPACER) ? SPACER : fmSmall.boundingRect("999").width();

        //Time conflicts are colored differently
        if(static_cast<Event*>(index.internalPointer())->isFavourite())
        if(static_cast<Event*>(index.internalPointer())->hasTimeConflict())
        {
            bkgrColor = Qt::yellow;
        }

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

            painter->setBrush( bkgrColor );
            //painter->setBrush(lastGradient);
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

            painter->setBrush( bkgrColor );
            //painter->setBrush(middleGradient);
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
#ifdef MAEMO
        // alarm
        if(static_cast<Event*>(index.internalPointer())->hasAlarm())
            painter->drawImage(mControls[AlarmControlOn]->drawPoint(option.rect),*mControls[AlarmControlOn]->image());
        else
            painter->drawImage(mControls[AlarmControlOff]->drawPoint(option.rect),*mControls[AlarmControlOff]->image());
#endif
        // map
        painter->drawImage(mControls[MapControl]->drawPoint(option.rect),*mControls[MapControl]->image());
        // Time conflict
        if(static_cast<Event*>(index.internalPointer())->hasTimeConflict())
            painter->drawImage(mControls[WarningControl]->drawPoint(option.rect),*mControls[WarningControl]->image());

        // draw texts
        Event *event = static_cast<Event*>(index.internalPointer());
        QPointF titlePointF(mControls[FavouriteControlOn]->drawPoint(option.rect));
        titlePointF.setX(option.rect.x()+SPACER);
        titlePointF.setY(titlePointF.y()+mControls[FavouriteControlOn]->image()->height());
        QTime start = event->start().time();
        painter->setFont(fontBig);
        painter->drawText(titlePointF,start.toString("hh:mm") + "-" + start.addSecs(event->duration()).toString("hh:mm") + ", " + event->room());
        // title
        titlePointF.setY(titlePointF.y()+fmBig.height()-fmBig.descent());
        painter->setFont(fontBigB);
        QString title = event->title();
        if(fmBigB.boundingRect(title).width() > (option.rect.width()-2*SPACER)) // the title won't fit the screen
        {
            // chop words from the end
            while( (fmBigB.boundingRect(title + "...").width() > (option.rect.width()-2*SPACER)) && !title.isEmpty())
            {
                title.chop(1);
                // chop characters one-by-one from the end
                while( (!title.at(title.length()-1).isSpace()) && !title.isEmpty())
                {
                    title.chop(1);
                }
            }
            title += "...";
        }
        painter->drawText(titlePointF,title);
        // persons
        titlePointF.setY(titlePointF.y()+fmSmall.height()-fmSmall.descent());
        painter->setFont(fontSmall);
        painter->drawText(titlePointF,"Presenter(s): " + event->persons().join(" and "));
        // track
        titlePointF.setY(titlePointF.y()+fmSmall.height()-fmSmall.descent());
        painter->drawText(titlePointF,"Track: " + Track::retrieveTrackName(event->trackId()));
    }
    else // doesn't have parent - time-groups' elements (top items)
    {
        QFont fontSmall = option.font;
        fontSmall.setBold(true);
        fontSmall.setPixelSize(option.rect.height()*scaleFactor1);
        QFontMetrics fmSmall(fontSmall);

        QFont fontBig = option.font;
        fontBig.setBold(true);
        fontBig.setPixelSize(option.rect.height()*scaleFactor2);
        QFontMetrics fmBig(fontBig);

        int spacer = (fmSmall.boundingRect("999").width() < SPACER) ? SPACER : fmSmall.boundingRect("999").width();

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

        // draw icons 
        painter->setFont(fontSmall);
        QPoint drawPoint =
            option.rect.topRight()
            - QPoint(
                    spacer + mControls[FavouriteControlOn]->image()->width(),
                    - option.rect.height()/2 + mControls[FavouriteControlOn]->image()->height()/2);
        painter->drawImage(drawPoint,*mControls[FavouriteControlOn]->image());
        painter->drawText(drawPoint+QPoint(mControls[FavouriteControlOn]->image()->width()+2, option.rect.height()/2),
                QString::number(numberOfFavourities(index)));
#ifdef MAEMO
        drawPoint.setX(drawPoint.x() - spacer - mControls[FavouriteControlOn]->image()->width());
        painter->drawImage(drawPoint,*mControls[AlarmControlOn]->image());
        painter->drawText(drawPoint+QPoint(mControls[FavouriteControlOn]->image()->width()+2, option.rect.height()/2),
                QString::number(numberOfAlarms(index)));
#endif
        // draw texts
        QString numEvents = QString::number(index.model()->rowCount(index)).append("/");
        drawPoint.setX(drawPoint.x() - spacer - fmSmall.boundingRect(numEvents).width());
        drawPoint.setY(drawPoint.y() + option.rect.height()/2);
        painter->drawText(drawPoint,numEvents);

        QPointF titlePointF = QPoint(
                option.rect.x()+SPACER,
                option.rect.y()+option.rect.height()-fmBig.descent());
        painter->setFont(fontBig);

        painter->drawText(titlePointF,qVariantValue<QString>(index.data()));
    }

    //// HIGHLIGHTING SELECTED ITEM
    //if (option.state & QStyle::State_Selected)
        //painter->fillRect(option.rect, option.palette.highlight());

    painter->restore();
}

QSize Delegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)

    if (index.internalId() == 0) // time group
    {
        return QSize(40,40);
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
        {
            if(id == WarningControl)
            {
                if(static_cast<Event*>(aIndex.internalPointer())->hasTimeConflict())
                    return id;
            }
            else
                return id;
        }
    }

    return ControlNone;
}

void Delegate::defineControls()
{
    Control *control;
    QPoint p(0,0);
    // FAVOURITE ICONs
    // on
    control = new Control(FavouriteControlOn,QString(":icons/favourite-onBig.png"));
    p = QPoint(0,SPACER);
    p.setX(p.x()-control->image()->width()-SPACER);
    control->setDrawPoint(p);
    mControls.insert(FavouriteControlOn,control);
    // off
    control = new Control(FavouriteControlOff,QString(":icons/favourite-offBig.png"));
    p = QPoint(0,SPACER);
    p.setX(p.x()-control->image()->width()-SPACER);
    control->setDrawPoint(p);
    mControls.insert(FavouriteControlOff,control);

#ifdef MAEMO
    // ALARM ICONs
    // on
    control = new Control(AlarmControlOn,QString(":icons/alarm-onBig.png"));
    p = mControls[FavouriteControlOn]->drawPoint();
    p.setX(p.x()-control->image()->width()-SPACER);
    control->setDrawPoint(p);
    mControls.insert(AlarmControlOn,control);
    // off
    control = new Control(AlarmControlOff,QString(":icons/alarm-offBig.png"));
    p = mControls[FavouriteControlOff]->drawPoint();
    p.setX(p.x()-control->image()->width()-SPACER);
    control->setDrawPoint(p);
    mControls.insert(AlarmControlOff,control);

    // MAP ICON
    control = new Control(MapControl,QString(":icons/compassBig.png"));
    p = mControls[AlarmControlOn]->drawPoint();
    p.setX(p.x()-control->image()->width()-SPACER);
    control->setDrawPoint(p);
    mControls.insert(MapControl,control);
#else
    // MAP ICON
    control = new Control(MapControl,QString(":icons/compassBig.png"));
    p = mControls[FavouriteControlOn]->drawPoint();
    p.setX(p.x()-control->image()->width()-SPACER);
    control->setDrawPoint(p);
    mControls.insert(MapControl,control);
#endif

    // WARNING ICON
    control = new Control(WarningControl,QString(":icons/exclamation.png"));
    p = mControls[MapControl]->drawPoint();
    p.setX(p.x()-control->image()->width()-SPACER);
    control->setDrawPoint(p);
    mControls.insert(WarningControl,control);
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

