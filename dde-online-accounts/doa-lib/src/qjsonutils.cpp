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
#include "qjsonutils.h"
#include "doaprovider.h"

#include <QDebug>

QString QJsonUtils::getJsonString(const QMap<QString, QVariant> &jsonMap)
{
    if (jsonMap.size() == 0) {
        return "";
    }

    QJsonDocument doc = QJsonDocument::fromVariant(QVariant(jsonMap));
    QByteArray jsonArray = doc.toJson(QJsonDocument::Compact);

    return QString(jsonArray);
}

/**
 * @brief QJsonUtils::account2JsonObject
 * @param doaProvider
 * @return
 * DOAProvider 类对象转 QJsonObject
 */
QJsonObject QJsonUtils::doaProvider2JsonObject(const DOAProvider *doaProvider)
{
    QJsonObject accountObject;

    if (doaProvider == nullptr) {
        return accountObject;
    }

    accountObject.insert("accountname", doaProvider->getAccountName());
    accountObject.insert("accountstat", doaProvider->getAccountStat());
    accountObject.insert("accountid", doaProvider->getAccountID());
    accountObject.insert("accountdbuspath", doaProvider->getPath());
    accountObject.insert("accounttype", doaProvider->getProtocol());
    accountObject.insert("accountflag", doaProvider->getProviderName());
    accountObject.insert("username", doaProvider->getDisplayName());
    accountObject.insert("calendardisable", doaProvider->getCalendarDisabled());
    accountObject.insert("accounturi", doaProvider->getUri());
    accountObject.insert("createtime", doaProvider->getCreateTime());
    accountObject.insert("accounturl", doaProvider->getUrl());

    return accountObject;
}

QString QJsonUtils::doaProvider2String(const DOAProvider *doaProvider, QJsonUtils::IterfaceOper iterfaceoper)
{
    QJsonObject resultObject;

    switch (iterfaceoper) {
    case QJsonUtils::ADD: {
        QJsonObject accountObject = doaProvider2JsonObject(doaProvider);
        resultObject.insert("iterfaceoper", "ADD");
        resultObject.insert("stat", "0");
        resultObject.insert("iterfacecontent", accountObject);
        break;
    }
    case QJsonUtils::DEL: {
        QJsonObject accountObject;
        accountObject.insert("accountid", doaProvider->getAccountID());
        resultObject.insert("iterfaceoper", "DEL");
        resultObject.insert("stat", "0");
        resultObject.insert("iterfacecontent", accountObject);
        break;
    }
    default:
        break;
    }

    QJsonDocument doc;
    doc.setObject(resultObject);

    return doc.toJson(QJsonDocument::Compact);
}

bool QJsonUtils::jsonString2DoaProvider(const QString jsonString, DOAProvider *doaProvider)
{
    QJsonParseError jsonerror;
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toLatin1(), &jsonerror);

    if (doc.isNull() || jsonerror.error != QJsonParseError::NoError) {
        qCritical() << "jsonString error:" << jsonerror.errorString();
        return false;
    }

    QJsonObject accountObject;

    if (doaProvider == nullptr) {
        return false;
    }

    if (doc.isObject()) {
        QJsonObject object = doc.object();

        QJsonObject::iterator it = object.begin();
        while (it != object.end()) {
            switch (it.value().type()) {
            case QJsonValue::String: {
                QJsonArray sub = it.value().toArray();
                if (it.key() == "logintype") { //登录方式
                    doaProvider->setLoginType((DOAProvider::LoginType)it.value().toString().toInt());
                } else if (it.key() == "accounttype") { //协议类型
                    doaProvider->setProtocol((DOAProvider::ProtocolType)it.value().toString().toInt());
                } else if (it.key() == "accountname") { //帐户名
                    doaProvider->setAccountName(it.value().toString());
                    doaProvider->setDisplayName(it.value().toString());
                } else if (it.key() == "accountpassword") { //帐户密码
                    doaProvider->setAccountPassword(it.value().toString());
                } else if (it.key() == "accounturl") { //服务器名称
                    if (!it.value().toString().isEmpty()) {
                        doaProvider->setUrl(it.value().toString());
                        if (!doaProvider->getUrl().toLower().startsWith("https")) {
                            doaProvider->setSSL(false);
                        }
                    }
                } else if (it.key() == "uuid") { //登录UUID
                    if (!it.value().toString().isEmpty()) {
                        doaProvider->setAccountID(it.value().toString());
                    }
                }
                break;
            }
            default:
                break;
            }
            it++;
        }
    }

    return true;
}

/**
 * @brief accountAddJsonArray
 * @param doaProvider
 * @param jsonarray
 * DOAProvider对象写入JsonArray
 */
void QJsonUtils::accountAddJsonArray(const DOAProvider *doaProvider, QJsonArray &jsonarray)
{
    QJsonObject accountObject;

    if (doaProvider == nullptr) {
        return;
    }

    accountObject.insert("accountname", doaProvider->getAccountName());
    accountObject.insert("accountstat", doaProvider->getAccountStat());
    accountObject.insert("accountid", doaProvider->getAccountID());
    accountObject.insert("accountdbuspath", doaProvider->getPath());
    accountObject.insert("accounttype", doaProvider->getProtocol());
    accountObject.insert("accountflag", doaProvider->getProviderName());
    accountObject.insert("username", doaProvider->getDisplayName());
    accountObject.insert("calendardisable", doaProvider->getCalendarDisabled());
    accountObject.insert("accounturi", doaProvider->getUri());
    accountObject.insert("createtime", doaProvider->getCreateTime());
    accountObject.insert("accounturl", doaProvider->getUrl());

    jsonarray.append(accountObject);
}
