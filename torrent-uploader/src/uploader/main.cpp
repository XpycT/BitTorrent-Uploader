#include <QTextCodec>
#include <QSettings>
#include <qtsingleapplication.h>
#include "version.h"
#include "dialogs/mainwindow.h"
#include "dialogs/welcomedialog.h"
int main(int argc, char **argv)
{
  QTextCodec::setCodecForTr(QTextCodec::codecForName("WINDOWS-1251"));
  QTextCodec::setCodecForCStrings(QTextCodec::codecForName("WINDOWS-1251"));

    QtSingleApplication instance(argc, argv);
    if (instance.sendMessage("Wake up!"))
        return 0;

    QSettings settings(QApplication::organizationName(), QApplication::applicationName());
    bool s_hide_welcome  =settings.value("General/hideWelcome",false).toBool();
    if(!s_hide_welcome){
        WelcomeDialog welcome;
        if(welcome.exec()==QDialog::Rejected)
            return 1;
    }

    QtSingleApplication::setApplicationName(UPLOADER_NAME);
    QtSingleApplication::setApplicationVersion(UPLOADER_VERSION);
    QtSingleApplication::setOrganizationName(UPLOADER_ORGANIZATION);
    QtSingleApplication::setOrganizationDomain(UPLOADER_DOMAIN);
    QtSingleApplication::addLibraryPath(QtSingleApplication::applicationDirPath() + "/plugins");

    QString locale = QLocale::system().name();

    QTranslator qtTranslator;
    qtTranslator.load(QString("qt_") + locale, ":/i18n");
    QtSingleApplication::installTranslator(&qtTranslator);

    QTranslator translator;
    translator.load(QString("i18n_") + locale, ":/i18n");
    QtSingleApplication::installTranslator(&translator);

    MainWindow dlg;
    dlg.show();

    instance.setActivationWindow(&dlg);

    //QObject::connect(&instance, SIGNAL(messageReceived(const QString&)),
    //		     &logview, SLOT(append(const QString&)));

    return instance.exec();
}

