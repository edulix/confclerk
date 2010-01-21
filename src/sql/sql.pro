include(../global.pri)
TEMPLATE = lib
TARGET = sql
DESTDIR = ../bin
CONFIG += static
QT += sql xml

# module dependencies
LIBS += -L$$DESTDIR -lmvc -lorm
INCLUDEPATH += ../mvc ../orm
DEPENDPATH += .

HEADERS += sqlengine.h \
           schedulexmlparser.h

SOURCES += sqlengine.cpp \
           schedulexmlparser.cpp
           
