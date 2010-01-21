#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QTreeView>

class TreeView : public QTreeView
{
    Q_OBJECT
public:
    TreeView(QWidget *aParent = NULL);
    ~TreeView() {}
private:
    void mouseReleaseEvent(QMouseEvent *aEvent);
    bool testForControlClicked(const QModelIndex &aIndex, const QPoint &aPoint);
private slots:
    void handleItemClicked(const QModelIndex &index);
signals:
    void requestForMap(const QModelIndex &aIndex);
    void requestForWarning(const QModelIndex &aIndex);
    void eventHasChanged(int aEventId); // emited when user changes some event details, eg. sets it Favourite
};

#endif /* TREEVIEW_H */

