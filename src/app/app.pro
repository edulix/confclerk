include(../global.pri)
TEMPLATE = app
TARGET = fosdem-schedule
DESTDIR = ../bin
QT += sql xml network dbus 
CONFIG(maemo5) {
    QT += maemo5
}

# module dependencies
LIBS += -L$$DESTDIR -lgui -lmvc -lsql
INCLUDEPATH += ../gui ../sql ../mvc ../orm
DEPENDPATH += . ../gui
TARGETDEPS += $$DESTDIR/libmvc.a $$DESTDIR/libgui.a $$DESTDIR/libsql.a
maemo {
    LIBS += -L$$DESTDIR -lqalarm -lalarm
    INCLUDEPATH += ../alarm
    DEPENDPATH +=  ../alarm
    TARGETDEPS += $$DESTDIR/libqalarm.a
}

HEADERS += appsettings.h \
        application.h \
    alarmdbus.h \
	alarmdbusadaptorp.h

SOURCES += main.cpp \
           application.cpp \
           appsettings.cpp \
    alarmdbus.cpp \
	alarmdbusadaptor.cpp

RESOURCES += ../icons.qrc \
             ../maps.qrc

# qmake cannot work properly if the resource file does not exist already
system(rm -f ../fosdem.sqlite && sqlite3 ../fosdem.sqlite <../fosdem.sql) {
 RESOURCES += ../db.qrc
} else {
 error(sqlite3 failed)
}

db.target = ../fosdem.sqlite
db.depends = ../fosdem.sql
db.commands = rm -f $$db.target && sqlite3 $$db.target <$$db.depends
QMAKE_EXTRA_TARGETS += db

# instalation related

PREFIX = /usr/bin
INSTALLS = target
target.path = $$PREFIX

