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
#include "doaaccountinfowidget.h"
#include "dialog/doaaccountremovedialog.h"

#include <DWarningButton>
#include <DFontSizeManager>

#include <QLabel>
#include <QVBoxLayout>
#include <QScroller>
#include <QEvent>
#include <QResizeEvent>

DWIDGET_USE_NAMESPACE

DOAAccountInfoWidget::DOAAccountInfoWidget(QWidget *parent)
    : QWidget(parent)
    , m_content(new QWidget(this))
    , m_scrollArea(new QScrollArea(this))
    , m_accountInfo(new DOAInfoWidget(this))
    , m_accountProtocolLbl(new QLabel("CalDAV", this))
    , m_applyToWidget(new DOAApplyToWidget(this))
    , m_errorWidget(new DOAErrorWidget)
    , m_accountModel(nullptr)
{
    initWidget();
}

void DOAAccountInfoWidget::setModel(DOAAccountModel *model)
{
    if (model && m_accountModel != model) {
        if (m_accountModel) {
            disconnect(m_accountModel, &DOAAccountModel::signalSelectAccountChanged, this, &DOAAccountInfoWidget::slotUpdateCurrentAccount);
            disconnect(m_accountModel, &DOAAccountModel::signalPasswordChanged, this, &DOAAccountInfoWidget::slotPropertyChanged);
        }
        m_accountModel = model;
        connect(m_accountModel, &DOAAccountModel::signalSelectAccountChanged, this, &DOAAccountInfoWidget::slotUpdateCurrentAccount);
        connect(m_accountModel, &DOAAccountModel::signalPasswordChanged, this, &DOAAccountInfoWidget::slotPropertyChanged);
        connect(m_accountModel, &DOAAccountModel::signalAccountStatusChanged, this, &DOAAccountInfoWidget::slotPropertyChanged);
    }
    slotUpdateCurrentAccount();
}

void DOAAccountInfoWidget::slotUpdateCurrentAccount()
{
    //获取当前帐户信息
    m_Account = m_accountModel->getCurrentAccount();
    if (m_Account) {
        //设置帐户信息
        m_accountInfo->setShowData(m_Account->getUserName(), m_Account->getUrl(), m_Account->getAccountName(), m_Account->getAccountPassword());
        m_applyToWidget->clearApp();
        //设置应用于应用
        for (int i = 0; i < m_Account->getApplyObject().size(); ++i) {
            m_applyToWidget->addApp(m_Account->getApplyObject().at(i));
        }

        slotShowErrorMsg();
    }
}

//移除当前帐户
void DOAAccountInfoWidget::slotDeleteCurrentAccount()
{
    //删除提示对话框
    DOAAccountRemoveDialog removeDialog(this);
    connect(&removeDialog, &DOAAccountRemoveDialog::signalDeleteAccount, m_Account, &DOAAccount::slotRemove);
    removeDialog.exec();
}

//更新显示名称
void DOAAccountInfoWidget::slotUpdateUserName(const QString &userName)
{
    //更新显示名称
    m_Account->updateUserName(userName);
}

//更新密码
void DOAAccountInfoWidget::slotUpdatePassword(const QString &passowrd)
{
    //更新密码
    m_Account->updatePassword(passowrd);
}

void DOAAccountInfoWidget::slotShowErrorMsg()
{
    if (m_Account->getAccountState() == DOAAccount::Account_AuthenticationFailed && m_errorWidget->isHidden()) {
        m_errorWidget->setErrorMsg(m_Account->getAccountState());
        m_errorWidget->setHidden(false);
    } else if (m_Account->getAccountState() != DOAAccount::Account_Success && m_errorWidget->isHidden()) {
        m_errorWidget->setErrorMsg(m_Account->getAccountState());
        m_errorWidget->setHidden(false);
    } else if (m_Account->getAccountState() == DOAAccount::Account_Success && !m_errorWidget->isHidden()) {
        m_errorWidget->setHidden(true);
    }
}

//更新同步属性
void DOAAccountInfoWidget::slotUpdateApplyToItem(const DOAApplyToObject &app)
{
    //更新显示名称
    m_Account->updateApplyTo(app);
}

void DOAAccountInfoWidget::slotPropertyChanged(const QString &accountID)
{
    if (m_Account) {
        if (m_Account->getAccountID() == accountID) {
            slotShowErrorMsg();
            m_accountInfo->setShowData(m_Account->getUserName(), m_Account->getUrl(), m_Account->getAccountName(), m_Account->getAccountPassword());
        }
    }
}

void DOAAccountInfoWidget::initWidget()
{
    //自动滚动区
    m_scrollArea = new QScrollArea;
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setFrameStyle(QFrame::NoFrame);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_scrollArea->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    m_scrollArea->setContentsMargins(0, 0, 0, 0);

    m_scrollArea->setWidget(m_content);

    //删除按钮
    DWarningButton *warningBtn = new DWarningButton(this);
    warningBtn->setText(tr("Delete Account"));
    connect(warningBtn, &DWarningButton::clicked, this, &DOAAccountInfoWidget::slotDeleteCurrentAccount);

    DFontSizeManager::instance()->bind(m_accountProtocolLbl, DFontSizeManager::T3, QFont::Bold);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(warningBtn);
    layout->addWidget(m_errorWidget);
    layout->addSpacing(20);

    layout->addWidget(m_accountProtocolLbl);
    layout->addSpacing(20);
    layout->addWidget(m_accountInfo);
    layout->addSpacing(20);
    layout->addWidget(m_applyToWidget);
    layout->addStretch();
    m_content->setLayout(layout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->addWidget(m_scrollArea);
    mainLayout->setSpacing(0);
    this->setLayout(mainLayout);

    connect(m_accountInfo, &DOAInfoWidget::signalUpdateUserName, this, &DOAAccountInfoWidget::slotUpdateUserName);
    connect(m_accountInfo, &DOAInfoWidget::signalUpdatePassword, this, &DOAAccountInfoWidget::slotUpdatePassword);
    connect(m_applyToWidget, &DOAApplyToWidget::signApplyToItemChange, this, &DOAAccountInfoWidget::slotUpdateApplyToItem);
}

void DOAAccountInfoWidget::resizeEvent(QResizeEvent *event)
{
    if (m_content)
        m_content->setFixedWidth(event->size().width());
}
