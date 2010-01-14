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

HEADERS += \
    event.h \
    conference.h \
    delegate.h \
    eventmodel.h \
    treeview.h
SOURCES += \
    event.cpp \
    conference.cpp \
    delegate.cpp \
    eventmodel.cpp \
    treeview.cpp

