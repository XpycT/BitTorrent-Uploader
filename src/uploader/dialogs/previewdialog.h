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
#ifndef PREVIEWDIALOG_H
#define PREVIEWDIALOG_H

#include <QDialog>
class QWebView;
class QSettings;
class PreviewDialog : public QDialog
{
    Q_OBJECT
public:
    PreviewDialog(QWidget *parent=0,const QString &name=QString()
                  ,const QString &category=QString(),const QString &content=QString()
                  ,const QString &poster=QString(),const QStringList &screens=QStringList());
private:
    QString parseTBDevYuna(const QString &name
                  ,const QString &category,const QString &content
                  ,const QString &poster,const QStringList &screens) const;
    QString parseTBDevYunaContent(const QString &content) const;
    QWebView *view;
    QSettings *m_settings;
};

#endif // PREVIEWDIALOG_H
