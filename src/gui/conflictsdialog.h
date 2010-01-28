#ifndef CONFLICTSDIALOG_H
#define CONFLICTSDIALOG_H

#include "ui_conflictsdialog.h"
#include <QDialog>

class ConflictsDialog : public QDialog, Ui::ConflictsDialog
{
    Q_OBJECT
public:
    ConflictsDialog(int aEventId, QWidget *aParent = NULL);
    ~ConflictsDialog();
signals:
    void eventHasChanged(int aEventId, bool aReloadModel = false);
};

#endif /* CONFLICTSDIALOG_H */ 

