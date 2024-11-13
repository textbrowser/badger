purge.commands = find . -name \'*~\' -exec rm {} \\;

CONFIG		+= qt release warn_on
DEFINES		+= QT_DEPRECATED_WARNINGS
LANGUAGE	= C++
QMAKE_CLEAN     += NAME
QT		+= gui widgets

QMAKE_CXXFLAGS_RELEASE += -Wall \
                          -Wcast-qual \
                          -Wdouble-promotion \
                          -Wenum-compare \
                          -Wextra \
                          -Wfloat-equal \
                          -Wformat=2 \
                          -Wl,-z,relro \
                          -Wlogical-op \
                          -Wno-class-memaccess \
                          -Wno-deprecated-copy \
                          -Wold-style-cast \
                          -Woverloaded-virtual \
                          -Wpointer-arith \
                          -Wstack-protector \
                          -Wstrict-overflow=1 \
                          -Wundef \
                          -fPIE \
                          -fstack-protector-all \
                          -fwrapv \
                          -pedantic \
                          -pie \
                          -std=c++17

QMAKE_DISTCLEAN     += -r .qmake* \
                       -r Temporary
QMAKE_EXTRA_TARGETS = purge
QMAKE_STRIP	    = echo

INCLUDEPATH	+= Source

MOC_DIR     = Temporary/moc
OBJECTS_DIR = Temporary/obj
RCC_DIR     = Temporary/rcc
UI_DIR      = Temporary/ui

FORMS          += UI/badger_ubuntu_22_04.ui \
		  UI/badger_ubuntu_24_04.ui
HEADERS	       += Source/badger.h Source/badger_calendar_widget.h
SOURCES	       += Source/badger.cc \
                  Source/badger_main.cc
TRANSLATIONS    =

PROJECTNAME     = NAME
TARGET          = NAME
TEMPLATE	= app
