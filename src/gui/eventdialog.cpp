#include "eventdialog.h"

#include <QDebug>

EventDialog::EventDialog(const QModelIndex &aIndex, QWidget *aParent)
    : QDialog(aParent)
    , mIndex(aIndex)
{
    setupUi(this);

    abstract->setStyleSheet("background-color : transparent;");
    description->setStyleSheet("background-color : transparent;");

    Event *event = static_cast<Event *>(mIndex.internalPointer());
    title->setText(event->title());
    persons->setText(event->persons().join(" and "));
    abstract->setPlainText(event->abstract());
    description->setPlainText(event->description());
}

