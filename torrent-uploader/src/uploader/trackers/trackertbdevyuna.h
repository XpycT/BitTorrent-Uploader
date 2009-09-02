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
