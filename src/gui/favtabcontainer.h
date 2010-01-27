/*
 * favtabcontainer.h
 *
 *  Created on: Jan 27, 2010
 *      Author: maemo
 */

#ifndef FAVTABCONTAINER_H_
#define FAVTABCONTAINER_H_

#include "tabcontainer.h"

class FavTabContainer: public TabContainer
{
    Q_OBJECT
public:
    FavTabContainer(QWidget *aParent);
    virtual ~FavTabContainer(){}

public slots:
    virtual void updateTreeViewModel(int aEventId);

protected:
    virtual void loadEvents( const QDate &aDate, const int aConferenceId );
};

#endif /* FAVTABCONTAINER_H_ */
