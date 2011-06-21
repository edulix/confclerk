BEGIN TRANSACTION;
CREATE TABLE CONFERENCE ( id INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL
    , title VARCHAR UNIQUE NOT NULL
    , subtitle VARCHAR
    , venue VARCHAR
    , city VARCHAR NOT NULL
    , start INTEGER NOT NULL
    , end INTEGER NOT NULL
    , days INTEGER
    , day_change INTEGER
    , timeslot_duration INTEGER
    , active INTEGER DEFAULT 0
    , url VARCHAR UNIQUE
    , map VARCHAR);

CREATE TABLE TRACK ( id INTEGER  PRIMARY KEY AUTOINCREMENT  NOT NULL
    , xid_conference INTEGER -- NOT NULL
    , name VARCHAR UNIQUE NOT NULL );

CREATE TABLE ROOM ( id INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL
    , xid_conference INTEGER -- NOT NULL
    , name VARCHAR UNIQUE NOT NULL
    , picture VARCHAR NOT NULL);

CREATE TABLE PERSON ( id INTEGER PRIMARY KEY  NOT NULL
    , xid_conference INTEGER -- NOT NULL
    , name VARCHAR UNIQUE NOT NULL);

CREATE TABLE EVENT ( xid_conference INTEGER  NOT NULL
    , id INTEGER NOT NULL
    , start INTEGER NOT NULL
    , duration INTEGER NOT NULL
    , xid_track INTEGER NOT NULL REFERENCES TRACK(id)
    , type VARCHAR
    , language VARCHAR
    , tag VARCHAR
    , title VARCHAR NOT NULL
    , subtitle VARCHAR
    , abstract VARCHAR
    , description VARCHAR
    , favourite INTEGER DEFAULT 0
    , alarm INTEGER DEFAULT 0
    , PRIMARY KEY (xid_conference ,id)
    , FOREIGN KEY(xid_conference) REFERENCES CONFERENCE(id)
    , FOREIGN KEY(xid_track) REFERENCES TRACK(id));

CREATE TABLE EVENT_PERSON ( xid_conference INTEGER NOT NULL
    , xid_event INTEGER NOT NULL
    , xid_person INTEGER NOT NULL
    , UNIQUE ( xid_conference , xid_event , xid_person ) ON CONFLICT REPLACE
    , FOREIGN KEY(xid_conference) REFERENCES CONFERENCE(id)
    , FOREIGN KEY(xid_conference, xid_event) REFERENCES EVENT(xid_conference, id)
    , FOREIGN KEY(xid_person) REFERENCES PERSON(id));


CREATE TABLE EVENT_ROOM ( xid_conference INTEGER NOT NULL
    , xid_event INTEGER NOT NULL
    , xid_room INTEGER NOT NULL
    , UNIQUE ( xid_conference , xid_event , xid_room ) ON CONFLICT REPLACE
    , FOREIGN KEY(xid_conference) REFERENCES CONFERENCE(id)
    , FOREIGN KEY(xid_conference, xid_event) REFERENCES EVENT(xid_conference, id)
    , FOREIGN KEY(xid_room) REFERENCES ROOM(id));

CREATE TABLE LINK ( id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL
    , xid_conference INTEGER NOT NULL
    , xid_event INTEGER NOT NULL
    , name VARCHAR
    , url VARCHAR NOT NULL
    , UNIQUE ( xid_conference , xid_event , url ) ON CONFLICT REPLACE
    , FOREIGN KEY(xid_conference) REFERENCES CONFERENCE(id)
    , FOREIGN KEY(xid_conference, xid_event) REFERENCES EVENT(xid_conference, id));
COMMIT;
