include(../global.pri)
TEMPLATE = app
TARGET = confclerk
DESTDIR = ../bin
QT += sql xml network
CONFIG(maemo5) {
    QT += maemo5
}

# module dependencies
LIBS += -L$$DESTDIR -lgui -lmvc -lsql
INCLUDEPATH += ../gui ../sql ../mvc ../orm
DEPENDPATH += . ../gui
POST_TARGETDEPS += $$DESTDIR/libmvc.a $$DESTDIR/libgui.a $$DESTDIR/libsql.a
maemo {
    LIBS += -L$$DESTDIR -lqalarm -lalarm
    INCLUDEPATH += ../alarm
    DEPENDPATH +=  ../alarm
    POST_TARGETDEPS += $$DESTDIR/libqalarm.a
}

HEADERS += appsettings.h \
        application.h

SOURCES += main.cpp \
           application.cpp \
           appsettings.cpp

RESOURCES += ../icons.qrc \
			 ../db.qrc \
			 ../../data/data.qrc

# instalation related
PREFIX = /usr/bin
INSTALLS = target
target.path = $$PREFIX

