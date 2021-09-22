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
#ifndef DOAACCOUNTPASSWORD_H
#define DOAACCOUNTPASSWORD_H

#include <QDBusAbstractInterface>
#include <QDBusPendingReply>
#include <QDBusError>

#define PASSWORD_DBUS_INTEERFACENAME "com.dde.onlineaccount.password"
#define PASSWORD_DBUS_NAME "com.dde.onlineaccount"

/**
 * @brief The DOAAccountPassword class      帐户密码操作
 */
class DOAAccountPassword : public QDBusAbstractInterface
{
    Q_OBJECT
public:
    explicit DOAAccountPassword(const QString &path, QObject *parent = nullptr);

    /**
     * @brief getPassword       获取密码
     */
    void getPassword();

    /**
     * @brief changePassword      修改密码
     * @param password            加密后的密码
     */
    void changePassword(const QString &password);
signals:
    /**
     * @brief signalPassword        发送密码
     * @param password              加密后的密码
     */
    void signalPassword(const QString &password);

    /**
     * @brief signalChangePasswordResult    发送修改密码返回结果
     * @param result                        返回结果，true:修改成功，false:修改失败
     */
    void signalChangePasswordResult(const bool result);
public slots:
    /**
     * @brief slotDBusError     服务对象错误信息处理
     * @param error             错误信息
     */
    void slotDBusError(const QDBusError &error);
};

#endif // DOAACCOUNTPASSWORD_H
