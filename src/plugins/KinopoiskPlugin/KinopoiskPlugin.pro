TEMPLATE = lib
CONFIG += plugin
QT += gui \
    network
TARGET = kinopoisk

CONFIG(debug, debug|release) {
    message(Build Debug!)
    RCC_DIR = ../../../build/$${TARGET}/debug/rcc
    MOC_DIR = ../../../build/$${TARGET}/debug/moc
    OBJECTS_DIR = ../../../build/$${TARGET}/debug/obj

    mac|unix: TARGET = $$join(TARGET,,,_debug)
    win32: TARGET = $$join(TARGET,,d)
} else {
    message(Build Release!)
    RCC_DIR = ../../../build/$${TARGET}/release/rcc
    MOC_DIR = ../../../build/$${TARGET}/release/moc
    OBJECTS_DIR = ../../../build/$${TARGET}/release/obj
}

DESTDIR = ../../../bin/plugins/search

SOURCES = KinopoiskPlugin.cpp \
    selectmoviedialog.cpp
HEADERS = KinopoiskPlugin.h \
    selectmoviedialog.h \
    ../../common/version.h \
    ../../common/interfaces.h

DEPENDPATH +=. \
    ../../common \

INCLUDEPATH +=. \
    ../../common \

