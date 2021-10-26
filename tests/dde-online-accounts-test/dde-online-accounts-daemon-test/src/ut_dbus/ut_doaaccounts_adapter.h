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
#ifndef UT_DOAACCOUNTS_ADAPTER_H
#define UT_DOAACCOUNTS_ADAPTER_H

#include "gtest/gtest.h"
#include "dbus/doaaccounts_adapter.h"

class ut_doaaccounts_adapter : public ::testing::Test
{
public:
    void SetUp() override;
    void TearDown() override;
protected:
    DOAAccountsadapter *doaAccountsadapter = nullptr;

    bool stub_resultAllFalse();
    bool stub_resultTrue();
    DOAProvider::LoginState login();
    void sendPropertiesChanged();
};

#endif // UT_DOAACCOUNTS_ADAPTER_H
