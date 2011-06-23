/*
 * Copyright (C) 2010 Ixonos Plc.
 * Copyright (C) 2011 Philipp Spitzer, gregor herrmann
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
#include "urlinputdialog.h"

#include <QFileDialog>
#include <QPushButton>

UrlInputDialog::UrlInputDialog(QWidget* parent)
: QDialog(parent)
{
    setupUi(this);

    QPushButton* openFile = buttons->addButton("Open File...", QDialogButtonBox::ActionRole);

    connect(openFile, SIGNAL(clicked()), SLOT(openFileClicked()));
    connect(buttons, SIGNAL(accepted()), SLOT(acceptClicked()));
    connect(buttons, SIGNAL(rejected()), SLOT(rejectClicked()));
}

void UrlInputDialog::openFileClicked()
{
    QString file = QFileDialog::getOpenFileName(this, "Select Conference Schedule", QString(), "Schedule Files (*.xml);;All Files(*)");

    if (file.isNull()) {
        return;
    } else {
        saved_result = file;
        done(HaveFile);
    }
}

void UrlInputDialog::acceptClicked()
{
    saved_result = urlEntry->text();
    setResult(HaveUrl);
}

void UrlInputDialog::rejectClicked()
{
    setResult(Cancel);
}
