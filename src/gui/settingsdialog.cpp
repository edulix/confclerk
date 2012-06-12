/*
 * Copyright (C) 2010 Ixonos Plc.
 * Copyright (C) 2011-2012 Philipp Spitzer, gregor herrmann, Stefan Stahl
 *
 * This file is part of ConfClerk.
 *
 * ConfClerk is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 2 of the License, or (at your option)
 * any later version.
 *
 * ConfClerk is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * ConfClerk.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "settingsdialog.h"

#include <appsettings.h>
#include <QDebug>

SettingsDialog::SettingsDialog(QWidget *aParent)
    : QDialog(aParent)
{
    setupUi(this);
    connect(directConnection, SIGNAL(clicked(bool)), SLOT(connectionTypeChanged(bool)));
}


void SettingsDialog::loadDialogData()
{
    // deserialize dialog data
    address->setText(AppSettings::proxyAddress());
    port->setValue(AppSettings::proxyPort());
    directConnection->setChecked(AppSettings::isDirectConnection());
    proxyWidget->setDisabled(directConnection->isChecked());
}


void SettingsDialog::saveDialogData()
{
    // serialize dialog data
    AppSettings::setProxyAddress(address->text());
    AppSettings::setProxyPort(port->value());
    AppSettings::setDirectConnection(directConnection->isChecked());
}


void SettingsDialog::connectionTypeChanged(bool aState)
{
    proxyWidget->setDisabled(aState);
}


