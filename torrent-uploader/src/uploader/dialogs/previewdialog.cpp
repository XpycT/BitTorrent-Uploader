#include "previewdialog.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QWebView>
PreviewDialog::PreviewDialog(QWidget *parent,QString &content)
        :QDialog(parent)
{
    setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);
    view = new QWebView;
    view->load(QUrl("http://google.com/"));
    QPushButton *closeButton=new QPushButton(tr("Close preview"));
    connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));

    QVBoxLayout *layout=new QVBoxLayout;
    layout->addWidget(view);
    layout->addWidget(closeButton);
    setLayout(layout);
}
