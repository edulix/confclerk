
#ifndef DAYVIEWTABCONTAINER_H_
#define DAYVIEWTABCONTAINER_H_

#include "tabcontainer.h"

class DayViewTabContainer: public TabContainer {
    Q_OBJECT
public:
    DayViewTabContainer(QWidget *aParent);
    virtual ~DayViewTabContainer();
protected:
    virtual void loadEvents(const QDate &aDate, const int aConferenceId );
};

#endif /* DAYVIEWTABCONTAINER_H_ */
