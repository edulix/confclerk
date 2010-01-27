
#include "favtabcontainer.h"

FavTabContainer::FavTabContainer(QWidget *aParent) : TabContainer( aParent )
{
}

void FavTabContainer::loadEvents( const QDate &aDate, const int aConferenceId )
{
    static_cast<EventModel*>(treeView->model())->loadFavEvents( aDate, aConferenceId );
}

void FavTabContainer::updateTreeViewModel(int aEventId)
{
    // requires special handling
    // we need to reload favourites, because some favourite could be deleted
    //static_cast<EventModel*>(favTreeView->model())->updateModel(aEventId);
    int confId = Conference::activeConference();
    QDate startDate = Conference::getById(confId).start();
    QDate endDate = Conference::getById(confId).end();
    dayNavigator->setDates(startDate, endDate);
    updateTreeView( Conference::getById(confId).start() );
}

