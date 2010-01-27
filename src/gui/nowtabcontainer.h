/*
 * nowtabcontainer.h
 *
 *  Created on: Jan 27, 2010
 *      Author: maemo
 */

#ifndef NOWTABCONTAINER_H_
#define NOWTABCONTAINER_H_

#include "tabcontainer.h"

class NowTabContainer: public TabContainer
{
    Q_OBJECT
public:
    NowTabContainer( QWidget *aParent );
    virtual ~NowTabContainer() { }

protected:
    virtual void loadEvents( const QDate &aDate, const int aConferenceId );

private slots:
    void timerUpdateTreeView();
};

#endif /* NOWTABCONTAINER_H_ */
