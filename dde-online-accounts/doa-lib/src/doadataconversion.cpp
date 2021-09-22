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
        accountList.m_infoList.append(accountJsonObjectToInfo(accountArray.at(i).toObject()));
    }
    accountList.accountCount = accountlistObj.value("accountcnt").toInt();
    accountList.interfaceStatus = accountlistObj.value("stat").toInt();
    return accountList;
}

QDateTime fromeConverDateTime(const QString &dateTimeStr)
{
    return QDateTime::fromString(dateTimeStr, Qt::ISODate);
}

//将帐户信息jsonObject转换为AccountInfo结构体
DOAAccountList::AccountInfo accountJsonObjectToInfo(const QJsonObject &jsonObject)
{
    DOAAccountList::AccountInfo accountInfo;
    accountInfo.accountID = jsonObject.value("accountid").toString();
    accountInfo.accountName = jsonObject.value("accountname").toString();
    accountInfo.accountState = jsonObject.value("accountstat").toInt();
    accountInfo.accountDBusPath = jsonObject.value("accountdbuspath").toString();
    accountInfo.accountType = jsonObject.value("accounttype").toInt();
    accountInfo.accountFlag = jsonObject.value("accountflag").toInt();
    accountInfo.displayName = jsonObject.value("username").toString();
    accountInfo.accountAddTime = fromeConverDateTime(jsonObject.value("createtime").toString());
    accountInfo.serverIP = jsonObject.value("accounturl").toString();
    //
    if (jsonObject.contains("calendardisable")) {
        accountInfo.applyToCalendarState.isValid = true;
        accountInfo.applyToCalendarState.disEnable = jsonObject.value("calendardisable").toBool();
    }
    return accountInfo;
}

QList<QVariant> accountListChangeParameterAnalysis(const QString &msg)
{
    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(msg.toLocal8Bit(), &json_error));
    if (json_error.error != QJsonParseError::NoError) {
        qWarning() << json_error.errorString();
        return QList<QVariant> {};
    }
    QList<QVariant> result {};
    QJsonObject accountlistObj = jsonDoc.object();
    QString iterfaceoper = accountlistObj.value("iterfaceoper").toString();
    int stat = accountlistObj.value("stat").toInt();
    QJsonObject accountContent = accountlistObj.value("iterfacecontent").toObject();
    result << iterfaceoper << stat << accountContent;
    return result;
}

DOAAccountList::AccountInfo accountJsonObjectToInfo(const QVariant &json)
{
    return accountJsonObjectToInfo(json.toJsonObject());
}

QString remvoeAccountJsonObjectToInfo(const QVariant &json)
{
    QJsonObject jsonObject = json.toJsonObject();
    return jsonObject.value("accountid").toString();
}
