TEMPLATE = lib
TARGET = qalarm
DESTDIR = ../bin
CONFIG += static

# module dependencies
LIBS += -lalarm
DEPENDPATH += .

HEADERS += alarm.h

SOURCES += alarm.cpp 

