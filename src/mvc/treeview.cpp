#include <QMouseEvent>

#include "treeview.h"
#include "delegate.h"
#include "event.h"
#include "eventmodel.h"

#ifdef MAEMO
#include <alarm.h>
#endif

#include <QDebug>

TreeView::TreeView(QWidget *aParent)
    : QTreeView(aParent)
{
    connect(this, SIGNAL(clicked(QModelIndex)), SLOT(handleItemClicked(QModelIndex)));
}

void TreeView::mouseReleaseEvent(QMouseEvent *aEvent)
{
    QModelIndex index = currentIndex();
    QPoint point = aEvent->pos();

    // test whether we have handled the mouse event
    if(!testForControlClicked(index,point))
    {
        // pass the event to the Base class, so item clicks/events are handled correctly
        QTreeView::mouseReleaseEvent(aEvent);
    }
}

// returns bool if some Control was clicked
bool TreeView::testForControlClicked(const QModelIndex &aIndex, const QPoint &aPoint) 
{
    bool handled = false;

    if(!aIndex.isValid())
        return handled;

    QRect rect = visualRect(aIndex); // visual QRect of selected/clicked item in the list
    Delegate *delegate = static_cast<Delegate*>(itemDelegate(aIndex));
    switch(delegate->whichControlClicked(aIndex,aPoint))
    {
        case Delegate::FavouriteControlOn:
        case Delegate::FavouriteControlOff:
            {
                // handle Favourite Control clicked
                Event event = Event::getById(aIndex.data().toInt(),1);
                if(event.isFavourite())
                    event.setFavourite(false);
                else
                    event.setFavourite(true);
                event.update("favourite");
                qDebug() << " FAVOURITE [" << qVariantValue<QString>(aIndex.data()) << "] -> " << event.isFavourite();
                // since the Favourite icon has changed, update TreeViews accordingly
                // all TreeViews have to listen on this signal
                emit(eventHasChanged(event.id()));
                handled = true;
            }
            break;
        case Delegate::AlarmControlOn:
        case Delegate::AlarmControlOff:
            {
                // handle Alarm Control clicked
                Event event = Event::getById(aIndex.data().toInt(),1);
                if(event.hasAlarm())
                {
                    event.setHasAlarm(false); // update DB
#ifdef MAEMO
                    // remove alarm from the 'alarmd' alrms list
                    Alarm alarm;
                    alarm.deleteAlarm(event.id());
                    // TODO: test if removing was successfull
#endif /* MAEMO */
                }
                else
                {
                    event.setHasAlarm(true);
#ifdef MAEMO
                    // add alarm to the 'alarmd'
                    Alarm alarm;
                    int cookie = alarm.addAlarm(event.id(),QDateTime::currentDateTime().addSecs(10));
                    qDebug() << "cookie: " << cookie;
#endif /* MAEMO */
                }
                event.update("alarm");
                qDebug() << " ALARM [" << qVariantValue<QString>(aIndex.data()) << "] -> " << event.hasAlarm();
                // since the Alarm icon has changed, update TreeView accordingly
                // all TreeViews have to listen on this signal
                emit(eventHasChanged(event.id()));
                handled = true;
            }
            break;
        case Delegate::MapControl:
            {
                // handle Alarm Control clicked
                qDebug() << "MAP CLICKED: " << qVariantValue<QString>(aIndex.data());
                emit(requestForMap(aIndex));
                handled = true;
            }
        break;
        case Delegate::WarningControlOff:
        case Delegate::WarningControlOn:
        {

            qDebug() << "WARNING CLICKED: " << qVariantValue<QString>(aIndex.data());
            // TODO: implement
            emit(requestForWarning(aIndex));
            handled = true;
        }
        break;
        case Delegate::ControlNone:
        default:
            {
                // item was clicked, but not a control
                handled = false;
            }
    };

    return handled;
}

void TreeView::handleItemClicked(const QModelIndex &index)
{
    if(!index.parent().isValid()) // time-group
    {
        if(isExpanded(index)) 
            setExpanded(index, false);
        else
            setExpanded(index, true);
    }
}

void TreeView::setAllExpanded(bool aExpanded)
{
    for(int i=0; i<model()->rowCount(QModelIndex()); i++)
    {
        setExpanded(model()->index(i,0,QModelIndex()),aExpanded);
    }
}

