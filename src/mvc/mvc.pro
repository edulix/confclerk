include(../global.pri)
TEMPLATE = lib
TARGET = mvc
DESTDIR = ../bin
CONFIG += static
QT += sql

# module dependencies
LIBS += -L$$DESTDIR -lorm
INCLUDEPATH += ../orm
DEPENDPATH += . ../orm
TARGETDEPS += $$DESTDIR/liborm.a

maemo { 
    LIBS += -L$$DESTDIR -lqalarm -lalarm
    INCLUDEPATH += ../alarm
    DEPENDPATH +=  ../alarm
    TARGETDEPS += $$DESTDIR/libqalarm.a
}

HEADERS += activity.h \
           event.h \
           conference.h \
           delegate.h \
           eventmodel.h \
           treeview.h

SOURCES += activity.cpp \
           event.cpp \
           conference.cpp \
           delegate.cpp \
           eventmodel.cpp \
           treeview.cpp
