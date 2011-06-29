include(../global.pri)
TEMPLATE = lib
TARGET = gui
DESTDIR = ../bin
CONFIG += static
QT += sql \
    xml \
    network

# module dependencies
LIBS += -L$$DESTDIR \
    -lmvc \
    -lorm \
    -lsql
INCLUDEPATH += ../orm \
    ../mvc \
    ../sql \
    ../app
DEPENDPATH += . \
    ../orm \
    ../mvc \
    ../sql
POST_TARGETDEPS += $$DESTDIR/liborm.a \
    $$DESTDIR/libmvc.a \
    $$DESTDIR/libsql.a
maemo { 
    LIBS += -L$$DESTDIR \
        -lqalarm
    INCLUDEPATH += ../alarm
    DEPENDPATH += ../alarm
    POST_TARGETDEPS += $$DESTDIR/libqalarm.a
}

# A shamelessly long list of sources, headers and forms.
# Please note that resources MUST be added to the app module
# (which means they need to be added to the test module as well,
# but I am sure you can live with that for the time being).

FORMS += searchhead.ui \
    mainwindow.ui \
    daynavigatorwidget.ui \
    about.ui \
    eventdialog.ui \
    conflictsdialog.ui \
    tabcontainer.ui \
    mapwindow.ui \
    settingsdialog.ui \
    conferenceeditor.ui \
    urlinputdialog.ui

HEADERS += roomstabcontainer.h \
    nowtabcontainer.h \
    trackstabcontainer.h \
    favtabcontainer.h \
    searchtabcontainer.h \
    searchhead.h \
    dayviewtabcontainer.h \
    conflictdialogcontainer.h \
    conflictsdialog.h \
    mainwindow.h \
    daynavigatorwidget.h \
    eventdialog.h \
    tabcontainer.h \
    mapwindow.h \
    settingsdialog.h \
    conferenceeditor.h \
    urlinputdialog.h

SOURCES += roomstabcontainer.cpp \
    nowtabcontainer.cpp \
    trackstabcontainer.cpp \
    favtabcontainer.cpp \
    searchtabcontainer.cpp \
    searchhead.cpp \
    dayviewtabcontainer.cpp \
    conflictdialogcontainer.cpp \
    conflictsdialog.cpp \
    mainwindow.cpp \
    daynavigatorwidget.cpp \
    eventdialog.cpp \
    tabcontainer.cpp \
    mapwindow.cpp \
    settingsdialog.cpp \
    conferenceeditor.cpp \
    urlinputdialog.cpp

HEADERS += errormessage.h
SOURCES += errormessage.cpp
CONFIG(maemo5) {
    QT += maemo5
}

#maemo { 
#    FORMS += alarmdialog.ui
#    HEADERS += alarmdialog.h
#    SOURCES += alarmdialog.cpp
#}
