#ifndef TABCONTAINER_H
#define TABCONTAINER_H

#include <QWidget>
#include "ui_tabcontainer.h"

class TabContainer : public QWidget, Ui::TabContainer
{
    Q_OBJECT
public:

    // type of the container
    // specifies the type of the data that treeView holds
    enum Type
    {
        EContainerTypeNone = 0,
        EContainerTypeDay,
        EContainerTypeFavs,
        EContainerTypeTracks,
        EContainerTypeRooms,
        EContainerTypeSearch,
        EContainerTypeNow
    };

    TabContainer(QWidget *aParent = NULL);
    ~TabContainer() {}
    void setType(TabContainer::Type aType);

signals:
    void eventHasChanged(int aEventId);

public slots:
    void updateTreeViewModel(int aEventId);
    void setDates(const QDate &aStart, const QDate &aEnd);

private slots:
    void updateTreeView(const QDate &aDate);
    void timerUpdateTreeView();
    void itemClicked(const QModelIndex &aIndex);
    void displayMap(const QModelIndex &aIndex);
    void displayWarning(const QModelIndex &aIndex);
    void searchClicked();
    void searchAgainClicked();

private:
    TabContainer::Type mType;
};

#endif /* TABCONTAINER_H */

