#include "tabcontainer.h"

#include <QFile>
#include <QMessageBox>
#include <QTimer>

#include <sqlengine.h>
#include <appsettings.h>

#include <conference.h>

#include <treeview.h>
#include <eventmodel.h>
#include <delegate.h>

#include "eventdialog.h"
#include "mapwindow.h"

TabContainer::TabContainer(QWidget *aParent)
    : QWidget(aParent)
    , mType(EContainerTypeNone)
{
    setupUi(this);

    searchAgainButton->hide();
    searchHead->hide();

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

    connect(searchButton, SIGNAL(clicked()), SLOT(searchClicked()));
    connect(searchAgainButton, SIGNAL(clicked()), SLOT(searchAgainClicked()));

    if(!Conference::getAll().count()) // no conference(s) in the DB
    {
        dayNavigator->hide(); // hide DayNavigatorWidget
    }
    else
    {
        QDate aStartDate = Conference::getById(AppSettings::confId()).start();
        QDate aEndDate = Conference::getById(AppSettings::confId()).end();
        dayNavigator->setDates(aStartDate, aEndDate);
    }
}

void TabContainer::setType(TabContainer::Type aType)
{
    mType = aType;

    if(aType == EContainerTypeNow)
    {
        QTimer *timer = new QTimer( this );
        connect( timer, SIGNAL(timeout()), SLOT(timerUpdateTreeView()) );
        timer->start( 30000); // 30 seconds timer
    }
    if(aType == EContainerTypeSearch)
    {
        searchHead->show();
    }
}

void TabContainer::updateTreeView(const QDate &aDate)
{
    switch(mType)
    {
        case EContainerTypeDay:
            {
                static_cast<EventModel*>(treeView->model())->loadEvents(aDate,AppSettings::confId());
            }
            break;
        case EContainerTypeFavs:
            {
                static_cast<EventModel*>(treeView->model())->loadFavEvents(aDate,AppSettings::confId());
            }
            break;
        case EContainerTypeTracks:
            {
                static_cast<EventModel*>(treeView->model())->loadEventsByTrack(aDate, AppSettings::confId());
            }
            break;
        case EContainerTypeRooms:
            {
                static_cast<EventModel*>(treeView->model())->loadEventsByRoom(aDate, AppSettings::confId());
            }
            break;
        case EContainerTypeNow:
            {
                static_cast<EventModel*>(treeView->model())->loadNowEvents(AppSettings::confId());
                treeView->setAllExpanded(true);
            }
            break;
        case EContainerTypeSearch:
            {
                treeView->reset();
                int eventsCount = static_cast<EventModel*>(treeView->model())->loadSearchResultEvents(aDate,AppSettings::confId());
                if( eventsCount ||
                        dayNavigator->getCurrentDate() != Conference::getById(AppSettings::confId()).start() ){
                    searchAgainButton->show();
                    dayNavigator->show();
                    treeView->show();
                    searchHead->hide();
                }
                else{
                    treeView->hide();
                    searchAgainButton->hide();
                    dayNavigator->hide();
                    searchHead->show();
                }
            }
            break;
        case EContainerTypeNone:
        default:
            {
                qDebug() << "Container type not specified";
            }
    }
    treeView->reset();
    dayNavigator->show();
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
    switch(mType)
    {
        case EContainerTypeFavs:
            {
                // requires special handling
                // we need to reload favourites, because some favourite could be deleted
                //static_cast<EventModel*>(favTreeView->model())->updateModel(aEventId);
                QDate aStartDate = Conference::getById(AppSettings::confId()).start();
                QDate aEndDate = Conference::getById(AppSettings::confId()).end();
                dayNavigator->setDates(aStartDate, aEndDate);
                updateTreeView( Conference::getById(AppSettings::confId()).start() );
            }
            break;
        case EContainerTypeDay:
        case EContainerTypeNone:
        default:
            {
                static_cast<EventModel*>(treeView->model())->updateModel(aEventId);
            }
    }
}

void TabContainer::setDates(const QDate &aStart, const QDate &aEnd)
{
    dayNavigator->setDates(aStart, aEnd);
}

void TabContainer::timerUpdateTreeView()
{
    if(mType == EContainerTypeNow)
    {
        updateTreeView(QDate());
    }
}

void TabContainer::searchClicked()
{
    if(mType == EContainerTypeSearch)
    {
        QHash<QString,QString> columns;

        if( searchTitle->isChecked() )
            columns.insertMulti("EVENT", "title");
        if( searchAbstract->isChecked() )
            columns.insertMulti("EVENT", "abstract");
        if( searchTag->isChecked() )
            columns.insertMulti("EVENT", "tag");
        if( searchSpeaker->isChecked() )
            columns["PERSON"] = "name";
        if( searchRoom->isChecked() )
            columns["ROOM"] = "name";

        QString keyword = searchEdit->text().replace( QString("%"), QString("\\%") );
        qDebug() << "\nKeyword to search: " << keyword;
        SqlEngine::searchEvent( AppSettings::confId(), columns, keyword );

        QDate startDate = Conference::getById(AppSettings::confId()).start();
        QDate endDate = Conference::getById(AppSettings::confId()).end();
        dayNavigator->setDates(startDate, endDate);
        updateTreeView( Conference::getById(AppSettings::confId()).start() );
    }
}

void TabContainer::searchAgainClicked()
{
    if(mType == EContainerTypeSearch)
    {
        searchHead->show();
        searchAgainButton->hide();
        dayNavigator->hide();
        treeView->hide();
    }
}

