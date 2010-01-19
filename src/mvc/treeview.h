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
signals:
    void requestForMap(const QModelIndex &aIndex);
};

#endif /* TREEVIEW_H */

