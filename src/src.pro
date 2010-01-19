include(global.pri)
TEMPLATE = subdirs
SUBDIRS  = orm mvc sql gui app
maemo : SUBDIRS += alarm
#SUBDIRS += test
CONFIG += ordered

