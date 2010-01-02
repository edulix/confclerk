TEMPLATE = lib
TARGET = gui
DESTDIR = ../bin
CONFIG += static
QT += sql

# module dependencies
LIBS += -L$$DESTDIR -lmodel -orm
INCLUDEPATH += ../orm ../model
DEPENDPATH += . ../orm ../model
TARGETDEPS += $$DESTDIR/liborm.a $$DESTDIR/libmodel.a


# A shamelessly long list of sources, headers and forms.
# Please note that resources MUST be added to the app module
# (which means they need to be added to the test module as well,
# but I am sure you can live with that for the time being).
SOURCES += mainwindow.cpp
HEADERS += mainwindow.h

