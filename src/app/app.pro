TEMPLATE = app
TARGET = fosdem
DESTDIR = ../bin
QT += sql

# module dependencies
LIBS += -L$$DESTDIR -lgui -lmodel
INCLUDEPATH += ../gui
DEPENDPATH += . ../gui
TARGETDEPS += $$DESTDIR/libmodel.a $$DESTDIR/libgui.a

SOURCES += main.cpp

RESOURCES += ../icons.qrc

