#ifndef _interfaces_h_
#define _interfaces_h_
class QString;
class QStringList;
// ======================================================================
class PluginInterface {
public:
    PluginInterface() {}
    virtual ~PluginInterface() {}

    virtual QStringList operations() const = 0;

    virtual void operation() = 0;

    virtual void getDescription(QString &descr)=0;
};

Q_DECLARE_INTERFACE(PluginInterface,
                    "com.xpyct.bittorrentUploader.PluginInterface/1.0"
                   )
#endif //_interfaces_h_
