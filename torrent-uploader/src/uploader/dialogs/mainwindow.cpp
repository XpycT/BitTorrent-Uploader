#include <QtGui>
#include "mainwindow.h"
#include "dialogs/welcomedialog.h"
#include "dialogs/settingsdialog.h"
#include "dialogs/previewdialog.h"
#include "trackers/trackertbdevyuna.h"

#ifdef MEDIA_INFO
#ifdef Q_WS_WIN
    #ifdef MEDIAINFO_LIBRARY
        #include "MediaInfo/MediaInfo.h" //Staticly-loaded library (.lib or .a or .so)
        #define MediaInfoNameSpace MediaInfoLib;
    #else //MEDIAINFO_LIBRARY
        #include "MediaInfoDLL/MediaInfoDLL.h" //Dynamicly-loaded library (.dll or .so)
        #define MediaInfoNameSpace MediaInfoDLL;
    #endif //MEDIAINFO_LIBRARY
    #include <iostream>
    #include <iomanip>
    using namespace MediaInfoNameSpace;    
#endif
#endif

MainWindow::MainWindow()
{
    setupUi(this);

    centralwidget->setEnabled(false);
    menu_Tools->setEnabled(false);

    m_settings = new QSettings(QApplication::organizationName(), QApplication::applicationName());
    setWindowTitle(QString("%1 [%2]").arg(QApplication::applicationName())
                   .arg(QApplication::applicationVersion()));

    loadPlugins();
    createStatusBar();
    readSettings();

    if(!s_hide_welcome){
        WelcomeDialog welcome;
        if(welcome.exec()==QDialog::Accepted)
            readSettings();
    }
    switch(s_tracker_type){
        case 0:
        tracker=new TrackerTBDevYuna;        
    }
    tracker->checkLogin(s_login,s_password);
    setConnectMode(Connecting);

    connect(tracker,SIGNAL(categoryDone()),this,SLOT(getCategory()));
    connect(tracker,SIGNAL(blockInterface(bool&)),this,SLOT(blockInterface(bool&)));
    connect(tracker,SIGNAL(uploadDone(QString&)),this,SLOT(startDownload(QString&)));
    connect(tracker,SIGNAL(errorMessage(QString&)),this,SLOT(showError(QString&)));

    connect(action_Preferences,SIGNAL(triggered()),this,SLOT(showPreferences()));
    connect(actionAbout_Torrent_Uploader,SIGNAL(triggered()),this,SLOT(showAbout()));
    connect(action_Reconnect,SIGNAL(triggered()),this,SLOT(reconnect()));

#ifdef MEDIA_INFO
    QAction* act = new QAction(this);
    act->setText(tr("Get Media Info..."));
    connect(act, SIGNAL(triggered()), this, SLOT(getMediaInfo()));
    menu_Tools->addSeparator();
    menu_Tools->addAction(act);
#endif


}
void MainWindow::showError(QString &message){
    uploadButton->setEnabled(true);
    setConnectMode(Connected);
    QMessageBox::warning(this,tr("Error"),
                         message);    
}
void MainWindow::startDownload(QString &fileName){
    uploadButton->setEnabled(true);
    setConnectMode(Connected);
     if(QFile::exists(s_client_path)){
         QStringList arguments;
         arguments << fileName;
         QProcess  *btclient = new QProcess;
         btclient->start(s_client_path,arguments);
    }

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
void MainWindow::on_uploadButton_clicked(){
    uploadButton->setEnabled(false);
    setConnectMode(Uploading);
    QString t_name=lineEditTorrentName->text();
    QString t_file=lineEditTorrentFile->text();
    QString t_descr=editor->toPlainText();
    QString cat=comboBoxTorrentCategory->currentText();    
    int t_cat;

     QMapIterator<int,QString> i(map);
     while (i.hasNext()) {
         i.next();
         if(i.value()==cat)
             t_cat = i.key();
     }
     QString t_image_poster=poster->getFileName();
     QStringList t_screens;
    if (!screen1->getFileName().isEmpty())
        t_screens << screen1->getFileName();
    if (!screen2->getFileName().isEmpty())
        t_screens << screen2->getFileName();
    if (!screen3->getFileName().isEmpty())
        t_screens << screen3->getFileName();

    tracker->uploadRelease(t_file,t_name
                           ,t_descr,t_cat
                           ,t_image_poster,t_screens);
}
void MainWindow::showPreferences(){
    SettingsDialog dlg(this);
    if(dlg.exec()){
        readSettings();
        tracker->checkLogin(s_login,s_password);
    }
}

void MainWindow::showAbout(){
   QMessageBox::about(this,QApplication::applicationName()
                      ,QString("<h3>%1 %2</h3>").arg(QApplication::applicationName())
                      .arg(QApplication::applicationVersion()));

}
void MainWindow::reconnect(){
    setConnectMode(Connecting);
    readSettings();
    tracker->checkLogin(s_login,s_password);
}
void MainWindow::blockInterface(bool &isBlocked){
   centralwidget->setEnabled(isBlocked);
   menu_Tools->setEnabled(isBlocked);
   if(!isBlocked)
       setConnectMode(Disconnected);
}
void MainWindow::getCategory(){
    comboBoxTorrentCategory->clear();

    //QMap<int,QString> map;
    map = tracker->returnCategory();
    qDebug() << map.count();

     QMapIterator<int,QString> i(map);
     while (i.hasNext()) {
         i.next();
         comboBoxTorrentCategory->addItem(i.value());
     }
     setConnectMode(Connected);
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

    s_client_path   =m_settings->value("General/ClientPath", "").toString();

    s_tracker_type  =m_settings->value("General/TrackerType", 0).toInt();
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
                statusLabel->setText(tr("Retrieving movie list from '%1'")
                                     .arg(currentConnectMode==Connecting_kp?
                                          "KINOPOISK.RU"
                                          :"IMDB.COM"));
            }
            break;
        case Retrieving_kp:
        case Retrieving_imdb:{
                connectMovie->movie()->setPaused(false);
                connectMovie->setVisible(true);
                connectLabel->setVisible(false);
                statusLabel->setText(tr("Retrieving movie description from '%1'")
                                     .arg(currentConnectMode==Retrieving_kp?
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

                if(!centralwidget->isEnabled()){
                        centralwidget->setEnabled(true);
                        menu_Tools->setEnabled(true);
                 }
            }
            break;
        case Disconnected:{
                connectMovie->movie()->setPaused(true);
                connectMovie->setVisible(false);
                connectLabel->setVisible(true);
                connectLabel->setPixmap(QPixmap(":/images/network_disconnect.png"));
                statusLabel->setText(tr("Connected unsuccessfully."));

                centralwidget->setEnabled(false);
                menu_Tools->setEnabled(false);
            }
            break;
        case Uploading:{
                connectMovie->movie()->setPaused(false);
                connectMovie->setVisible(true);
                connectLabel->setVisible(false);
                statusLabel->setText(tr("Uploading to tracker '%1'")
                                     .arg(QApplication::organizationDomain()));
            }
            break;
        case Done:{
                connectMovie->movie()->setPaused(true);
                connectMovie->setVisible(false);
                connectLabel->setVisible(true);
                connectLabel->setPixmap(QPixmap(":/images/tick.png"));
                statusLabel->setText(tr("Done."));
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

#ifdef MEDIA_INFO
void MainWindow::getMediaInfo()
{
// Обьявляем полностью все поддерживаемые форматы :)
QString formats;
formats.append(tr("All supported formats (*.mkv *.mka *.mks *.ogg *.ogm *.avi *.wav *.mpeg *.mpg *.vob *.mp4 *.mpgv *.mpv *.m1v *.m2v *.mp2 *.mp3 *.asf *.wma *.wmv *.qt *.mov *.rm *.rmvb *.ra *.ifo *.ac3 *.dts *.aac *.ape *.mac *.flac *.dat *.aiff *.aifc *.au *.iff *.paf *.sd2 *.irca *.w64 *.mat *.pvf *.xi *.sds *.avr);;"));
formats.append(tr("Matroska (*.mkv *.mka *.mks);;"));
formats.append(tr("Ogg (*.ogg *.ogm);;"));
formats.append(tr("Riff (*.avi *.wav);;"));
formats.append(tr("Mpeg 1&2 container (*.mpeg *.mpg *.vob);;"));
formats.append(tr("Mpeg 4 container (*.mp4);;"));
formats.append(tr("Mpeg video specific (*.mpgv *.mpv *.m1v *.m2v);;"));
formats.append(tr("Mpeg audio specific (*.mp2 *.mp3);;"));
formats.append(tr("Windows Media (*.asf *.wma *.wmv);;"));
formats.append(tr("Quicktime (*.qt *.mov);;"));
formats.append(tr("Real (*.rm *.rmvb *.ra);;"));
formats.append(tr("DVD-Video (*.ifo);;"));
formats.append(tr("AC3 (*.ac3);;"));
formats.append(tr("DTS (*.dts);;"));
formats.append(tr("AAC (*.aac);;"));
formats.append(tr("Monkey's Audio (*.ape *.mac);;"));
formats.append(tr("Flac (*.flac);;"));
formats.append(tr("CDXA, like Video-CD (*.dat);;"));
formats.append(tr("Apple/SGI (*.aiff *.aifc);;"));
formats.append(tr("Sun/NeXT (*.au);;"));
formats.append(tr("Amiga IFF/SVX8/SV16 (*.iff);;"));
formats.append(tr("Ensoniq PARIS (*.paf);;"));
formats.append(tr("Sound Designer 2 (*.sd2);;"));
formats.append(tr("Berkeley/IRCAM/CARL (*.irca);;"));
formats.append(tr("SoundFoundry WAVE 64 (*.w64);;"));
formats.append(tr("Matlab (*.mat);;"));
formats.append(tr("Portable Voice format (*.pvf);;"));
formats.append(tr("FastTracker2 Extanded (*.xi);;"));
formats.append(tr("Midi Sample dump Format (*.sds);;"));
formats.append(tr("Audio Visual Research (*.avr);;"));

    QString lastDir=m_settings->value("LastDir", "").toString();
    QString media=QFileDialog::getOpenFileName(this,tr("Select Media File"),
                                               lastDir,
                                               formats);

    if(media.isEmpty())
        return;
     m_settings->setValue("LastDir", QFileInfo(media).absoluteDir().path());

        MediaInfo MI;
        MI.Open(media.toStdWString()); // конвертируем путь к файлу в нужный формат и открываем медиа файл

        String To_Display;
        To_Display += _T("\n[u]File Info[/u]\r\n");

        To_Display += _T("[b]Format:[/b] ");
        To_Display += MI.Get(Stream_General, 0, _T("Format"), Info_Text, Info_Name).c_str();
        To_Display += _T("\r\n[b]File Size:[/b] ");
        To_Display += MI.Get(Stream_General, 0, _T("FileSize/String"), Info_Text, Info_Name).c_str();
        To_Display += _T("\r\n[b]Duration:[/b] ");
        To_Display += MI.Get(Stream_General, 0, _T("Duration/String"), Info_Text, Info_Name).c_str();

        To_Display += _T("\r\n\r\n[u]Video[/u]");
        To_Display += _T("\r\n[b]Format:[/b] ");
        To_Display += MI.Get(Stream_Video, 0, _T("Format"), Info_Text, Info_Name).c_str();
        To_Display += _T(" (");
        To_Display += MI.Get(Stream_Video, 0, _T("CodecID"), Info_Text, Info_Name).c_str();
        To_Display += _T(")\r\n[b]Bit rate:[/b] ");
        To_Display += MI.Get(Stream_Video, 0, _T("BitRate/String"), Info_Text, Info_Name).c_str();
        To_Display += _T("\r\n[b]Width:[/b] ");
        To_Display += MI.Get(Stream_Video, 0, _T("Width/String"), Info_Text, Info_Name).c_str();
        To_Display += _T("\r\n[b]Height:[/b] ");
        To_Display += MI.Get(Stream_Video, 0, _T("Height/String"), Info_Text, Info_Name).c_str();


        QString s=QString::fromStdWString(MI.Get(Stream_General, 0, _T("AudioCount"), Info_Text, Info_Name).c_str());
        int aud = s.toInt();
        //qDebug()<<"Audio Count: "<<aud;
        for(int i=0;i<aud;i++){
            QString str=QString("\r\n\r\n[u]Audio #%1[/u]").arg(i+1);
            To_Display += str.toStdWString();
            To_Display += _T("\r\n[b]Language:[/b] ");
            To_Display += MI.Get(Stream_Audio, i, _T("Language/String"), Info_Text, Info_Name).c_str();
            To_Display += _T("\r\n[b]Title:[/b] ");
            To_Display += MI.Get(Stream_Audio, i, _T("Title"), Info_Text, Info_Name).c_str();
            To_Display += _T("\r\n[b]BitRate:[/b] ");
            To_Display += MI.Get(Stream_Audio, i, _T("BitRate/String"), Info_Text, Info_Name).c_str();
            To_Display += _T("\r\n[b]Format:[/b] ");
            To_Display += MI.Get(Stream_Audio, i, _T("Format"), Info_Text, Info_Name).c_str();
            //To_Display += _T("\r\n[b]StreamKindID:[/b] ");
            //To_Display += MI.Get(Stream_Audio, i, _T("StreamKindPos"), Info_Text, Info_Name).c_str();

        }

    editor->appendPlainText(QString::fromStdWString(To_Display));
}
#endif

// ----------------------------------------------------------------------
void MainWindow::loadPlugins()
{
    QDir dir(QApplication::applicationDirPath());
    if (!dir.cd("plugins/search")) {
        QMessageBox::critical(0, "", tr("plugins directory does not exist"));
        return;
    }
//    if (!dir.cd("search")) {
//        QMessageBox::critical(0, "", tr("plugins directory does not exist"));
//        return;
//    }
    foreach (QString strFileName, dir.entryList(QDir::Files)) {
        QPluginLoader loader(dir.absoluteFilePath(strFileName));
        connect(loader.instance(),SIGNAL(getDescription(QString&)) ,this,SLOT(getMovie(QString&)));
        connect(loader.instance(),SIGNAL(getStatus(int)) ,this,SLOT(pluginStatus(int)));
        addToMenu(qobject_cast<QObject*>(loader.instance()));
    }
}

// ----------------------------------------------------------------------
void MainWindow::addToMenu(QObject* pobj)
{
    if (!pobj) {
        return;
    }

    PluginInterface* pI = qobject_cast<PluginInterface*>(pobj);
    if (pI) {
        QStringList lstOperations = pI->operations();
        foreach (QString str, lstOperations) {
            QAction* pact = new QAction(str, pobj);
            connect(pact, SIGNAL(triggered()),
                    this, SLOT(slotStringOperation())
                   );
            menu_Tools->addAction(pact);

        }
    }
}

// ----------------------------------------------------------------------
void MainWindow::slotStringOperation()
{
    QAction* pact = qobject_cast<QAction*>(sender());

    PluginInterface* pI = qobject_cast<PluginInterface*>(pact->parent());
    pI->operation();

}
// ----------------------------------------------------------------------
void MainWindow::getMovie(QString &descr)
{
   setConnectMode(Done);
   editor->setPlainText(descr);
}
void MainWindow::pluginStatus(int status){
   setConnectMode((ConnectMode)status);
}
