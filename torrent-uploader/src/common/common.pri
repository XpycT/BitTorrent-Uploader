include(../3rdparty/qtsingleapplication/src/qtsingleapplication.pri)
include(../3rdparty/qtcolorcombobox/src/qtcolorcombobox.pri)
CONFIG += qt
QT += network webkit

DESTDIR = ../../bin

DEPENDPATH += \
    . \
    ../common \

INCLUDEPATH += \
    . \
    ../common \

contains(_MEDIA_INFO, 1 ) {
    DEFINES += MEDIA_INFO
    # Change path to your library folder
    INCLUDEPATH += ../../../3rdPartyLibs/MediaInfo/Developers/Source
}
contains(_CREATE_TORRENT, 1 ) {
    CONFIG += static
    DEFINES += CREATE_TORRENT
win32:INCLUDEPATH += . \
        ../../../3rdPartyLibs/libtorrent/include \
        ../../../3rdPartyLibs/libtorrent/zlib \
        ../../../../boost_1_42_0
win32:LIBS += -L"D:\SVN\3rdPartyLibs\libtorrent\bin\gcc-mingw-4.4.0\release\boost-source\character-set-ansi\dht-support-off\link-static\runtime-link-static\threading-multi" \
    -L"D:\boost_1_42_0\bin.v2\libs\system\build\gcc-mingw-4.4.0\release\boost-source\character-set-ansi\dht-support-off\link-static\threading-multi" \
    -L"D:\boost_1_42_0\bin.v2\libs\filesystem\build\gcc-mingw-4.4.0\release\link-static" \
    -llibtorrent -llibboost_system-mgw44-mt-1_42 -lws2_32 -llibboost_filesystem-mgw44-1_42
}



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
