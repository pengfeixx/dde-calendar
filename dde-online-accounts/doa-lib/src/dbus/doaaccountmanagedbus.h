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
#ifndef DOAACCOUNTMANAGEDBUS_H
#define DOAACCOUNTMANAGEDBUS_H

#include "consts.h"

#include <QDBusAbstractInterface>
#include <QDBusPendingReply>

#define DBUS_INTEERFACENAME "com.dde.onlineaccount.manager"
#define DBUS_NAME "com.dde.onlineaccount"
#define DBUS_PATH "/com/dde/onlineaccount/manager"

/**
 * @brief The DOAAccountManageDBus class    帐户管理DBus接口
 */
class DOAAccountManageDBus : public QDBusAbstractInterface
{
    Q_OBJECT
public:
    explicit DOAAccountManageDBus(QObject *parent = nullptr);

public:
    /**
     * @brief addAccount        添加帐户
     * @param info              帐户信息
     * @return                  返回结果
     */
    qint32 addAccount(const AddAccountInfo &info);

    /**
     * @brief getAccountList        获取所有帐户信息
     * @return
     */
    DOAAccountList::AccountInfoList getAccountList();

    void loginCancle(const QString &uuid);
signals:

public slots:
    /**
     * @brief propertyChanged  关联的dbus服务属性改变
     * @param msg
     */
    void propertyChanged(const QDBusMessage &msg);
};

#endif // DOAACCOUNTMANAGEDBUS_H
