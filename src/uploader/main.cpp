/***************************************************************************
 *   Copyright (C) 2009-2010 by Tarabaka Alexander <XpycT.TOP@gmail.com>   *
 *                                                                         *
 *  This file is part of a BitTorrent Uploader.				   *
 *									   *
 *  BitTorrent Uploader is free software: you can redistribute it and/or   *
 *  modify it under the terms of the GNU General Public License as         *
 *  published by the Free Software Foundation, either version 3 of the     *
 *  License, or (at your option) any later version.			   *
 *									   *
 *  BitTorrent Uploader is distributed in the hope that it will be useful, *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of	   *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	   *
 *  GNU General Public License for more details.			   *
 *									   *
 *  You should have received a copy of the GNU General Public License      *
 *  along with BitTorrent Uploader.                                        *
 *  If not, see <http://www.gnu.org/licenses/>.                            *
 ***************************************************************************/
#include <QTextCodec>
#include <QSettings>
#include <qtsingleapplication.h>
#include "version.h"
#include "dialogs/mainwindow.h"
#include "dialogs/welcomedialog.h"
int main(int argc, char **argv)
{
  QTextCodec::setCodecForTr(QTextCodec::codecForName("WINDOWS-1251")); //WINDOWS-1251
  QTextCodec::setCodecForCStrings(QTextCodec::codecForName("WINDOWS-1251")); //WINDOWS-1251

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

