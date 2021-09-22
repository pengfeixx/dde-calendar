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
#ifndef DOAACCOUNTLISTMODEL_H
#define DOAACCOUNTLISTMODEL_H

#include "consts.h"

#include <QAbstractListModel>

class DOAAccountListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit DOAAccountListModel(QObject *parent = nullptr);

    //必须实现的函数
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    /**
     * @brief addAccount        添加帐户信息
     * @param account           帐户信息
     */
    void addAccount(const AccountItemData &account);

    /**
     * @brief removeAccount     移除帐户信息
     * @param accountID         帐户id
     */
    void removeAccount(const QString &accountID);

    /**
     * @brief changeAccount     修改帐户信息
     * @param account           帐户信息
     */
    void changeAccount(const AccountItemData &account);

    /**
     * @brief clearAccount      清空帐户信息
     */
    void clearAccount();
signals:

public slots:
private:
    QList<AccountItemData> m_accountList;
};

#endif // DOAACCOUNTLISTMODEL_H
