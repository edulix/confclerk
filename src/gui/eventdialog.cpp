#include "eventdialog.h"

#include <QScrollBar>

EventDialog::EventDialog(const QModelIndex &aIndex, QWidget *aParent)
    : QDialog(aParent)
    , mIndex(aIndex)
{
    setupUi(this);

    abstract->setStyleSheet("background-color : transparent;");
    description->setStyleSheet("background-color : transparent;");

    // use text color from 'title' QLabel
    QColor color = title->palette().color(QPalette::Active, QPalette::WindowText);
    QPalette p = abstract->palette();
    //p.setColor(QPalette::Active, QPalette::Text, Qt::blue);
    p.setColor(QPalette::Active, QPalette::Text, color);
    p.setColor(QPalette::Active, QPalette::WindowText, color);
    abstract->setPalette(p);
    description->setPalette(p);

    // set scrollbars color
    QPalette p2 = description->verticalScrollBar()->palette();
    p2.setColor(QPalette::Active, QPalette::Background, color);
    //description->verticalScrollBar()->setStyleSheet("background-color : blue;");
    abstract->verticalScrollBar()->setPalette(p2);
    description->verticalScrollBar()->setPalette(p2);

    Event *event = static_cast<Event *>(mIndex.internalPointer());
    title->setText(event->title());
    persons->setText(event->persons().join(" and "));
    abstract->setPlainText(event->abstract());
    description->setPlainText(event->description());
}

