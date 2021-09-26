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
#ifndef DOAACCOUNTDBUS_H
#define DOAACCOUNTDBUS_H

#include <QDBusAbstractInterface>

#define ACCOUNT_DBUS_INTEERFACENAME "com.dde.onlineaccount.account"
#define ACCOUNT_DBUS_NAME "com.dde.onlineaccount"

/**
 * @brief The DOAAccountDBus class      具体帐户的DBus
 */
class DOAAccountDBus : public QDBusAbstractInterface
{
    Q_OBJECT
public:
    explicit DOAAccountDBus(const QString &path, QObject *parent = nullptr);

    /**
     * @brief remove        删除帐户
     * @return
     */
    bool remove();

    /**
     * @brief checkAccountState     更新帐户状态
     */
    void checkAccountState();

    /**
     * @brief getCalendarDisabled       获取是否应用于日历
     * @return
     */
    bool getCalendarDisabled();

    /**
     * @brief setCalendarDisabled       设置是否应用与日历
     * @param disabled
     * @return
     */
    bool setCalendarDisabled(bool disabled);

    /**
     * @brief getUserName           获取用户名
     * @return
     */
    QString getUserName();

    /**
     * @brief setUserName       设置用户名
     * @param userName          用户名
     * @return
     */
    bool setUserName(const QString &userName);

    /**
     * @brief getAccountID      获取帐户id
     * @return
     */
    QString getAccountID();

    /**
     * @brief getProviderName     获取帐户服务提供商,比如QQ等
     * @return
     */
    int getProviderName();

    /**
     * @brief getProviderType    获取帐户类型,比如CalDav等
     * @return
     */
    int getProviderType();

private:
    /**
     * @brief getPropertyByName     根据属性名称获取属性值
     * @param porpertyName          属性名称
     * @return
     */
    QVariant getPropertyByName(const char *porpertyName);

    /**
     * @brief setPropertyByName     根据属性名称设置属性值
     * @param porpertyName          属性名称
     * @param value                 设置的属性
     * @return                      是否设置成功
     */
    bool setPropertyByName(const char *porpertyName, const QVariant &value);
signals:

    /**
     * @brief signalUserNameChanged     用户名改变
     * @param userName
     */
    void signalUserNameChanged(const QString &userName);

    /**
     * @brief signalCalendarDisabled      是否应用于日历改变
     * @param disabled
     */
    void signalCalendarDisabled(bool disabled);

    /**
     * @brief signalStatusChanged      状态改变信号
     * @param status            状态
     */
    void signalStatusChanged(const int status);
public slots:
    /**
     * @brief PropertiesChanged     监听相关属性
     * @param msg
     */
    void propertiesChanged(const QDBusMessage &msg);
};

#endif // DOAACCOUNTDBUS_H
