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
}
void TrackerTBDevYuna::checkLogin(const QString &login,const QString &password){
    QString logininfo=QString("username=%1&password=%2")
                      .arg(login).arg(password);
    QNetworkRequest request;
    QString url=QApplication::organizationDomain();
    request.setUrl(QUrl("http://"+url+"/tracker/takelogin.php"));
    request.setRawHeader("Host",url.toLocal8Bit());
    request.setRawHeader("User-Agent", "BitTorrent Uploader 1.0");
    request.setRawHeader("Referer", "http://"+url.toLocal8Bit());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::ContentLengthHeader, logininfo.length());

    manager->post(request,logininfo.toLocal8Bit());
    setStatus(Login);
}
void TrackerTBDevYuna::uploadRelease(){
    qDebug() << "UPLOAD FILE";
}
void TrackerTBDevYuna::getCategory(){
    //qDebug() << "get TBDev Yuna Edition category";
    manager->get(QNetworkRequest(QUrl("http://"+QApplication::organizationDomain()+"/tracker/upload.php")));
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
    }

    //qDebug() << statusCode;

}
