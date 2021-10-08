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

#include <QHBoxLayout>

DOAErrorWidget::DOAErrorWidget(QWidget *parent)
    : QWidget(parent)
{
    m_spinner = new DSpinner();
    m_spinner->setFixedSize(20, 20);

    //错误图标
    m_iconLabel = new QLabel(this);
    m_iconLabel->setPixmap(QIcon::fromTheme("doa_error").pixmap(QSize(20, 20)));
    //错误信息
    m_errorMessageLabel = new QLabel(tr("Network error, please check and"));
    m_errorMessageLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

    //重试
    m_tryAginLink = new DCommandLinkButton(tr("try again"));
    connect(m_tryAginLink, &DCommandLinkButton::clicked, this, &DOAErrorWidget::slot_tryAgain);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addStretch();
    layout->addWidget(m_spinner);
    layout->addWidget(m_iconLabel);
    layout->addSpacing(8);
    layout->addWidget(m_errorMessageLabel);
    layout->addWidget(m_tryAginLink);
    layout->addStretch();
    this->setLayout(layout);
}

DOAErrorWidget::~DOAErrorWidget()
{
    m_spinner->stop();
}

void DOAErrorWidget::setErrorMsg(const DOAAccount::AccountState accountState)
{
    m_spinner->stop();
    m_iconLabel->setVisible(true);
    m_spinner->setVisible(false);
    setErrorMsgStat(DOAErrorWidget::ErrorMsgShow);
    switch (accountState) {
    case DOAAccount::Account_AuthenticationFailed:
        //密码异常
        m_errorMessageLabel->setText(tr("Cannot connect to the account, please check your password"));
        m_tryAginLink->setVisible(false);
        break;
    case DOAAccount::Account_NetWorkException:
        m_errorMessageLabel->setText(tr("Network error, please check and"));
        m_tryAginLink->setVisible(true);
        break;
    default:
        //服务器异常
        m_errorMessageLabel->setText(tr("Server error, please"));
        m_tryAginLink->setVisible(true);
        break;
    }
}

void DOAErrorWidget::slot_tryAgain()
{
    m_spinner->start();
    m_iconLabel->setVisible(false);
    m_spinner->setVisible(true);
    m_errorMessageLabel->setText(tr("Connecting to the account..."));
    m_tryAginLink->setVisible(false);
    setErrorMsgStat(DOAErrorWidget::ErrorMsgChecking);
    emit this->sign_tryAgain();
}

DOAErrorWidget::ErrorMsgStat DOAErrorWidget::getErrorMsgStat() const
{
    return errorMsgStat;
}

void DOAErrorWidget::setErrorMsgStat(const ErrorMsgStat &value)
{
    errorMsgStat = value;
}
