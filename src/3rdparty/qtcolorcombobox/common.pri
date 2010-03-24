infile(config.pri, SOLUTIONS_LIBRARY, yes): CONFIG += qtcolorcombobox-uselib
TEMPLATE += fakelib
QTCOLORCOMBOBOX_LIBNAME = $$qtLibraryTarget(QtSolutions_ColorComboBox-2.4)
TEMPLATE -= fakelib
QTCOLORCOMBOBOX_LIBDIR = $$PWD/lib
unix:qtcolorcombobox-uselib:!qtcolorcombobox-buildlib:QMAKE_RPATHDIR += $$QTCOLORCOMBOBOX_LIBDIR
