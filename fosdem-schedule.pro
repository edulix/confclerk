# fosdem-schedule.pro

QMAKEVERSION = $$[QMAKE_VERSION]
ISQT4 = $$find(QMAKEVERSION, ^[2-9])
isEmpty( ISQT4 ) {
error("Use the qmake include with Qt4.4 or greater, on Debian that is
qmake-qt4");
}

TEMPLATE = subdirs
SUBDIRS = src

# for changelog target:
# svn2cl --group-by-day --reparagraph
