purge.commands = find . -name '*~' -exec rm {} \\;

CONFIG		+= qt release warn_on
DEFINES		+= QT_DEPRECATED_WARNINGS
LANGUAGE	= C++
QMAKE_CLEAN	+= nvidia-modeset
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
                          -std=c++11

QMAKE_DISTCLEAN     += -r .qmake* \
                       -r temp
QMAKE_EXTRA_TARGETS = purge
QMAKE_STRIP	    = echo

INCLUDEPATH	+= Source

MOC_DIR     = temp/moc
OBJECTS_DIR = temp/obj
RCC_DIR     = temp/rcc
UI_DIR      = temp/ui

FORMS          += UI/badger.ui
HEADERS	       += Source/badger.h
SOURCES	       += Source/badger.cc
TRANSLATIONS    =

PROJECTNAME	= nvidia-modeset
TARGET		= nvidia-modeset
TEMPLATE	= app
