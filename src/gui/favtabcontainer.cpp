
#include "favtabcontainer.h"

FavTabContainer::FavTabContainer(QWidget *aParent) : TabContainer( aParent )
{
}

void FavTabContainer::loadEvents( const QDate &aDate, const int aConferenceId )
{
    static_cast<EventModel*>(treeView->model())->loadFavEvents( aDate, aConferenceId );
}

