#include "previewdialog.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QWebView>
#include <QFile>
PreviewDialog::PreviewDialog(QWidget *parent,QString &content)
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

    view->setHtml(html);
    QPushButton *closeButton=new QPushButton(tr("Close preview"));
    connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));

    QVBoxLayout *layout=new QVBoxLayout;
    layout->addWidget(view);
    layout->addWidget(closeButton);
    setLayout(layout);
}
