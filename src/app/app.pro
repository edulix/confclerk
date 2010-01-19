TEMPLATE = app
TARGET = fosdem
DESTDIR = ../bin
QT += sql xml

# module dependencies
LIBS += -L$$DESTDIR -lgui -lmvc -lsql
INCLUDEPATH += ../gui
DEPENDPATH += . ../gui
TARGETDEPS += $$DESTDIR/libmvc.a $$DESTDIR/libgui.a $$DESTDIR/libsql.a

SOURCES += main.cpp

RESOURCES += ../icons.qrc \
             ../maps.qrc \
             ../schedule.qrc

# instalation related

PREFIX = /usr/share
INSTALLS = target
target.path = $$PREFIX/bin
