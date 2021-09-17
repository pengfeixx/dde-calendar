/*
* Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
*
* Author:     wangyou <wangyou@uniontech.com>
*
* Maintainer: wangyou <wangyou@uniontech.com>
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
#ifndef ACCOUNTDB_H
#define ACCOUNTDB_H

#include "account_result.h"

#include <QObject>

struct AccountDbPrivate;

class AccountDB : public QObject
{
    Q_OBJECT
public:
    explicit AccountDB(QObject *parent = nullptr);
    ~AccountDB() override;

signals:
    void initDbAsync();
    void selectAccountResult(const AccountResultList &accountResultList);
    void addAccountResult(const QString &accountID, bool result);

public slots:
    void initDb();
    void queryAccountList();
    bool addAccount(const AccountInfo &accountInfo);
    void updateProperty(const QString &accountID, const QString &property, QVariant value);
    void deleteAccount(const QString &accountID);

private:
    void initConnections();
    void initAccountTable();
    AccountDbPrivate *p_ = nullptr;
};

#endif // ACCOUNTDB_H
