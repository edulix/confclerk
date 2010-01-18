include(../global.pri)
TEMPLATE = lib
TARGET = sql
DESTDIR = ../bin
CONFIG += static
QT += sql xml

# module dependencies
DEPENDPATH += .

HEADERS += sqlengine.h \
           schedulexmlparser.h

SOURCES += sqlengine.cpp \
           schedulexmlparser.cpp
           
