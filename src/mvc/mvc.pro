include(../global.pri)
TEMPLATE = lib
TARGET = mvc
DESTDIR = ../bin
CONFIG += static
QT += sql

# module dependencies
LIBS += -L$$DESTDIR -lorm
INCLUDEPATH += ../orm ../app
DEPENDPATH += . ../orm
TARGETDEPS += $$DESTDIR/liborm.a

maemo { 
    LIBS += -L$$DESTDIR -lqalarm -lalarm
    INCLUDEPATH += ../alarm
    DEPENDPATH +=  ../alarm
    TARGETDEPS += $$DESTDIR/libqalarm.a
}

HEADERS += event.h \
           conference.h \
           track.h \
           delegate.h \
           eventmodel.h \
           treeview.h

SOURCES += event.cpp \
           conference.cpp \
           track.cpp \
           delegate.cpp \
           eventmodel.cpp \
           treeview.cpp
