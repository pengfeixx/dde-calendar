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
#ifndef UT_ACCOUNTDB_H
#define UT_ACCOUNTDB_H

#include "gtest/gtest.h"
#include "db/accountdb.h"
#include "../../third-party_stub/stub.h"

#include <QStandardPaths>

class ut_accountdb : public ::testing::Test
{
public:
    ut_accountdb();
    void SetUp() override;
    void TearDown() override;

    bool stub_resultTrue();
    bool stub_resultAllFalse();
    bool stub_result();
protected:
    AccountDB *db = nullptr;
    QString stub_writableLocation(QStandardPaths::StandardLocation type);
    QString firstremovedbfile();
};

#endif // UT_ACCOUNTDB_H
