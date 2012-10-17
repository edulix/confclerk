TEMPLATE = lib
TARGET = qalarm
DESTDIR = ../bin
CONFIG += static
QT += sql
QMAKE_CLEAN += ../bin/libqalarm.a

# module dependencies
LIBS += -lalarm
DEPENDPATH += .

HEADERS += alarm.h \

SOURCES += alarm.cpp \

INCLUDEPATH += ../gui \
    ../mvc \ 
    ../orm \
    ../sql
