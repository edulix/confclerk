#include "tabcontainer.h"

#include <QFile>
#include <QMessageBox>
#include <QTimer>

#include <treeview.h>
#include <delegate.h>

#include "eventdialog.h"
#include "mapwindow.h"

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

    connect(treeView, SIGNAL(eventHasChanged(int)), SIGNAL(eventHasChanged(int)));
    connect(treeView, SIGNAL(clicked(const QModelIndex &)), SLOT(itemClicked(const QModelIndex &)));
    connect(treeView, SIGNAL(requestForMap(const QModelIndex &)), SLOT(displayMap(const QModelIndex &)));
    connect(treeView, SIGNAL(requestForWarning(const QModelIndex &)), SLOT(displayWarning(const QModelIndex &)));

    if(!Conference::getAll().count()) // no conference(s) in the DB
    {
        dayNavigator->hide(); // hide DayNavigatorWidget
    }
    else
    {
        QDate aStartDate = Conference::getById(Conference::activeConference()).start();
        QDate aEndDate = Conference::getById(Conference::activeConference()).end();
        dayNavigator->setDates(aStartDate, aEndDate);
    }
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
    connect(&dialog, SIGNAL(eventHasChanged(int)), this, SIGNAL(eventHasChanged(int)));
    dialog.exec();
    disconnect(&dialog, SIGNAL(eventHasChanged(int)), this, SIGNAL(eventHasChanged(int)));
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

void TabContainer::displayWarning(const QModelIndex &aIndex)
{
    Q_UNUSED(aIndex);

    QMessageBox::warning(
        this,
        tr("Time Conflict Warning"),
        tr("This event happens at the same time than another one of your favourites.") );
}

void TabContainer::updateTreeViewModel(int aEventId)
{
    static_cast<EventModel*>(treeView->model())->updateModel(aEventId);
}

void TabContainer::setDates(const QDate &aStart, const QDate &aEnd)
{
    dayNavigator->setDates(aStart, aEnd);
}

