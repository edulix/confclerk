include(global.pri)
TEMPLATE = subdirs
maemo : SUBDIRS += alarm
SUBDIRS  += orm mvc sql gui app
#SUBDIRS += test
CONFIG += ordered

