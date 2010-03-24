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
#ifndef _interfaces_h_
#define _interfaces_h_
class QString;
class QStringList;
// ======================================================================
class PluginInterface {
public:
    PluginInterface() {}
    virtual ~PluginInterface() {}

    virtual QStringList operations() const = 0;

    virtual void operation() = 0;

    virtual void getDescription(QString &descr)=0;

    virtual void getStatus(int status)=0;
};

Q_DECLARE_INTERFACE(PluginInterface,
                    "com.xpyct.bittorrentUploader.PluginInterface/1.0"
                   )
#endif //_interfaces_h_
