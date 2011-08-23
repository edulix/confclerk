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
#include "delegate.h"
#include "eventmodel.h"
#include <track.h>

#include <QDebug>
#include <QPainter>

#include "room.h"

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
    if (!mViewPtr)
        return;

    painter->save();

    QColor textColor = option.palette.color(QPalette::Text);

    if(hasParent(index))
    {
        // entry horizontal layout:
        // * spacer (aka y position of image)
        // * image
        // * rest is text, which is 1 line of title with big letters and 2 lines of Presenter and Track
        int aux = option.rect.height() - SPACER - mControls[FavouriteControlOn]->image()->height();
        Event *event = static_cast<Event*>(index.internalPointer());

        // font SMALL
        QFont fontSmall = option.font;
        fontSmall.setBold(false);
        fontSmall.setPixelSize(aux*0.2);
        QFontMetrics fmSmall(fontSmall);
        // font SMALL bold
        QFont fontSmallB = fontSmall;
        fontSmallB.setBold(true);

        // font BIG
        QFont fontBig = option.font;
        fontBig.setBold(false);
        fontBig.setPixelSize(aux*0.33);
        QFontMetrics fmBig(fontBig);

        // font BIG bold
        QFont fontBigB = fontBig;
        fontBigB.setBold(true);
        QFontMetrics fmBigB(fontBigB);

        // background (in case of time conflicts)
        if(event->hasTimeConflict()) {
            painter->setBrush(Qt::yellow);
            painter->setPen(Qt::NoPen);
            painter->drawRect(option.rect);
        }

        // background (without time conflicts)
        else {
            QStyleOption styleOption;
            styleOption.rect = option.rect;
            qApp->style()->drawPrimitive(QStyle::PE_PanelItemViewItem, &styleOption, painter, mViewPtr);
        }

        // draw Controls
        foreach(Control* c, mControls.values()) {
            c->setEnabled(false);
        }
        if(event->isFavourite())
            mControls[FavouriteControlOn]->paint(painter, option.rect);
        else
            mControls[FavouriteControlOff]->paint(painter, option.rect);
#ifdef MAEMO
        if(event->hasAlarm())
            mControls[AlarmControlOn]->paint(painter, option.rect);
        else
            mControls[AlarmControlOff]->paint(painter, option.rect);
#endif
        if(event->hasTimeConflict())
            mControls[WarningControl]->paint(painter, option.rect);

        // draw texts
        // it starts just below the image
        // ("position of text" is lower-left angle of the first letter,
        //  so the first line is actually at the same height as the image)
        painter->setPen(QPen(event->hasTimeConflict() ? Qt::black : textColor));
        QPointF titlePointF(option.rect.x() + SPACER,
                            option.rect.y() + SPACER + mControls[FavouriteControlOn]->image()->height());
        QTime start = event->start().time();
        painter->setFont(fontBig);
        painter->drawText(titlePointF,start.toString("hh:mm") + "-" + start.addSecs(event->duration()).toString("hh:mm") + ", " + event->roomName());

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
        QString presenterPrefix = event->persons().count() < 2 ? "Presenter" : "Presenters";
        painter->drawText(titlePointF,presenterPrefix + ": " + event->persons().join(" and "));

        // track
        titlePointF.setY(titlePointF.y()+fmSmall.height()-fmSmall.descent());
        painter->drawText(titlePointF,"Track: " + Track::retrieveTrackName(event->trackId()));
    }

    else // doesn't have parent - time-groups' elements (top items)
    {
        int numFav = numberOfFavourities(index);

        QStyleOptionButton styleOptionButton;
        styleOptionButton.rect = option.rect;
        if (isExpanded(index)) styleOptionButton.state = QStyle::State_Sunken;
        // styleOptionButton.text = qVariantValue<QString>(index.data());
        qApp->style()->drawPrimitive(QStyle::PE_PanelButtonCommand, &styleOptionButton, painter, mViewPtr);
        // qApp->style()->drawControl(QStyle::CE_PushButtonLabel, &styleOptionButton, painter, mViewPtr);
        // qApp->style()->drawPrimitive(QStyle::PE_IndicatorArrowDown, &styleOptionButton, painter, mViewPtr);

        QFont fontSmall = option.font;
        fontSmall.setBold(true);
        fontSmall.setPixelSize(option.rect.height()*scaleFactor1);
        QFontMetrics fmSmall(fontSmall);

        QFont fontBig = option.font;
        fontBig.setBold(true);
        fontBig.setPixelSize(option.rect.height()*scaleFactor2);
        QFontMetrics fmBig(fontBig);

        int spacer = (fmSmall.boundingRect("999").width() < SPACER) ? SPACER : fmSmall.boundingRect("999").width();

        // draw icons
        painter->setPen(QPen(textColor));
        painter->setFont(fontSmall);
        QImage *image = mControls[numFav ? FavouriteControlOn : FavouriteControlOff]->image();
        QPoint drawPoint =
            option.rect.topRight()
            - QPoint(
                    spacer + image->width(),
                    - option.rect.height()/2 + image->height()/2);
        painter->drawImage(drawPoint,*image);
        painter->drawText(drawPoint+QPoint(image->width()+2, image->height() - 2),
                QString::number(numFav));
#ifdef MAEMO
        drawPoint.setX(drawPoint.x() - spacer - image->width());
        painter->drawImage(drawPoint,*mControls[AlarmControlOn]->image());
        painter->drawText(drawPoint+QPoint(image->width()+2, image->height() - 2),
                QString::number(numberOfAlarms(index)));
#endif
        // draw texts
        QString numEvents = QString::number(index.model()->rowCount(index)).append("/");
        drawPoint.setX(drawPoint.x() - spacer - fmSmall.boundingRect(numEvents).width());
        drawPoint.setY(drawPoint.y()+image->height() - 2);
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
        Control *control = mControls[id];
        if (control->enabled()
            and control->drawRect(static_cast<QTreeView*>(parent())->visualRect(aIndex)).contains(aPoint))
        {
            return id;
        }
    }

    return ControlNone;
}

Delegate::Control::Control(ControlId aControlId, const QString &aImageName, const Control* prev_control)
    : mId(aControlId)
    , mImage(new QImage(aImageName))
    , mDrawPoint(QPoint(0,0))
    , mEnabled(false)
{
    QPoint p;
    if (prev_control == NULL) {
        p = QPoint(0, SPACER);
    } else {
        p = prev_control->drawPoint();
    }
    p.setX(p.x()-image()->width()-SPACER);
    setDrawPoint(p);
}

void Delegate::Control::paint(QPainter* painter, const QRect rect)
{
    painter->drawImage(drawPoint(rect),*image());
    setEnabled(true);
}

void Delegate::defineControls()
{
    // FAVOURITE ICONs
    // on
    mControls.insert(FavouriteControlOn, new Control(FavouriteControlOn, QString(":icons/emblem-new.png"), NULL));
    // off
    mControls.insert(FavouriteControlOff, new Control(FavouriteControlOff, QString(":icons/emblem-new-off.png"), NULL));

#ifdef MAEMO
    // ALARM ICONs
    // on
    mControls.insert(AlarmControlOn,
                    new Control(AlarmControlOn, QString(":icons/appointment-soon.png"), mControls[FavouriteControlOn]));
    // off
    mControls.insert(AlarmControlOff,
                    new Control(AlarmControlOff, QString(":icons/appointment-soon-off.png"), mControls[FavouriteControlOff]));
#endif

    // WARNING ICON
    mControls.insert(WarningControl,
                    new Control(WarningControl, QString(":icons/dialog-warning.png"), mControls[FavouriteControlOn]));
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

