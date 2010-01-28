
#ifndef FAVTABCONTAINER_H_
#define FAVTABCONTAINER_H_

#include "tabcontainer.h"

class FavTabContainer: public TabContainer
{
    Q_OBJECT
public:
    FavTabContainer(QWidget *aParent);
    virtual ~FavTabContainer(){}

protected:
    virtual void loadEvents( const QDate &aDate, const int aConferenceId );
};

#endif /* FAVTABCONTAINER_H_ */
