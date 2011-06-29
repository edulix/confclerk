TEMPLATE = app
TARGET = test
DESTDIR = ../bin
CONFIG += qtestlib console
QT += sql

# module dependencies
LIBS += -L$$DESTDIR -lgui -lmvc
INCLUDEPATH += ../gui ../mvc ../orm
DEPENDPATH += . ../gui ../mvc ../orm
POST_TARGETDEPS += $$DESTDIR/libmvc.a $$DESTDIR/libgui.a $$DESTDIR/liborm.a

SOURCES += main.cpp \
    mvc/EventTest.cpp

HEADERS += \
    mvc/EventTest.h

