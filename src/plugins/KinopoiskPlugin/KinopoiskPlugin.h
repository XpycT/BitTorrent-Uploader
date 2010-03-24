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
#ifndef _KinopoiskPlugin_h_
#define _KinopoiskPlugin_h_

#include <QObject>
#include "interfaces.h"

class QNetworkAccessManager;
class QNetworkReply;
// ======================================================================
class KinopoiskPlugin : public QObject, public PluginInterface {
Q_OBJECT
Q_INTERFACES(PluginInterface)

public:
    KinopoiskPlugin();
    virtual ~KinopoiskPlugin();

    virtual QStringList operations() const;
    virtual void     operation ();
    enum Status {Login,Category,Movie};

signals:
    /*virtual*/ void getDescription(QString &descr);
    /*virtual*/ void getStatus(int status);

private slots:
    void replyFinished(QNetworkReply*);
private:
    bool isLogin;
    QString m_login,m_password,description;
    QNetworkAccessManager *manager;
    void checkLogin();
    void searchMovie(const QString &name);
    void getMovie(const QString &name);
    void setStatus(Status status);
    QString parseMovie(const QString &content);
    Status currentStatus;
};
#endif //_KinopoiskPlugin_h_
