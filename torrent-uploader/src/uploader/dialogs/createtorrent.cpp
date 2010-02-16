#include "createtorrent.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QDebug>
//#include <QTextCodec>

#include "libtorrent/entry.hpp"
#include "libtorrent/bencode.hpp"
#include "libtorrent/torrent_info.hpp"
#include "libtorrent/file.hpp"
#include "libtorrent/storage.hpp"
#include "libtorrent/hasher.hpp"
#include "libtorrent/create_torrent.hpp"
#include "libtorrent/file.hpp"

#include <boost/bind.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/fstream.hpp>

using namespace boost::filesystem;
using namespace libtorrent;

bool file_filter(std::string const& f)
{
        if (filename(f)[0] == '.') return false;
        //qDebug()<<f.c_str();
        return true;
}

quint64 listFolder ( QString path ) {
        QDir currentFolder( path );

        quint64 totalsize = 0;

        currentFolder.setFilter( QDir::Dirs | QDir::Files | QDir::NoSymLinks );
        currentFolder.setSorting( QDir::Name );

        QFileInfoList folderitems( currentFolder.entryInfoList() );

        foreach ( QFileInfo i, folderitems ) {
                QString iname( i.fileName() );
                if ( iname == "." || iname == ".." || iname.isEmpty() )
                        continue;

                if ( i.isDir() )
                        totalsize += listFolder( path+"/"+iname );
                else
                        totalsize += i.size();
        }
        return totalsize;
}

createtorrent::createtorrent(QWidget *parent)
    :QDialog(parent)
{
    setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);
    layout()->setSizeConstraint(QLayout::SetFixedSize);

    creatorThread = new torrentCreatorThread(this);
    connect(creatorThread, SIGNAL(creationSuccess(QString)), this, SLOT(handleCreationSuccess(QString)));
    connect(creatorThread, SIGNAL(creationFailure(QString)), this, SLOT(handleCreationFailure(QString)));
    connect(creatorThread, SIGNAL(updateProgress(int)), this, SLOT(updateProgressBar(int)));
    path::default_name_check(no_check);


    QSettings settings(QApplication::organizationName(), QApplication::applicationName());

    trackers_list->setPlainText(settings.value("TrackerList","").toString());
    URLSeeds_list->setPlainText(settings.value("WebSeeds","").toString());


    show();
}
createtorrent::~createtorrent() {
    QSettings settings(QApplication::organizationName(), QApplication::applicationName());
    settings.setValue("TrackerList", trackers_list->toPlainText());
    settings.setValue("WebSeeds", URLSeeds_list->toPlainText());
  delete creatorThread;
}
void createtorrent::on_addFile_button_clicked()
{
    QSettings settings(QApplication::organizationName(), QApplication::applicationName());
    QString lastDir = settings.value("LastDir","").toString();

    QString file = QFileDialog::getOpenFileName(this, tr("Select a file to add to the torrent"), lastDir, QString(), 0, QFileDialog::ShowDirsOnly);
    if(!file.isEmpty()){
      textInputPath->setText(file);
      settings.setValue("LastDir", QFileInfo(file).absoluteDir().path());
  }
}

void createtorrent::on_addFolder_button_clicked()
{
    QSettings settings(QApplication::organizationName(), QApplication::applicationName());
    QString lastDir = settings.value("LastDir","").toString();
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select a folder to add to the torrent"), lastDir, QFileDialog::ShowDirsOnly);
    if(!dir.isEmpty()){
      textInputPath->setText(dir);
      settings.setValue("LastDir", QDir(dir).absolutePath());
  }
}

int createtorrent::getPieceSize() const {
  switch(comboPieceSize->currentIndex()) {
  case 0:{
          QString file=textInputPath->text();
          QFileInfo fi(file);
          quint64 fileSize=0;
          quint64 dirSize=0;
          int pieceSize=0;
          int needToSet=0;

          if(fi.isFile()){
              fileSize=fi.size();
              pieceSize=fileSize/1000;
          }
          if(fi.isDir()){
              //qDebug()<<"this is dir";
              dirSize=listFolder(file);
              pieceSize=dirSize/1000;
          }
          if(pieceSize<(32*1024)){
              needToSet=32;
          }else if(pieceSize<(64*1024)){
              needToSet=64;
          }else if(pieceSize<(128*1024)){
              needToSet=128;
          }else if(pieceSize<(256*1024)){
              needToSet=256;
          }else if(pieceSize<(512*1024)){
              needToSet=512;
          }else if(pieceSize<(1024*1024)){
              needToSet=1024;
          }else if(pieceSize<(2048*1024)){
              needToSet=2048;
          }else{
              needToSet=4096;
          }
     return needToSet*1024;
  }
  case 1:
    return 32*1024;
  case 2:
    return 64*1024;
  case 3:
    return 128*1024;
  case 4:
    return 256*1024;
  case 5:
    return 512*1024;
  case 6:
    return 1024*1024;
  case 7:
    return 2048*1024;
  default:
    return 512*1024;
  }
}

