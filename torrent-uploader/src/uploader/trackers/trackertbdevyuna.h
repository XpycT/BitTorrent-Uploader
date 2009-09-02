#ifndef TRACKERTBDEVYUNA_H
#define TRACKERTBDEVYUNA_H

#include "trackerrequest.h"
#include <QMap>

class QNetworkAccessManager;
class QNetworkReply;

class TrackerTBDevYuna : public TrackerRequest
{
    Q_OBJECT
public:
    TrackerTBDevYuna();
    void checkLogin(const QString &login,const QString &password);
    void uploadRelease();
    enum Status {Login,Category};
signals:
    void categoryDone();
    void blockInterface(bool &isBlocked);
private slots:
    void replyFinished(QNetworkReply*);    
private:
    void getCategory();
    void setStatus(Status status);
    void parseCategory(QString &content);
    QNetworkAccessManager *manager;
    bool isBlocked;
    Status currentStatus;
};

#endif // TRACKERTBDEVYUNA_H
