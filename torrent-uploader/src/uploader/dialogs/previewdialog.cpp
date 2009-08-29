#include "previewdialog.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QWebView>
#include <QFile>
#include <QDateTime>
#include <QSettings>
#include <QApplication>
#include <QDebug>
PreviewDialog::PreviewDialog(QWidget *parent,QString &name
                             ,QString &category,QString &content
                             ,QString &poster,QStringList &screens)
        :QDialog(parent)
{
    setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);
    view = new QWebView;
    view->setContextMenuPolicy(Qt::ContextMenuPolicy(Qt::NoContextMenu));

    QFile file(":/preview/preview.html");
    if (!file.open(QIODevice::ReadOnly))
         return;
    QString html=file.readAll();
    file.close();

    QString screenshot;
    for (int i = 0; i < screens.size(); ++i)
          screenshot.append(QString("<LI><A href='#'><IMG src='%1' alt='image' width='114px' height='80px'></A></LI>").arg(screens.at(i)));

    content.replace("\n","<br/>");
    html.replace("%name%", name);
    html.replace("%category%", category);
    html.replace("%description%", content);
    html.replace("%poster%",poster);
    html.replace("%screens%",screenshot);
    html.replace("%date%", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    QSettings settings(QApplication::organizationName(), QApplication::applicationName());
    html.replace("%user%",settings.value("Profile/Login","").toString());



    view->setHtml(html);
    QPushButton *closeButton=new QPushButton(tr("Close preview"));
    connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));

    QVBoxLayout *layout=new QVBoxLayout;
    layout->addWidget(view);
    layout->addWidget(closeButton);
    setLayout(layout);
}
