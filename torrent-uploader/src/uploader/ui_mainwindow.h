/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun 14. Feb 16:29:56 2010
**      by: Qt User Interface Compiler version 4.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>
#include "widgets/bbcodewidget.h"
#include "widgets/imagewidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Reconnect;
    QAction *action_Exit;
    QAction *action_Preferences;
    QAction *actionAbout_Torrent_Uploader;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    ImageWidget *poster;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEditTorrentFile;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *createTorrentButton;
    QPushButton *browseTorrentButton;
    QLabel *label_2;
    QComboBox *comboBoxTorrentCategory;
    QLabel *label_3;
    QLineEdit *lineEditTorrentName;
    ImageWidget *screen1;
    ImageWidget *screen2;
    ImageWidget *screen3;
    BBCodeWidget *editor;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *uploadButton;
    QPushButton *clearButton;
    QPushButton *previewButton;
    QMenuBar *menubar;
    QMenu *menu_File;
    QMenu *menu_Tools;
    QMenu *menu_Options;
    QMenu *menu_Help;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(850, 600);
        MainWindow->setAutoFillBackground(false);
        action_Reconnect = new QAction(MainWindow);
        action_Reconnect->setObjectName(QString::fromUtf8("action_Reconnect"));
        action_Exit = new QAction(MainWindow);
        action_Exit->setObjectName(QString::fromUtf8("action_Exit"));
        action_Preferences = new QAction(MainWindow);
        action_Preferences->setObjectName(QString::fromUtf8("action_Preferences"));
        actionAbout_Torrent_Uploader = new QAction(MainWindow);
        actionAbout_Torrent_Uploader->setObjectName(QString::fromUtf8("actionAbout_Torrent_Uploader"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        poster = new ImageWidget(centralwidget);
        poster->setObjectName(QString::fromUtf8("poster"));
        poster->setMinimumSize(QSize(250, 291));
        poster->setMaximumSize(QSize(250, 309));

        gridLayout->addWidget(poster, 0, 0, 2, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setScaledContents(false);

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lineEditTorrentFile = new QLineEdit(centralwidget);
        lineEditTorrentFile->setObjectName(QString::fromUtf8("lineEditTorrentFile"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEditTorrentFile);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(148, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        createTorrentButton = new QPushButton(centralwidget);
        createTorrentButton->setObjectName(QString::fromUtf8("createTorrentButton"));

        horizontalLayout->addWidget(createTorrentButton);

        browseTorrentButton = new QPushButton(centralwidget);
        browseTorrentButton->setObjectName(QString::fromUtf8("browseTorrentButton"));

        horizontalLayout->addWidget(browseTorrentButton);


        formLayout->setLayout(1, QFormLayout::FieldRole, horizontalLayout);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        comboBoxTorrentCategory = new QComboBox(centralwidget);
        comboBoxTorrentCategory->setObjectName(QString::fromUtf8("comboBoxTorrentCategory"));

        formLayout->setWidget(2, QFormLayout::FieldRole, comboBoxTorrentCategory);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_3);

        lineEditTorrentName = new QLineEdit(centralwidget);
        lineEditTorrentName->setObjectName(QString::fromUtf8("lineEditTorrentName"));

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEditTorrentName);


        gridLayout->addLayout(formLayout, 0, 1, 1, 3);

        screen1 = new ImageWidget(centralwidget);
        screen1->setObjectName(QString::fromUtf8("screen1"));
        screen1->setMinimumSize(QSize(0, 180));
        screen1->setMaximumSize(QSize(16777215, 180));

        gridLayout->addWidget(screen1, 1, 1, 1, 1);

        screen2 = new ImageWidget(centralwidget);
        screen2->setObjectName(QString::fromUtf8("screen2"));
        screen2->setMinimumSize(QSize(0, 180));
        screen2->setMaximumSize(QSize(16777215, 180));

        gridLayout->addWidget(screen2, 1, 2, 1, 1);

        screen3 = new ImageWidget(centralwidget);
        screen3->setObjectName(QString::fromUtf8("screen3"));
        screen3->setMinimumSize(QSize(0, 180));
        screen3->setMaximumSize(QSize(16777215, 180));

        gridLayout->addWidget(screen3, 1, 3, 1, 1);

        editor = new BBCodeWidget(centralwidget);
        editor->setObjectName(QString::fromUtf8("editor"));

        gridLayout->addWidget(editor, 2, 0, 1, 4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        uploadButton = new QPushButton(centralwidget);
        uploadButton->setObjectName(QString::fromUtf8("uploadButton"));

        horizontalLayout_2->addWidget(uploadButton);

        clearButton = new QPushButton(centralwidget);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));

        horizontalLayout_2->addWidget(clearButton);

        previewButton = new QPushButton(centralwidget);
        previewButton->setObjectName(QString::fromUtf8("previewButton"));

        horizontalLayout_2->addWidget(previewButton);


        gridLayout->addLayout(horizontalLayout_2, 3, 0, 1, 4);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 850, 21));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menu_Tools = new QMenu(menubar);
        menu_Tools->setObjectName(QString::fromUtf8("menu_Tools"));
        menu_Options = new QMenu(menubar);
        menu_Options->setObjectName(QString::fromUtf8("menu_Options"));
        menu_Help = new QMenu(menubar);
        menu_Help->setObjectName(QString::fromUtf8("menu_Help"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu_File->menuAction());
        menubar->addAction(menu_Tools->menuAction());
        menubar->addAction(menu_Options->menuAction());
        menubar->addAction(menu_Help->menuAction());
        menu_File->addAction(action_Reconnect);
        menu_File->addSeparator();
        menu_File->addAction(action_Exit);
        menu_Options->addAction(action_Preferences);
        menu_Help->addAction(actionAbout_Torrent_Uploader);

        retranslateUi(MainWindow);
        QObject::connect(action_Exit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        action_Reconnect->setText(QApplication::translate("MainWindow", "&Reconnect", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        action_Reconnect->setStatusTip(QApplication::translate("MainWindow", "Reconnect to the site", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        action_Reconnect->setShortcut(QApplication::translate("MainWindow", "Ctrl+R", 0, QApplication::UnicodeUTF8));
        action_Exit->setText(QApplication::translate("MainWindow", "E&xit", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        action_Exit->setStatusTip(QApplication::translate("MainWindow", "Exit from application", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        action_Exit->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", 0, QApplication::UnicodeUTF8));
        action_Preferences->setText(QApplication::translate("MainWindow", "&Preferences...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        action_Preferences->setStatusTip(QApplication::translate("MainWindow", "Open preference dialog", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        action_Preferences->setShortcut(QApplication::translate("MainWindow", "Ctrl+P", 0, QApplication::UnicodeUTF8));
        actionAbout_Torrent_Uploader->setText(QApplication::translate("MainWindow", "&About Torrent Uploader", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Torrent File:", 0, QApplication::UnicodeUTF8));
        createTorrentButton->setText(QApplication::translate("MainWindow", "Create...", 0, QApplication::UnicodeUTF8));
        browseTorrentButton->setText(QApplication::translate("MainWindow", "Browse...", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Category:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Name :", 0, QApplication::UnicodeUTF8));
        uploadButton->setText(QApplication::translate("MainWindow", "Upload", 0, QApplication::UnicodeUTF8));
        clearButton->setText(QApplication::translate("MainWindow", "Clear", 0, QApplication::UnicodeUTF8));
        previewButton->setText(QApplication::translate("MainWindow", "Preview...", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menu_Tools->setTitle(QApplication::translate("MainWindow", "Tools", 0, QApplication::UnicodeUTF8));
        menu_Options->setTitle(QApplication::translate("MainWindow", "&Options", 0, QApplication::UnicodeUTF8));
        menu_Help->setTitle(QApplication::translate("MainWindow", "&Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
