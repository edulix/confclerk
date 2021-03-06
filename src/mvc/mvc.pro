include(../global.pri)
TEMPLATE = lib
TARGET = mvc
DESTDIR = ../bin
CONFIG += static
QT += sql 
QMAKE_CLEAN += ../bin/libmvc.a

# module dependencies
LIBS += -L$$DESTDIR \
    -lorm
INCLUDEPATH += ../orm ../app
DEPENDPATH += . \
    ../orm
POST_TARGETDEPS += $$DESTDIR/liborm.a
maemo { 
    LIBS += -L$$DESTDIR \
        -lqalarm \
        -lalarm
    INCLUDEPATH += ../alarm
    DEPENDPATH += ../alarm
    POST_TARGETDEPS += $$DESTDIR/libqalarm.a
}
HEADERS += event.h \
    conference.h \
    track.h \
    delegate.h \
    eventmodel.h \
    treeview.h \
    room.h \
    conferencemodel.h
SOURCES += event.cpp \
    conference.cpp \
    track.cpp \
    delegate.cpp \
    eventmodel.cpp \
    treeview.cpp \
    room.cpp \
    conferencemodel.cpp
