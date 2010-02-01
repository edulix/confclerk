include(global.pri)
TEMPLATE = subdirs
maemo : SUBDIRS += alarm
SUBDIRS  += orm sql mvc gui app 
#SUBDIRS += test
CONFIG += ordered

