#include "selectmoviedialog.h"
#include <QCommandLinkButton>
#include <QVBoxLayout>
SelectMovieDialog::SelectMovieDialog(QWidget *parent,QString &content)
        :QDialog(parent)
{    
    QVBoxLayout *layout=new QVBoxLayout;

     QRegExp rx("<a class=\"all\" href=\"/level/1/film/(\\d+)/sr/1/\">(.*)</a>,&nbsp;<a.*>(\\d+)</a>");
     rx.setMinimal(true);
     QString str = content;
     int pos = 0;
     while ((pos = rx.indexIn(str, pos)) != -1) {
         QCommandLinkButton *btn=new QCommandLinkButton(this);
         btn->setText(QString("%1 (%2)").arg(rx.cap(2)).arg(rx.cap(3)));
         btn->setObjectName(rx.cap(1));
         connect(btn,SIGNAL(clicked()),this,SLOT(selectMovie()));
         layout->addWidget(btn);

         pos += rx.matchedLength();
     }

     setLayout(layout);
}
void SelectMovieDialog::selectMovie(){
    movieID =sender()->objectName();
    QDialog::accept();
}
