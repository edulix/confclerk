TEMPLATE = app
TARGET = fosdem
DESTDIR = ../bin
QT += sql xml

# module dependencies
LIBS += -L$$DESTDIR -lgui -lmodel -lsql
INCLUDEPATH += ../gui
DEPENDPATH += . ../gui
TARGETDEPS += $$DESTDIR/libmodel.a $$DESTDIR/libgui.a $$DESTDIR/libsql.a

SOURCES += main.cpp

RESOURCES += ../icons.qrc

