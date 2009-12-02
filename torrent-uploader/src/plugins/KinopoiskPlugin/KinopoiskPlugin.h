#ifndef _KinopoiskPlugin_h_
#define _KinopoiskPlugin_h_

#include <QObject>
#include "interfaces.h"

class QNetworkAccessManager;
class QNetworkReply;
// ======================================================================
class KinopoiskPlugin : public QObject, public PluginInterface {
Q_OBJECT
Q_INTERFACES(PluginInterface)

public:
    KinopoiskPlugin();
    virtual ~KinopoiskPlugin();

    virtual QStringList operations() const;
    virtual void     operation ();
    enum Status {Login,Category,Movie};
signals:
    /*virtual*/ void getDescription(QString &descr);

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
#endif //_KinopoiskPlugin_h_
