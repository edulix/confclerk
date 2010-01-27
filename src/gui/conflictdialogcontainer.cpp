
#include "conflictdialogcontainer.h"

ConflictDialogContainer::ConflictDialogContainer(QWidget *aParent)
    : TabContainer( aParent )
{
}

void ConflictDialogContainer::loadEvents( const QDate &aDate, const int aConferenceId )
{
    static_cast<EventModel*>(treeView->model())->loadConflictEvents( mEventId, aConferenceId );
    dayNavigator->hide();
}

