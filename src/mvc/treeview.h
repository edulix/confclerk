#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QTreeView>


class TreeView : public QTreeView
{
public:
    TreeView(QWidget *aParent = NULL);
    ~TreeView() {}
private:
    void mouseReleaseEvent(QMouseEvent *aEvent);
    void testForControlClicked(const QModelIndex &aIndex, const QPoint &aPoint);
};

#endif /* TREEVIEW_H */

