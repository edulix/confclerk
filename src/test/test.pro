TEMPLATE = app
TARGET = test
DESTDIR = ../bin
CONFIG += qtestlib console
QT += sql

# module dependencies
LIBS += -L$$DESTDIR -lgui -lmodel
INCLUDEPATH += ../gui ../model ../orm
DEPENDPATH += . ../gui ../model ../orm
TARGETDEPS += $$DESTDIR/libmodel.a $$DESTDIR/libgui.a $$DESTDIR/liborm.a

SOURCES += main.cpp \
    model/EventTest.cpp

HEADERS += \
    model/EventTest.h

