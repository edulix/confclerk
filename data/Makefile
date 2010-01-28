# Makefile - install Maemo specific data files 

PKG		= fosdem-schedule
ICON		= fosdem
PREFIX		= $(INSTALL_ROOT)/usr/share
INSTALL_FILE	= install -m 644 -p
CHK_DIR		= test -d
MKDIR         	= mkdir -p

.PHONY: install uninstall clean distclean

all:

install: 
	$(CHK_DIR) $(PREFIX)/applications/hildon/ || $(MKDIR) $(PREFIX)/applications/hildon/ 
	$(INSTALL_FILE) ./maemo/$(PKG).desktop $(PREFIX)/applications/hildon/

	$(CHK_DIR) $(PREFIX)/icons/hicolor/26x26/hildon/ || $(MKDIR) $(PREFIX)/icons/hicolor/26x26/hildon/ 
	$(INSTALL_FILE) ./26x26/$(ICON).png $(PREFIX)/icons/hicolor/26x26/hildon/

	$(CHK_DIR) $(PREFIX)/icons/hicolor/48x48/hildon/ || $(MKDIR) $(PREFIX)/icons/hicolor/48x48/hildon/ 
	$(INSTALL_FILE) ./48x48/$(ICON).png $(PREFIX)/icons/hicolor/48x48/hildon/

	$(CHK_DIR) $(PREFIX)/icons/hicolor/64x64/hildon/ || $(MKDIR) $(PREFIX)/icons/hicolor/64x64/hildon/
	$(INSTALL_FILE) ./64x64/$(ICON).png $(PREFIX)/icons/hicolor/64x64/hildon/


uninstall:
	$(RM) $(PREFIX)/applications/hildon/$(PKG).desktop
	$(RM) $(PREFIX)/icons/hicolor/26x26/hildon/$(ICON).png
	$(RM) $(PREFIX)/icons/hicolor/48x48/hildon/$(ICON).png
	$(RM) $(PREFIX)/icons/hicolor/64x64/hildon/$(ICON).png

clean:

distclean:
