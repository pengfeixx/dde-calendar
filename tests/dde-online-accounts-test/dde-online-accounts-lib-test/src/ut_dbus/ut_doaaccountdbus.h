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
#ifndef UT_DOAACCOUNTDBUS_H
#define UT_DOAACCOUNTDBUS_H

#include "gtest/gtest.h"
#include "doaaccountdbus.h"

class ut_doaaccountdbus : public ::testing::Test
{
public:
    ut_doaaccountdbus();
public:
    void SetUp() override;
    void TearDown() override;
    QDBusMessage stub_reply();
    QDBusMessage::MessageType stub_type();
    QDBusPendingCall stub_asyncCallWithArgumentList(const QString &method,
                                               const QList<QVariant> &args);
    bool stub_resultAllFalse();
    bool stub_resultTrue();
    QVariant stub_resultQVariant();
    bool stub_setPropertyByName(const char *porpertyName, const QVariant &value);
protected:
    DOAAccountDBus *doaaccountdbus = nullptr;
};

#endif // UT_DOAACCOUNTDBUS_H
