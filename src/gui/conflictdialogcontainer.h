
#ifndef CONFLICTDIALOGCONTAINER_H
#define CONFLICTDIALOGCONTAINER_H

#include "tabcontainer.h"

class ConflictDialogContainer: public TabContainer
{
    Q_OBJECT
public:
    ConflictDialogContainer(QWidget *aParent);
    virtual ~ConflictDialogContainer(){}

    void setEventId(int aEventId) { mEventId = aEventId; }

protected:
    virtual void loadEvents( const QDate &aDate, const int aConferenceId );

private:
    int mEventId;
};

#endif /* CONFLICTDIALOGCONTAINER_H */