QStringList createtorrent::allItems(QPlainTextEdit *list){
  QStringList res;
  QStringList tmp;

  tmp = list->toPlainText().split("\n");
  for(int i=0;i<tmp.length();i++){
      if(!QString(tmp.at(i)).simplified().isEmpty())
          res << QString(tmp.at(i)).simplified();
  }

  return res;
}

void createtorrent::on_createButton_clicked()
{
    QString input = textInputPath->text().trimmed();
    QString f=QFileInfo(input).fileName();
    qDebug()<<f;
    if (input.endsWith(QDir::separator()))
      input.chop(1);
    if(input.isEmpty()){
      QMessageBox::critical(0, tr("No input path set"), tr("Please type an input path first"));
      return;
    }
    QStringList trackers = allItems(trackers_list);

    QSettings settings(QApplication::organizationName(), QApplication::applicationName());
    QString lastDir = settings.value("LastDir","").toString();
    QString destination = QFileDialog::getSaveFileName(this, tr("Select destination torrent file")
                                  , lastDir+QDir::separator()+f.replace(QRegExp(" "),".")+".torrent"
                                  , tr("Torrent Files")+QString::fromUtf8(" (*.torrent)"));
    if(!destination.isEmpty()) {
      if(!destination.endsWith(QString::fromUtf8(".torrent")))
        destination += QString::fromUtf8(".torrent");
      settings.setValue("LastDir", QFileInfo(destination).absoluteDir().path());
    } else {
      return;
    }
    QStringList url_seeds = allItems(URLSeeds_list);
    QString comment = txt_comment->text();
    creatorThread->create(input, destination, trackers, url_seeds, comment, false, getPieceSize());

}

void createtorrent::handleCreationFailure(QString msg) {
  QMessageBox::information(0, tr("Torrent creation"), tr("Torrent creation was unsuccessful, reason: %1").arg(msg));
}

void createtorrent::handleCreationSuccess(QString path) {
  emit torrent_to_upload(path);
  //QMessageBox::information(0, tr("Torrent creation"), tr("Torrent was created successfully:")+" "+path);
  close();
}
void createtorrent::updateProgressBar(int progress) {
  progressBar->setValue(progress);
}

//
// Torrent Creator Thread
//

void torrentCreatorThread::create(QString _input_path, QString _save_path, QStringList _trackers, QStringList _url_seeds, QString _comment, bool _is_private, int _piece_size) {
  input_path = _input_path;
  save_path = _save_path;
  trackers = _trackers;
  url_seeds = _url_seeds;
  comment = _comment;
  is_private = _is_private;
  piece_size = _piece_size;
  abort = false;
  start();
}

void sendProgressUpdateSignal(int i, int num, torrentCreatorThread *parent){
  parent->sendProgressSignal((int)(i*100./(float)num));
}

void torrentCreatorThread::sendProgressSignal(int progress) {
  emit updateProgress(progress);
}

void torrentCreatorThread::run() {
  emit updateProgress(0);
  char const* creator_str = "Torrent Uploader";
  try {

      file_storage fs;
      file_pool fp;
      std::string full_path = libtorrent::complete(input_path.toLocal8Bit().data());
      add_files(fs, full_path, file_filter);
      if(abort) return;
      create_torrent t(fs, piece_size);


      // Add url seeds
      QString seed;
      foreach(seed, url_seeds){
          t.add_url_seed(seed.toLocal8Bit().data());
      }
      for(int i=0; i<trackers.size(); ++i){
          t.add_tracker(trackers.at(i).toLocal8Bit().data());
      }
      if(abort) return;
      set_piece_hashes(t, parent_path(full_path)
                       , boost::bind<void>(&sendProgressUpdateSignal, _1, t.num_pieces(), this));
      if(abort) return;
      t.set_creator(creator_str);
      t.set_comment((const char*)comment.toLocal8Bit());
      t.set_priv(is_private);
      if(abort) return;
      // create the torrent and print it to out
      ofstream out(complete(path((const char*)save_path.toLocal8Bit())), std::ios_base::binary);
      bencode(std::ostream_iterator<char>(out), t.generate());

      emit updateProgress(100);
      emit creationSuccess(save_path);
  }
  catch (std::exception& e){
//      QTextCodec *codec = QTextCodec::codecForName("CP1251");
//      QTextCodec::setCodecForTr(codec);
//      QTextCodec::setCodecForCStrings(codec);
//      QTextCodec::setCodecForLocale(codec);
//      qDebug() << e.what();
    emit creationFailure(QString::fromUtf8(e.what()));
  }
}
