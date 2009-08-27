#include <QSettings>
#include "welcomedialog.h"
#include "version.h"
WelcomeDialog::WelcomeDialog(QWidget *parent)
        :QDialog(parent)
{
    setupUi(this);
    setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);
    group->setVisible(false);
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    readSettings();

    connect(moreButton, SIGNAL(toggled(bool)), this, SLOT(changeIcon(bool)));
}

void WelcomeDialog::changeIcon(bool s)
{
  if (s) {
    moreButton->setIcon(QIcon(":/images/arrow-up.png"));
  }
  else {
    moreButton->setIcon(QIcon(":/images/arrow-down.png"));
  }
}
void WelcomeDialog::on_okButton_clicked(){
    saveSettings();
}
void WelcomeDialog::saveSettings(){
    QSettings settings(UPLOADER_ORGANIZATION, UPLOADER_NAME);
    settings.setValue("Profile/Login", loginLineEdit->text());
    settings.setValue("Profile/Password", passwordLineEdit->text());
    settings.setValue("Profile/KPLogin", loginLineEditKP->text());
    settings.setValue("Profile/KPPassword", passwordLineEditKP->text());
    settings.setValue("Profile/IMDBLogin", emailLineEditIMDB->text());
    settings.setValue("Profile/IMDBPassword", passwordLineEditIMDB->text());

    settings.setValue("General/hideWelcome", hideBox->isChecked());
    settings.setValue("General/useKP", groupBoxKP->isChecked());
    settings.setValue("General/useIMDB", groupBoxIMDB->isChecked());

    settings.setValue("General/TrackerType", comboBox->currentIndex());
}
void WelcomeDialog::readSettings(){
    QSettings settings(UPLOADER_ORGANIZATION, UPLOADER_NAME);
    loginLineEdit->setText(settings.value("Profile/Login","").toString());
    passwordLineEdit->setText(settings.value("Profile/Password","").toString());
    loginLineEditKP->setText(settings.value("Profile/KPLogin", "").toString());
    passwordLineEditKP->setText(settings.value("Profile/KPPassword", "").toString());
    emailLineEditIMDB->setText(settings.value("Profile/IMDBLogin", "").toString());
    passwordLineEditIMDB->setText(settings.value("Profile/IMDBPassword", "").toString());

    if (settings.value("General/hideWelcome",false).toBool())
        hideBox->setChecked(true);
    if (settings.value("General/useKP",false).toBool())
        groupBoxKP->setChecked(true);
    if (settings.value("General/useIMDB",false).toBool())
        groupBoxIMDB->setChecked(true);

    comboBox->setCurrentIndex(settings.value("Profile/TrackerType", 0).toInt());
}
