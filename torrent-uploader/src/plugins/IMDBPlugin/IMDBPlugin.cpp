#include <QtGui>
#include <QtNetwork>
#include "version.h"
#include "IMDBPlugin.h"
#include "selectmoviedialog.h"
// ----------------------------------------------------------------------
void IMDBPlugin::checkLogin()
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
void IMDBPlugin::replyFinished(QNetworkReply* reply){
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
                             //QMessageBox::information(0,"",tmp);
                             emit getDescription(description);
                    }
                    break;
                }
            }
            break;
    }
}
void IMDBPlugin::searchMovie(const QString &name){
    emit getStatus(2); // Connecting_imdb
    QByteArray str=name.toLocal8Bit();

    QNetworkRequest request;
    request.setUrl(QUrl("http://www.imdb.com/find?s=tt&q="+str.toPercentEncoding()));
    request.setRawHeader("Host","www.imdb.com");
    request.setRawHeader("User-Agent", "Opera/9.80 (Windows NT 6.1; U; ru) Presto/2.2.15 Version/10.10");
    request.setRawHeader("Referer", "http://www.imdb.com/");
    request.setRawHeader("Accept","text/html, application/xml;q=0.9, application/xhtml+xml, image/png, image/jpeg, image/gif, image/x-xbitmap, */*;q=0.1");
    request.setRawHeader("Accept-Language","ru,en;q=0.9,ru-RU;q=0.8");
    request.setRawHeader("Accept-Charset","iso-8859-1, utf-8, utf-16, *;q=0.1");

    manager->get(request);
    setStatus(Category);
}
void IMDBPlugin::getMovie(const QString &name){
    emit getStatus(4); // Retrieving_imdb
    QByteArray str=name.toLocal8Bit();

    QNetworkRequest request;
    request.setUrl(QUrl("http://www.imdb.com/title/tt"+str+"/"));
    request.setRawHeader("Host","www.imdb.com");
    request.setRawHeader("User-Agent", "Opera/9.80 (Windows NT 6.1; U; ru) Presto/2.2.15 Version/10.10");
    request.setRawHeader("Referer", "http://www.imdb.com/");
    request.setRawHeader("Accept","text/html, application/xml;q=0.9, application/xhtml+xml, image/png, image/jpeg, image/gif, image/x-xbitmap, */*;q=0.1");
    request.setRawHeader("Accept-Language","ru,en;q=0.9,ru-RU;q=0.8");
    request.setRawHeader("Accept-Charset","iso-8859-1, utf-8, utf-16, *;q=0.1");

    manager->get(request);
    setStatus(Movie);
}
QString IMDBPlugin::parseMovie(const QString &content){
    QString tmpStr;
    QString descr=content;

    descr.replace("&raquo;","»");
    descr.replace("&laquo;","«");
    descr.replace("&lt;","<");
    descr.replace("&gt;",">");
    descr.replace("&quot;","\"");
    descr.replace("&#x27;","'");
    descr.replace("&#x22;","\"");
    descr.replace("more","");

    QRegExp rx("<title>(.*)</title>");
    rx.setMinimal(true);
    rx.indexIn(descr);
    tmpStr.append(QString("[b]Name:[/b]%1\n").arg(rx.cap(1).replace("&nbsp;"," ")));

//    rx.setPattern("<div class=\"starbar-meta\">.*<b>(.*)</b>.*>(.*)</a>");
//    tmpStr.append(QString("[b]User Rating:[/b] %1 %2\n").arg(rx.cap(1)).arg(rx.cap(2)));

         QRegExp rx2("<div class=\"info\">.*<h5>(.*)</h5>.*<div class=\"info-content\">(.*)</div>");
         rx2.setMinimal(true);
         int pos = 0;
         while ((pos = rx2.indexIn(descr, pos)) != -1) {
             QString tmp;
             QRegExp rx3("<a.*>(.*)</a>");
             rx3.setMinimal(true);
             int pos2 = 0;
             while ((pos2 = rx3.indexIn(rx2.cap(2), pos2)) != -1) {
                 tmp.append(rx3.cap(1).replace("&nbsp;"," ")+", ");
                 pos2 += rx3.matchedLength();
             }
             tmp.chop(2);
             tmp.replace("\n","");
             tmp.replace("\r","");
             tmp.replace("&nbsp;","");

             if(!rx2.cap(1).contains("MOVIEmeter", Qt::CaseInsensitive)
                 && !rx2.cap(1).contains("Contact", Qt::CaseInsensitive)
                 && !rx2.cap(1).contains("Seasons", Qt::CaseInsensitive)
                 && !rx2.cap(1).contains("Tagline", Qt::CaseInsensitive)
                 && !rx2.cap(1).contains("Plot", Qt::CaseInsensitive)
                 && !rx2.cap(1).contains("Awards", Qt::CaseInsensitive)
                 && !rx2.cap(1).contains("NewsDesk", Qt::CaseInsensitive)
                 && !rx2.cap(1).contains("Reviews", Qt::CaseInsensitive)
                 && !rx2.cap(1).contains("Also", Qt::CaseInsensitive)
                 && !rx2.cap(1).contains("Color", Qt::CaseInsensitive)
                 && !rx2.cap(1).contains("Aspect", Qt::CaseInsensitive)
                 && !rx2.cap(1).contains("Also", Qt::CaseInsensitive)
                 && !rx2.cap(1).contains("Trivia", Qt::CaseInsensitive)
                 && !rx2.cap(1).contains("Goofs", Qt::CaseInsensitive)
                 && !rx2.cap(1).contains("Quotes", Qt::CaseInsensitive)
                 && !rx2.cap(1).contains("Connections", Qt::CaseInsensitive)
                 && !rx2.cap(1).contains("Soundtrack", Qt::CaseInsensitive)){
                 tmpStr.append(QString("[b]%1[/b] %2\n").arg(rx2.cap(1)).arg(tmp.isEmpty()?rx2.cap(2):tmp));
             }
             pos += rx2.matchedLength();
         }

//     QRegExp rx2("<tr><td class=\"type\">(.*)</td><td.*>(.*)</td></tr>");
//     rx2.setMinimal(true);
//     int pos = 0;
//     while ((pos = rx2.indexIn(descr, pos)) != -1) {
//         QString tmp;
//         ////////
//         QRegExp rx3("<a.*>(.*)</a>");
//         rx3.setMinimal(true);
//         int pos2 = 0;
//         while ((pos2 = rx3.indexIn(rx2.cap(2), pos2)) != -1) {
//             tmp.append(rx3.cap(1).replace("&nbsp;"," ")+", ");
//             pos2 += rx3.matchedLength();
//         }
//         tmp.chop(2);
//         tmp.replace(QRegExp("<img.*/images/mpaa/(.*).gif.*>"),"[img]http://www.kinopoisk.ru/images/mpaa/\\1.gif[/img]");
//
//         QString rx2str=rx2.cap(2);
//         QRegExp rx2rx("<img.*/images/flags/(.*).gif.*>");
//         rx2rx.setMinimal(true);
//         rx2str.replace(rx2rx,"[img]http://www.kinopoisk.ru/images/flags/\\1.gif[/img]");
//         rx2str.replace("&nbsp;"," ");
//         ////////
//         tmpStr.append(QString("[b]%1:[/b] %2\n").arg(rx2.cap(1)).arg(tmp.isEmpty()?rx2str:tmp));
//         pos += rx2.matchedLength();
//     }
//
//    QRegExp rx4("<span class=\"_reachbanner_\">(.*)</span>");
//    rx4.setMinimal(true);
//    rx4.indexIn(content);
//    QString des=rx4.cap(1);
//    des.replace("&#151;","-");
//    des.replace("&nbsp;"," ");
//    des.replace("<br>","\n");
//    tmpStr.append(QString("\n[b]ξοθρΰνθε:[/b] %1\n").arg(des));


    return tmpStr;
}
// ----------------------------------------------------------------------
void IMDBPlugin::setStatus(Status status){
    currentStatus = status;
}
// ----------------------------------------------------------------------
IMDBPlugin::IMDBPlugin()
{
   QTextCodec::setCodecForTr(QTextCodec::codecForName("WINDOWS-1251"));
   QTextCodec::setCodecForCStrings(QTextCodec::codecForName("WINDOWS-1251"));
   QTextCodec::setCodecForLocale(QTextCodec::codecForName("WINDOWS-1251"));

   QSettings settings(UPLOADER_ORGANIZATION, UPLOADER_NAME);
   m_login =settings.value("Profile/IMDBLogin", "").toString();
   m_password =settings.value("Profile/IMDBPassword", "").toString();
   manager = new QNetworkAccessManager;
   connect(manager, SIGNAL(finished(QNetworkReply*)),
             this, SLOT(replyFinished(QNetworkReply*)));
   //checkLogin();
}
// ----------------------------------------------------------------------
/*virtual*/ IMDBPlugin::~IMDBPlugin()
{
}

// ----------------------------------------------------------------------
/*virtual*/ QStringList IMDBPlugin::operations() const
{
    return QStringList() << tr("Search movie (imdb.com)...");
}

// ----------------------------------------------------------------------
/*virtual*/ void IMDBPlugin::operation()
{
    QString movieName = QInputDialog::getText(0,tr("Enter movie"),tr("Enter movie name:"));
    if(!movieName.isEmpty())
            searchMovie(movieName);
}

Q_EXPORT_PLUGIN2(PluginInterface, IMDBPlugin)
