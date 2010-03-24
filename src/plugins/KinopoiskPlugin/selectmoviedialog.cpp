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
