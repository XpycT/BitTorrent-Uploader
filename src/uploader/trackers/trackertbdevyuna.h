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
#ifndef TRACKERTBDEVYUNA_H
#define TRACKERTBDEVYUNA_H

#include "trackerrequest.h"
#include <QMap>

class QNetworkAccessManager;
class QNetworkReply;
class QFile;

class TrackerTBDevYuna : public TrackerRequest
{
    Q_OBJECT
public:
    TrackerTBDevYuna();
    void checkLogin(const QString &login,const QString &password);
    void uploadRelease(const QString &file,const QString &name
                               ,const QString &descr,const int &categoryID
                               ,const QString &poster,const QStringList &screens);
    enum Status {Login,Category,Upload,Download};
signals:
    void categoryDone();
    void blockInterface(bool &isBlocked);
    void uploadDone(QString &fileName);
    void errorMessage(QString &message);
private slots:
    void replyFinished(QNetworkReply*);    
private:
    void downloadFile(const QString &id);
    void getCategory();
    void setStatus(Status status);
    void parseCategory(QString &content);
    QByteArray fileToSend(const QString &fieldName,const QString &fileName
                          ,const QByteArray &boundary);
    QNetworkAccessManager *manager;
    bool isBlocked;
    QString client;
    QString url;
    QString poweredBy;
    QString id;
    QString tname;
    QFile *torrentFile;
    Status currentStatus;
};

#endif // TRACKERTBDEVYUNA_H
