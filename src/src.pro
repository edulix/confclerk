include(global.pri)
TEMPLATE = subdirs
SUBDIRS  += orm mvc sql gui
maemo : SUBDIRS += alarm
SUBDIRS += app
#SUBDIRS += test
CONFIG += ordered

