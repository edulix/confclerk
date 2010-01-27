
#ifndef TRACKSTABCONTAINER_H_
#define TRACKSTABCONTAINER_H_

#include "tabcontainer.h"

class TracksTabContainer: public TabContainer
{
    Q_OBJECT
public:
    TracksTabContainer( QWidget *aParent );
    virtual ~TracksTabContainer() {}

protected:
    virtual void loadEvents( const QDate &aDate, const int aConferenceId );

};

#endif /* TRACKSTABCONTAINER_H_ */
