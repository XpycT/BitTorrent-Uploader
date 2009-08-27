#ifndef WELCOMEDIALOG_H
#define WELCOMEDIALOG_H

#include <QDialog>
#include "ui_welcomedialog.h"
class WelcomeDialog : public QDialog, public Ui::WelcomeDialog
{
    Q_OBJECT
public:
    WelcomeDialog(QWidget *parent=0);
private slots:
    void changeIcon(bool s);
    void on_okButton_clicked();
private:
    void readSettings();
    void saveSettings();
};

#endif // WELCOMEDIALOG_H
