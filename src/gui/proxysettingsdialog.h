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

