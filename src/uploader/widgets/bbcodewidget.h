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
#ifndef BBCODEWIDGET_H
#define BBCODEWIDGET_H

#include <qtcolorcombobox.h>

#include <QPlainTextEdit>
#include <QToolBar>
#include <QFontComboBox>
#include <QComboBox>
#include <QAction>
class BBCodeWidget : public QPlainTextEdit
{
    Q_OBJECT
public:
    BBCodeWidget(QWidget *parent=0);
private slots:
    void addTag(QAction*);
    void setFont();
    void setFont_h();
    void setColor(const QColor &);
protected:
    void createActions();
    void insertDoubleTag(const QString &tag,QString opt="");
    void insertSingleTag(const QString &tag,QString opt="");
    void resizeEvent(QResizeEvent *re);
    QToolBar *toolbar1,*toolbar2;
    QFontComboBox *fcb;
    QComboBox *fsp;
    QtColorComboBox *combo;
    QAction *b, *i, *u, *s;
    QAction *ac, *al, *ar, *aj;
    QAction *code, *php, *spoiler, *spoiler_alt, *quote, *quote_alt;
    QAction *link, *mail, *img;
    QAction *hr, *li;

};

#endif // BBCODEWIDGET_H
