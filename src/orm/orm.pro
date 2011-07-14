TEMPLATE = lib
TARGET = orm
DESTDIR = ../bin
CONFIG += static
QT += sql
QMAKE_CLEAN += ../bin/liborm.a

# module dependencies
DEPENDPATH += .
HEADERS += ormrecord.h
