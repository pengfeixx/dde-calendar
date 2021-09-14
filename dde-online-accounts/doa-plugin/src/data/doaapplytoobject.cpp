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
#include "doaapplytoobject.h"

DOAApplyToObject::DOAApplyToObject()
    : m_isApply(true)
{
}

QString DOAApplyToObject::appName() const
{
    return m_appName;
}

void DOAApplyToObject::setAppName(const QString &appName)
{
    m_appName = appName;
}

bool DOAApplyToObject::isApply() const
{
    return m_isApply;
}

void DOAApplyToObject::setIsApply(bool isApply)
{
    m_isApply = isApply;
}

bool DOAApplyToObject::operator==(const DOAApplyToObject &app) const
{
    return this->appName() == app.appName() && this->isApply() && app.isApply();
}
