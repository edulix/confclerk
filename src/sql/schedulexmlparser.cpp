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

#include <QDomDocument>
#include <QHash>

#include "schedulexmlparser.h"
#include "sqlengine.h"

#include <QDebug>

ScheduleXmlParser::ScheduleXmlParser(QObject *aParent)
    : QObject(aParent)
{
}

int ScheduleXmlParser::parseData(const QByteArray &aData, const QString& url)
{
    QDomDocument document;
    document.setContent (aData, false);

    QDomElement scheduleElement = document.firstChildElement("schedule");

    SqlEngine::beginTransaction();

    int confId = 0;
    if (!scheduleElement.isNull())
    {
        QDomElement conferenceElement = scheduleElement.firstChildElement("conference");
        if (!conferenceElement.isNull())
        {
            QHash<QString,QString> conference;
            conference["id"] = QString::number(0); // conference ID is assigned automatically, or obtained from the DB
            conference["title"] = conferenceElement.firstChildElement("title").text();
            conference["subtitle"] = conferenceElement.firstChildElement("subtitle").text();
            conference["venue"] = conferenceElement.firstChildElement("venue").text();
            conference["city"] = conferenceElement.firstChildElement("city").text();
            conference["start"] = conferenceElement.firstChildElement("start").text(); // date
            conference["end"] = conferenceElement.firstChildElement("end").text(); // date
            conference["days"] = conferenceElement.firstChildElement("days").text(); // int
            conference["day_change"] = conferenceElement.firstChildElement("day_change").text(); // time
            conference["timeslot_duration"] = conferenceElement.firstChildElement("timeslot_duration").text(); // time
            conference["url"] = url;
            SqlEngine::addConferenceToDB(conference);
            confId = conference["id"].toInt();
            emit(parsingSchedule(conference["title"]));
        }

        // we need to get count of all events in order to emit 'progressStatus' signal
        int totalEventsCount = scheduleElement.elementsByTagName("event").count();

        // parsing day elements
        int currentEvent = 0; // hold global idx of processed event
        QDomNodeList dayList = scheduleElement.elementsByTagName("day");
        for (int i=0; i<dayList.count(); i++)
        {
            QDomElement dayElement = dayList.at(i).toElement();
            //QDate dayDate = QDate::fromString(dayElement.attribute("date"),DATE_FORMAT);
            //int dayIndex = dayElement.attribute("index").toInt();

            // parsing room elements
            QDomNodeList roomList = dayElement.elementsByTagName("room");
            for (int i=0; i<roomList.count(); i++)
            {
                QDomElement roomElement = roomList.at(i).toElement();
                // roomElement has to be 'Element' and it has to have 'name' attribute
                // TODO: 'event' has also 'room' node, so it can be unstable if that node has also 'name' attribute
                if(roomElement.hasAttribute("name"))
                {
                    // parsing event elements
                    QDomNodeList eventList = roomElement.elementsByTagName("event");
                    for (int i=0; i<eventList.count(); i++)
                    {
                        currentEvent++;
                        QDomElement eventElement = eventList.at(i).toElement();

                        // now we have all info to create ROOM/EVENT_ROOM record(s)
                        QHash<QString,QString> room;
                        room["name"] = roomElement.attribute("name");
                        room["event_id"] = eventElement.attribute("id");
                        room["conference_id"] = QString::number(confId,10);
                        room["picture"] = "NOT DEFINED YET"; // TODO: implement some mapping to assign correct picture to specified room_name
                        SqlEngine::addRoomToDB(room);

                        // process event's nodes
                        QHash<QString,QString> event;
                        event["id"] = eventElement.attribute("id");;
                        event["conference_id"] = QString::number(confId, 10);
                        event["start"] = eventElement.firstChildElement("start").text(); // time eg. 10:00
                        event["date"] = dayElement.attribute("date"); // date eg. 2009-02-07
                        event["duration"] = eventElement.firstChildElement("duration").text(); // time eg. 00:30
                        event["room_name"] = eventElement.firstChildElement("room").text(); // string eg. "Janson"
                        event["tag"] = eventElement.firstChildElement("tag").text(); // string eg. "welcome"
                        event["title"] = eventElement.firstChildElement("title").text(); // string eg. "Welcome"
                        event["subtitle"] = eventElement.firstChildElement("subtitle").text(); // string
                        event["track"] = eventElement.firstChildElement("track").text(); // string eg. "Keynotes"
                        event["type"] = eventElement.firstChildElement("type").text(); // string eg. "Podium"
                        event["language"] = eventElement.firstChildElement("language").text(); // language eg. "English"
                        event["abstract"] = eventElement.firstChildElement("abstract").text(); // string
                        event["description"] = eventElement.firstChildElement("description").text(); // string
                        SqlEngine::addEventToDB(event);
                        // process persons' nodes
                        QList<QString> persons;
                        QDomElement personsElement = eventElement.firstChildElement("persons");
                        QDomNodeList personList = personsElement.elementsByTagName("person");
                        for(int i = 0;i < personList.count();i++){
                            QHash<QString,QString> person;
                            person["id"] = personList.at(i).toElement().attribute("id");
                            person["name"] = personList.at(i).toElement().text();
                            person["event_id"] = eventElement.attribute("id");
                            person["conference_id"] = QString::number(confId, 10);
                            //qDebug() << "adding Person: " << person["name"];
                            SqlEngine::addPersonToDB(person);
                        }
                        // process links' nodes
                        QDomElement linksElement = eventElement.firstChildElement("links");
                        QDomNodeList linkList = linksElement.elementsByTagName("link");
                        for(int i = 0;i < linkList.count();i++){
                            QHash<QString,QString> link;
                            link["name"] = linkList.at(i).toElement().text();
                            link["url"] = linkList.at(i).toElement().attribute("href");
                            link["event_id"] = eventElement.attribute("id");
                            link["conference_id"] = QString::number(confId, 10);
                            SqlEngine::addLinkToDB(link);
                        }
                        // emit signal to inform the user about the current status (how many events are parsed so far - expressed in %)
                        int status = currentEvent * 100 / totalEventsCount;
                        progressStatus(status);
                    } // parsing event elements
                }
            } // parsing room elements
        } // parsing day elements
    } // schedule element
    SqlEngine::commitTransaction();

    return confId;
}

