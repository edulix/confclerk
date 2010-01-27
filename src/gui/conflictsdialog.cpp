#include "conflictsdialog.h"

ConflictsDialog::ConflictsDialog(int aEventId, QWidget *aParent)
    : QDialog(aParent)
{
    setupUi(this);
    connect(container, SIGNAL(eventHasChanged(int)), this, SIGNAL(eventHasChanged(int)));
    connect(container, SIGNAL(eventHasChanged(int)), container, SLOT(updateTreeViewModel(int)));

    container->setEventId(aEventId);

    int confId = Conference::activeConference();
    QDate startDate = Conference::getById(confId).start();
    QDate endDate = Conference::getById(confId).end();
    container->setDates(startDate, endDate);
}

ConflictsDialog::~ConflictsDialog()
{
    disconnect(container, SIGNAL(eventHasChanged(int)), this, SIGNAL(eventHasChanged(int)));
}

