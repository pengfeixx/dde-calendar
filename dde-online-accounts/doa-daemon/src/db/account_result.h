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
#ifndef ACCOUNT_RESULT_H
#define ACCOUNT_RESULT_H

#include <QString>

//数据库数据结构
struct AccountInfo {
    QString m_accountID; //帐户ID
    QString m_accountUserName; //帐户用户名
    QString m_accountName; //帐户名
    QString m_accountURL; //帐户服务器地址
    QString m_accountPassword; //帐户密码
    QString m_accountPort; //帐户端口
    QString m_accountType; //帐户类型
    bool m_isSSL; //是否SSL
    QString m_state; //帐户状态
    QString m_accountDbusPath; //帐户Dbus服务路径
    QString m_accountProviderType; //帐户服务商名称
    bool m_calendarDisabled; //是否禁用日历同步
    QString m_accountURI; //服务器URI
    QString m_accountCreateTime; //创建时间
};

typedef QList<AccountInfo> AccountResultList;

#endif // ACCOUNT_RESULT_H
