#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

class QSettings;

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT
public:
    MainWindow();
private slots:
    void showPreferences();
    void showAbout();
private:
    bool askOnClose();
    void readSettings();

    QSettings *m_settings;
    QString s_login,s_password;
    QString s_login_kp,s_password_kp;
    QString s_login_imdb,s_password_imdb;
    QString s_client_path;

    bool s_hide_welcome,s_use_kp,s_use_imdb;

    int s_tracker_type;

protected:    
    void closeEvent(QCloseEvent *e);

};

#endif // MAINWINDOW_H
