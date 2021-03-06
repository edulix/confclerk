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

#include "conferencemodel.h"

ConferenceModel::ConferenceModel(QObject* parent)
: QAbstractListModel(parent)
, conferences(Conference::getAll())
{ }

int ConferenceModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) {
        return 0;
    } else {
        return conferences.size();
    }
}

QVariant ConferenceModel::data(const QModelIndex& index, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    return conferences[index.row()].title();

    try {
        const Conference& c = conferenceFromIndex(index);
        return c.title();
    } catch (OrmNoObjectException&) {
        return QVariant();
    }

}

const Conference& ConferenceModel::conferenceFromIndex(const QModelIndex& index) const
{
    if (index.parent().isValid()
        or index.column() != 0
        or index.row() >= conferences.size())
    {
        throw OrmNoObjectException();
    }
    return conferences[index.row()];
}

QModelIndex ConferenceModel::indexFromId(int id) const
{
    for (int i = 0; i < conferences.size(); ++i) {
        if (conferences[i].id() == id) {
            return index(i, 0);
        }
    }

    return QModelIndex();
}

void ConferenceModel::newConferenceBegin()
{
}

void ConferenceModel::newConferenceEnd(int conferenceId) {
    Q_UNUSED(conferenceId);
    reinit();
}

void ConferenceModel::conferenceRemoved()
{
    reinit();
}
