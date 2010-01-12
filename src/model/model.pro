TEMPLATE = lib
TARGET = model
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
    delegate.h \
    eventmodel.h \
    treeview.h
SOURCES += \
    event.cpp \
    delegate.cpp \
    eventmodel.cpp \
    treeview.cpp

