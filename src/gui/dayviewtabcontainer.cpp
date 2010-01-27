
#include "dayviewtabcontainer.h"

DayViewTabContainer::DayViewTabContainer(QWidget *aParent) : TabContainer( aParent )
{
}

DayViewTabContainer::~DayViewTabContainer()
{
}

void DayViewTabContainer::loadEvents( const QDate &aDate, const int aConferenceId )
{
    static_cast<EventModel*>(treeView->model())->loadEvents( aDate, aConferenceId );
}
