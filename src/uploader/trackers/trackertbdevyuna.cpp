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
#include "trackertbdevyuna.h"
#include "version.h"
#include <QtCore>
#include <QtNetwork>
#include <QApplication>
TrackerTBDevYuna::TrackerTBDevYuna():isBlocked(false)
{
 manager = new QNetworkAccessManager;
 connect(manager, SIGNAL(finished(QNetworkReply*)),
         this, SLOT(replyFinished(QNetworkReply*)));
 url=QApplication::organizationDomain();
 client=QString("%1 / %2").arg(UPLOADER_NAME).arg(UPLOADER_VERSION);
 poweredBy=QString("%1").arg(UPLOADER_COPYRIGHT);
}
void TrackerTBDevYuna::checkLogin(const QString &login,const QString &password){
    QString logininfo=QString("username=%1&password=%2")
                      .arg(login).arg(password);
    QNetworkRequest request;
    request.setUrl(QUrl("http://"+url+"/takelogin.php"));
    request.setRawHeader("Host",url.toLocal8Bit());
    request.setRawHeader("X-Powered-By",poweredBy.toLocal8Bit());
    request.setRawHeader("User-Agent", client.toLocal8Bit());
    request.setRawHeader("Referer", "http://"+url.toLocal8Bit());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::ContentLengthHeader, logininfo.length());

    manager->post(request,logininfo.toLocal8Bit());
    setStatus(Login);
}
void TrackerTBDevYuna::uploadRelease(const QString &file,const QString &name
                               ,const QString &descr,const int &categoryID
                               ,const QString &poster,const QStringList &screens)
{
    QString cat = QString("%1").arg(categoryID);
    QByteArray boundary = "----WebKitFormBoundarycKynmwwOlIssy6YN";
    QByteArray bytesToSend,fileBytes;

    if(!file.isEmpty())
        fileBytes.append(fileToSend("tfile",file,boundary));
    if(!poster.isEmpty())
        fileBytes.append(fileToSend("image0",poster,boundary));    
    for(int i=0;i<screens.length();i++){
        int img=i+1;
        fileBytes.append(fileToSend(QString("image%1").arg(img),screens.at(i),boundary));
    }
    QString content=descr+UPLOADER_SIGNATURE;
    bytesToSend = "--"+boundary+"\r\n"+
    "Content-Disposition: form-data; name=\"MAX_FILE_SIZE\"\r\n\r\n1000000\r\n"+
    "--"+boundary+"\r\nContent-Disposition: form-data; name=\"name\"\r\n\r\n"+name.toLocal8Bit()+"\r\n"+
    "--"+boundary+"\r\nContent-Disposition: form-data; name=\"descr\"\r\n\r\n"+content.toLocal8Bit()+"\r\n"+
    "--"+boundary+"\r\nContent-Disposition: form-data; name=\"type\"\r\n\r\n"+cat.toLocal8Bit()+"\r\n"+
    fileBytes+
    "--"+boundary+"--";

    QNetworkRequest request;
    request.setUrl(QUrl("http://"+url+"/takeupload.php"));
    request.setRawHeader("Host",url.toLocal8Bit());
    request.setRawHeader("X-Powered-By",poweredBy.toLocal8Bit());
    request.setRawHeader("User-Agent", client.toLocal8Bit());
    request.setRawHeader("Referer", "http://"+url.toLocal8Bit()+"/upload.php");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data; boundary="+boundary);
    request.setHeader(QNetworkRequest::ContentLengthHeader, bytesToSend.size());

    manager->post(request,bytesToSend);
    setStatus(Upload);
}

