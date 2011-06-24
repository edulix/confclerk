# confclerk.pro

QMAKEVERSION = $$[QMAKE_VERSION]
ISQT4 = $$find(QMAKEVERSION, ^[2-9])
isEmpty( ISQT4 ) {
error("Use the qmake include with Qt4.4 or greater, on Debian that is
qmake-qt4");
}

TEMPLATE = subdirs
SUBDIRS = src

VERSION = 0.5.0

QMAKE_DISTCLEAN += src/bin/*.a
QMAKE_EXTRA_TARGETS += tarball icon changelog release

changelog.target = ChangeLog
changelog.commands = \
	svn up && svn2cl --group-by-day --reparagraph
changelog.CONFIG = phony

icon.target = data/$${TARGET}.png
icon.commands = convert data/$${TARGET}.svg data/$${TARGET}.png
icon.depends = data/$${TARGET}.svg

release.depends = tarball

tarball.target = $${TARGET}-$${VERSION}.tar.gz
tarball.commands = \
	$(DEL_FILE) -r $${TARGET}-$${VERSION} ; \
	$(MKDIR) $${TARGET}-$${VERSION} ; \
	$(COPY_DIR) * $${TARGET}-$${VERSION}/ ; \
	$(DEL_FILE) $${TARGET}-$${VERSION}/*.pro.user \
		$${TARGET}-$${VERSION}/$${TARGET}-$${VERSION}.tar.gz \
		$(DEL_FILE) -r $${TARGET}-$${VERSION}/$${TARGET}-$${VERSION} \
		$${TARGET}-$${VERSION}/Makefile ; \
	tar -cz --exclude=.svn -f $$tarball.target $${TARGET}-$${VERSION} ; \
	$(DEL_FILE) -r $${TARGET}-$${VERSION}
tarball.depends = changelog icon distclean
