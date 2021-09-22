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
#include "doaapplytoitem.h"

#include <QHBoxLayout>

DOAApplyToItem::DOAApplyToItem(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(10, 8, 10, 8);
    m_appIcon = new QLabel();
    m_appName = new QLabel();
    m_appName->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_switchBtn = new DSwitchButton();
    layout->addWidget(m_appIcon);
    layout->addWidget(m_appName);
    layout->addStretch();
    layout->addWidget(m_switchBtn);
    this->setLayout(layout);
    //根据UI图设置固定高度为48
    setFixedHeight(48);

    connect(m_switchBtn, &DSwitchButton::clicked, this, &DOAApplyToItem::changeState);
}

void DOAApplyToItem::setApplyObject(const DOAApplyToObject &app)
{
    m_ApplyObject = app;
    QIcon icon = QIcon::fromTheme(m_ApplyObject.appName(), QIcon::fromTheme("application-x-desktop"));
    QSize size(32, 32);
    const qreal ratio = devicePixelRatioF();
    QPixmap pixmap = icon.pixmap(size * ratio).scaled(size * ratio, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    pixmap.setDevicePixelRatio(ratio);
    m_appIcon->setPixmap(pixmap);
    //TODO: 根据应用名，获取应用显示名称
    m_appName->setText(m_ApplyObject.appName());
    m_switchBtn->setChecked(m_ApplyObject.isApply());
}

void DOAApplyToItem::changeState(bool state)
{
    //如果状态不一样则更新状态
    if (m_ApplyObject.isApply() != state) {
        m_ApplyObject.setIsApply(state);
        emit signalChange(m_ApplyObject);
    }
}
