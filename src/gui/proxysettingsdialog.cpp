/*
 * Copyright (C) 2010 Ixonos Plc.
 *
 * This file is part of fosdem-schedule.
 *
 * fosdem-schedule is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 2 of the License, or (at your option)
 * any later version.
 *
 * fosdem-schedule is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * fosdem-schedule.  If not, see <http://www.gnu.org/licenses/>.
 */
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

