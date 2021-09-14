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
    //获取帐户信息
    DOAAccountList::AccountInfoList accountList = m_accountDBus->getAccountList();
    std::sort(accountList.m_infoList.begin(), accountList.m_infoList.end());
    for (int i = 0; i < accountList.accountCount; ++i) {
        DOAAccount *account = new DOAAccount(this);
        account->setAccountInfo(accountList.m_infoList.at(i));
        m_accounts[account->getAccountID()] = account;
    }
    //如果帐号数不为空，则这只第一个为默认帐号
    if (m_accounts.size() > 0) {
        m_currentAccount = m_accounts.begin().value();
    }
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

DOAAccount *DOAAccountModel::getAccount(QString accountID)
{
    DOAAccount *account = nullptr;
    if (m_accounts.contains(accountID)) {
        account = m_accounts.find(accountID).value();
    }
    return account;
}

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
        emit signalSelectAccountChange();
        return true;
    }
    //若不包含则设置为空
    m_currentAccount = nullptr;
    return false;
}

DOAAccount *DOAAccountModel::getCurrentAccount()
{
    return m_currentAccount;
}

qint32 DOAAccountModel::slotAddAccount(const AddAccountInfo &info)
{
    return m_accountDBus->addAccount(info);
}

void DOAAccountModel::slotCancleLogin(const QString &uuid)
{
    m_accountDBus->loginCancle(uuid);
}
