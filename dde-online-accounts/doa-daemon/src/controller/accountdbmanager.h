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
#ifndef ACCOUNTDBMANAGER_H
#define ACCOUNTDBMANAGER_H

#include "db/accountdb.h"

#include <QObject>
#include <QVariant>

class QThread;
class AccountDB;

class AccountDBManager : public QObject
{
    Q_OBJECT
public:
    explicit AccountDBManager(QObject *parent = nullptr);
    ~AccountDBManager() override;

signals:
    //查询帐户列表
    void sign_selectAccountList();
    //查询帐户列表结果
    void sign_selectAccountResult(const AccountResultList &accountResultList);
    //增加帐户
    bool sign_addAccount(const AccountInfo &accountInfo);
    //增加帐户结果
    void sign_addAccountResult(const QString &accountID, bool result);
    //修改字段
    void sign_updateProperty(const QString &accountID, const QString &property, QVariant value);
    //删除帐户
    void sign_deleteAccount(const QString &accountID);
public slots:

private:
    void initDbManager();

    AccountDB *db_;
    QThread *db_thread_;
};

#endif // ACCOUNTDBMANAGER_H
