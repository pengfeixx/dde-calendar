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
#include "doaerrorwidget.h"
#include "displaytext.h"

#include <DCommandLinkButton>

#include <QLabel>
#include <QHBoxLayout>

DWIDGET_USE_NAMESPACE

DOAErrorWidget::DOAErrorWidget(QWidget *parent)
    : QWidget(parent)
{
    //错误图标
    QLabel *iconLabel = new QLabel(this);
    iconLabel->setPixmap(QIcon::fromTheme("doa_error").pixmap(QSize(20, 20)));
    //错误信息
    QLabel *errorMessageLabel = new QLabel(DOA::AccountInfo::networkError);
    errorMessageLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    //重试
    DCommandLinkButton *tryAginLink = new DCommandLinkButton("try agin");

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addStretch();
    layout->addWidget(iconLabel);
    layout->addSpacing(8);
    layout->addWidget(errorMessageLabel);
    layout->addWidget(tryAginLink);
    layout->addStretch();
    this->setLayout(layout);
}
