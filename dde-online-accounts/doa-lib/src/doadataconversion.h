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
#ifndef DOADATACONVERSION_H
#define DOADATACONVERSION_H

#include "consts.h"

#include <QString>

class QJsonObject;
//数据转换 序列化和反序列化
/**
 * @brief addAccountInfoToJson      添加帐户信息序列化
 * @param info                      帐户信息
 * @return
 */
QString addAccountInfoToJson(const AddAccountInfo &info);

/**
 * @brief accountListJsonToAccountInfoList      将获取到的帐户信息反序列化
 * @param str
 * @return
 */
DOAAccountList::AccountInfoList accountListJsonToAccountInfoList(const QString &str);

/**
 * @brief fromeConverDateTime       转换时间，从QString到QDateTime
 * @param dateTimeStr
 * @return
 */
QDateTime fromeConverDateTime(const QString &dateTimeStr);

/**
 * @brief accountJsonObjectToInfo           将帐户信息jsonObject转换为AccountInfo结构体
 * @param jsonObject                        帐户信息jsonObject
 * @return
 */
DOAAccountList::AccountInfo accountJsonObjectToInfo(const QJsonObject &jsonObject);
DOAAccountList::AccountInfo accountJsonObjectToInfo(const QVariant &json);

/**
 * @brief accountListChangeParameterAnalysis        帐户列表信息改变参数解析
 * @param msg
 * @return
 */
QList<QVariant> accountListChangeParameterAnalysis(const QString &msg);

/**
 * @brief remvoeAccountJsonObjectToInfo         移除帐户jsonObject解析
 * @param json
 * @return
 */
QString remvoeAccountJsonObjectToInfo(const QVariant &json);
#endif // DOADATACONVERSION_H
