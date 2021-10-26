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
#ifndef UT_DOAACCOUNTMANAGER_H
#define UT_DOAACCOUNTMANAGER_H

#include "gtest/gtest.h"
#include "dbus/doaaccountmanager.h"

class ut_doaaccountmanager: public ::testing::Test
{
public:
    void SetUp() override;
    void TearDown() override;
protected:
    DOAAccountManager *doaAccountManager = nullptr;
private:
    bool stub_resultTrue();
    bool stub_resultAllFalse();
    QString stub_getAccountID();
    QString stub_getAccountName();
    QString stub_getAccountIDCall();
    DOAProvider::LoginState login();
    bool stub_result();
    QString stub_writableLocation(QStandardPaths::StandardLocation type);
    QString firstremovedbfile();
};

#endif // UT_DOAACCOUNTMANAGER_H
