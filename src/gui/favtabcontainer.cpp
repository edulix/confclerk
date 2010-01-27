/*
 * favtabcontainer.cpp
 *
 *  Created on: Jan 27, 2010
 *      Author: maemo
 */

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
    QDate aStartDate = Conference::getById(AppSettings::confId()).start();
    QDate aEndDate = Conference::getById(AppSettings::confId()).end();
    dayNavigator->setDates(aStartDate, aEndDate);
    updateTreeView( Conference::getById(AppSettings::confId()).start() );
}
