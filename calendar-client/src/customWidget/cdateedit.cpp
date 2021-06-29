/*
* Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
*
* Author:     chenhaifeng  <chenhaifeng@uniontech.com>
*
* Maintainer: chenhaifeng  <chenhaifeng@uniontech.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "cdateedit.h"

#include <QLineEdit>
#include <QMouseEvent>

CDateEdit::CDateEdit(QWidget *parent)
    : DDateEdit(parent)
{
    //平板模式设置不可输入
    lineEdit()->setReadOnly(true);
}

void CDateEdit::mousePressEvent(QMouseEvent *event)
{
    DDateEdit::mousePressEvent(event);
    //锁屏时窗管是根据窗口的WidgetAttribute为Combo或Menu来关闭窗口
    //获取下拉日历窗口
    QWidget *calendarPopup = this->findChild<QWidget *>("qt_datetimedit_calendar");
    if (nullptr != calendarPopup) {
        //设置属性
        calendarPopup->setAttribute(Qt::WA_X11NetWmWindowTypeCombo);
    }
}
