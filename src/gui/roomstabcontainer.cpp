
#include "roomstabcontainer.h"

RoomsTabContainer::RoomsTabContainer( QWidget *aParent ) : TabContainer( aParent )
{
}

void RoomsTabContainer::loadEvents( const QDate &aDate, const int aConferenceId )
{
    static_cast<EventModel*>(treeView->model())->loadEventsByRoom( aDate, aConferenceId );
}
