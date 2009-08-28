include(../common.pri)
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

qtcolorcombobox-uselib:!qtcolorcombobox-buildlib {
    LIBS += -L$$QTCOLORCOMBOBOX_LIBDIR -l$$QTCOLORCOMBOBOX_LIBNAME
} else {
    SOURCES += $$PWD/qtcolorcombobox.cpp
    HEADERS += $$PWD/qtcolorcombobox.h
}

win32 {
    contains(TEMPLATE, lib):contains(CONFIG, shared):DEFINES += QT_QTCOLORCOMBOBOX_EXPORT
    else:qtcolorcombobox-uselib:DEFINES += QT_QTCOLORCOMBOBOX_IMPORT
}
