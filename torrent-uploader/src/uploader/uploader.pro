_RC_FILE = 1
_MEDIA_INFO = 1

include(../common/common.pri)
TEMPLATE = app
INCLUDEPATH += .
SOURCES += main.cpp \
    dialogs/welcomedialog.cpp \
    dialogs/settingsdialog.cpp \
    widgets/ImageWidget.cpp \
    widgets/bbcodewidget.cpp \
    dialogs/mainwindow.cpp \
    dialogs/previewdialog.cpp \
    trackers/trackertbdevyuna.cpp
HEADERS += version.h \
    dialogs/welcomedialog.h \
    dialogs/settingsdialog.h \
    widgets/ImageWidget.h \
    widgets/bbcodewidget.h \
    dialogs/mainwindow.h \
    dialogs/previewdialog.h \
    trackers/trackertbdevyuna.h \
    trackers/trackerrequest.h \
    ../common/interfaces.h
FORMS += dialogs/welcomedialog.ui \
    dialogs/settingsdialog.ui \
    dialogs/mainwindow.ui
