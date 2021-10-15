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
#include "doainfoitem.h"
#include "doapasswordedit.h"

#include <DFontSizeManager>
#include <DBackgroundGroup>
#include <DLineEdit>
#include <DPalette>

#include <QVBoxLayout>
#include <QLabel>

DWIDGET_USE_NAMESPACE
DOAInfoWidget::DOAInfoWidget(QWidget *parent)
    : QWidget(parent)
{
    initWidget();
}

void DOAInfoWidget::setShowData(const QString &userName, const QString &url, const QString &accountName, const QString &password)
{
    //只有当用户名被修改时才更新
    if (m_displayName != userName) {
        //存储用户名，若用户删除后需要设置
        m_displayName = userName;
        m_userName->setText(m_displayName);
    }
    //只有当密码被修改时才更新
    if (m_password != password) {
        m_password = password;
        m_passwordEdit->setText(password);
        //密码恢复默认设置
        m_passwordEdit->setPasswordButtonAutoHide(true);
        m_passwordEdit->setEchoButtonIsVisible(false);
    }

    m_serverAddressLbl->setText(url);
    m_accountName->setText(accountName);
}

void DOAInfoWidget::initWidget()
{
    QLabel *accountLabl = new QLabel(tr("Account Info"), this);
    accountLabl->setAlignment(Qt::AlignLeft);
    DFontSizeManager::instance()->bind(accountLabl, DFontSizeManager::T5, QFont::Medium);
    //设置内容左边距
    QMargins margins = accountLabl->contentsMargins();
    margins.setLeft(10);
    accountLabl->setContentsMargins(margins);

    QVBoxLayout *vboxlayout = new QVBoxLayout();
    vboxlayout->setMargin(0);
    {
        //用户名
        m_userName = new DLineEdit(this);
        DOAInfoItem *userNameItem = new DOAInfoItem(tr("User Name"), m_userName);
        connect(m_userName, &DLineEdit::focusChanged, this, &DOAInfoWidget::slotUserNameFocusChanged);
        connect(m_userName, &DLineEdit::textChanged, this, &DOAInfoWidget::slotUserNameTextChanged);
        vboxlayout->addWidget(userNameItem);
    }

    {
        //服务器地址
        m_serverAddressLbl = new QLabel(this);
        DFontSizeManager::instance()->bind(m_serverAddressLbl, DFontSizeManager::T8, QFont::Normal);
        DOAInfoItem *serverAddressItem = new DOAInfoItem(tr("Server IP"), m_serverAddressLbl);
        m_serverAddressLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        vboxlayout->addWidget(serverAddressItem);
    }

    {
        //帐户
        m_accountName = new QLabel(this);
        DFontSizeManager::instance()->bind(m_accountName, DFontSizeManager::T8, QFont::Normal);
        DOAInfoItem *accountItem = new DOAInfoItem(tr("Account"), m_accountName);
        m_accountName->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        vboxlayout->addWidget(accountItem);
    }

    {
        //密码
        m_passwordEdit = new DOAPasswordEdit(this);
        //设置密码显示按钮自动隐藏
        m_passwordEdit->setPasswordButtonAutoHide(true);
        connect(m_passwordEdit, &DOAPasswordEdit::signalePasswordChanged, this, &DOAInfoWidget::signalUpdatePassword);
        DOAInfoItem *passwordItem = new DOAInfoItem(tr("Password"), m_passwordEdit);
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
    mainLayout->addSpacing(5);
    mainLayout->addWidget(group);
    this->setLayout(mainLayout);
}

//用户名编辑框焦点离开处理
void DOAInfoWidget::slotUserNameFocusChanged(const bool onFocus)
{
    if (!onFocus) {
        //如果内容多于32则提示
        if (m_userName->lineEdit()->text().size() > 32) {
            m_userName->setAlert(true);
            m_userName->setAlertMessageAlignment(Qt::AlignTop);
            m_userName->showAlertMessage(tr("No more than 32 characters please"), this);
            return;
        }
        //如果内容为空则设置为之前的用户名
        if (m_userName->lineEdit()->text().isEmpty()) {
            m_userName->setText(m_displayName);
            return;
        }
        //如果内容为上次保存内容则退出
        if (m_userName->lineEdit()->text() == m_displayName)
            return;
        m_displayName = m_userName->lineEdit()->text();
        emit signalUpdateUserName(m_displayName);
    }
}

void DOAInfoWidget::slotUserNameTextChanged(const QString &text)
{
    Q_UNUSED(text)
    if (m_userName->isAlert()) {
        m_userName->setAlert(false);
        m_userName->hideAlertMessage();
    }
}
