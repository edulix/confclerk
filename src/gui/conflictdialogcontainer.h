
#ifndef CONFLICTDIALOGCONTAINER_H
#define CONFLICTDIALOGCONTAINER_H

#include "tabcontainer.h"

class ConflictDialogContainer: public TabContainer
{
    Q_OBJECT
public:
    ConflictDialogContainer(QWidget *aParent);
    virtual ~ConflictDialogContainer(){}

public slots:
    virtual void updateTreeViewModel(int aEventId);

protected:
    virtual void loadEvents( const QDate &aDate, const int aConferenceId );
};

#endif /* CONFLICTDIALOGCONTAINER_H */

