#include <QtGui>
#include <QtNetwork>
#include "version.h"
#include "KinopoiskPlugin.h"
#include "selectmoviedialog.h"
// ----------------------------------------------------------------------
void KinopoiskPlugin::checkLogin()
{
    QString logininfo=QString("shop_user[login]=%1&shop_user[pass]=%2&shop_user[mem]=on&auth=%E2%EE%E9%F2%E8+%ED%E0+%F1%E0%E9%F2")
                      .arg(m_login).arg(m_password);
    QNetworkRequest request;
    request.setUrl(QUrl("http://www.kinopoisk.ru/level/30/"));
    request.setRawHeader("Host","www.kinopoisk.ru");
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US) AppleWebKit/530.5 (KHTML, like Gecko) Chrome/2.0.172.43 Safari/530.5");
    request.setRawHeader("Referer", "http://www.kinopoisk.ru/level/30/");
    request.setRawHeader("Accept","application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5");
    request.setRawHeader("Accept-Encoding","gzip,deflate,sdch");
    request.setRawHeader("Accept-Language","ru-RU,ru;q=0.8,en-US;q=0.6,en;q=0.4");
    request.setRawHeader("Accept-Charset","windows-1251,utf-8;q=0.7,*;q=0.3");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::ContentLengthHeader, logininfo.length());

    manager->post(request,logininfo.toLocal8Bit());
    setStatus(Login);

}
void KinopoiskPlugin::replyFinished(QNetworkReply* reply){
    int statusCode= reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    int status = currentStatus;
    switch(status){
        case Login:{
                 switch(statusCode){
                     case 200:{
                        qDebug() << "false login";
                    }
                    break;
                }
            }
            break;
        case Category:{
                 switch(statusCode){
                     case 200:{
                             emit getStatus(8); // Done
                             QString tmp=reply->readAll();
                             SelectMovieDialog dlg(0,tmp);
                             if(dlg.exec()){
                                 getMovie(dlg.movieID);
                             }

                    }
                    break;
                }
            }
            break;
        case Movie:{
                 switch(statusCode){
                     case 200:{
                             QString tmp=reply->readAll();
                             description = parseMovie(tmp);
                             //QMessageBox::information(0,"",description);
                             emit getDescription(description);
                    }
                    break;
                }
            }
            break;
    }
}
void KinopoiskPlugin::searchMovie(const QString &name){

    emit getStatus(1); //Connecting_kp
    QByteArray str=name.toLocal8Bit();

    QNetworkRequest request;
    request.setUrl(QUrl("http://www.kinopoisk.ru/index.php?kp_query="+str.toPercentEncoding()));
    request.setRawHeader("Host","www.kinopoisk.ru");
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US) AppleWebKit/530.5 (KHTML, like Gecko) Chrome/2.0.172.43 Safari/530.5");
    request.setRawHeader("Referer", "http://www.kinopoisk.ru/");
    request.setRawHeader("Accept","application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5");
    request.setRawHeader("Accept-Language","ru-RU,ru;q=0.8,en-US;q=0.6,en;q=0.4");
    request.setRawHeader("Accept-Charset","windows-1251,utf-8;q=0.7,*;q=0.3");

    manager->get(request);
    setStatus(Category);
}
void KinopoiskPlugin::getMovie(const QString &name){
    emit getStatus(3); //Retrieving_kp
    QByteArray str=name.toLocal8Bit();

    QNetworkRequest request;
    request.setUrl(QUrl("http://www.kinopoisk.ru/level/1/film/"+str+"/"));
    request.setRawHeader("Host","www.kinopoisk.ru");
    request.setRawHeader("User-Agent", "Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US) AppleWebKit/530.5 (KHTML, like Gecko) Chrome/2.0.172.43 Safari/530.5");
    request.setRawHeader("Referer", "http://www.kinopoisk.ru/");
    request.setRawHeader("Accept","application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5");
    request.setRawHeader("Accept-Language","ru-RU,ru;q=0.8,en-US;q=0.6,en;q=0.4");
    request.setRawHeader("Accept-Charset","windows-1251,utf-8;q=0.7,*;q=0.3");

    manager->get(request);
    setStatus(Movie);
}
QString KinopoiskPlugin::parseMovie(const QString &content){
    QString tmpStr;
    QString descr;
    QString act;
    QRegExp rxactr("<!-- актеры фильма -->(.*)(Роли дублировали|<!-- /актеры фильма -->)");
    rxactr.setMinimal(true);
    rxactr.indexIn(content);
    act =rxactr.cap(1);

    QRegExp rxdescr("<!-- инфа о фильме -->(.*)<!-- /инфа о фильме -->");
    rxdescr.setMinimal(true);
    rxdescr.indexIn(content);
    descr =rxdescr.cap(1);

    descr.replace("&raquo;","»");
    descr.replace("&laquo;","«");
    descr.replace("&lt;","<");
    descr.replace("&gt;",">");
    descr.replace("&quot;","\"");
    descr.replace("&#x27;","'");

    QRegExp rx("class=\"moviename-big\">(.*)</h1>");
    rx.setMinimal(true);
    rx.indexIn(descr);
    tmpStr.append(QString("[b]название:[/b] %1\n").arg(rx.cap(1).replace("&nbsp;","")));

    QRegExp rx1("<span style=\"color: #666; font-size: 13px\">(.*)</span>");
    rx1.setMinimal(true);
    rx1.indexIn(descr);
    tmpStr.append(QString("[b]оригинальное название:[/b] %1\n").arg(rx1.cap(1).replace("&nbsp;","")));

    QRegExp rxact("<a href=\"/level/4/people/.*>(.*)</a>");
    rxact.setMinimal(true);
    int posact = 0;
    QString tmpact;
    while ((posact = rxact.indexIn(act, posact)) != -1) {
            tmpact.append(rxact.cap(1).replace("&nbsp;"," ")+", ");
            posact += rxact.matchedLength();
    }
    tmpact.chop(2);
    tmpStr.append(QString("[b]в главных ролях:[/b] %1\n").arg(tmpact));


     QRegExp rx2("<tr><td class=\"type\">(.*)</td><td.*>(.*)</td></tr>");
     rx2.setMinimal(true);
     int pos = 0;
     while ((pos = rx2.indexIn(descr, pos)) != -1) {
         QString tmp;
         ////////
         QRegExp rx3("<a.*>(.*)</a>");
         rx3.setMinimal(true);
         int pos2 = 0;
         while ((pos2 = rx3.indexIn(rx2.cap(2), pos2)) != -1) {
             tmp.append(rx3.cap(1).replace("&nbsp;"," ")+", ");
             pos2 += rx3.matchedLength();
         }
         tmp.chop(2);
         tmp.replace(QRegExp("<img.*/images/mpaa/(.*).gif.*>"),"[img]http://www.kinopoisk.ru/images/mpaa/\\1.gif[/img]");

         QString rx2str=rx2.cap(2);
         QRegExp rx2rx("<img.*/images/flags/(.*).gif.*>");
         rx2rx.setMinimal(true);
         rx2str.replace(rx2rx,"[img]http://www.kinopoisk.ru/images/flags/\\1.gif[/img]");
         rx2str.replace("&nbsp;"," ");
         ////////
         tmpStr.append(QString("[b]%1:[/b] %2\n").arg(rx2.cap(1)).arg(tmp.isEmpty()?rx2str:tmp));
         pos += rx2.matchedLength();
     }

    QRegExp rx4("<span class=\"_reachbanner_\">(.*)</span>");
    rx4.setMinimal(true);
    rx4.indexIn(content);
    QString des=rx4.cap(1);
    des.replace("&#151;","-");
    des.replace("&nbsp;"," ");
    des.replace("<br>","\n");
    tmpStr.append(QString("\n[b]описание:[/b] %1\n").arg(des));


    return tmpStr;
}
// ----------------------------------------------------------------------
void KinopoiskPlugin::setStatus(Status status){
    currentStatus = status;
}
// ----------------------------------------------------------------------
KinopoiskPlugin::KinopoiskPlugin()
{
   QTextCodec::setCodecForTr(QTextCodec::codecForName("WINDOWS-1251"));
   QTextCodec::setCodecForCStrings(QTextCodec::codecForName("WINDOWS-1251"));
   QTextCodec::setCodecForLocale(QTextCodec::codecForName("WINDOWS-1251"));

   QSettings settings(UPLOADER_ORGANIZATION, UPLOADER_NAME);
   m_login =settings.value("Profile/KPLogin", "").toString();
   m_password =settings.value("Profile/KPPassword", "").toString();
   manager = new QNetworkAccessManager;
   connect(manager, SIGNAL(finished(QNetworkReply*)),
             this, SLOT(replyFinished(QNetworkReply*)));
   checkLogin();
}
// ----------------------------------------------------------------------
/*virtual*/ KinopoiskPlugin::~KinopoiskPlugin()
{
}

// ----------------------------------------------------------------------
/*virtual*/ QStringList KinopoiskPlugin::operations() const
{
    return QStringList() << tr("Search movie (kinopoisk.ru)...");
}

// ----------------------------------------------------------------------
/*virtual*/ void KinopoiskPlugin::operation()
{
    QString movieName = QInputDialog::getText(0,tr("Enter movie"),tr("Enter movie name:"));
    if(!movieName.isEmpty())
            searchMovie(movieName);
}

Q_EXPORT_PLUGIN2(PluginInterface, KinopoiskPlugin)
