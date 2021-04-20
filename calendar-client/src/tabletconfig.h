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
#ifndef TABLETCONFIG_H
#define TABLETCONFIG_H

#include <QObject>

/**
 * @brief The TabletConfig class
 * 平板配置类
 */
class TabletConfig : public QObject
{
    Q_OBJECT
public:
    explicit TabletConfig(QObject *parent = nullptr);

    static bool isTablet();
    static void setIsTablet(bool isTablet);
    //设置显示或隐藏虚拟键盘
    static void setVirtualKeyboard(bool isShow);
    //判断虚拟键盘是否显示
    static bool isShowVirtualKeyboard();
signals:

public slots:
private:
    static bool m_isTablet; //是否为平板模式
};

#endif // TABLETCONFIG_H
