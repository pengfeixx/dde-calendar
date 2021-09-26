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
#ifndef DISPLAYTEXT_H
#define DISPLAYTEXT_H

#include <QString>
#include <QObject>

namespace DOA {
//显示名称
const QString displayName = QObject::tr("Network Accounts");

//***********帐户列表界面
namespace AccountListWidget {
//添加网络帐户
const QString addAccountStr = QObject::tr("Add Account");
//无帐户提示
const QString noAccountPrompt = QObject::tr("No accounts yet");
} // namespace AccountListWidget

//***********帐户协议窗口
namespace ProtocolWidget {
//添加网络帐户
const QString addAccountStr = QObject::tr("Add an Account");
//请选择添加的帐户类型
const QString selectAccountProtocol = QObject::tr("Choose an account type");
//CalDAV帐户
const QString calDavName = QObject::tr("CalDAV Account");
} // namespace ProtocolWidget

//***********帐户信息窗口
namespace AccountInfo {
//删除帐户按钮
const QString deleteAccount = QObject::tr("Delete Account");
//*********错误信息
const QString tryAginStr = QObject::tr("try again");
//网络异常
const QString networkError = QObject::tr("Network error, please check and");
//服务器异常
const QString serverError = QObject::tr("Server error, please");

//密码异常
const QString passwordError = QObject::tr("Cannot connect to the account, please check your password");

//********帐户信息
const QString accountInfo = QObject::tr("Account Info");
//用户名
const QString displayName = QObject::tr("User Name");
//用户名称过长提醒
const QString userNameTooLong = QObject::tr("No more than 32 characters please");
//服务器地址
const QString serverAddress = QObject::tr("Server IP");
//帐户
const QString account = QObject::tr("Account");
//密码
const QString password = QObject::tr("Password");

//*******应用于
const QString applyToStr = QObject::tr("Apply to");

} // namespace AccountInfo

//添加界面
namespace LoginWidget {
//添加CalDAV帐户
const QString addCalDav = QObject::tr("Add a CalDAV Account");
//登录方式
const QString loginModel = QObject::tr("Sign-in");
//自动
const QString loginAuto = QObject::tr("Auto");
//手动
const QString LoginManual = QObject::tr("Manual");
//帐户名称
const QString accountName = QObject::tr("Account");
//帐户提示信息
const QString accountPlaceholder = QObject::tr("Email/Phone number");
//密码
const QString accountPassword = QObject::tr("Password");
//密码提示
const QString accountPasswordPlaceholder = QObject::tr("Required");
//服务器地址
const QString serverIp = QObject::tr("Server IP");
//服务器地址提示
const QString serveripPlaceholder = QObject::tr("Required");
//取消按钮
const QString CancelBtn = QObject::tr("Cancel", "button");
//登录按钮
const QString signInBtn = QObject::tr("Sign In", "button");
//只支持QQ帐号提示
const QString supportQQ = QObject::tr("Now only QQ account is supported");
//帐户已添加
const QString accountIsLogin = QObject::tr("Account added already");
//邮箱地址不合法
const QString illegalEmail = QObject::tr("Illegal email address");

//登录验证界面
const QString verification = QObject::tr("Verifying the account...");

//登录超时
const QString loginTimeout = QObject::tr("Login timeout");
//服务器异常
const QString serverError = QObject::tr("Server error, please try again");
//认证失败
const QString loginError = QObject::tr("Cannot verify the account and password");
//重复登录
const QString repeatAdd = QObject::tr("Account added already");
} // namespace LoginWidget

namespace RemoveAccountWidget {
//您确定要删除此帐户吗？
const QString deleteAccount = QObject::tr("Are you sure you want to delete this account?");
//您即将删除此设备中与之关联的所有内容，请谨慎操作
const QString deletePrompt = QObject::tr("You will lose all data associated with the account on this device");
//取消
const QString cancel = QObject::tr("Cancel");
//删除
const QString deletebtn = QObject::tr("Delete");
} // namespace RemoveAccountWidget
} // namespace DOA

#endif // DISPLAYTEXT_H
