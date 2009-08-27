include(../3rdparty/qtsingleapplication/src/qtsingleapplication.pri)
CONFIG += qt
QT += network
DESTDIR = ../../bin

DEPENDPATH += \
    . \
    ../common \

INCLUDEPATH += \
    . \
    ../common \

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

RESOURCES += ../../data/uploader.qrc
