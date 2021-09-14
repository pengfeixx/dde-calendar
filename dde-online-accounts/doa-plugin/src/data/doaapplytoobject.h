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
#ifndef DOAAPPLYTOOBJECT_H
#define DOAAPPLYTOOBJECT_H

#include <QObject>

/**
 * @brief The applyToObject class   应用于具体对象
 */
class DOAApplyToObject
{
public:
    DOAApplyToObject();

    /**
     * @brief appName   获取对应的应用名称
     * @return  返回对应的应用名称
     */
    QString appName() const;

    /**
     * @brief setAppName    设置对应的应用名称
     * @param appName       应用名称
     */
    void setAppName(const QString &appName);

    /**
     * @brief isApply   是否应用于
     * @return
     */
    bool isApply() const;

    /**
     * @brief setIsApply    设置是否应用于
     * @param isApply
     */
    void setIsApply(bool isApply);

    bool operator==(const DOAApplyToObject &app) const;

private:
    //具体应用名称
    QString m_appName;
    //是否应用
    bool m_isApply;
};

#endif // DOAAPPLYTOOBJECT_H
