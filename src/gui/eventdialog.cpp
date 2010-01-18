#include "eventdialog.h"

EventDialog::EventDialog(const QModelIndex &aIndex, QWidget *aParent)
    : QDialog(aParent)
    , mIndex(aIndex)
{
    setupUi(this);
    Event *event = static_cast<Event *>(mIndex.internalPointer());
    title->setText(event->title());
    persons->setText(QString::number(event->id()));
    abstract->setPlainText(event->abstract());
    description->setPlainText(event->description());
}

