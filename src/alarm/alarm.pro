TEMPLATE = lib
TARGET = qalarm
DESTDIR = ../bin
CONFIG += static qdbus 
QT += sql dbus
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
    


