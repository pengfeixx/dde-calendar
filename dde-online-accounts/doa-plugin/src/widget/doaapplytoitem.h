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
#ifndef DOAAPPLYTOITEM_H
#define DOAAPPLYTOITEM_H

#include "doaapplytoobject.h"

#include <DSwitchButton>

#include <QWidget>
#include <QLabel>

DWIDGET_USE_NAMESPACE
class DOAApplyToItem : public QWidget
{
    Q_OBJECT
public:
    explicit DOAApplyToItem(QWidget *parent = nullptr);

    /**
     * @brief setApplyObject        设置应用于对象
     * @param app
     */
    void setApplyObject(const DOAApplyToObject &app);
signals:
    void signalChange(const DOAApplyToObject &app);
public slots:
    void changeState(bool state);

private:
    QLabel *m_appIcon = nullptr;
    QLabel *m_appName = nullptr;
    DSwitchButton *m_switchBtn = nullptr;
    bool m_enbale = false;

    DOAApplyToObject m_ApplyObject;
};

#endif // DOAAPPLYTOITEM_H
