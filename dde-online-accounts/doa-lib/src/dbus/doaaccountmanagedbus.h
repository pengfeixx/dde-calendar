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
#include <QDBusError>

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
     */
    void addAccount(const AddAccountInfo &info);

    /**
     * @brief getAccountList        获取所有帐户信息
     */
    void getAccountList();

    /**
     * @brief loginCancle           取消登录
     * @param uuid                  对应的uuid
     */
    void loginCancle(const QString &uuid);

private:
    /**
     * @brief accountListChangeHandle     帐户列表信息改变处理
     * @param infoStr               改变信息
     */
    void accountListChangeHandle(const QString &infoStr);

signals:
    /**
     * @brief signalAddAccountResults       发送添加帐户返回结果
     * @param results
     */
    void signalAddAccountResults(int results);

    /**
     * @brief signalGetAccountList          发送获取所有帐户信息
     * @param infoList
     */
    void signalGetAccountList(const DOAAccountList::AccountInfoList &infoList);

    /**
     * @brief signalLoginCancle             发送取消登录成功信息
     */
    void signalLoginCancle();

    /**
     * @brief signalAddAccountInfo          发送增加的帐户信息
     * @param info
     */
    void signalAddAccountInfo(const DOAAccountList::AccountInfo &info);

    /**
     * @brief signalDeleteAccount           发送移除的帐户id
     * @param accountID
     */
    void signalDeleteAccount(const QString &accountID);
public slots:
    /**
     * @brief propertyChanged  关联的dbus服务属性改变
     * @param msg
     */
    void propertyChanged(const QDBusMessage &msg);

    /**
     * @brief slotDBusError     服务对象错误信息处理
     * @param error             错误信息
     */
    void slotDBusError(const QDBusError &error);

    /**
     * @brief slotGetAccountList        处理获取到的所有帐户信息
     * @param infoList                  所有帐户信息
     */
    void slotGetAccountList(const QString &infoList);
};

#endif // DOAACCOUNTMANAGEDBUS_H
