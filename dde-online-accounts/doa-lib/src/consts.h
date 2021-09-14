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
#ifndef CONSTS_H
#define CONSTS_H

#include <QString>
#include <QDateTime>
#include <QMetaType>
#include <QVector>

//帐户列表显示内容格式
struct AccountItemData {
    QString accountId = ""; //帐户id
    QString accountName = ""; //帐户名称
    QString accountDisplayName = ""; //帐户用户名
    bool accountState = true; //帐户状态
    QDateTime accountAddDateTime; //帐户添加时间
    QString accountTypeFileName = "";
    bool operator==(const AccountItemData &app) const
    {
        return this->accountId == app.accountId;
    }
    bool operator<(const AccountItemData &app) const
    {
        return this->accountAddDateTime < app.accountAddDateTime;
    }
};
Q_DECLARE_METATYPE(AccountItemData)

//帐户类型
enum ProtocolType {
    Type_CalDAV //caldav协议
};

struct AccountProtocol {
    ProtocolType protocolType = ProtocolType::Type_CalDAV;
    QString protocolDisplayName;
};
Q_DECLARE_METATYPE(AccountProtocol)

//创建帐户信息
struct AddAccountInfo {
    int type = 1; //协议    1:CALDAV
    int loginModel = 1; //登录模式  1:自动 2：手动
    QString accountName = ""; //帐户名称
    QString accountPassword = ""; //帐户密码
    QString serverIP = ""; //服务器地址
    QString UUID = ""; //登录帐号标识
};
Q_DECLARE_METATYPE(AddAccountInfo)

//获取的帐户列表信息
namespace DOAAccountList {
//应用于相关应用
struct ApplyState {
    bool isValid = false; //是否有效，默认无效
    bool disEnable = true; //使无效
};
//获取的帐户信息
struct AccountInfo {
    QString accountName = ""; //帐户
    QString accountID = ""; //帐户id
    int accountState = 0; //帐户状态
    QString accountDBusPath = ""; //帐户DBus路径
    int accountType = 0; //帐户协议
    int accountFlag = 0; //帐户提供商
    QString displayName = ""; //用户名
    QString serverIP = ""; //帐户服务器地址
    QDateTime accountAddTime; //帐户添加时间
    ApplyState applyToCalendarState; //应用于日历状态
    ApplyState applyToEMailState; //应用于邮箱状态
    bool operator<(const AccountInfo &info) const
    {
        return accountAddTime < info.accountAddTime;
    }
};

struct AccountInfoList {
    QVector<AccountInfo> m_infoList {}; //帐户信息
    int accountCount = 0; //帐户个数
    int interfaceStatus = 0; //接口状态
};
} // namespace DOAAccountList

Q_DECLARE_METATYPE(DOAAccountList::AccountInfo)
Q_DECLARE_METATYPE(DOAAccountList::AccountInfoList)

#endif // CONSTS_H
