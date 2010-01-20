# Makefile - install Maemo specific data files 

PKG		= fosdem
PREFIX		= $(INSTALL_ROOT)/usr/share
INSTALL_FILE	= install -m 644 -p
CHK_DIR	= test -d
MKDIR         	= mkdir -p

.PHONY: install uninstall clean distclean

all:

install: 
	$(CHK_DIR) $(PREFIX)/applications/hildon/ || $(MKDIR) $(PREFIX)/applications/hildon/ 
	$(INSTALL_FILE) ./maemo/$(PKG).desktop $(PREFIX)/applications/hildon/

	$(CHK_DIR) $(PREFIX)/icons/hicolor/26x26/hildon/ || $(MKDIR) $(PREFIX)/icons/hicolor/26x26/hildon/ 
	$(INSTALL_FILE) ./26x26/$(PKG).png $(PREFIX)/icons/hicolor/26x26/hildon/

	$(CHK_DIR) $(PREFIX)/icons/hicolor/48x48/hildon/ || $(MKDIR) $(PREFIX)/icons/hicolor/48x48/hildon/ 
	$(INSTALL_FILE) ./48x48/$(PKG).png $(PREFIX)/icons/hicolor/48x48/hildon/


uninstall:
	$(RM) $(PREFIX)/applications/hildon/$(PKG).desktop
	$(RM) $(PREFIX)/icons/hicolor/26x26/hildon/$(PKG).png
	$(RM) $(PREFIX)/icons/hicolor/48x48/hildon/$(PKG).png

clean:

distclean: