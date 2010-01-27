
#include "conflictdialogcontainer.h"

ConflictDialogContainer::ConflictDialogContainer(QWidget *aParent)
    : TabContainer( aParent )
{
}

void ConflictDialogContainer::loadEvents( const QDate &aDate, const int aConferenceId )
{
    Q_UNUSED(aDate);

    static_cast<EventModel*>(treeView->model())->loadConflictEvents( mEventId, aConferenceId );
    dayNavigator->hide();
}

void ConflictDialogContainer::updateTreeView(const QDate &aDate)
{
    TabContainer::updateTreeView(aDate);
    treeView->setAllExpanded(true);
}

