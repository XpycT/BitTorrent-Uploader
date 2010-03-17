/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created: Wed Mar 17 15:41:01 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStackedWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QGridLayout *gridLayout_5;
    QSpacerItem *horizontalSpacer;
    QListWidget *menuList;
    QStackedWidget *pageWidget;
    QWidget *pageProfile;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QFormLayout *formLayout;
    QLabel *loginLabel;
    QLineEdit *loginLineEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QSpacerItem *horizontalSpacer_2;
    QLabel *registerLink;
    QGroupBox *groupBoxKP;
    QGridLayout *gridLayout_2;
    QFormLayout *formLayout_2;
    QLabel *loginLabel_2;
    QLineEdit *loginLineEditKP;
    QLabel *passwordLabel_2;
    QLineEdit *passwordLineEditKP;
    QSpacerItem *horizontalSpacer_3;
    QLabel *registerLinkKP;
    QGroupBox *groupBoxIMDB;
    QGridLayout *gridLayout_3;
    QFormLayout *formLayout_3;
    QLabel *loginLabel_3;
    QLineEdit *loginLineEditIMDB;
    QLabel *passwordLabel_3;
    QLineEdit *passwordLineEditIMDB;
    QSpacerItem *horizontalSpacer_4;
    QLabel *registerLinkIMDB;
    QWidget *pageOther;
    QGridLayout *gridLayout_6;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *clientLineEdit;
    QPushButton *selectClientButton;
    QSpacerItem *verticalSpacer;
    QFrame *line;
    QPushButton *resetButton;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QString::fromUtf8("SettingsDialog"));
        SettingsDialog->resize(477, 416);
        gridLayout_5 = new QGridLayout(SettingsDialog);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        horizontalSpacer = new QSpacerItem(232, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 3, 0, 1, 2);

        menuList = new QListWidget(SettingsDialog);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/profile.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(menuList);
        __qlistwidgetitem->setIcon(icon);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/application-x-desktop.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(menuList);
        __qlistwidgetitem1->setIcon(icon1);
        menuList->setObjectName(QString::fromUtf8("menuList"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(menuList->sizePolicy().hasHeightForWidth());
        menuList->setSizePolicy(sizePolicy);
        menuList->setMinimumSize(QSize(142, 0));
        menuList->setMaximumSize(QSize(142, 16777215));
        menuList->setFrameShape(QFrame::StyledPanel);
        menuList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        menuList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        menuList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        menuList->setProperty("showDropIndicator", QVariant(true));
        menuList->setIconSize(QSize(16, 16));

        gridLayout_5->addWidget(menuList, 0, 0, 1, 1);

        pageWidget = new QStackedWidget(SettingsDialog);
        pageWidget->setObjectName(QString::fromUtf8("pageWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pageWidget->sizePolicy().hasHeightForWidth());
        pageWidget->setSizePolicy(sizePolicy1);
        pageProfile = new QWidget();
        pageProfile->setObjectName(QString::fromUtf8("pageProfile"));
        gridLayout_4 = new QGridLayout(pageProfile);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        groupBox = new QGroupBox(pageProfile);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        loginLabel = new QLabel(groupBox);
        loginLabel->setObjectName(QString::fromUtf8("loginLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, loginLabel);

        loginLineEdit = new QLineEdit(groupBox);
        loginLineEdit->setObjectName(QString::fromUtf8("loginLineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, loginLineEdit);

        passwordLabel = new QLabel(groupBox);
        passwordLabel->setObjectName(QString::fromUtf8("passwordLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, passwordLabel);

        passwordLineEdit = new QLineEdit(groupBox);
        passwordLineEdit->setObjectName(QString::fromUtf8("passwordLineEdit"));
        passwordLineEdit->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, passwordLineEdit);


        gridLayout->addLayout(formLayout, 0, 0, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(216, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        registerLink = new QLabel(groupBox);
        registerLink->setObjectName(QString::fromUtf8("registerLink"));
        registerLink->setOpenExternalLinks(true);

        gridLayout->addWidget(registerLink, 1, 1, 1, 1);


        gridLayout_4->addWidget(groupBox, 0, 0, 1, 1);

        groupBoxKP = new QGroupBox(pageProfile);
        groupBoxKP->setObjectName(QString::fromUtf8("groupBoxKP"));
        groupBoxKP->setCheckable(true);
        groupBoxKP->setChecked(false);
        gridLayout_2 = new QGridLayout(groupBoxKP);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        loginLabel_2 = new QLabel(groupBoxKP);
        loginLabel_2->setObjectName(QString::fromUtf8("loginLabel_2"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, loginLabel_2);

        loginLineEditKP = new QLineEdit(groupBoxKP);
        loginLineEditKP->setObjectName(QString::fromUtf8("loginLineEditKP"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, loginLineEditKP);

        passwordLabel_2 = new QLabel(groupBoxKP);
        passwordLabel_2->setObjectName(QString::fromUtf8("passwordLabel_2"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, passwordLabel_2);

        passwordLineEditKP = new QLineEdit(groupBoxKP);
        passwordLineEditKP->setObjectName(QString::fromUtf8("passwordLineEditKP"));
        passwordLineEditKP->setEchoMode(QLineEdit::Password);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, passwordLineEditKP);


        gridLayout_2->addLayout(formLayout_2, 0, 0, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(178, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 1, 0, 1, 1);

        registerLinkKP = new QLabel(groupBoxKP);
        registerLinkKP->setObjectName(QString::fromUtf8("registerLinkKP"));
        registerLinkKP->setOpenExternalLinks(true);

        gridLayout_2->addWidget(registerLinkKP, 1, 1, 1, 1);


        gridLayout_4->addWidget(groupBoxKP, 1, 0, 1, 1);

        groupBoxIMDB = new QGroupBox(pageProfile);
        groupBoxIMDB->setObjectName(QString::fromUtf8("groupBoxIMDB"));
        groupBoxIMDB->setCheckable(true);
        groupBoxIMDB->setChecked(false);
        gridLayout_3 = new QGridLayout(groupBoxIMDB);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        loginLabel_3 = new QLabel(groupBoxIMDB);
        loginLabel_3->setObjectName(QString::fromUtf8("loginLabel_3"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, loginLabel_3);

        loginLineEditIMDB = new QLineEdit(groupBoxIMDB);
        loginLineEditIMDB->setObjectName(QString::fromUtf8("loginLineEditIMDB"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, loginLineEditIMDB);

        passwordLabel_3 = new QLabel(groupBoxIMDB);
        passwordLabel_3->setObjectName(QString::fromUtf8("passwordLabel_3"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, passwordLabel_3);

        passwordLineEditIMDB = new QLineEdit(groupBoxIMDB);
        passwordLineEditIMDB->setObjectName(QString::fromUtf8("passwordLineEditIMDB"));
        passwordLineEditIMDB->setEchoMode(QLineEdit::Password);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, passwordLineEditIMDB);


        gridLayout_3->addLayout(formLayout_3, 0, 0, 1, 2);

        horizontalSpacer_4 = new QSpacerItem(178, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 1, 0, 1, 1);

        registerLinkIMDB = new QLabel(groupBoxIMDB);
        registerLinkIMDB->setObjectName(QString::fromUtf8("registerLinkIMDB"));
        registerLinkIMDB->setOpenExternalLinks(true);

        gridLayout_3->addWidget(registerLinkIMDB, 1, 1, 1, 1);


        gridLayout_4->addWidget(groupBoxIMDB, 2, 0, 1, 1);

        pageWidget->addWidget(pageProfile);
        pageOther = new QWidget();
        pageOther->setObjectName(QString::fromUtf8("pageOther"));
        gridLayout_6 = new QGridLayout(pageOther);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        groupBox_2 = new QGroupBox(pageOther);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        clientLineEdit = new QLineEdit(groupBox_2);
        clientLineEdit->setObjectName(QString::fromUtf8("clientLineEdit"));

        horizontalLayout->addWidget(clientLineEdit);

        selectClientButton = new QPushButton(groupBox_2);
        selectClientButton->setObjectName(QString::fromUtf8("selectClientButton"));
        selectClientButton->setMaximumSize(QSize(25, 16777215));

        horizontalLayout->addWidget(selectClientButton);


        gridLayout_6->addWidget(groupBox_2, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer, 2, 0, 1, 1);

        pageWidget->addWidget(pageOther);

        gridLayout_5->addWidget(pageWidget, 0, 1, 1, 4);

        line = new QFrame(SettingsDialog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_5->addWidget(line, 1, 0, 2, 5);

        resetButton = new QPushButton(SettingsDialog);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        resetButton->setMaximumSize(QSize(31, 25));
        resetButton->setAutoFillBackground(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        resetButton->setIcon(icon2);
        resetButton->setAutoDefault(false);

        gridLayout_5->addWidget(resetButton, 2, 2, 2, 1);

        okButton = new QPushButton(SettingsDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setMaximumSize(QSize(88, 16777215));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/dialog-ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        okButton->setIcon(icon3);

        gridLayout_5->addWidget(okButton, 2, 3, 2, 1);

        cancelButton = new QPushButton(SettingsDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setMaximumSize(QSize(88, 16777215));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/dialog-cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        cancelButton->setIcon(icon4);

        gridLayout_5->addWidget(cancelButton, 2, 4, 2, 1);

        QWidget::setTabOrder(menuList, loginLineEdit);
        QWidget::setTabOrder(loginLineEdit, passwordLineEdit);
        QWidget::setTabOrder(passwordLineEdit, groupBoxKP);
        QWidget::setTabOrder(groupBoxKP, loginLineEditKP);
        QWidget::setTabOrder(loginLineEditKP, passwordLineEditKP);
        QWidget::setTabOrder(passwordLineEditKP, groupBoxIMDB);
        QWidget::setTabOrder(groupBoxIMDB, loginLineEditIMDB);
        QWidget::setTabOrder(loginLineEditIMDB, passwordLineEditIMDB);
        QWidget::setTabOrder(passwordLineEditIMDB, resetButton);
        QWidget::setTabOrder(resetButton, okButton);
        QWidget::setTabOrder(okButton, cancelButton);
        QWidget::setTabOrder(cancelButton, clientLineEdit);
        QWidget::setTabOrder(clientLineEdit, selectClientButton);

        retranslateUi(SettingsDialog);
        QObject::connect(cancelButton, SIGNAL(clicked()), SettingsDialog, SLOT(reject()));
        QObject::connect(okButton, SIGNAL(clicked()), SettingsDialog, SLOT(accept()));

        pageWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QApplication::translate("SettingsDialog", "Preferences", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = menuList->isSortingEnabled();
        menuList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = menuList->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("SettingsDialog", "Profiles", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem1 = menuList->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("SettingsDialog", "Other", 0, QApplication::UnicodeUTF8));
        menuList->setSortingEnabled(__sortingEnabled);

        groupBox->setTitle(QApplication::translate("SettingsDialog", "Tracker Account", 0, QApplication::UnicodeUTF8));
        loginLabel->setText(QApplication::translate("SettingsDialog", "Login:", 0, QApplication::UnicodeUTF8));
        passwordLabel->setText(QApplication::translate("SettingsDialog", "Password", 0, QApplication::UnicodeUTF8));
        registerLink->setText(QApplication::translate("SettingsDialog", "<a style='text-decoration:none; color:#1a4d82;' href=\"#\">Register</a>", 0, QApplication::UnicodeUTF8));
        groupBoxKP->setTitle(QApplication::translate("SettingsDialog", "KINOPOISK.RU Account (not necessarily)", 0, QApplication::UnicodeUTF8));
        loginLabel_2->setText(QApplication::translate("SettingsDialog", "Login:", 0, QApplication::UnicodeUTF8));
        passwordLabel_2->setText(QApplication::translate("SettingsDialog", "Password", 0, QApplication::UnicodeUTF8));
        registerLinkKP->setText(QApplication::translate("SettingsDialog", "<a style='text-decoration:none; color:#1a4d82;' href=\"http://www.kinopoisk.ru/level/30/#new\">Register</a>", 0, QApplication::UnicodeUTF8));
        groupBoxIMDB->setTitle(QApplication::translate("SettingsDialog", "IMDB.COM Account (not necessarily)", 0, QApplication::UnicodeUTF8));
        loginLabel_3->setText(QApplication::translate("SettingsDialog", "Email:", 0, QApplication::UnicodeUTF8));
        passwordLabel_3->setText(QApplication::translate("SettingsDialog", "Password", 0, QApplication::UnicodeUTF8));
        registerLinkIMDB->setText(QApplication::translate("SettingsDialog", "<a style='text-decoration:none; color:#1a4d82;' href=\"https://secure.imdb.com/register-imdb/?why=personalize\">Register</a>", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("SettingsDialog", "Select BitTorrent client", 0, QApplication::UnicodeUTF8));
        selectClientButton->setText(QApplication::translate("SettingsDialog", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        resetButton->setToolTip(QApplication::translate("SettingsDialog", "Reset all settings", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        resetButton->setText(QString());
        okButton->setText(QApplication::translate("SettingsDialog", "OK", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("SettingsDialog", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
