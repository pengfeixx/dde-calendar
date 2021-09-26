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
#ifndef DOAACCOUNT_H
#define DOAACCOUNT_H

#include "doaapplytoobject.h"
#include "consts.h"

#include <QObject>
#include <QVector>
#include <QDateTime>

class DOAAccountDBus;
class DOAAccountPassword;
/**
 * @brief The account class 网络帐户数据
 */
class DOAAccount : public QObject
{
    Q_OBJECT
public:
    //帐户协议
    enum AccountProtocol {
        Protocol_CalDav = 1 //caldav协议
        ,
        Protocol_Exchange //exchange协议
        ,
        Protocol_LDAP //LDAP协议
    };
    //帐户状态
    enum AccountState {
        Account_Success //登录成功
        ,
        Account_TimeOut //登录超时
        ,
        Account_ServerException //服务器异常
        ,
        Account_AuthenticationFailed //认证失败
    };
    explicit DOAAccount(QObject *parent = nullptr);

    /**
     * @brief getAccountName    获取帐户名称
     * @return                  返回帐户名称
     */
    QString getAccountName() const;

    /**
     * @brief setAccountName    设置帐户名称
     * @param value             帐户名称
     */
    void setAccountName(const QString &value);

    /**
     * @brief getAccountPassword    获取帐户密码
     * @return                      返回帐户密码
     */
    QString getAccountPassword() const;

    /**
     * @brief setAccountPassword    设置帐户密码
     * @param value                 帐户密码
     */
    void setAccountPassword(const QString &value);

    /**
     * @brief getDisplayName        获取显示名称
     * @return                      返回显示名称
     */
    QString getUserName() const;

    /**
     * @brief setUserName        设置帐户显示名称
     * @param value                 帐户显示名称
     */
    void setUserName(const QString &value);

    /**
     * @brief getUrl        获取服务器地址
     * @return              返回服务器地址
     */
    QString getUrl() const;

    /**
     * @brief setUrl        设置服务器地址
     * @param value         服务器地址
     */
    void setUrl(const QString &value);

    /**
     * @brief getPath       获取相关资源路径
     * @return              返回相关资源路径
     */
    QString getPath() const;

    /**
     * @brief setPath       设置相关资源路径
     * @param value         相关资源路径
     */
    void setPath(const QString &value);

    /**
     * @brief getProtocol   获取该帐户协议
     * @return              返回帐户协议
     */
    AccountProtocol getProtocol() const;

    /**
     * @brief setProtocol   设置帐户协议
     * @param Protocol      帐户协议
     */
    void setProtocol(const AccountProtocol &Protocol);

    /**
     * @brief addApplyObject    添加应用于相关应用
     * @param applyObject       相关应用
     */
    void addApplyObject(const DOAApplyToObject &applyObject);

    /**
     * @brief getApplyObject     获取应用于的所有应用
     * @return                   返回
     */
    QVector<DOAApplyToObject> getApplyObject() const;

    /**
     * @brief getAccountID      获取帐户id
     * @return                  返回帐户id
     */
    QString getAccountID() const;

    /**
     * @brief setAccountID      设置帐户id
     * @param value             帐户id
     */
    void setAccountID(const QString &value);

    /**
     * @brief getState       获取帐户状态
     * @return
     */
    AccountState getAccountState() const;

    /**
     * @brief setAccountState      设置帐户状态
     * @param isError
     */
    void setAccountState(AccountState state);

    /**
     * @brief setAddAccountDateTime     设置添加帐户时间
     * @param addDateTime
     */
    void setAddAccountDateTime(const QDateTime &addDateTime);

    /**
     * @brief getAddAccountDateTime     获取添加帐户时间
     * @return
     */
    QDateTime getAddAccountDateTime() const;

    /**
     * @brief setAccountDBusPath        设置帐户DBus路径
     * @param dbusPath
     */
    void setAccountDBusPath(const QString &dbusPath);

    /**
     * @brief setAccountInfo            设置帐户信息
     * @param info
     */
    void setAccountInfo(const DOAAccountList::AccountInfo &info);

    /**
     * @brief updateUserName            更新用户名
     * @param userName
     */
    void updateUserName(const QString &userName);

    void updateApplyTo(const DOAApplyToObject &app);

    void updatePassword(const QString &password);

public:
    //信息调试打印
    friend QDebug operator<<(QDebug debug, const DOAAccount &account);
    friend QDebug operator<<(QDebug debug, const DOAAccount *account);

private:
    /**
     * @brief createDBus       创建与帐户关联的DBus
     */
    void createDBus();

    /**
     * @brief getProtocolByindex        根据协议编号获取对应的协议
     * @param index
     * @return
     */
    AccountProtocol getProtocolByindex(const int index);

    /**
     * @brief getStateByIndex           根据帐户状态编号获取对应的状态
     * @param index
     * @return
     */
    AccountState getStateByIndex(const int index);
signals:
    void signalUserNameChanged(const QString &accountID) const;

    void signalPasswordChanged(const QString &accountID) const;

    void signalAccountStatusChanged(const QString &accountID) const;
public slots:
    /**
     * @brief slotUserNameChanged       用户名改变
     * @param userName                  用户名
     */
    void slotUserNameChanged(const QString &userName);

    /**
     * @brief slotCalendarDisabled      是否应用于日历属性改变
     * @param disabled
     */
    void slotCalendarDisabled(bool disabled);

    /**
     * @brief slotGetPassword       处理加密后的密码
     * @param password              加密后的密码
     */
    void slotGetPassword(const QString &password);

    /**
     * @brief slotRemove            移除该帐户
     */
    void slotRemove();

    /**
     * @brief slotAccountStatus            更新状态
     */
    void slotAccountStatus(int accountStatus);

    /**
     * @brief slotCheckState            检测状态
     */
    void slotCheckState();

private:
    QString m_accountID = ""; //帐户id
    QString m_accountName = ""; //帐户名称
    QString m_accountPassword = ""; //帐户密码
    QString m_displayName = ""; //帐户显示名称
    QString m_url = ""; //帐户服务器地址
    QString m_path = ""; //帐户路径
    QString m_DBusPath = ""; //帐户DBus路径
    AccountProtocol m_Protocol = Protocol_CalDav; //协议类型
    AccountState m_state = Account_Success; //帐户状态
    QDateTime m_addDateTime; //添加帐户时间
    QVector<DOAApplyToObject> m_applyObject {}; //应用于相关应用集
    DOAAccountDBus *m_accountDBus = nullptr; //每个帐户对应一个帐户信息DBus服务
    DOAAccountPassword *m_passwordDBus = nullptr; //每个帐户对应一个密码相关的DBus服务
};

#endif // DOAACCOUNT_H
