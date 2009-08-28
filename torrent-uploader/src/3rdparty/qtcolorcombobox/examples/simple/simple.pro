TEMPLATE = app

!include(../../src/qtcolorcombobox.pri) {
	message("Error including ../../src/qtcolorcombobox.pri")
}

SOURCES += main.cpp

