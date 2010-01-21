include(../global.pri)
TEMPLATE = app
TARGET = fosdem
DESTDIR = ../bin
QT += sql xml

# module dependencies
LIBS += -L$$DESTDIR -lgui -lmvc -lsql
INCLUDEPATH += ../gui
DEPENDPATH += . ../gui
TARGETDEPS += $$DESTDIR/libmvc.a $$DESTDIR/libgui.a $$DESTDIR/libsql.a
maemo {
    LIBS += -L$$DESTDIR -lqalarm -lalarm
    INCLUDEPATH += ../alarm
    DEPENDPATH +=  ../alarm
    TARGETDEPS += $$DESTDIR/libqalarm.a
}

SOURCES += main.cpp

RESOURCES += ../icons.qrc \
             ../maps.qrc

# instalation related

PREFIX = /usr/bin
INSTALLS = target
target.path = $$PREFIX

