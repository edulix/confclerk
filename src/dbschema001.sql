BEGIN TRANSACTION;

CREATE TABLE conference (
	id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
	title VARCHAR NOT NULL,
	subtitle VARCHAR,
	venue VARCHAR,
	city VARCHAR,
	start INTEGER NOT NULL, -- timestamp (Unix Epoch)
	end INTEGER NOT NULL,   -- timestamp (Unix Epoch)
	day_change INTEGER,
	timeslot_duration INTEGER,
	active INTEGER DEFAULT 0,
	url VARCHAR
);

CREATE TABLE track (
	id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
	xid_conference INTEGER NOT NULL REFERENCES conference(id),
	name VARCHAR NOT NULL,
	UNIQUE (xid_conference, name)
);

CREATE TABLE room (
	id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
	xid_conference INTEGER NOT NULL REFERENCES conference(id),
	name VARCHAR NOT NULL,
	picture VARCHAR,
	UNIQUE (xid_conference, name)
);

CREATE TABLE person (
	id INTEGER NOT NULL,
	xid_conference INTEGER NOT NULL REFERENCES conference(id),
	name VARCHAR NOT NULL,
	PRIMARY KEY (id, xid_conference)
); 

CREATE TABLE event (
	xid_conference INTEGER NOT NULL REFERENCES conference(id),
	id INTEGER NOT NULL,
	start INTEGER NOT NULL,
	duration INTEGER NOT NULL, -- duration of the event in seconds
	xid_track INTEGER NOT NULL REFERENCES track(id),
	type VARCHAR,
	language VARCHAR,
	tag VARCHAR,
	title VARCHAR NOT NULL,
	subtitle VARCHAR,
	abstract VARCHAR,
	description VARCHAR,
	favourite INTEGER DEFAULT 0,
	alarm INTEGER DEFAULT 0,
	PRIMARY KEY (xid_conference, id)
);

CREATE TABLE event_person (
	xid_conference INTEGER NOT NULL,
	xid_event INTEGER NOT NULL,
	xid_person INTEGER NOT NULL,
	UNIQUE (xid_conference, xid_event, xid_person ) ON CONFLICT REPLACE,
	FOREIGN KEY(xid_conference) REFERENCES conference(id),
	FOREIGN KEY(xid_conference, xid_event) REFERENCES event(xid_conference, id),
	FOREIGN KEY(xid_conference, xid_person) REFERENCES person(xid_conference, id)
);

CREATE TABLE event_room (
	xid_conference INTEGER NOT NULL,
	xid_event INTEGER NOT NULL,
	xid_room INTEGER NOT NULL,
	UNIQUE (xid_conference, xid_event, xid_room) ON CONFLICT REPLACE,
	FOREIGN KEY(xid_conference) REFERENCES conference(id),
	FOREIGN KEY(xid_conference, xid_event) REFERENCES event(xid_conference, id),
	FOREIGN KEY(xid_conference, xid_room) REFERENCES room(xid_conference, id)
);

CREATE TABLE link (
	id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
	xid_conference INTEGER NOT NULL,
	xid_event INTEGER NOT NULL,
	name VARCHAR,
	url VARCHAR NOT NULL,
	UNIQUE (xid_conference, xid_event , url) ON CONFLICT REPLACE,
	FOREIGN KEY(xid_conference) REFERENCES conference(id),
	FOREIGN KEY(xid_conference, xid_event) REFERENCES event(xid_conference, id)
);

PRAGMA user_version=1;

COMMIT;
