#include <QTextCodec>
#include <qtsingleapplication.h>
#include "version.h"
#include "dialogs/settingsdialog.h"
int main(int argc, char **argv)
{
  QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
  QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QtSingleApplication instance(argc, argv);
    if (instance.sendMessage("Wake up!"))
        return 0;

    QtSingleApplication::setApplicationName(UPLOADER_NAME);
    QtSingleApplication::setApplicationVersion(UPLOADER_VERSION);
    QtSingleApplication::setOrganizationName(UPLOADER_ORGANIZATION);
    QtSingleApplication::setOrganizationDomain(UPLOADER_DOMAIN);
    QtSingleApplication::addLibraryPath(QtSingleApplication::applicationDirPath() + "/plugins");

    SettingsDialog dlg;
    dlg.exec();

    instance.setActivationWindow(&dlg);

    //QObject::connect(&instance, SIGNAL(messageReceived(const QString&)),
    //		     &logview, SLOT(append(const QString&)));

    return instance.exec();
}
