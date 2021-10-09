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
    , m_listModel(new DOAAccountListModel(m_listView))
    , m_listDelegate(new DOAAccountListItemDelegate(m_listView))
    , m_stackedWidget(new DStackedWidget)
{
    initWidget();

    connect(m_addAccountBtn, &DFloatingButton::clicked, this, &DOAAccountListWidget::slotClickeAddAccount);
    connect(m_listDelegate, &DOAAccountListItemDelegate::signalSelectItem, this, &DOAAccountListWidget::slotSelectItem);
}

DOAAccountListWidget::~DOAAccountListWidget()
{
    //释放资源，取消对应关联
}

void DOAAccountListWidget::setModel(DOAAccountModel *model)
{
    if (model && m_model != model) {
        if (m_model) {
            //解除连接
            disconnect(m_model, &DOAAccountModel::signalDeleteAccount, this, &DOAAccountListWidget::slotGetDeleteAccount);
            disconnect(m_model, &DOAAccountModel::signalAddAccountInfo, this, &DOAAccountListWidget::slotGetAddAccount);
            disconnect(m_model, &DOAAccountModel::signalChangeState, this, &DOAAccountListWidget::slotShowStateChanged);
            disconnect(m_model, &DOAAccountModel::signalUserNameChanged, this, &DOAAccountListWidget::slotAccountItemDataChanged);
            disconnect(m_model, &DOAAccountModel::signalAccountStatusChanged, this, &DOAAccountListWidget::slotAccountItemDataChanged);
            disconnect(m_model, &DOAAccountModel::signalGetAccountListSuccess, this, &DOAAccountListWidget::slotGetAccountListSuccess);
        }
        m_model = model;
        //添加信号连接
        connect(m_model, &DOAAccountModel::signalDeleteAccount, this, &DOAAccountListWidget::slotGetDeleteAccount);
        connect(m_model, &DOAAccountModel::signalAddAccountInfo, this, &DOAAccountListWidget::slotGetAddAccount);
        connect(m_model, &DOAAccountModel::signalChangeState, this, &DOAAccountListWidget::slotShowStateChanged);
        connect(m_model, &DOAAccountModel::signalUserNameChanged, this, &DOAAccountListWidget::slotAccountItemDataChanged);
        connect(m_model, &DOAAccountModel::signalAccountStatusChanged, this, &DOAAccountListWidget::slotAccountItemDataChanged);
        slotGetAccountListSuccess();
        connect(m_model, &DOAAccountModel::signalGetAccountListSuccess, this, &DOAAccountListWidget::slotGetAccountListSuccess);
    }
}

void DOAAccountListWidget::initWidget()
{
    //新建用户按钮
    m_addAccountBtn->setFixedSize(50, 50);
    m_addAccountBtn->setToolTip(tr("Add Account"));
    m_addAccountBtn->setAccessibleName("Add Account");
    //无帐户信息提示
    m_promptLbl->setText(tr("No accounts yet"));
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

//点击添加帐户事件
void DOAAccountListWidget::slotClickeAddAccount()
{
    if (m_model) {
        m_model->setState(DOAAccountModel::Account_Create);
        QModelIndex index;
        m_listView->setCurrentIndex(index);
    }
}

//添加获取到添加的帐户信息
void DOAAccountListWidget::slotGetAddAccount(const DOAAccount *info)
{
    AccountItemData itemData = getItemData(info);
    m_listModel->addAccount(itemData);
    qDebug() << info->getAccountID();
    qDebug() << info->getUserName();
    QModelIndex index;
    int count = m_listModel->rowCount(index);
    //设置刚刚添加的为选中状态
    index = m_listModel->index(count - 1);
    m_listView->setCurrentIndex(index);
}

//移除获取到需要移除的帐户ID
void DOAAccountListWidget::slotGetDeleteAccount(const QString &accountID)
{
    m_listModel->removeAccount(accountID);
    QModelIndex index;
    if (m_listModel->rowCount(index) > 0) {
        //设置第一个为选中状态
        index = m_listModel->index(0);
        m_listView->setCurrentIndex(index);
    }
}

//页面显示状态
void DOAAccountListWidget::slotShowStateChanged()
{
    if (m_model) {
        DOAAccountModel::AccountWidgetState state = m_model->state();
        switch (state) {
        case DOAAccountModel::Account_Init:
            m_stackedWidget->setCurrentIndex(0);
            m_addAccountBtn->setEnabled(false);
            break;
        default:
            m_stackedWidget->setCurrentIndex(1);
            m_addAccountBtn->setEnabled(true);
            break;
        }
    }
}

//帐户项数据发生改变
void DOAAccountListWidget::slotAccountItemDataChanged(const QString &accountID)
{
    if (m_model) {
        //数据更新时会取消item选中状态，先获取当前选中项，待数据更新后重新设置当期选中项
        QModelIndex index = m_listView->currentIndex();
        DOAAccount *account = m_model->getAccount(accountID);
        AccountItemData itemData = getItemData(account);
        m_listModel->changeAccount(itemData);
        m_listView->setCurrentIndex(index);
    }
}

//所有用户信息获取成功处理
void DOAAccountListWidget::slotGetAccountListSuccess()
{
    if (m_model->getAccountMap().size() > 0) {
        getAccountList();
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

//获取帐户列表信息
void DOAAccountListWidget::getAccountList()
{
    if (m_model) {
        //先清空
        m_listModel->clearAccount();
        //获取所有的帐户信息
        QMap<QString, DOAAccount *> accountMap = m_model->getAccountMap();
        QMap<QString, DOAAccount *>::iterator iter = accountMap.begin();
        for (; iter != accountMap.end(); ++iter) {
            AccountItemData itemData = getItemData(iter.value());
            m_listModel->addAccount(itemData);
        }
    }
}

AccountItemData DOAAccountListWidget::getItemData(const DOAAccount *account)
{
    AccountItemData itemData {};
    if (account) {
        itemData.accountId = account->getAccountID();
        itemData.accountName = account->getAccountName();
        //如果帐户状态为登录成功则不显示错误标志
        itemData.accountState = account->getAccountState() == DOAAccount::AccountState::Account_Success ? false : true;
        itemData.accountDisplayName = account->getUserName();
        //TODO 根据具体协议显示不同的协议图标
        itemData.accountTypeFileName = "doa_caldav";
    }
    return itemData;
}
