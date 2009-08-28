#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <ui_settingsdialog.h>
class SettingsDialog : public QDialog, public Ui::SettingsDialog
{
    Q_OBJECT
public:
    SettingsDialog(QWidget *parent=0);
private slots:
    void on_okButton_clicked();
    void on_resetButton_clicked();
    void on_selectClientButton_clicked();
private:
    void readSettings();
    void saveSettings();
};

#endif // SETTINGSDIALOG_H
