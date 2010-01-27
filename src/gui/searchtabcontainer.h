
#ifndef SEARCHTAB_H_
#define SEARCHTAB_H_

#include <QWidget>

#include "tabcontainer.h"
#include "searchhead.h"

class SearchTabContainer: public TabContainer {
    Q_OBJECT
public:
    SearchTabContainer(QWidget *aParent);
    virtual ~SearchTabContainer();
protected:
    virtual void loadEvents( const QDate &aDate, const int aConferenceId );
private slots:
    void searchButtonClicked();
    void searchAgainClicked();

private:
    SearchHead *header;
    QToolButton *searchAgainButton;
};

#endif /* SEARCHTAB_H_ */
