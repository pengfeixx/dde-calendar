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
#include "doaprovider.h"

#include <QDebug>

DOAProvider::DOAProvider(QObject *parent)
    : QObject(parent)
{
}

/**
 * @brief getAccountName    获取帐户名称
 * @return                  返回帐户名称
 */
QString DOAProvider::getAccountName() const
{
    return m_accountName;
}

/**
 * @brief setAccountName    设置帐户名称
 * @param value             帐户名称
 */
void DOAProvider::setAccountName(const QString &value)
{
    m_accountName = value;
}

/**
 * @brief getAccountPassword    获取帐户密码
 * @return                      返回帐户密码
 */
QString DOAProvider::getAccountPassword() const
{
    return m_accountPassword;
}

/**
 * @brief setAccountPassword    设置帐户密码
 * @param value                 帐户密码
 */
void DOAProvider::setAccountPassword(const QString &value)
{
    m_accountPassword = value;
}

/**
 * @brief getUrl        获取服务器地址
 * @return              返回服务器地址
 */
QString DOAProvider::getUrl() const
{
    return m_accountURL;
}

/**
 * @brief setUrl        设置服务器地址
 * @param value         服务器地址
 */
void DOAProvider::setUrl(const QString &value)
{
    m_accountURL = value;
}

/**
 * @brief getPath       获取相关资源路径
 * @return              返回相关资源路径
 */
QString DOAProvider::getPath() const
{
    return m_accountDbusPath;
}

/**
 * @brief setPath       设置相关资源路径
 * @param value         相关资源路径
 */
void DOAProvider::setPath(const QString &value)
{
    m_accountDbusPath = value;
}

/**
 * @brief getProtocol   获取该帐户协议
 * @return              返回帐户协议
 */
DOAProvider::ProtocolType DOAProvider::getProtocol() const
{
    return m_accountType;
}

/**
 * @brief setProtocol   设置帐户协议
 * @param Protocol      帐户协议
 */
void DOAProvider::setProtocol(const ProtocolType &Protocol)
{
    m_accountType = Protocol;
}

/**
 * @brief getDisplayName        获取显示名称
 * @return                      返回显示名称
 */
QString DOAProvider::getDisplayName() const
{
    return m_accountUserName;
}

/**
 * @brief setDisplayName        设置帐户显示名称
 * @param value                 帐户显示名称
 */
void DOAProvider::setDisplayName(const QString &value)
{
    m_accountUserName = value;
}

/**
 * @brief getUri        获取日历数据Uri
 * @return                      返回日历数据Uri
 */
QString DOAProvider::getUri() const
{
    return m_accountURI;
}

/**
 * @brief setUri        设置日历数据Uri
 * @param value                 日历数据Uri
 */
void DOAProvider::setUri(const QString &value)
{
    m_accountURI = value;
}

/**
 * @brief getCreateTime        获取创建时间
 * @return                      返回创建时间
 */
QString DOAProvider::getCreateTime() const
{
    return m_accountCreateTime;
}

/**
 * @brief setCreateTime        设置创建时间
 * @param value                 创建时间
 */
void DOAProvider::setCreateTime(const QString &value)
{
    m_accountCreateTime = value;
}

/**
 * @brief getAccountStat        获取帐户状态
 * @return                      返回帐户状态
 */
DOAProvider::LoginState DOAProvider::getAccountStat() const
{
    return m_accountStat;
}

/**
 * @brief setAccountStat        设置帐户状态
 * @param value                 帐户状态
 */
void DOAProvider::setAccountStat(const LoginState &value)
{
    m_accountStat = value;
}

/**
 * @brief getAccountID        获取帐户ID
 * @return                      返回帐户ID
 */
QString DOAProvider::getAccountID() const
{
    return m_accountID;
}

/**
 * @brief setAccountID        设置帐户ID
 * @param value                 帐户ID
 */
void DOAProvider::setAccountID(const QString &value)
{
    m_accountID = value;
}

/**
 * @brief getLoginType        获取帐户登录方式
 * @return                      返回帐户登录方式
 */
DOAProvider::LoginType DOAProvider::getLoginType() const
{
    return m_loginType;
}

/**
 * @brief setLoginType        设置帐户登录方式
 * @param value                 帐户登录方式
 */
void DOAProvider::setLoginType(const LoginType &value)
{
    m_loginType = value;
}

/**
 * @brief getProviderName        获取服务商名称
 * @return                      返回服务商名称
 */
DOAProvider::AccountType DOAProvider::getProviderName() const
{
    return m_accountProviderType;
}

/**
 * @brief setProviderName        设置服务商名称
 * @param value                 服务商名称
 */
void DOAProvider::setProviderName(const AccountType &value)
{
    m_accountProviderType = value;
}

/**
 * @brief getCalendarDisabled        获取禁用日历标识
 * @return                      返回禁用日历标识
 */
bool DOAProvider::getCalendarDisabled() const
{
    return m_calendarDisabled;
}

/**
 * @brief setCalendarDisabled        设置禁用日历标识
 * @param value                 禁用日历标识
 */
void DOAProvider::setCalendarDisabled(const bool &value)
{
    m_calendarDisabled = value;
}

/**
 * @brief getSSL        获取SSL标识
 * @return                      返回SSL标识
 */
bool DOAProvider::getSSL() const
{
    return m_isSSL;
}

/**
 * @brief setSSL        设置SSL标识
 * @param value                 SSL标识
 */
void DOAProvider::setSSL(const bool &value)
{
    m_isSSL = value;
}
