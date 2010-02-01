TEMPLATE = lib
TARGET = qalarm
DESTDIR = ../bin
CONFIG += static qdbus 
QT += sql dbus

# module dependencies
LIBS += -lalarm
DEPENDPATH += .

HEADERS += alarm.h \

SOURCES += alarm.cpp \

INCLUDEPATH += ../gui \
    ../mvc \ 
    ../orm \
    ../sql
    


