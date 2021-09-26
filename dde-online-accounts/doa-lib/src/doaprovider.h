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
#ifndef DOAPROVIDER_H
#define DOAPROVIDER_H

#include <QObject>

class DOAProvider : public QObject
{
    Q_OBJECT
public:
    explicit DOAProvider(QObject *parent = nullptr);

    //帐户类型
    enum ProtocolType {
        CALDAV = 1,
        EXCHANGE,
        LDAP,
    };
    Q_ENUM(ProtocolType)

    //帐户类型
    enum AccountType {
        QQ = 1,
        FEISHU
    };
    Q_ENUM(AccountType)

    //登录模式
    enum LoginType {
        AUTO = 1,
        MANUAL,
        ADVANCED
    };
    Q_ENUM(LoginType)

    //登录状态码
    enum LoginState {
        SUCCESS = 0, //成功
        TIMEOUT, //超时
        UserCancel, //用户取消
        ServerError, //服务器异常
        AuthenticationFailed, //认证失败
        AccountNameError, //帐户名格式错误
        PassWordError, //密码错误 格式、加解密失败
        AccountNameEmpty, //帐户名为空
        PassWordEmpty, //密码为空
        DatatError, //请求数据错误
        RepeatLogin, //重复登录
        DBError //数据库错误
    };
    Q_ENUM(LoginState)

    virtual LoginState login() = 0;
    virtual void loginCancel() = 0;

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
    ProtocolType getProtocol() const;

    /**
     * @brief setProtocol   设置帐户协议
     * @param Protocol      帐户协议
     */
    void setProtocol(const ProtocolType &Protocol);

    /**
     * @brief getDisplayName        获取显示名称
     * @return                      返回显示名称
     */
    QString getDisplayName() const;

    /**
     * @brief setDisplayName        设置帐户显示名称
     * @param value                 帐户显示名称
     */
    void setDisplayName(const QString &value);

    /**
     * @brief getUri        获取日历数据Uri
     * @return                      返回日历数据Uri
     */
    QString getUri() const;

    /**
     * @brief setUri        设置日历数据Uri
     * @param value                 日历数据Uri
     */
    void setUri(const QString &value);

    /**
     * @brief getCreateTime        获取创建时间
     * @return                      返回创建时间
     */
    QString getCreateTime() const;

    /**
     * @brief setCreateTime        设置创建时间
     * @param value                 创建时间
     */
    void setCreateTime(const QString &value);

    /**
     * @brief getAccountStat        获取帐户状态
     * @return                      返回帐户状态
     */
    LoginState getAccountStat() const;

    /**
     * @brief setAccountStat        设置帐户状态
     * @param value                 帐户状态
     */
    void setAccountStat(const LoginState &value);

    /**
     * @brief getAccountID        获取帐户ID
     * @return                      返回帐户ID
     */
    QString getAccountID() const;

    /**
     * @brief setAccountID        设置帐户ID
     * @param value                 帐户ID
     */
    void setAccountID(const QString &value);

    /**
     * @brief getLoginType        获取帐户登录方式
     * @return                      返回帐户登录方式
     */
    LoginType getLoginType() const;

    /**
     * @brief setLoginType        设置帐户登录方式
     * @param value                 帐户登录方式
     */
    void setLoginType(const LoginType &value);

    /**
     * @brief getProviderName        获取服务商名称
     * @return                      返回服务商名称
     */
    AccountType getProviderName() const;

    /**
     * @brief setProviderName        设置服务商名称
     * @param value                 服务商名称
     */
    void setProviderName(const AccountType &value);

    /**
     * @brief getCalendarDisabled        获取禁用日历标识
     * @return                      返回禁用日历标识
     */
    bool getCalendarDisabled() const;

    /**
     * @brief setCalendarDisabled        设置禁用日历标识
     * @param value                 禁用日历标识
     */
    void setCalendarDisabled(const bool &value);

    /**
     * @brief getSSL        获取SSL标识
     * @return                      返回SSL标识
     */
    bool getSSL() const;

    /**
     * @brief setSSL        设置SSL标识
     * @param value                 SSL标识
     */
    void setSSL(const bool &value);

    /**
     * @brief getAccountPort 获取端口号
     * @return 端口号
     */
    inline QString getAccountPort() const
    {
        return m_accountPort;
    }

    /**
     * @brief setAccountPort 设置端口号
     * @param accountPort 端口号
     */
    inline void setAccountPort(const QString &accountPort)
    {
        m_accountPort = accountPort;
    }

private:
    //帐户类型
    ProtocolType m_accountType {CALDAV};
    //密码
    QString m_accountPassword = "";
    //服务器地址
    QString m_accountURL = "";
    //接口请求对账=服务器地址/接口路径
    QString m_accountURI = "";
    //用户名
    QString m_accountUserName = "";
    //帐户名
    QString m_accountName = "";
    //请求端口
    QString m_accountPort = "";
    //帐户编号唯一
    QString m_accountID = "";
    //登录类型 自动 高级 手动
    LoginType m_loginType {AUTO};
    //帐户Dbus类型
    QString m_accountDbusPath = "";
    //帐户服务商名称
    AccountType m_accountProviderType {QQ};
    //帐户状态
    LoginState m_accountStat {ServerError};
    //是否使用SSL 默认true
    bool m_isSSL {true};
    //是否禁用同步日历 默认false
    bool m_calendarDisabled {false};
    //创建时间
    QString m_accountCreateTime = "";
};

#endif // DOAPROVIDER_H
