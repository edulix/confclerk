#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>

class TabWidget : public QTabWidget
{
    Q_OBJECT
public:
    TabWidget(QWidget *aParent = NULL);
    ~TabWidget() {}
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
signals:
    void infoIconClicked();
private:
    QPoint mPressPoint;
    QImage mInfoImage;
};

#endif /* TABWIDGET_H */

