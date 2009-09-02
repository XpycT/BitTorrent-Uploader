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
    virtual void uploadRelease() = 0;
    virtual QMap<int,QString> returnCategory(){return catmap;}
signals:
    void categoryDone();
    void blockInterface(bool &isBlocked);
protected:
    QMap<int,QString> catmap;
};

#endif // TRACKERREQUEST_H
