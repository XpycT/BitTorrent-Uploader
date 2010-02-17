/********************************************************************************
** Form generated from reading UI file 'createTorrentDialog.ui'
**
** Created: Wed 17. Feb 12:33:00 2010
**      by: Qt User Interface Compiler version 4.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATETORRENTDIALOG_H
#define UI_CREATETORRENTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_createTorrentDialog
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLineEdit *textInputPath;
    QSpacerItem *horizontalSpacer;
    QPushButton *addFile_button;
    QPushButton *addFolder_button;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QPlainTextEdit *trackers_list;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_2;
    QPlainTextEdit *URLSeeds_list;
    QSpacerItem *verticalSpacer;
    QLabel *label_3;
    QLineEdit *txt_comment;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_2;
    QComboBox *comboPieceSize;
    QPushButton *createButton;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *cancelButton;
    QProgressBar *progressBar;
    QLabel *label_5;

    void setupUi(QDialog *createTorrentDialog)
    {
        if (createTorrentDialog->objectName().isEmpty())
            createTorrentDialog->setObjectName(QString::fromUtf8("createTorrentDialog"));
        createTorrentDialog->resize(393, 436);
        QFont font;
        font.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font.setPointSize(8);
        createTorrentDialog->setFont(font);
        gridLayout_3 = new QGridLayout(createTorrentDialog);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox = new QGroupBox(createTorrentDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textInputPath = new QLineEdit(groupBox);
        textInputPath->setObjectName(QString::fromUtf8("textInputPath"));

        gridLayout->addWidget(textInputPath, 0, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(193, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        addFile_button = new QPushButton(groupBox);
        addFile_button->setObjectName(QString::fromUtf8("addFile_button"));
        addFile_button->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(addFile_button, 1, 1, 1, 1);

        addFolder_button = new QPushButton(groupBox);
        addFolder_button->setObjectName(QString::fromUtf8("addFolder_button"));
        addFolder_button->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(addFolder_button, 1, 2, 1, 1);


        gridLayout_3->addWidget(groupBox, 1, 0, 1, 3);

        groupBox_2 = new QGroupBox(createTorrentDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        trackers_list = new QPlainTextEdit(groupBox_2);
        trackers_list->setObjectName(QString::fromUtf8("trackers_list"));
        trackers_list->setMaximumSize(QSize(16777215, 77));

        gridLayout_2->addWidget(trackers_list, 0, 1, 2, 2);

        verticalSpacer_2 = new QSpacerItem(20, 55, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 1, 0, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 2, 0, 1, 1);

        URLSeeds_list = new QPlainTextEdit(groupBox_2);
        URLSeeds_list->setObjectName(QString::fromUtf8("URLSeeds_list"));
        URLSeeds_list->setMaximumSize(QSize(16777215, 77));

        gridLayout_2->addWidget(URLSeeds_list, 2, 1, 2, 2);

        verticalSpacer = new QSpacerItem(20, 56, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 3, 0, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 4, 0, 1, 1);

        txt_comment = new QLineEdit(groupBox_2);
        txt_comment->setObjectName(QString::fromUtf8("txt_comment"));
        txt_comment->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(txt_comment, 4, 1, 1, 2);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 5, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(224, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 5, 1, 1, 1);

        comboPieceSize = new QComboBox(groupBox_2);
        comboPieceSize->setObjectName(QString::fromUtf8("comboPieceSize"));
        comboPieceSize->setMinimumSize(QSize(0, 25));

        gridLayout_2->addWidget(comboPieceSize, 5, 2, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 2, 0, 1, 3);

        createButton = new QPushButton(createTorrentDialog);
        createButton->setObjectName(QString::fromUtf8("createButton"));
        createButton->setMinimumSize(QSize(0, 25));

        gridLayout_3->addWidget(createButton, 3, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(174, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 3, 1, 1, 1);

        cancelButton = new QPushButton(createTorrentDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setMinimumSize(QSize(0, 25));

        gridLayout_3->addWidget(cancelButton, 3, 2, 1, 1);

        progressBar = new QProgressBar(createTorrentDialog);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(progressBar, 4, 0, 1, 3);

        label_5 = new QLabel(createTorrentDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setStyleSheet(QString::fromUtf8("background-color: rgb(253, 255, 234);"));

        gridLayout_3->addWidget(label_5, 0, 0, 1, 3);


        retranslateUi(createTorrentDialog);
        QObject::connect(cancelButton, SIGNAL(clicked()), createTorrentDialog, SLOT(reject()));

        comboPieceSize->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(createTorrentDialog);
    } // setupUi

    void retranslateUi(QDialog *createTorrentDialog)
    {
        createTorrentDialog->setWindowTitle(QApplication::translate("createTorrentDialog", "Create New Torrent", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("createTorrentDialog", "Select Source", 0, QApplication::UnicodeUTF8));
        addFile_button->setText(QApplication::translate("createTorrentDialog", "Add file", 0, QApplication::UnicodeUTF8));
        addFolder_button->setText(QApplication::translate("createTorrentDialog", "Add Directory", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("createTorrentDialog", "Torrent Properties", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("createTorrentDialog", "Trackers:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("createTorrentDialog", "Web Seeds:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("createTorrentDialog", "Connect:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("createTorrentDialog", "Piece Size:", 0, QApplication::UnicodeUTF8));
        comboPieceSize->clear();
        comboPieceSize->insertItems(0, QStringList()
         << QApplication::translate("createTorrentDialog", "(auto detect)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("createTorrentDialog", "32 KiB", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("createTorrentDialog", "64 KiB", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("createTorrentDialog", "128 KiB", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("createTorrentDialog", "256 KiB", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("createTorrentDialog", "512 KiB", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("createTorrentDialog", "1 MiB", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("createTorrentDialog", "2 MiB", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("createTorrentDialog", "4 MiB", 0, QApplication::UnicodeUTF8)
        );
        createButton->setText(QApplication::translate("createTorrentDialog", "Create and save as...", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("createTorrentDialog", "Close", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("createTorrentDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Beta test.</p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">In windows it not work correctly</p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class createTorrentDialog: public Ui_createTorrentDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATETORRENTDIALOG_H
