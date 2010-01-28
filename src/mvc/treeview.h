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
public slots:
    void setAllExpanded(bool aExpanded); // (aExpanded==true) => expanded; (aExpanded==false) => collapsed
private slots:
    void handleItemClicked(const QModelIndex &index);
signals:
    void requestForMap(const QModelIndex &aIndex);
    void requestForConflicts(const QModelIndex &aIndex);
    void eventHasChanged(int aEventId, bool aReloadModel = false); // emited when user changes some event details, eg. sets it Favourite
};

#endif /* TREEVIEW_H */

