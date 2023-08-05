
SOURCES += Main.cpp Krkr2DrawDeviceWrapper.cpp BasicDrawDevice.cpp

PROJECT_BASENAME = BasicDrawDevice

LDLIBS += -lwinmm -lgdi32

RC_LEGALCOPYRIGHT ?= Copyright (C) 2023-2023 Julian Uy; See details of license at license.txt, or the source code location.

include external/tp_stubz/Rules.lib.make
