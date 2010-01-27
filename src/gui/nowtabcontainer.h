
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

public slots:
    virtual void updateTreeView(const QDate &aDate);

private slots:
    void timerUpdateTreeView();
};

#endif /* NOWTABCONTAINER_H_ */
