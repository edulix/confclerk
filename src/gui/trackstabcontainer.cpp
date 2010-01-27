
#include "trackstabcontainer.h"

TracksTabContainer::TracksTabContainer( QWidget *aParent ) : TabContainer( aParent )
{
}

void TracksTabContainer::loadEvents( const QDate &aDate, const int aConferenceId )
{
    static_cast<EventModel*>(treeView->model())->loadEventsByTrack( aDate, aConferenceId );
}
