
#ifndef ROOMSTABCONTAINER_H_
#define ROOMSTABCONTAINER_H_

#include "tabcontainer.h"

class RoomsTabContainer: public TabContainer
{
    Q_OBJECT
public:
    RoomsTabContainer( QWidget *aParent );
    virtual ~RoomsTabContainer() {}

protected:
    virtual void loadEvents( const QDate &aDate, const int aConferenceId );

};

#endif /* ROOMSTABCONTAINER_H_ */
