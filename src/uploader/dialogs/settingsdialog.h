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
#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <ui_settingsdialog.h>
class SettingsDialog : public QDialog, public Ui::SettingsDialog
{
    Q_OBJECT
public:
    SettingsDialog(QWidget *parent=0);
private slots:
    void on_okButton_clicked();
    void on_resetButton_clicked();
    void on_selectClientButton_clicked();
private:
    void readSettings();
    void saveSettings();
};

#endif // SETTINGSDIALOG_H
