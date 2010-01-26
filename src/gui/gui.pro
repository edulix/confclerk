include(../global.pri)
TEMPLATE = lib
TARGET = gui
DESTDIR = ../bin
CONFIG += static
QT += sql xml

# module dependencies
LIBS += -L$$DESTDIR -lmvc -lorm -lsql
INCLUDEPATH += ../orm ../mvc ../sql ../app
DEPENDPATH += . ../orm ../mvc ../sql
TARGETDEPS += $$DESTDIR/liborm.a $$DESTDIR/libmvc.a $$DESTDIR/libsql.a
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
         importscheduledialog.ui \
         about.ui \
         eventdialog.ui \
         mapwindow.ui

HEADERS += mainwindow.h \
           daynavigatorwidget.h \
           importscheduledialog.h \
           eventdialog.h \
           tabwidget.h \
           mapwindow.h

SOURCES += mainwindow.cpp \
           daynavigatorwidget.cpp \
           importscheduledialog.cpp \
           eventdialog.cpp \
           tabwidget.cpp \
           mapwindow.cpp

maemo {
    FORMS += alarmdialog.ui
    HEADERS += alarmdialog.h
    SOURCES += alarmdialog.cpp
}

