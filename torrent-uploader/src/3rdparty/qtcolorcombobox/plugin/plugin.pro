TEMPLATE = lib
CONFIG += qt plugin designer release

TARGET = qtcolorcomboboxplugin
include(../src/qtcolorcombobox.pri)

SOURCES += plugin.cpp
HEADERS += plugin.h

TARGET = $$qtLibraryTarget($$TARGET)
PLUGINDIR = $$[QT_INSTALL_PLUGINS]/designer
win32: DLLDESTDIR = $$PLUGINDIR
else: DESTDIR = $$PLUGINDIR

target.path += $$PLUGINDIR
INSTALLS += target
