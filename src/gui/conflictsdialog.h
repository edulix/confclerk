#ifndef CONFLICTSDIALOG_H
#define CONFLICTSDIALOG_H

#include "ui_conflictsdialog.h"
#include <QDialog>

class ConflictsDialog : public QDialog, Ui::ConflictsDialog
{
    Q_OBJECT
public:
    ConflictsDialog(QWidget *aParent = NULL);
    ~ConflictsDialog();
signals:
    void eventHasChanged(int aEventId);
};

#endif /* CONFLICTSDIALOG_H */ 

