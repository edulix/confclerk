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

HEADERS += event.h
SOURCES += event.cpp

