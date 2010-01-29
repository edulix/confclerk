#include "proxysettingsdialog.h"

#include <appsettings.h>
#include <QDebug>

ProxySettingsDialog::ProxySettingsDialog(QWidget *aParent)
    : QDialog(aParent)
{
    setupUi(this);

    // deserialize dialog data
    address->setText(AppSettings::proxyAddress());
    port->setValue(AppSettings::proxyPort());
    directConnection->setChecked(AppSettings::isDirectConnection());

    connect(okButton, SIGNAL(clicked()), SLOT(saveDialogData()));
    connect(directConnection, SIGNAL(clicked(bool)), SLOT(connectionTypeChanged(bool)));

    if(directConnection->isChecked())
        proxyWidget->hide();
}

void ProxySettingsDialog::connectionTypeChanged(bool aState)
{
    aState ? proxyWidget->hide() : proxyWidget->show();
}

void ProxySettingsDialog::saveDialogData()
{
    // serialize dialog data
    AppSettings::setProxyAddress(address->text());
    AppSettings::setProxyPort(port->value());
    AppSettings::setDirectConnection(directConnection->isChecked());

    close();
}

