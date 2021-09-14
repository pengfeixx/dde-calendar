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
#include "doainfowidget.h"
#include "displaytext.h"
#include "doainfoitem.h"

#include <DFontSizeManager>
#include <DBackgroundGroup>
#include <DLineEdit>

#include <QVBoxLayout>
#include <QLabel>

DWIDGET_USE_NAMESPACE
DOAInfoWidget::DOAInfoWidget(QWidget *parent)
    : QWidget(parent)
{
    initWidget();
}

void DOAInfoWidget::setShowData(const QString &userName, const QString &url, const QString &accountName)
{
    //存储用户名，若用户删除后需要设置
    m_displayName = userName;
    m_userName->setText(m_displayName);
    m_serverAddressLbl->setText(url);
    m_accountName->setText(accountName);
    //    m_passwordEdit->setText()
}

void DOAInfoWidget::initWidget()
{
    QLabel *accountLabl = new QLabel(DOA::AccountInfo::accountInfo, this);
    accountLabl->setAlignment(Qt::AlignLeft);
    DFontSizeManager::instance()->bind(accountLabl, DFontSizeManager::T5, QFont::Medium);

    QVBoxLayout *vboxlayout = new QVBoxLayout();
    vboxlayout->setMargin(0);
    {
        //用户名
        m_userName = new DLineEdit(this);
        DOAInfoItem *userNameItem = new DOAInfoItem(DOA::AccountInfo::displayName, m_userName);
        vboxlayout->addWidget(userNameItem);
    }

    {
        //服务器地址
        m_serverAddressLbl = new QLabel(this);
        DOAInfoItem *serverAddressItem = new DOAInfoItem(DOA::AccountInfo::serverAddress, m_serverAddressLbl);
        m_serverAddressLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        vboxlayout->addWidget(serverAddressItem);
    }

    {
        //帐户
        m_accountName = new QLabel(this);
        DOAInfoItem *accountItem = new DOAInfoItem(DOA::AccountInfo::account, m_accountName);
        m_accountName->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        vboxlayout->addWidget(accountItem);
    }

    {
        //密码
        m_passwordEdit = new QLineEdit(this);
        m_passwordEdit->setEchoMode(QLineEdit::Password);
        DOAInfoItem *passwordItem = new DOAInfoItem(DOA::AccountInfo::password, m_passwordEdit);
        vboxlayout->addWidget(passwordItem);
    }

    DBackgroundGroup *group = new DBackgroundGroup();
    group->setLayout(vboxlayout);
    group->setItemSpacing(1);
    group->setItemMargins(QMargins(0, 0, 0, 0));
    group->setBackgroundRole(QPalette::Window);
    group->setUseWidgetBackground(false);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->addWidget(accountLabl);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(group);
    this->setLayout(mainLayout);
}
