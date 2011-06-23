include(../global.pri)
TEMPLATE = app
TARGET = fosdem-schedule
DESTDIR = ../bin
QT += sql xml network 
CONFIG(maemo5) {
    QT += maemo5 dbus
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
    HEADERS += alarmdbus.h \
        alarmdbusadaptorp.h
    SOURCES += alarmdbus.cpp \
        alarmdbusadaptor.cpp
}

HEADERS += appsettings.h \
        application.h

SOURCES += main.cpp \
           application.cpp \
           appsettings.cpp

RESOURCES += ../icons.qrc \
             ../maps.qrc \
			 ../db.qrc

# instalation related
PREFIX = /usr/bin
INSTALLS = target
target.path = $$PREFIX

