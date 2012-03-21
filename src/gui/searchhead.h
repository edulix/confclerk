/*
 * Copyright (C) 2010 Ixonos Plc.
 * Copyright (C) 2011-2012 Philipp Spitzer, gregor herrmann
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
#ifndef SEARCHHEAD_H
#define SEARCHHEAD_H

#include <QtGui/QWidget>
#include <QDebug>
#include "ui_searchhead.h"

class SearchHead : public QWidget, public Ui::SearchHeadClass
{
    Q_OBJECT

public:
    SearchHead(QWidget *parent = 0);
    ~SearchHead();

signals:
    void searchClicked();

private slots:
    void searchButtonClicked();

//private:
    //Ui::SearchHeadClass ui;
};

#endif // SEARCHHEAD_H
