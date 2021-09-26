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
#ifndef QJSONUTILS_H
#define QJSONUTILS_H

#include "doaprovider.h"

#include <QJsonDocument>
#include <QMap>
#include <QVariant>
#include <QJsonArray>
#include <QJsonObject>

class QJsonUtils
{
public:
    enum IterfaceOper {
        ADD,
        MODIFY,
        DEL
    };

    /**
     * @brief getJsonString
     * @param jsonMap
     * @return
     * Map转JsonString
     */
    static QString getJsonString(const QMap<QString, QVariant> &jsonMap);

    /**
     * @brief doaProvider2JsonObject
     * @param doaProvider
     * @return
     * DOAProvider 类对象转QJsonObject
     */
    static QJsonObject doaProvider2JsonObject(const DOAProvider *doaProvider);

    /**
     * @brief jsonString2DoaProvider
     * @param jsonString
     * @param doaProvider
     * jsonString 转DOAProvider对象
     */
    static bool jsonString2DoaProvider(const QString jsonString, DOAProvider *doaProvider);

    /**
     * @brief accountAddJsonArray
     * @param doaProvider
     * @param jsonarray
     * DOAProvider对象写入JsonArray
     */
    static void accountAddJsonArray(const DOAProvider *doaProvider, QJsonArray &jsonarray);

    /**
     * @brief QJsonUtils::doaProvider2String
     * @param doaProvider 帐户对象
     * @param iterfaceoper 操作对象 ADD/DEL
     * @return
     * 生成增加/删除 JSON字符串
     */
    static QString doaProvider2String(const DOAProvider *doaProvider, QJsonUtils::IterfaceOper iterfaceoper);
};

#endif // QJSONUTILS_H
