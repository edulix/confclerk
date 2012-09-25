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
#ifndef CONFERENCE_EDITOR_H
#define CONFERENCE_EDITOR_H

#include "ui_conferenceeditor.h"

#include <QItemSelectionModel>

class ConferenceModel;

/** ConferenceEditor clas is used for managing list of conferences.

That is, selecting an active conference, adding a new conference from URL or
file, removing a conference, refreshing a conference from URL that is saved in
the DB.

It does not do anything of this itself, instead emitting controlling signals.
On the ConferenceEditor creation, they are connected to proper listeners.

\see MainWindow::showConferences()
*/
class ConferenceEditor : public QDialog, private Ui::ConferenceEditor {
    Q_OBJECT

public:
    ConferenceEditor(ConferenceModel* model, QWidget* parent);
    virtual ~ConferenceEditor() { }
signals:
    void haveConferenceSelected(int id);
    void noneConferenceSelected();

    void haveConferenceUrl(const QString& url, int conferenceId);
    void haveConferenceFile(const QString& path, int conferenceId);
    void removeConferenceRequested(int id);
    void changeUrlRequested(int, const QString&);

    void wantCurrent(const QModelIndex&, QItemSelectionModel::SelectionFlags);
public slots:
    void importStarted();
    void importFinished(int conferenceId);
    void conferenceRemoved();
    void showParsingProgress(int);
private slots:
    void itemSelected(const QModelIndex& current, const QModelIndex& previous);
    void addClicked();
    void removeClicked();
    void changeUrlClicked();
    void refreshClicked();

private:
    ConferenceModel* model;
    int selected_id;
    QString import_in_progress_title;
};

#endif
