#ifndef PROXYSETTINGSDIALOG_H
#define PROXYSETTINGSDIALOG_H

#include <QDialog>
#include "ui_proxysettingsdialog.h"

class ProxySettingsDialog : public QDialog, Ui::ProxySettingsDialog
{
    Q_OBJECT
public:
    ProxySettingsDialog(QWidget *aParent = NULL);
    ~ProxySettingsDialog() {}
private slots:
    void connectionTypeChanged(bool aState);
    void saveDialogData();
};

#endif /* PROXYSETTINGSDIALOG_H */  

