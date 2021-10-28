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
#ifndef UT_DOAACCOUNTINFOWIDGET_H
#define UT_DOAACCOUNTINFOWIDGET_H

#include "gtest/gtest.h"
#include "doaaccountinfowidget.h"

class ut_doaaccountinfowidget : public ::testing::Test
{
public:
    ut_doaaccountinfowidget();
    void SetUp() override;
    void TearDown() override;
    void stub_slotUpdateCurrentAccount();
    int stub_slotDialogExec();
protected:
    DOAAccountInfoWidget *doaAccountInfoWidget = nullptr;

};

#endif // UT_DOAACCOUNTINFOWIDGET_H
