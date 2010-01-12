TEMPLATE = lib
TARGET = gui
DESTDIR = ../bin
CONFIG += static
QT += sql xml

# module dependencies
LIBS += -L$$DESTDIR -lmodel -lorm -lsql
INCLUDEPATH += ../orm ../model ../sql
DEPENDPATH += . ../orm ../model ../sql
TARGETDEPS += $$DESTDIR/liborm.a $$DESTDIR/libmodel.a $$DESTDIR/libsql.a


# A shamelessly long list of sources, headers and forms.
# Please note that resources MUST be added to the app module
# (which means they need to be added to the test module as well,
# but I am sure you can live with that for the time being).
FORMS += mainwindow.ui
SOURCES += mainwindow.cpp
HEADERS += mainwindow.h

