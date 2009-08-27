_RC_FILE = 1
include(../common/common.pri)
TEMPLATE = app
INCLUDEPATH += .
SOURCES += main.cpp \
    dialogs/welcomedialog.cpp \
    dialogs/settingsdialog.cpp
HEADERS += version.h \
    dialogs/welcomedialog.h \
    dialogs/settingsdialog.h
FORMS += dialogs/welcomedialog.ui \
    dialogs/settingsdialog.ui
