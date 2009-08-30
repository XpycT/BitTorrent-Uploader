#include <QtGui>
#include "mainwindow.h"
#include "dialogs/welcomedialog.h"
#include "dialogs/settingsdialog.h"
#include "dialogs/previewdialog.h"

MainWindow::MainWindow()
{
    setupUi(this);
    m_settings = new QSettings(QApplication::organizationName(), QApplication::applicationName());
    setWindowTitle(QString("%1 [%2]").arg(QApplication::applicationName())
                   .arg(QApplication::applicationVersion()));

    createStatusBar();
    readSettings();

    if(!s_hide_welcome){
        WelcomeDialog welcome;
        if(welcome.exec()==QDialog::Accepted)
            readSettings();
    }
    //setConnectMode(Connecting_imdb);
    connect(action_Preferences,SIGNAL(triggered()),this,SLOT(showPreferences()));
    connect(actionAbout_Torrent_Uploader,SIGNAL(triggered()),this,SLOT(showAbout()));
}
void MainWindow::on_browseTorrentButton_clicked(){
    QString lastDir=m_settings->value("LastDir", "").toString();
    QString fileName=QFileDialog::getOpenFileName(this,tr("Select a .torrent file")
                                                  ,lastDir,tr("Torrent File (*.torrent)"));
    if(fileName.isEmpty())
        return;
    lineEditTorrentFile->setText(fileName);
    m_settings->setValue("LastDir", QFileInfo(fileName).absoluteDir().path());
}
void MainWindow::on_previewButton_clicked(){
    QString name=lineEditTorrentName->text();
    QString category=comboBoxTorrentCategory->currentText();
    QString content=editor->toPlainText();
    QString image_poster=poster->getFileName();

    QStringList screens;
    if (!screen1->getFileName().isEmpty())
        screens << screen1->getFileName();
    if (!screen2->getFileName().isEmpty())
        screens << screen2->getFileName();
    if (!screen3->getFileName().isEmpty())
        screens << screen3->getFileName();

    PreviewDialog preview(0,name,category,content,image_poster,screens);
    preview.exec();
}
void MainWindow::on_clearButton_clicked(){
    lineEditTorrentFile->clear();
    lineEditTorrentName->clear();
    comboBoxTorrentCategory->setCurrentIndex(0);
    editor->clear();
}
void MainWindow::showPreferences(){
    SettingsDialog dlg(this);
    dlg.exec();
}

void MainWindow::showAbout(){
   QMessageBox::about(this,QApplication::applicationName()
                      ,QString("<h1>%1</h1>").arg(QApplication::applicationName()));

}

void  MainWindow::readSettings(){
    s_login         =m_settings->value("Profile/Login","").toString();
    s_password      =m_settings->value("Profile/Password","").toString();
    s_login_kp      =m_settings->value("Profile/KPLogin", "").toString();
    s_password_kp   =m_settings->value("Profile/KPPassword", "").toString();
    s_login_imdb    =m_settings->value("Profile/IMDBLogin", "").toString();
    s_password_imdb =m_settings->value("Profile/IMDBPassword", "").toString();

    s_hide_welcome  =m_settings->value("General/hideWelcome",false).toBool();
    s_use_kp        =m_settings->value("General/useKP",false).toBool();
    s_use_imdb      =m_settings->value("General/useIMDB",false).toBool();

    s_client_path   =m_settings->value("General/TrackerType", "").toString();   

    s_tracker_type  =m_settings->value("General/ClientPath", 0).toInt();
}
void MainWindow::setConnectMode(ConnectMode Mode){
    currentConnectMode = Mode;
    switch(currentConnectMode){
        case Connecting:{
                connectMovie->movie()->setPaused(false);
                connectMovie->setVisible(true);
                connectLabel->setVisible(false);
                statusLabel->setText(tr("Connected to tracker '%1'")
                                     .arg(QApplication::organizationDomain()));
            }
            break;
        case Connecting_kp:
        case Connecting_imdb:{
                connectMovie->movie()->setPaused(false);
                connectMovie->setVisible(true);
                connectLabel->setVisible(false);
                statusLabel->setText(tr("Retrieving data from '%1'")
                                     .arg(currentConnectMode==Connecting_kp?
                                          "KINOPOISK.RU"
                                          :"IMDB.COM"));
            }
            break;
        case Connected:{
                connectMovie->movie()->setPaused(true);
                connectMovie->setVisible(false);
                connectLabel->setVisible(true);
                connectLabel->setPixmap(QPixmap(":/images/network_connect.png"));
                statusLabel->setText(tr("Connected successfully."));

                if(!centralwidget->isEnabled())
                        centralwidget->setEnabled(true);
            }
            break;
        case Disconnected:{
                connectMovie->movie()->setPaused(true);
                connectMovie->setVisible(false);
                connectLabel->setVisible(true);
                connectLabel->setPixmap(QPixmap(":/images/network_disconnect.png"));
                statusLabel->setText(tr("Connected unsuccessfully."));

                centralwidget->setEnabled(false);
            }
            break;
    }
}
void MainWindow::closeEvent(QCloseEvent *e)
{
    if (askOnClose())
        e->accept();
    else
        e->ignore();
}
bool MainWindow::askOnClose()
{
    QMessageBox::StandardButton ret;
    ret = QMessageBox::question(this, tr("Torrent Uploader"),
                               tr("Do you want to quit?"),
                               QMessageBox::Ok
                               | QMessageBox::Cancel);
    if (ret == QMessageBox::Cancel)
        return false;
    return true;
}
void MainWindow::createStatusBar()
{
  connectLabel = new QLabel;
  connectLabel->setVisible(false);

  connectMovie = new QLabel;
  connectMovie->setMovie(new QMovie(":/images/load.gif", QByteArray()));
  connectMovie->setVisible(false);

  statusLabel = new QLabel(tr("Not connected."));
  statusLabel->setWordWrap(true);

  statusBar = new QStatusBar;
  statusBar->addWidget(connectLabel);
  statusBar->addWidget(connectMovie);
  statusBar->addWidget(statusLabel, 1);

  statusBar->setStyleSheet("QStatusBar::item { border-width: 0; }");
  setStatusBar(statusBar);
}
