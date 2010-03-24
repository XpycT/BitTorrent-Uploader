/***************************************************************************
 *   Copyright (C) 2009-2010 by Tarabaka Alexander <XpycT.TOP@gmail.com>   *
 *                                                                         *
 *  This file is part of a BitTorrent Uploader.				   *
 *									   *
 *  BitTorrent Uploader is free software: you can redistribute it and/or   *
 *  modify it under the terms of the GNU General Public License as         *
 *  published by the Free Software Foundation, either version 3 of the     *
 *  License, or (at your option) any later version.			   *
 *									   *
 *  BitTorrent Uploader is distributed in the hope that it will be useful, *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of	   *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	   *
 *  GNU General Public License for more details.			   *
 *									   *
 *  You should have received a copy of the GNU General Public License      *
 *  along with BitTorrent Uploader.                                        *
 *  If not, see <http://www.gnu.org/licenses/>.                            *
 ***************************************************************************/
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
