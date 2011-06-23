/*
 * Copyright (C) 2010 Ixonos Plc.
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
#ifndef URL_INPUT_DIALOG_H
#define URL_INPUT_DIALOG_H

#include "ui_urlinputdialog.h"

class UrlInputDialog : public QDialog, private Ui::UrlInputDialog {
    Q_OBJECT
public:
    enum {
        Cancel,
        HaveUrl,
        HaveFile
    };
    UrlInputDialog(QWidget* parent);
    virtual ~UrlInputDialog() { }

    QString url() { return saved_result; }
private slots:
    void acceptClicked();
    void rejectClicked();
    void openFileClicked();
private:
    QString saved_result;
};

#endif
