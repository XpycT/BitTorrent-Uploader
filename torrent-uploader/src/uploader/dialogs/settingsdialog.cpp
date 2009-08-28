#include "settingsdialog.h"
#include "version.h"
#include <QSettings>
#include <QListWidgetItem>
#include <QFileDialog>
SettingsDialog::SettingsDialog(QWidget *parent)
        :QDialog(parent)
{
    setupUi(this);
    setWindowTitle(QString("%1 - %2").arg(QApplication::applicationName())
                   .arg(tr("Preferences")));

    setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);
    layout()->setSizeConstraint(QLayout::SetFixedSize);

    registerLink->setText(tr("<a style='text-decoration:none; color:#1a4d82;' href='http://%1'>Register</a>").arg(UPLOADER_DOMAIN));

    readSettings();
    connect(menuList,SIGNAL(currentRowChanged(int)),pageWidget,SLOT(setCurrentIndex(int)));

}

void SettingsDialog::on_resetButton_clicked(){
    loginLineEdit->setText("");
    passwordLineEdit->setText("");
    loginLineEditKP->setText("");
    passwordLineEditKP->setText("");
    loginLineEditIMDB->setText("");
    passwordLineEditIMDB->setText("");

    groupBoxKP->setChecked(false);
    groupBoxIMDB->setChecked(false);

    clientLineEdit->setText("");
}
void SettingsDialog::on_okButton_clicked(){
    saveSettings();
}
void SettingsDialog::on_selectClientButton_clicked(){
    QSettings settings(UPLOADER_ORGANIZATION, UPLOADER_NAME);

    QString lastDir = settings.value("LastDir","").toString();

    QString path = QFileDialog::getOpenFileName(0,tr("Select BitTorrent client")
                                                ,lastDir,tr("BitTorrent client (*.*)"));
    if(path.isEmpty())
        return;
    clientLineEdit->setText(path);
    settings.setValue("LastDir", QFileInfo(path).absoluteDir().path());
}
void SettingsDialog::saveSettings(){
    QSettings settings(UPLOADER_ORGANIZATION, UPLOADER_NAME);
    settings.setValue("Profile/Login", loginLineEdit->text());
    settings.setValue("Profile/Password", passwordLineEdit->text());
    settings.setValue("Profile/KPLogin", loginLineEditKP->text());
    settings.setValue("Profile/KPPassword", passwordLineEditKP->text());
    settings.setValue("Profile/IMDBLogin", loginLineEditIMDB->text());
    settings.setValue("Profile/IMDBPassword", passwordLineEditIMDB->text());

    settings.setValue("General/useKP", groupBoxKP->isChecked());
    settings.setValue("General/useIMDB", groupBoxIMDB->isChecked());

    settings.setValue("General/ClientPath", clientLineEdit->text());
}
void SettingsDialog::readSettings(){
    QSettings settings(UPLOADER_ORGANIZATION, UPLOADER_NAME);
    loginLineEdit->setText(settings.value("Profile/Login","").toString());
    passwordLineEdit->setText(settings.value("Profile/Password","").toString());
    loginLineEditKP->setText(settings.value("Profile/KPLogin", "").toString());
    passwordLineEditKP->setText(settings.value("Profile/KPPassword", "").toString());
    loginLineEditIMDB->setText(settings.value("Profile/IMDBLogin", "").toString());
    passwordLineEditIMDB->setText(settings.value("Profile/IMDBPassword", "").toString());

    if (settings.value("General/useKP",false).toBool())
        groupBoxKP->setChecked(true);
    if (settings.value("General/useIMDB",false).toBool())
        groupBoxIMDB->setChecked(true);

    clientLineEdit->setText(settings.value("General/ClientPath", "").toString());
}
