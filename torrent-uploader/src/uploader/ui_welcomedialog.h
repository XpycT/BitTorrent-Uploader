/********************************************************************************
** Form generated from reading ui file 'welcomedialog.ui'
**
** Created: Fri 28. Aug 07:26:21 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_WELCOMEDIALOG_H
#define UI_WELCOMEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WelcomeDialog
{
public:
    QGridLayout *gridLayout_3;
    QFormLayout *formLayout;
    QLabel *loginLabel;
    QLineEdit *loginLineEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QCheckBox *hideBox;
    QPushButton *okButton;
    QPushButton *moreButton;
    QSpacerItem *verticalSpacer;
    QWidget *group;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBoxKP;
    QGridLayout *gridLayout;
    QFormLayout *formLayout_2;
    QLabel *loginLabelKP;
    QLineEdit *loginLineEditKP;
    QLabel *passwordLabelKP;
    QLineEdit *passwordLineEditKP;
    QGroupBox *groupBoxIMDB;
    QGridLayout *gridLayout_2;
    QFormLayout *formLayout_3;
    QLabel *emailLabelIMDB;
    QLineEdit *emailLineEditIMDB;
    QLabel *passwordLabelIMDB;
    QLineEdit *passwordLineEditIMDB;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QComboBox *comboBox;

    void setupUi(QDialog *WelcomeDialog)
    {
        if (WelcomeDialog->objectName().isEmpty())
            WelcomeDialog->setObjectName(QString::fromUtf8("WelcomeDialog"));
        WelcomeDialog->resize(276, 337);
        gridLayout_3 = new QGridLayout(WelcomeDialog);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        loginLabel = new QLabel(WelcomeDialog);
        loginLabel->setObjectName(QString::fromUtf8("loginLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, loginLabel);

        loginLineEdit = new QLineEdit(WelcomeDialog);
        loginLineEdit->setObjectName(QString::fromUtf8("loginLineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, loginLineEdit);

        passwordLabel = new QLabel(WelcomeDialog);
        passwordLabel->setObjectName(QString::fromUtf8("passwordLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, passwordLabel);

        passwordLineEdit = new QLineEdit(WelcomeDialog);
        passwordLineEdit->setObjectName(QString::fromUtf8("passwordLineEdit"));
        passwordLineEdit->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, passwordLineEdit);


        gridLayout_3->addLayout(formLayout, 0, 0, 1, 1);

        line = new QFrame(WelcomeDialog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        hideBox = new QCheckBox(WelcomeDialog);
        hideBox->setObjectName(QString::fromUtf8("hideBox"));

        horizontalLayout->addWidget(hideBox);

        okButton = new QPushButton(WelcomeDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/dialog-ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        okButton->setIcon(icon);

        horizontalLayout->addWidget(okButton);

        moreButton = new QPushButton(WelcomeDialog);
        moreButton->setObjectName(QString::fromUtf8("moreButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/arrow-down.png"), QSize(), QIcon::Normal, QIcon::Off);
        moreButton->setIcon(icon1);
        moreButton->setCheckable(true);

        horizontalLayout->addWidget(moreButton);


        gridLayout_3->addLayout(horizontalLayout, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(255, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 3, 0, 1, 1);

        group = new QWidget(WelcomeDialog);
        group->setObjectName(QString::fromUtf8("group"));
        group->setEnabled(true);
        verticalLayout = new QVBoxLayout(group);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBoxKP = new QGroupBox(group);
        groupBoxKP->setObjectName(QString::fromUtf8("groupBoxKP"));
        groupBoxKP->setCheckable(true);
        groupBoxKP->setChecked(false);
        gridLayout = new QGridLayout(groupBoxKP);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        loginLabelKP = new QLabel(groupBoxKP);
        loginLabelKP->setObjectName(QString::fromUtf8("loginLabelKP"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, loginLabelKP);

        loginLineEditKP = new QLineEdit(groupBoxKP);
        loginLineEditKP->setObjectName(QString::fromUtf8("loginLineEditKP"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, loginLineEditKP);

        passwordLabelKP = new QLabel(groupBoxKP);
        passwordLabelKP->setObjectName(QString::fromUtf8("passwordLabelKP"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, passwordLabelKP);

        passwordLineEditKP = new QLineEdit(groupBoxKP);
        passwordLineEditKP->setObjectName(QString::fromUtf8("passwordLineEditKP"));
        passwordLineEditKP->setEchoMode(QLineEdit::Password);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, passwordLineEditKP);


        gridLayout->addLayout(formLayout_2, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBoxKP);

        groupBoxIMDB = new QGroupBox(group);
        groupBoxIMDB->setObjectName(QString::fromUtf8("groupBoxIMDB"));
        groupBoxIMDB->setCheckable(true);
        groupBoxIMDB->setChecked(false);
        gridLayout_2 = new QGridLayout(groupBoxIMDB);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        formLayout_3 = new QFormLayout();
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        emailLabelIMDB = new QLabel(groupBoxIMDB);
        emailLabelIMDB->setObjectName(QString::fromUtf8("emailLabelIMDB"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, emailLabelIMDB);

        emailLineEditIMDB = new QLineEdit(groupBoxIMDB);
        emailLineEditIMDB->setObjectName(QString::fromUtf8("emailLineEditIMDB"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, emailLineEditIMDB);

        passwordLabelIMDB = new QLabel(groupBoxIMDB);
        passwordLabelIMDB->setObjectName(QString::fromUtf8("passwordLabelIMDB"));

        formLayout_3->setWidget(1, QFormLayout::LabelRole, passwordLabelIMDB);

        passwordLineEditIMDB = new QLineEdit(groupBoxIMDB);
        passwordLineEditIMDB->setObjectName(QString::fromUtf8("passwordLineEditIMDB"));
        passwordLineEditIMDB->setEchoMode(QLineEdit::Password);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, passwordLineEditIMDB);


        gridLayout_2->addLayout(formLayout_3, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBoxIMDB);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(group);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        comboBox = new QComboBox(group);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_2->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout_3->addWidget(group, 4, 0, 1, 1);

        QWidget::setTabOrder(loginLineEdit, passwordLineEdit);
        QWidget::setTabOrder(passwordLineEdit, hideBox);
        QWidget::setTabOrder(hideBox, okButton);
        QWidget::setTabOrder(okButton, moreButton);
        QWidget::setTabOrder(moreButton, groupBoxKP);
        QWidget::setTabOrder(groupBoxKP, loginLineEditKP);
        QWidget::setTabOrder(loginLineEditKP, passwordLineEditKP);
        QWidget::setTabOrder(passwordLineEditKP, groupBoxIMDB);
        QWidget::setTabOrder(groupBoxIMDB, emailLineEditIMDB);
        QWidget::setTabOrder(emailLineEditIMDB, passwordLineEditIMDB);
        QWidget::setTabOrder(passwordLineEditIMDB, comboBox);

        retranslateUi(WelcomeDialog);
        QObject::connect(okButton, SIGNAL(clicked()), WelcomeDialog, SLOT(accept()));
        QObject::connect(moreButton, SIGNAL(toggled(bool)), group, SLOT(setVisible(bool)));

        QMetaObject::connectSlotsByName(WelcomeDialog);
    } // setupUi

    void retranslateUi(QDialog *WelcomeDialog)
    {
        WelcomeDialog->setWindowTitle(QApplication::translate("WelcomeDialog", "User authorization", 0, QApplication::UnicodeUTF8));
        loginLabel->setText(QApplication::translate("WelcomeDialog", "Login :", 0, QApplication::UnicodeUTF8));
        passwordLabel->setText(QApplication::translate("WelcomeDialog", "Password :", 0, QApplication::UnicodeUTF8));
        hideBox->setText(QApplication::translate("WelcomeDialog", "Don't show this window", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("WelcomeDialog", "OK", 0, QApplication::UnicodeUTF8));
        groupBoxKP->setTitle(QApplication::translate("WelcomeDialog", "KINOPOISK.RU", 0, QApplication::UnicodeUTF8));
        loginLabelKP->setText(QApplication::translate("WelcomeDialog", "Login: ", 0, QApplication::UnicodeUTF8));
        passwordLabelKP->setText(QApplication::translate("WelcomeDialog", "Password: ", 0, QApplication::UnicodeUTF8));
        groupBoxIMDB->setTitle(QApplication::translate("WelcomeDialog", "IMDB.COM", 0, QApplication::UnicodeUTF8));
        emailLabelIMDB->setText(QApplication::translate("WelcomeDialog", "Email:", 0, QApplication::UnicodeUTF8));
        passwordLabelIMDB->setText(QApplication::translate("WelcomeDialog", "Password:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("WelcomeDialog", "Tracker type:", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("WelcomeDialog", "TBDev Yuna Editon", 0, QApplication::UnicodeUTF8)
        );
        Q_UNUSED(WelcomeDialog);
    } // retranslateUi

};

namespace Ui {
    class WelcomeDialog: public Ui_WelcomeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELCOMEDIALOG_H
