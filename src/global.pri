# This is 'global.pri' file which defines
# GLOBAL definitions for the project
# include this file in each "*.pro" file, where it's needed
# USAGE: include(./global.pri)

# VERSION
VERSION = 0.5.6
DEFINES += VERSION=\\\"$$VERSION\\\"

# Define 'MAEMO' specific CONFIG/DEFINE
# To handle 'MAEMO' specific soruces/code
DISTRO = $$system(cat /etc/issue)
contains( DISTRO, [Mm]aemo ) {
    # for 'MAEMO' specific source code parts
    DEFINES += MAEMO
    # for eg. including 'MAEMO' specific files
    CONFIG += maemo
}

contains( DISTRO, [Ii]nternet ) {
    contains( DISTRO, [Tt]ablet ) {
        # Nokia N810 device
        DEFINES += N810
    }
}

