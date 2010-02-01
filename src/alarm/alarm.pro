TEMPLATE = lib
TARGET = qalarm
DESTDIR = ../bin
CONFIG += static qdbus 
QT += sql dbus

# module dependencies
LIBS += -lalarm
DEPENDPATH += .

HEADERS += alarm.h \
		   alarmdbus.h \
		   alarmdbusadaptorp.h

SOURCES += alarm.cpp \
		   alarmdbus.cpp \
		   alarmdbusadaptor.cpp

INCLUDEPATH += ../gui \
    ../mvc \ 
    ../orm \
    ../sql
    


