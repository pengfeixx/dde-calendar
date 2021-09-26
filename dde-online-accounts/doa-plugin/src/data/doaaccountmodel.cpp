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
#include "doaaccountmodel.h"
#include "consts.h"

#include <QDebug>

DOAAccountModel::DOAAccountModel(QObject *parent)
    : QObject(parent)
{
    m_accountDBus = new DOAAccountManageDBus(this);

    connect(m_accountDBus, &DOAAccountManageDBus::signalAddAccountResults, this, &DOAAccountModel::signalAddAccountResults);
    connect(m_accountDBus, &DOAAccountManageDBus::signalGetAccountList, this, &DOAAccountModel::slotGetAccountList);
    connect(m_accountDBus, &DOAAccountManageDBus::signalAddAccountInfo, this, &DOAAccountModel::slotGetAccountInfo);
    connect(m_accountDBus, &DOAAccountManageDBus::signalDeleteAccount, this, &DOAAccountModel::slotGetDeleteAccountID);
    //获取帐户信息
    m_accountDBus->getAccountList();
}

//获取帐户界面的状态
DOAAccountModel::AccountWidgetState DOAAccountModel::state() const
{
    return m_state;
}

//设置帐户界面的状态
void DOAAccountModel::setState(const AccountWidgetState &state)
{
    //如果设置显示状态跟当前状态不一致则更新
    if (m_state != state) {
        m_state = state;
        emit signalChangeState();
    }
}

//获取帐户信息
DOAAccount *DOAAccountModel::getAccount(QString accountID)
{
    DOAAccount *account = nullptr;
    if (m_accounts.contains(accountID)) {
        account = m_accounts.find(accountID).value();
    }
    return account;
}

//获取所有帐户信息
QMap<QString, DOAAccount *> DOAAccountModel::getAccountMap()
{
    return m_accounts;
}

//设置当前显示帐户信息
bool DOAAccountModel::setCurrentAccountByID(QString accountID)
{
    //如果map中包含对应的帐户id则标记对应的帐户信息
    if (m_accounts.contains(accountID)) {
        //如果存在当前用户缓存信息且设置帐户id为当前显示帐户id 则退出
        if (m_currentAccount && m_currentAccount->getAccountID() == accountID) {
            return true;
        }
        m_currentAccount = m_accounts[accountID];
        m_currentAccount->slotCheckState();
        emit signalSelectAccountChanged();
        return true;
    }
    //若不包含则设置为空
    m_currentAccount = nullptr;
    return false;
}

//获取当前帐户信息
DOAAccount *DOAAccountModel::getCurrentAccount()
{
    return m_currentAccount;
}

DOAAccount *DOAAccountModel::createAccount(const DOAAccountList::AccountInfo &info)
{
    DOAAccount *account = new DOAAccount(this);
    account->setAccountInfo(info);
    connect(account, &DOAAccount::signalUserNameChanged, this, &DOAAccountModel::signalUserNameChanged);
    connect(account, &DOAAccount::signalPasswordChanged, this, &DOAAccountModel::slotAccountPasswordChange);
    connect(account, &DOAAccount::signalAccountStatusChanged, this, &DOAAccountModel::slotAccountStatusChange);
    return account;
}

//添加帐户
void DOAAccountModel::slotAddAccount(const AddAccountInfo &info)
{
    m_accountDBus->addAccount(info);
}

//取消登录
void DOAAccountModel::slotCancleLogin(const QString &uuid)
{
    m_accountDBus->loginCancle(uuid);
}

//处理获取到的所有帐户信息
void DOAAccountModel::slotGetAccountList(const DOAAccountList::AccountInfoList &infoList)
{
    DOAAccountList::AccountInfoList accountList = infoList;
    //进行排序，按照添加时间
    std::sort(accountList.m_infoList.begin(), accountList.m_infoList.end());
    for (int i = 0; i < accountList.accountCount; ++i) {
        DOAAccount *account = createAccount(accountList.m_infoList.at(i));
        m_accounts[account->getAccountID()] = account;
    }
    //如果帐号数不为空，则设置第一个为默认帐号
    if (m_accounts.size() > 0) {
        m_currentAccount = m_accounts.begin().value();
        setState(Account_Details);
    } else {
        setState(Account_Init);
    }
    emit signalGetAccountListSuccess();
    emit signalSelectAccountChanged();
}

//处理获取到添加的帐户信息
void DOAAccountModel::slotGetAccountInfo(const DOAAccountList::AccountInfo &info)
{
    //如果列表中包含对应的帐户id则退出
    if (m_accounts.contains(info.accountID)) {
        qWarning() << "The list contains the corresponding account," << info.accountID;
        return;
    }
    DOAAccount *account = createAccount(info);
    m_accounts[account->getAccountID()] = account;
    m_currentAccount = account;
    emit signalAddAccountInfo(account);
    setState(Account_Details);
    emit signalSelectAccountChanged();
}

//处理获取到的移除帐户id
void DOAAccountModel::slotGetDeleteAccountID(const QString &accountID)
{
    if (m_accounts.contains(accountID)) {
        m_accounts[accountID]->deleteLater();
        m_accounts.remove(accountID);
        emit signalDeleteAccount(accountID);
        //如果帐号数不为空，则这只第一个为默认帐号
        if (m_accounts.size() > 0) {
            m_currentAccount = m_accounts.begin().value();
            emit signalSelectAccountChanged();
        } else {
            setState(Account_Init);
        }
    }
}

//更新帐户密码
void DOAAccountModel::slotAccountPasswordChange(const QString &accountID)
{
    if (m_currentAccount == m_accounts.find(accountID).value()) {
        //只有当前详情帐户密码改变时才发送通知
        emit signalPasswordChanged(accountID);
    }
}

//更新帐户状态
void DOAAccountModel::slotAccountStatusChange(const QString &accountID)
{
    if (m_currentAccount == m_accounts.find(accountID).value()) {
        //只有当前详情帐户状态改变时才发送通知
        emit signalAccountStatusChanged(accountID);
    }
}
