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
#ifndef SCHEDULEXMLPARSER_H_
#define SCHEDULEXMLPARSER_H_

#include <QObject>
#include "sqlengine.h"

class ScheduleXmlParser : public QObject
{
    Q_OBJECT
    private:
        SqlEngine* sqlEngine;
    public:
        ScheduleXmlParser(SqlEngine* sqlEngine, QObject *aParent = NULL);

    public slots:
        void parseData(const QByteArray &aData, const QString& url, int conferenceId);

    signals:
        void progressStatus(int aStatus);
        void parsingScheduleBegin();
        void parsingScheduleEnd(int conferenceId);
};

#endif /* SCHEDULEXMLPARSER_H_ */

