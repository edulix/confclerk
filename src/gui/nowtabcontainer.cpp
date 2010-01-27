/*
 * nowtabcontainer.cpp
 *
 *  Created on: Jan 27, 2010
 *      Author: maemo
 */

#include <QTimer>
#include "nowtabcontainer.h"

NowTabContainer::NowTabContainer( QWidget *aParent ) : TabContainer( aParent )
{
    QTimer *timer = new QTimer( this );
    connect( timer, SIGNAL(timeout()), SLOT(timerUpdateTreeView()) );
    timer->start( 30000); // 30 seconds timer
}

void NowTabContainer::loadEvents( const QDate &aDate, const int aConferenceId )
{
    Q_UNUSED( aDate );
    static_cast<EventModel*>(treeView->model())->loadNowEvents( aConferenceId );
    treeView->setAllExpanded(true);
}

void NowTabContainer::timerUpdateTreeView()
{
    updateTreeView( QDate() );
}
