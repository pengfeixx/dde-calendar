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
#include "doaaccountlistmodel.h"

DOAAccountListModel::DOAAccountListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int DOAAccountListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_accountList.size();
}

QVariant DOAAccountListModel::data(const QModelIndex &index, int role) const
{
    QVariant ret;
    int row = index.row();

    if (row >= m_accountList.size() || (!index.isValid())) {
        return QVariant();
    }

    AccountItemData accountData = m_accountList.at(row);
    if (role == Qt::UserRole)
        ret = QVariant::fromValue(accountData);
    return ret;
}

bool DOAAccountListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool ret = false;
    int row = index.row();

    if (row >= m_accountList.size() || (!index.isValid())) {
        return false;
    }
    AccountItemData accountData = m_accountList.at(row);

    if (role == Qt::UserRole) {
        AccountItemData setData = value.value<AccountItemData>();
        ret = true;
    }
    m_accountList.replace(row, accountData);
    return ret;
}

void DOAAccountListModel::addAccount(const AccountItemData &account)
{
    if (m_accountList.contains(account))
        return;
    m_accountList.append(account);
}

void DOAAccountListModel::removeAccount(const AccountItemData &account)
{
    if (m_accountList.contains(account)) {
        m_accountList.removeOne(account);
    }
}
