#include <QMouseEvent>

#include "treeview.h"
#include "delegate.h"

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
        case Delegate::FavouriteControl:
            {
                // handle Favourite Control clicked
                qDebug() << "FAVOURITE CLICKED: " << qVariantValue<QString>(aIndex.data());
            }
            break;
        case Delegate::AlarmControl:
            {
                // handle Alarm Control clicked
                qDebug() << "ALARM CLICKED: " << qVariantValue<QString>(aIndex.data());
            }
            break;
        case Delegate::MapControl:
            {
                // handle Alarm Control clicked
                qDebug() << "MAP CLICKED: " << qVariantValue<QString>(aIndex.data());
            }
        break;
        case Delegate::ControlNone:
        default:
            {
                // item was clicked, but not a control
            }
    };
}

