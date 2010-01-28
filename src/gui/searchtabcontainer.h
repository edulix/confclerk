
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
public slots:
    void searchAgainClicked(); // made it public - to show header when 1.st conf importing is done successfuly
private slots:
    void searchButtonClicked();

private:
    SearchHead *header;
    QToolButton *searchAgainButton;
};

#endif /* SEARCHTAB_H_ */
