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
#include "doaaccountlistwidget.h"
#include "displaytext.h"
#include "consts.h"

#include <DStyleOption>
#include <DStandardItem>
#include <DFloatingButton>
#include <DFontSizeManager>

#include <QLabel>
#include <QVBoxLayout>

DWIDGET_USE_NAMESPACE

DOAAccountListWidget::DOAAccountListWidget(QWidget *parent)
    : QWidget(parent)
    , m_model(nullptr)
    , m_addAccountBtn(new DFloatingButton(DStyle::SP_IncreaseElement, this))
    , m_listView(new DListView(this))
    , m_promptLbl(new QLabel(this))
    , m_accountModel(new QStandardItemModel(this))
    , m_listModel(new DOAAccountListModel(m_listView))
    , m_listDelegate(new DOAAccountListItemDelegate(m_listView))
    , m_stackedWidget(new DStackedWidget)
{
    initWidget();

    connect(m_addAccountBtn, &DFloatingButton::clicked, this, &DOAAccountListWidget::slotAddAccount);
    connect(m_listDelegate, &DOAAccountListItemDelegate::signalSelectItem, this, &DOAAccountListWidget::slotSelectItem);
}

DOAAccountListWidget::~DOAAccountListWidget()
{
    //释放资源，取消对应关联
}

void DOAAccountListWidget::setModel(DOAAccountModel *model)
{
    if (model) {
        m_model = model;
        //添加信号连接
        if (m_model->getAccountMap().size() > 0) {
            addAccount();
            QModelIndex index = m_listModel->index(0);
            m_listView->setCurrentIndex(index);
            QVariant value = index.data(Qt::UserRole);
            AccountItemData accountData = value.value<AccountItemData>();
            slotSelectItem(accountData.accountId);
            m_stackedWidget->setCurrentIndex(1);
            m_addAccountBtn->setEnabled(true);
        } else {
            m_stackedWidget->setCurrentIndex(0);
            m_addAccountBtn->setEnabled(false);
        }
    }
}

void DOAAccountListWidget::initWidget()
{
    //新建用户按钮
    m_addAccountBtn->setFixedSize(50, 50);
    m_addAccountBtn->setToolTip(DOA::AccountListWidget::addAccountStr);
    m_addAccountBtn->setAccessibleName("Add Account");
    //无帐户信息提示
    m_promptLbl->setText(DOA::AccountListWidget::noAccountPrompt);
    DFontSizeManager::instance()->bind(m_promptLbl, DFontSizeManager::T5, QFont::Bold);
    m_promptLbl->setAlignment(Qt::AlignCenter);

    m_listView->setAccessibleName("accountListView");
    m_listView->setFrameShape(QFrame::NoFrame);
    m_listView->setViewportMargins(QMargins(5, 5, 5, 0));
    m_listView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_listView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_listView->setEditTriggers(QListView::NoEditTriggers);
    m_listView->setDragEnabled(false);
    m_listView->setIconSize(QSize(30, 30));
    m_listView->setLayoutDirection(Qt::LeftToRight);
    m_listView->setItemDelegate(m_listDelegate);
    m_listView->setModel(m_listModel);
    m_listView->setSpacing(5);

    m_stackedWidget->addWidget(m_promptLbl);
    m_stackedWidget->addWidget(m_listView);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->addWidget(m_stackedWidget);
    layout->addWidget(m_addAccountBtn, 0, Qt::AlignCenter);
    this->setLayout(layout);
}

void DOAAccountListWidget::slotSelectItem(QString accountID)
{
    m_model->setCurrentAccountByID(accountID);
    m_model->setState(DOAAccountModel::Account_Details);
}

void DOAAccountListWidget::slotAddAccount()
{
    if (m_model) {
        m_model->setState(DOAAccountModel::Account_Create);
        QModelIndex index;
        m_listView->setCurrentIndex(index);
    }
}

void DOAAccountListWidget::addAccount()
{
    if (m_model) {
        //获取所有的帐户信息
        QMap<QString, DOAAccount *> accountMap = m_model->getAccountMap();
        QMap<QString, DOAAccount *>::iterator iter = accountMap.begin();
        for (; iter != accountMap.end(); ++iter) {
            AccountItemData itemData;
            itemData.accountId = iter.value()->getAccountID();
            itemData.accountName = iter.value()->getAccountName();
            //如果帐户状态为登录成功则不显示错误标志
            itemData.accountState = iter.value()->getAccountState() == DOAAccount::AccountState::Account_Success ? false : true;
            itemData.accountDisplayName = iter.value()->getDisplayName();
            itemData.accountTypeFileName = "doa_caldav";
            m_listModel->addAccount(itemData);
        }
    }
}
