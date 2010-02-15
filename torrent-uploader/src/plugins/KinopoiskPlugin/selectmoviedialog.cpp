#include "selectmoviedialog.h"
#include <QCommandLinkButton>
#include <QVBoxLayout>
 #include <QLabel>
SelectMovieDialog::SelectMovieDialog(QWidget *parent,const QString &content)
        :QDialog(parent)
{    
    setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);
    QVBoxLayout *layout=new QVBoxLayout;

     QRegExp rx("<a class=\"all\" href=\"/level/1/film/(\\d+)/sr/1/\">(.*)</a>,&nbsp;<a.*>(\\d+)</a>");
     rx.setMinimal(true);
     QString str = content;
     int pos = 0;
     bool empty=true;
     while ((pos = rx.indexIn(str, pos)) != -1) {
         QCommandLinkButton *btn=new QCommandLinkButton(this);
         btn->setText(QString("%1 (%2)").arg(rx.cap(2)).arg(rx.cap(3)));
         btn->setObjectName(rx.cap(1));
         connect(btn,SIGNAL(clicked()),this,SLOT(selectMovie()));
         layout->addWidget(btn);

         empty=false;
         pos += rx.matchedLength();
     }
     if(empty){
        QLabel* lab = new QLabel(tr("Nothing Found :("), this);
        layout->addWidget(lab);
    }


     setLayout(layout);
}
void SelectMovieDialog::selectMovie(){
    movieID =sender()->objectName();
    QDialog::accept();
}
