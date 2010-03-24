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
#ifndef TRACKERREQUEST_H
#define TRACKERREQUEST_H
#include <QObject>
#include <QMap>
class TrackerRequest: public QObject
{    
public:
    TrackerRequest(){}
    virtual void checkLogin(const QString &login,const QString &password) = 0;
    virtual void getCategory() = 0;
    virtual void uploadRelease(const QString &file,const QString &name
                               ,const QString &descr,const int &categoryID
                               ,const QString &poster,const QStringList &screens) = 0;
    virtual QMap<int,QString> returnCategory(){return catmap;}
signals:
    void categoryDone();
    void blockInterface(bool &isBlocked);
    void uploadDone(QString &fileName);
    void errorMessage(QString &message);
protected:
    QMap<int,QString> catmap;
};

#endif // TRACKERREQUEST_H
