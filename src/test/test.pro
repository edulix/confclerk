TEMPLATE = app
TARGET = test
DESTDIR = ../bin
CONFIG += qtestlib console
QT += sql

# module dependencies
LIBS += -L$$DESTDIR -lgui -lmodel
INCLUDEPATH += ../gui ../model
DEPENDPATH += . ../gui ../model
TARGETDEPS += $$DESTDIR/libmodel.a $$DESTDIR/libgui.a

SOURCES += main.cpp \
    model/EventTest.cpp

HEADERS += \
    model/EventTest.h

