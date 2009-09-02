#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "trackers/trackerrequest.h"
#include "ui_mainwindow.h"

class QSettings;

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT
public:
    MainWindow();
    enum ConnectMode {Connecting,Connecting_kp,Connecting_imdb,Connected,Disconnected,Uploading};
private slots:
    void showPreferences();
    void showAbout();
    void reconnect();
    void getCategory();
    void startDownload(QString &fileName);
    void blockInterface(bool &isBlocked);
    void showError(QString &message);
    void on_browseTorrentButton_clicked();
    void on_clearButton_clicked();
    void on_previewButton_clicked();
    void on_uploadButton_clicked();
private:
    void setConnectMode(ConnectMode Mode);
    bool askOnClose();
    void readSettings();
    void createStatusBar();

    QSettings *m_settings;
    QString s_login,s_password;
    QString s_login_kp,s_password_kp;
    QString s_login_imdb,s_password_imdb;
    QString s_client_path;

    bool s_hide_welcome,s_use_kp,s_use_imdb;

    int s_tracker_type;

    QLabel *connectLabel;
    QLabel *connectMovie;
    QLabel *statusLabel;
    QStatusBar *statusBar;

    ConnectMode currentConnectMode;
    TrackerRequest *tracker;
    QMap<int,QString> map;

protected:    
    void closeEvent(QCloseEvent *e);

};

#endif // MAINWINDOW_H