QByteArray TrackerTBDevYuna::fileToSend(const QString &fieldName,const QString &fileName
                                        ,const QByteArray &boundary){
    QFile file(fileName);
    QFileInfo f = QFileInfo(file);
    QByteArray contentType;
    QString ext = f.suffix().toLower();
    if(ext=="png")
        contentType="image/png";
    else if(ext=="jpg" || ext== "jpeg")
        contentType="image/jpeg";
    else if(ext=="gif")
        contentType="image/gif";
    else if(ext=="torrent"){
        contentType="application/x-bittorrent";
        tname = f.fileName();
    }


    file.open(QFile::ReadOnly);
    QByteArray _bytesToSend;
    _bytesToSend = "--"+boundary+"\r\nContent-Disposition: form-data; name=\""+fieldName.toLocal8Bit()+"\"; filename=\""+f.fileName().toLocal8Bit()+"\"\r\n"+
    "Content-Type: "+contentType+"\r\n\r\n"+file.readAll()+"\r\n";
    file.close();
    return _bytesToSend;
}

void TrackerTBDevYuna::getCategory(){
    //qDebug() << "get TBDev Yuna Edition category";
    QNetworkRequest request;
    request.setUrl(QUrl("http://"+url+"/upload.php"));
    request.setRawHeader("Host",url.toLocal8Bit());
    request.setRawHeader("X-Powered-By",poweredBy.toLocal8Bit());
    request.setRawHeader("User-Agent", client.toLocal8Bit());
    manager->get(request);
    setStatus(Category);
}
void TrackerTBDevYuna::parseCategory(QString &content){

    QString text;
    QRegExp rx("<select name=\"type\">(.*)</select>");
    rx.setMinimal(true);
    rx.indexIn(content);
    text = rx.cap(1);

    QRegExp rx2("<option value=\"([^0]*)\">(.*)</option>");
    rx2.setMinimal(true);


    int pos = 0;

     while ((pos = rx2.indexIn(text, pos)) != -1) {
         //qDebug() << rx2.cap(1) <<" - "<< rx2.cap(2);
         catmap.insert(rx2.cap(1).toInt(), rx2.cap(2));
         pos += rx2.matchedLength();
     }

    emit categoryDone();
}
void TrackerTBDevYuna::downloadFile(const QString &id){
    QString path=QApplication::applicationDirPath();
    QDir dir(path);
    if (!dir.exists("torrent"))
        dir.mkdir("torrent");
    dir.cd("torrent");

   QUrl link=QUrl("http://"+url+"/download.php?id="+id+"&name="+tname);

   torrentFile = new QFile(path+"/torrent/"+tname);
   if (!torrentFile->open(QIODevice::WriteOnly))
         return;

    QNetworkRequest request;
    request.setUrl(QUrl(link));
    request.setRawHeader("Host",url.toLocal8Bit());
    request.setRawHeader("X-Powered-By",poweredBy.toLocal8Bit());
    request.setRawHeader("User-Agent", client.toLocal8Bit());
    manager->get(request);
    setStatus(Download);

}
void TrackerTBDevYuna::setStatus(Status status){
    currentStatus = status;
}
void TrackerTBDevYuna::replyFinished(QNetworkReply* reply){
    int statusCode= reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    int status = currentStatus;

    switch(status){
        case Login:{
                 switch(statusCode){
                     case 200:{
                        //qDebug() << "There need block interfase";
                        isBlocked = false;
                    }
                    break;
                    case 302:{
                        getCategory();
                        isBlocked = true;
                    }
                    break;
                }
                emit blockInterface(isBlocked);
            }
        break;
        case Category:
                switch(statusCode){
                    case 200:{
                        //qDebug() << "get and parce category";
                        QString content=reply->readAll();
                        parseCategory(content);
                    }
                    break;
                }
        break;
        case Upload:
                switch(statusCode){
                    case 302:{
                            QByteArray location= reply->rawHeader("Location");
                            QRegExp rx("id=(\\d+)");
                            rx.indexIn(location);
                            QString id=rx.cap(1);
                            downloadFile(id);
                    }
                    break;
                    case 200:{

                            QString msg=tr("File already exists!");
                            emit errorMessage(msg);
                    }
                    break;
                }
        break;
        case Download:
                switch(statusCode){
                    case 200:{
                            torrentFile->write(reply->readAll());
                            torrentFile->close();
                            QString f=torrentFile->fileName();
                            emit uploadDone(f);
                        }
                        break;
                }
        break;
    }

    //qDebug() << statusCode;

}
