include(../3rdparty/qtsingleapplication/src/qtsingleapplication.pri)
include(../3rdparty/qtcolorcombobox/src/qtcolorcombobox.pri)
CONFIG += qt
QT += network webkit
#QT -= phonon xml
DESTDIR = ../../bin

DEPENDPATH += \
    . \
    ../common \

INCLUDEPATH += \
    . \
    ../common \

win32:INCLUDEPATH += ../3rdparty/MediaInfo/Developers/Source


CONFIG(debug, debug|release) {
    message(Build Debug!)
    RCC_DIR = ../../build/$${TARGET}/debug/rcc
    MOC_DIR = ../../build/$${TARGET}/debug/moc
    OBJECTS_DIR = ../../build/$${TARGET}/debug/obj

    mac|unix: TARGET = $$join(TARGET,,,_debug)
    win32: TARGET = $$join(TARGET,,d)
} else {
    message(Build Release!)
    RCC_DIR = ../../build/$${TARGET}/release/rcc
    MOC_DIR = ../../build/$${TARGET}/release/moc
    OBJECTS_DIR = ../../build/$${TARGET}/release/obj
}
contains(_RC_FILE, 1 ) {
  win32:RC_FILE = $${TARGET}.rc
}
TRANSLATIONS += ../../data/i18n/i18n_en.ts \
                 ../../data/i18n/i18n_ru.ts

RESOURCES += ../../data/uploader.qrc
