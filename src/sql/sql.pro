include(../global.pri)
TEMPLATE = lib
TARGET = sql
DESTDIR = ../bin
CONFIG += static
QT += sql xml
QMAKE_CLEAN += ../bin/libsql.a

# module dependencies
LIBS += -L$$DESTDIR -lmvc -lorm
INCLUDEPATH += ../mvc ../orm ../app
DEPENDPATH += .

HEADERS += sqlengine.h \
           schedulexmlparser.h

SOURCES += sqlengine.cpp \
           schedulexmlparser.cpp
           
