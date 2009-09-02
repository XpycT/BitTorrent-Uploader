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
