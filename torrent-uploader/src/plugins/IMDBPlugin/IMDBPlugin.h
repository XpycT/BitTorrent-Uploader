#ifndef _IMDBPlugin_h_
#define _IMDBPlugin_h_

#include <QObject>
#include "interfaces.h"

class QNetworkAccessManager;
class QNetworkReply;
// ======================================================================
class IMDBPlugin : public QObject, public PluginInterface {
Q_OBJECT
Q_INTERFACES(PluginInterface)

public:
    IMDBPlugin();
    virtual ~IMDBPlugin();

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
#endif //_IMDBPlugin_h_
