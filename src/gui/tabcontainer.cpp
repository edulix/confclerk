#include "tabcontainer.h"

#include <QFile>
#include <QMessageBox>
#include <QTimer>

#include <treeview.h>
#include <delegate.h>

#include "eventdialog.h"
#include "mapwindow.h"

#include "conflictsdialog.h"

TabContainer::TabContainer(QWidget *aParent)
    : QWidget(aParent)
{
    setupUi(this);

    treeView->setHeaderHidden(true);
    treeView->setRootIsDecorated(false);
    treeView->setIndentation(0);
    treeView->setAnimated(true);
    treeView->setModel(new EventModel());
    treeView->setItemDelegate(new Delegate(treeView));

    connect(dayNavigator, SIGNAL(dateChanged(const QDate &)), SLOT(updateTreeView(const QDate &)));

    connect(treeView, SIGNAL(eventHasChanged(int,bool)), SIGNAL(eventHasChanged(int,bool)));
    connect(treeView, SIGNAL(clicked(const QModelIndex &)), SLOT(itemClicked(const QModelIndex &)));
    connect(treeView, SIGNAL(requestForMap(const QModelIndex &)), SLOT(displayMap(const QModelIndex &)));
    connect(treeView, SIGNAL(requestForConflicts(const QModelIndex &)), SLOT(displayConflicts(const QModelIndex &)));

    // day navigator is hidden by default
    dayNavigator->hide();
}

void TabContainer::updateTreeView(const QDate &aDate)
{
    dayNavigator->show();
    loadEvents( aDate, Conference::activeConference() );
    treeView->reset();
}

void TabContainer::itemClicked(const QModelIndex &aIndex)
{
    // have to handle only events, not time-groups
    if(!aIndex.parent().isValid()) // time-group
        return;

    EventDialog dialog(static_cast<Event*>(aIndex.internalPointer())->id(),this);
#ifdef N810
    dialog.setFixedWidth(static_cast<QWidget*>(parent())->width());
#endif
    connect(&dialog, SIGNAL(eventHasChanged(int,bool)), this, SIGNAL(eventHasChanged(int,bool)));
    dialog.exec();
    disconnect(&dialog, SIGNAL(eventHasChanged(int,bool)), this, SIGNAL(eventHasChanged(int,bool)));
}

void TabContainer::displayMap(const QModelIndex &aIndex)
{
    Event *event = static_cast<Event*>(aIndex.internalPointer());

    // room names are stored in lower-case format
    // room names are stored without dots in the name, eg. "aw.1124.png" -> "aw1124.png"
    QString mapPath = QString(":/maps/rooms/%1.png").arg(event->room().toLower().remove("."));
    if(!QFile::exists(mapPath))
        mapPath = QString(":/maps/rooms/not-available.png");

    QString roomName;
    if(mapPath.contains("not-available", Qt::CaseInsensitive))
        roomName = QString("Map is not available: %1").arg(event->room());
    else
        roomName = event->room();

    QPixmap map(mapPath);
    MapWindow window(map,roomName,this);
    window.exec();
}

void TabContainer::displayConflicts(const QModelIndex &aIndex)
{
    ConflictsDialog dialog(static_cast<Event*>(aIndex.internalPointer())->id(),this);
#ifdef N810
    dialog.setFixedWidth(static_cast<QWidget*>(parent())->width());
#endif
    connect(&dialog, SIGNAL(eventHasChanged(int,bool)), this, SIGNAL(eventHasChanged(int,bool)));
    dialog.exec();
    disconnect(&dialog, SIGNAL(eventHasChanged(int,bool)), this, SIGNAL(eventHasChanged(int,bool)));
}

void TabContainer::updateTreeViewModel(int aEventId, bool aReloadModel)
{
    if(aReloadModel)
    {
        // requires special handling
        // eg. in case of favourities - some favourities may have changed
        // and so we need to reload them
        int confId = Conference::activeConference();
        QDate startDate = Conference::getById(confId).start();
        QDate endDate = Conference::getById(confId).end();
        dayNavigator->setDates(startDate, endDate);
        updateTreeView( Conference::getById(confId).start() );
    }
    else
    {
        // just update event in the question
        static_cast<EventModel*>(treeView->model())->updateModel(aEventId);
    }
}

void TabContainer::setDates(const QDate &aStart, const QDate &aEnd)
{
    dayNavigator->setDates(aStart, aEnd);
}

