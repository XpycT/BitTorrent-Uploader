#ifndef CREATETORRENT_H
#define CREATETORRENT_H

//#include <QDialog>
#include "ui_createTorrentDialog.h"
#include <QThread>
class QSettings;
class torrentCreatorThread : public QThread {
  Q_OBJECT

  QString input_path;
  QString save_path;
  QStringList trackers;
  QStringList url_seeds;
  QString comment;
  bool is_private;
  int piece_size;
  bool abort;
  QDialog *parent;

  public:
    torrentCreatorThread(QDialog *_parent) {
        parent = _parent;
    }
    ~torrentCreatorThread() {
      abort = true;
      wait();
    }
    void create(QString _input_path, QString _save_path, QStringList _trackers, QStringList _url_seeds, QString _comment, bool _is_private, int _piece_size);
    void sendProgressSignal(int progress);

  protected:
    void run();

  signals:
    void creationFailure(QString msg);
    void creationSuccess(QString path);

  signals:
    void updateProgress(int progress);
};

class createtorrent : public QDialog, public Ui::createTorrentDialog
{
    Q_OBJECT
public:
    createtorrent(QWidget *parent=0);

signals:
  void torrent_to_upload(QString path);

private:
    torrentCreatorThread *creatorThread;
    QStringList allItems(QPlainTextEdit *list);
    int getPieceSize() const;

protected:
    ~createtorrent();

public slots:
    void updateProgressBar(int progress);

private slots:
    void on_createButton_clicked();
    void on_addFolder_button_clicked();
    void on_addFile_button_clicked();
    void handleCreationFailure(QString msg);
    void handleCreationSuccess(QString path);
};

#endif // CREATETORRENT_H
