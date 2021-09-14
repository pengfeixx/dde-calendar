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
#include "doadataconversion.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QDebug>

QString addAccountInfoToJson(const AddAccountInfo &info)
{
    QJsonObject infoJson;
    //登录模式
    infoJson.insert("logintype", info.loginModel);
    //帐户协议
    infoJson.insert("accounttype", info.type);
    //帐户
    infoJson.insert("accountname", info.accountName);
    //帐户密码
    infoJson.insert("accountpassword", info.accountPassword);
    //服务器地址
    infoJson.insert("accounturl", info.serverIP);
    //UUID
    infoJson.insert("uuid", info.UUID);

    // 构建 JSON 文档
    QJsonDocument document;
    document.setObject(infoJson);
    return QString(document.toJson(QJsonDocument::Compact));
}

DOAAccountList::AccountInfoList accountListJsonToAccountInfoList(const QString &str)
{
    DOAAccountList::AccountInfoList accountList;
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(str.toLocal8Bit(), &json_error));
    if (json_error.error != QJsonParseError::NoError) {
        qWarning() << json_error.errorString();
        return accountList;
    }
    QJsonObject accountlistObj = jsonDoc.object();
    QJsonArray accountArray = accountlistObj.value("accountlist").toArray();
    for (int i = 0; i < accountArray.size(); ++i) {
        DOAAccountList::AccountInfo accountInfo;
        QJsonObject accountInfoObj = accountArray.at(i).toObject();
        accountInfo.accountID = accountInfoObj.value("accountid").toString();
        accountInfo.accountName = accountInfoObj.value("accountname").toString();
        accountInfo.accountState = accountInfoObj.value("accountstat").toInt();
        accountInfo.accountDBusPath = accountInfoObj.value("accountdbuspath").toString();
        accountInfo.accountType = accountInfoObj.value("accounttype").toInt();
        accountInfo.accountFlag = accountInfoObj.value("accountflag").toInt();
        accountInfo.displayName = accountInfoObj.value("username").toString();
        accountInfo.accountAddTime = fromeConverDateTime(accountInfoObj.value("createtime").toString());
        accountInfo.serverIP = accountInfoObj.value("accounturl").toString();
        //
        if (accountInfoObj.contains("calendardisable")) {
            accountInfo.applyToCalendarState.isValid = true;
            accountInfo.applyToCalendarState.disEnable = accountInfoObj.value("calendardisable").toBool();
        }
        accountList.m_infoList.append(accountInfo);
    }
    accountList.accountCount = accountlistObj.value("accountcnt").toInt();
    accountList.interfaceStatus = accountlistObj.value("stat").toInt();
    return accountList;
}

QDateTime fromeConverDateTime(const QString &dateTimeStr)
{
    return QDateTime::fromString(dateTimeStr, Qt::ISODate);
}
