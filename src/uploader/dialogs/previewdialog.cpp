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
#include "previewdialog.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QtWebKit>
#include <QFile>
#include <QDateTime>
#include <QSettings>
#include <QApplication>
#include <QRegExp>
#include <QDebug>
PreviewDialog::PreviewDialog(QWidget *parent,const  QString &name
                             ,const  QString &category,const  QString &content
                             ,const  QString &poster,const  QStringList &screens)
        :QDialog(parent)
{

    m_settings=new QSettings(QApplication::organizationName(), QApplication::applicationName());
    int trackerType=m_settings->value("General/TrackerType",0).toInt();

    setWindowFlags(windowFlags() ^ Qt::WindowContextHelpButtonHint);
    view = new QWebView;
    view->setContextMenuPolicy(Qt::ContextMenuPolicy(Qt::NoContextMenu));
    QString text;
    switch(trackerType){
        case 0:
        text = parseTBDevYuna(name,category,content,poster,screens);
    }

    QFile file;
    file.setFileName(":/preview/jquery.min.js");
    file.open(QIODevice::ReadOnly);
    QString jQuery = file.readAll();
    file.close();

    view->setHtml(text);
    view->page()->mainFrame()->evaluateJavaScript(jQuery);
    view->page()->mainFrame()->evaluateJavaScript("$('div#spoiler').toggle(function(){$(this).children('img').attr({src: 'qrc:/preview/icon_minus.gif'});},function(){$(this).children('img').attr({src: 'qrc:/preview/icon_plus.gif'});});$('div#spoiler').click(function(){$(this).children('div').slideToggle('fast');});");

    QPushButton *closeButton=new QPushButton(tr("Close preview"));
    connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));

    QVBoxLayout *layout=new QVBoxLayout;
    layout->addWidget(view);
    layout->addWidget(closeButton);
    setLayout(layout);

}

QString PreviewDialog::parseTBDevYuna(const QString &name
                             ,const QString &category,const QString &content
                             ,const QString &poster,const QStringList &screens) const
{
    QFile file(":/preview/preview_yuna.html");
    if (!file.open(QIODevice::ReadOnly))
         return QString();
    QString html=file.readAll();
    file.close();

    QString screenshot;
    for (int i = 0; i < screens.size(); ++i)
          screenshot.append(QString("<LI><A href='#'><IMG src='%1' alt='image' width='114px' height='80px'></A></LI>").arg(screens.at(i)));

    html.replace("%name%", name);
    html.replace("%category%", category);
    html.replace("%description%", parseTBDevYunaContent(content));
    html.replace("%poster%",poster);
    html.replace("%screens%",screenshot);
    html.replace("%date%", QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

    html.replace("%user%",m_settings->value("Profile/Login","").toString());

    return html;
}
QString PreviewDialog::parseTBDevYunaContent(const QString &content) const{
    QString text=content;    
    text.replace("<","&lt;");
    text.replace(">","&gt;");
    text.replace("\"","&quot;");
    text.replace("\n","<br/>");
    text.replace("[li]","<li>");
    text.replace("[hr]","<hr>");
    QRegExp rx;
    rx.setMinimal(true);
    rx.setPattern("\\[b\\](.*)\\[/b\\]");
    text.replace(rx,"<b>\\1</b>");
    rx.setPattern("\\[i\\](.*)\\[/i\\]");
    text.replace(rx,"<em>\\1</em>");
    rx.setPattern("\\[u\\](.*)\\[/u\\]");
    text.replace(rx,"<u>\\1</u>");
    rx.setPattern("\\[s\\](.*)\\[/s\\]");
    text.replace(rx,"<s>\\1</s>");
    rx.setPattern("\\[(left|right|center|justify)\\](.*)\\[/\\1\\]");
    text.replace(rx,"<div align='\\1'>\\2</s>");
    rx.setPattern("\\[code\\](.*)\\[/code\\]");
    text.replace(rx,QString("<table width='100%' cellspacing='1' cellpadding='3' border='0' align='center'><tr style='background: #E5EFFF;font-size:12px;'><td style='border: 1px solid #000;'>%1</td></tr><tr><td style='font-size:12px;color: blue;border: 1px solid #000;'>\\1</td></tr></table>").arg(tr("Code:")));
    rx.setPattern("\\[php\\](.*)\\[/php\\]");
    text.replace(rx,QString("<table width='100%' cellspacing='1' cellpadding='3' border='0' align='center'><tr style='background: #F3E8FF;font-size:12px;'><td style='border: 1px solid #000;'>%1</td></tr><tr><td style='font-size:12px;color: blue;border: 1px solid #000;'>\\1</td></tr></table>").arg(tr("PHP-code:")));
    rx.setPattern("\\[quote\\](.*)\\[/quote\\]");
    text.replace(rx,QString("<table width='100%' cellspacing='1' cellpadding='3' align='center' ><tr style='background: #fac6c0;font-size:12px;'><td  style='border: 1px solid #000;'>%1</td></tr><tr style='font-size:12px;'><td style='border: 1px solid #000;'>\\1</td></tr></table>").arg(tr("Quote:")));
    rx.setPattern("\\[quote=([^\\]]*)\\](.*)\\[/quote\\]");
    text.replace(rx,QString("<table width='100%' cellspacing='1' cellpadding='3' align='center' ><tr style='background: #fac6c0;font-size:12px;'><td  style='border: 1px solid #000;'>\\1 %1</td></tr><tr style='font-size:12px;'><td style='border: 1px solid #000;'>\\2</td></tr></table>").arg(tr("write:")));
    rx.setPattern("\\[spoiler\\](.*)\\[/spoiler\\]");
    text.replace(rx,QString("<div id='spoiler' style='border: 1px solid #E0E0E0; padding: 3px'> <img src='qrc:/preview/icon_plus.gif'  title='%1' tooltip='%1'> %1 <div id='ss' style='DISPLAY: none;border: 1px dashed #E0E0E0; padding: 2px'>\\1</div></div>").arg(tr("Show/hide")));
    rx.setPattern("\\[spoiler=([^\\]]*)\\](.*)\\[/spoiler\\]");
    text.replace(rx,QString("<div id='spoiler' style='border: 1px solid #E0E0E0; padding: 3px'> <img src='qrc:/preview/icon_plus.gif'  title='%1' tooltip='%1'> \\1 <div id='ss' style='DISPLAY: none;border: 1px dashed #E0E0E0; padding: 2px'>\\2</div></div>").arg(tr("Show/hide")));

    rx.setPattern("\\[url=([^\\]]*)\\](.*)\\[/url\\]");
    text.replace(rx,"<a href='#'>\\2</a>");
    rx.setPattern("\\[mail\\](.*)\\[/mail\\]");
    text.replace(rx,"<a href='mailto:\\1'>\\1</a>");
    rx.setPattern("\\[img\\](.*)\\[/img\\]");
    text.replace(rx,"<img src='\\1' border=0/>");
    rx.setPattern("\\[size=([^\\]]*)\\](.*)\\[/size\\]");
    text.replace(rx,"<span style='font-size:\\1px;'>\\2</span>");
    rx.setPattern("\\[color=([^\\]]*)\\](.*)\\[/color\\]");
    text.replace(rx,"<span style='color:\\1;'>\\2</span>");
    rx.setPattern("\\[family=([^\\]]*)\\](.*)\\[/family\\]");
    text.replace(rx,"<span style='font-family:\\1;'>\\2</span>");
    return text;
}

