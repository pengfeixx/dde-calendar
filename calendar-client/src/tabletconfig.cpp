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
#include "tabletconfig.h"

#include <DApplication>
#include <QDesktopWidget>

DWIDGET_USE_NAMESPACE

//默认不为平板模式
bool TabletConfig::m_isTablet = false;
TabletConfig::TabletConfig(QObject *parent)
    : QObject(parent)
{
}

bool TabletConfig::isTablet()
{
    return m_isTablet;
}

void TabletConfig::setIsTablet(bool isTablet)
{
    m_isTablet = isTablet;
}

/**
 * @brief TabletConfig::setVirtualKeyboard      设置显示或隐藏虚拟键盘
 * @param isShow
 */
void TabletConfig::setVirtualKeyboard(bool isShow)
{
    if (isShow) {
        if (!TabletConfig::isShowVirtualKeyboard())
            DApplication::inputMethod()->show();
    } else {
        if (TabletConfig::isShowVirtualKeyboard())
            DApplication::inputMethod()->hide();
    }
}

/**
 * @brief TabletConfig::isShowVirtualKeyboard   获取虚拟键盘是否显示
 * @return
 */
bool TabletConfig::isShowVirtualKeyboard()
{
    return DApplication::inputMethod()->isVisible();
}

/**
 * @brief TabletConfig::getKeyboardRectangle    获取键盘矩阵
 * @return
 */
QRectF TabletConfig::getKeyboardRectangle()
{
    return DApplication::inputMethod()->keyboardRectangle();
}

/**
 * @brief TabletConfig::getHeightScale      获取屏幕高度缩放比
 * @return
 */
qreal TabletConfig::getHeightScale()
{
    //获取可用桌面大小
    QRect deskTopRect = QApplication::desktop()->availableGeometry();
    return deskTopRect.height() / 1080.0;
}
