#ifndef TABCONTAINER_H
#define TABCONTAINER_H

#include <QWidget>
#include "ui_tabcontainer.h"

#include <conference.h>
#include <sqlengine.h>
#include <conference.h>
#include <eventmodel.h>

class TabContainer : public QWidget, public Ui::TabContainer
{
    Q_OBJECT
public:

    TabContainer(QWidget *aParent = NULL);
    virtual ~TabContainer() {}

protected:
    virtual void loadEvents( const QDate &aDate, const int aConferenceId )
    {
        Q_UNUSED(aDate);
        Q_UNUSED(aConferenceId);
    };

signals:
    void eventHasChanged(int aEventId, bool aReloadModel);

public slots:
    virtual void updateTreeViewModel(int aEventId, bool aReloadModel = false);
    void setDates(const QDate &aStart, const QDate &aEnd);

protected slots:
    virtual void updateTreeView(const QDate &aDate);
    void itemClicked(const QModelIndex &aIndex);
    void displayMap(const QModelIndex &aIndex);
    void displayConflicts(const QModelIndex &aIndex);
};

#endif /* TABCONTAINER_H */

