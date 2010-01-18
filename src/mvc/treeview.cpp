#include <QMouseEvent>

#include "treeview.h"
#include "delegate.h"
#include "event.h"
#include "eventmodel.h"

#include <QDebug>

TreeView::TreeView(QWidget *aParent)
    : QTreeView(aParent)
{
}

void TreeView::mouseReleaseEvent(QMouseEvent *aEvent)
{
    QModelIndex index = currentIndex();
    QPoint point = aEvent->pos();

    testForControlClicked(index,point);

    // pass the event to the Base class, so item clicks/events are handled correctly
    QTreeView::mouseReleaseEvent(aEvent);
}

void TreeView::testForControlClicked(const QModelIndex &aIndex, const QPoint &aPoint) 
{
    if(!aIndex.isValid())
        return;

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
                {
                    static_cast<Event*>(aIndex.internalPointer())->setFavourite(false); // list of events
                    event.setFavourite(false); // update DB
                }
                else
                {
                    static_cast<Event*>(aIndex.internalPointer())->setFavourite(true); // list of events
                    event.setFavourite(true);
                }
                qDebug() << " FAVOURITE [" << qVariantValue<QString>(aIndex.data()) << "] -> " << event.isFavourite();
                event.update("favourite");
                // since the Favourite icon has changed, update TreeView accordingly
                static_cast<EventModel*>(model())->emitDataChangedSignal(aIndex,aIndex);
            }
            break;
        case Delegate::AlarmControlOn:
        case Delegate::AlarmControlOff:
            {
                // handle Alarm Control clicked
                Event event = Event::getById(aIndex.data().toInt(),1);
                if(event.hasAlarm())
                {
                    static_cast<Event*>(aIndex.internalPointer())->setHasAlarm(false); // list of events
                    event.setHasAlarm(false); // update DB
                }
                else
                {
                    static_cast<Event*>(aIndex.internalPointer())->setHasAlarm(true); // list of events
                    event.setHasAlarm(true);
                }
                qDebug() << " ALARM [" << qVariantValue<QString>(aIndex.data()) << "] -> " << event.hasAlarm();
                event.update("alarm");
                // since the Alarm icon has changed, update TreeView accordingly
                static_cast<EventModel*>(model())->emitDataChangedSignal(aIndex,aIndex);

            }
            break;
        case Delegate::MapControl:
            {
                // handle Alarm Control clicked
                qDebug() << "MAP CLICKED: " << qVariantValue<QString>(aIndex.data());
                emit(requestForMap(aIndex));
            }
        break;
        case Delegate::ControlNone:
        default:
            {
                // item was clicked, but not a control
            }
    };
}

