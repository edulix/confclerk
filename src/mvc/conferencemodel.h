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
#ifndef CONFERENCE_MODEL_H
#define CONFERENCE_MODEL_H

#include <QAbstractListModel>
#include <QList>

#include "conference.h"

/** ConferenceModel class represents list of conferences for ListViews that may need it.

It also provides typed access to the conferences from ConferenceEditor.

It does not actually modify anything in DB, this is performed by other classes.

\see ConferenceEditor, MainWindow::showConferences()
*/
class ConferenceModel : public QAbstractListModel {
    Q_OBJECT
public:
    ConferenceModel(QObject* parent);
    virtual ~ConferenceModel() { }

    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

    const Conference& conferenceFromIndex(const QModelIndex&) const;
    QModelIndex indexFromId(int id) const;
public slots:
    void newConferenceBegin();
    void newConferenceEnd(const QString& title);
    void conferenceRemoved();
private:
    // reinitialize list from database
    void reinit()
    {
        conferences = Conference::getAll();
        reset();
    }

    QList<Conference> conferences;
};

#endif
