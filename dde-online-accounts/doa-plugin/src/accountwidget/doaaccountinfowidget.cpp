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
            disconnect(m_accountModel, &DOAAccountModel::signalUserNameChanged, this, &DOAAccountInfoWidget::slotPropertyChanged);
            disconnect(m_accountModel, &DOAAccountModel::signalAccountStatusChanged, this, &DOAAccountInfoWidget::slotAccountStatusChanged);
            disconnect(m_accountModel, &DOAAccountModel::signShowDeleteDialog, this, &DOAAccountInfoWidget::slotDeleteCurrentAccount);
        }
        m_accountModel = model;
        connect(m_accountModel, &DOAAccountModel::signalSelectAccountChanged, this, &DOAAccountInfoWidget::slotUpdateCurrentAccount);
        connect(m_accountModel, &DOAAccountModel::signalPasswordChanged, this, &DOAAccountInfoWidget::slotPropertyChanged);
        connect(m_accountModel, &DOAAccountModel::signalUserNameChanged, this, &DOAAccountInfoWidget::slotPropertyChanged);
        connect(m_accountModel, &DOAAccountModel::signalAccountStatusChanged, this, &DOAAccountInfoWidget::slotAccountStatusChanged);
        //应用调用控制中心直接显示删除对话框
        connect(m_accountModel, &DOAAccountModel::signShowDeleteDialog, this, &DOAAccountInfoWidget::slotDeleteCurrentAccount);
    }
    slotUpdateCurrentAccount();
}

void DOAAccountInfoWidget::initData()
{
    m_errorWidget->initData();
}

/**
 * @brief DOAAccountInfoWidget::slotTryAgain
 * 重新检测帐户状态
 */
void DOAAccountInfoWidget::slotTryAgain()
{
    if (m_Account) {
        m_Account->slotCheckState();
    }
}

void DOAAccountInfoWidget::slotUpdateCurrentAccount()
{
    initData();
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
        //设置当前状态
        slotAccountStatusChanged(m_Account->getAccountID());
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
    if (m_Account) {
        m_Account->updateUserName(userName);
    }
}

//更新密码
void DOAAccountInfoWidget::slotUpdatePassword(const QString &passowrd)
{
    //更新密码
    if (m_Account) {
        m_Account->updatePassword(passowrd);
    }
}

/**
 * @brief DOAAccountInfoWidget::slotShowErrorMsg
 * 根据错误码显示错误信息
 */
void DOAAccountInfoWidget::slotShowErrorMsg()
{
    m_errorWidget->setErrorMsg(m_Account->getAccountState());
}

//更新同步属性
void DOAAccountInfoWidget::slotUpdateApplyToItem(const DOAApplyToObject &app)
{
    //更新显示名称
    if (m_Account) {
        m_Account->updateApplyTo(app);
    }
}

void DOAAccountInfoWidget::slotPropertyChanged(const QString &accountID)
{
    if (isCurrentShowAccount(accountID)) {
        m_accountInfo->setShowData(m_Account->getUserName(), m_Account->getUrl(), m_Account->getAccountName(), m_Account->getAccountPassword());
    }
}

//帐户状态发生改变
void DOAAccountInfoWidget::slotAccountStatusChanged(const QString &accountID)
{
    if (isCurrentShowAccount(accountID)) {
        slotShowErrorMsg();
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
    layout->addSpacing(10);
    layout->addWidget(m_errorWidget);
    layout->addSpacing(20);

    //默认隐藏错误信息
    m_errorWidget->setHidden(true);
    connect(m_errorWidget, &DOAErrorWidget::sign_tryAgain, this, &DOAAccountInfoWidget::slotTryAgain);

    //设置内容左边距
    QMargins margins = m_accountProtocolLbl->contentsMargins();
    margins.setLeft(10);
    m_accountProtocolLbl->setContentsMargins(margins);
    layout->addWidget(m_accountProtocolLbl);

    layout->addSpacing(10);
    layout->addWidget(m_accountInfo);
    layout->addSpacing(10);
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

//是否为当前显示帐户
bool DOAAccountInfoWidget::isCurrentShowAccount(const QString &accountID)
{
    //如果当前帐户有效且状态改变的帐户为当前帐户
    return m_Account && m_Account->getAccountID() == accountID;
}

void DOAAccountInfoWidget::resizeEvent(QResizeEvent *event)
{
    if (m_content)
        m_content->setFixedWidth(event->size().width());
}
