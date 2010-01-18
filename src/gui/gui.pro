include(global.pri)
TEMPLATE = lib
TARGET = gui
DESTDIR = ../bin
CONFIG += static
QT += sql xml

# module dependencies
LIBS += -L$$DESTDIR -lmvc -lorm -lsql -lqalarm
INCLUDEPATH += ../orm ../mvc ../sql ../alarm
DEPENDPATH += . ../orm ../mvc ../sql ../alarm
TARGETDEPS += $$DESTDIR/liborm.a $$DESTDIR/libmvc.a $$DESTDIR/libsql.a $$DESTDIR/libqalarm.a
maemo {
    LIBS += -L$$DESTDIR -lqalarm
    INCLUDEPATH += ../alarm
    DEPENDPATH +=  ../alarm
    TARGETDEPS +=  $$DESTDIR/libqalarm.a
}


# A shamelessly long list of sources, headers and forms.
# Please note that resources MUST be added to the app module
# (which means they need to be added to the test module as well,
# but I am sure you can live with that for the time being).

FORMS += mainwindow.ui \
         daynavigatorwidget.ui \
         about.ui

HEADERS += mainwindow.h \
           daynavigatorwidget.h

SOURCES += mainwindow.cpp \
           daynavigatorwidget.cpp

maemo {
    FORMS += alarmdialog.ui
    HEADERS += alarmdialog.h
    SOURCES += alarmdialog.cpp
}

