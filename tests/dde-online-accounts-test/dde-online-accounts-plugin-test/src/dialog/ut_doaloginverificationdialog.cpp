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
#include "ut_doaloginverificationdialog.h"

ut_doaloginverificationdialog::ut_doaloginverificationdialog()
{

}

void ut_doaloginverificationdialog::SetUp()
{
    doaLoginVerificationDialog = new DOALoginVerificationDialog();
}

void ut_doaloginverificationdialog::TearDown()
{
    delete doaLoginVerificationDialog;
    doaLoginVerificationDialog = nullptr;
}

TEST_F(ut_doaloginverificationdialog, ut_doaloginverificationdialog_isCaneclLogin_001)
{
    doaLoginVerificationDialog->m_caneclLogin = false;
    EXPECT_EQ(doaLoginVerificationDialog->isCaneclLogin(), false);
}

TEST_F(ut_doaloginverificationdialog, ut_doaloginverificationdialog_initWidget_001)
{
    EXPECT_EQ(doaLoginVerificationDialog->size(), QSize(420, 346));
}

TEST_F(ut_doaloginverificationdialog, ut_doaloginverificationdialog_slotClose_001)
{
    doaLoginVerificationDialog->slotClose();
    EXPECT_EQ(doaLoginVerificationDialog->m_caneclLogin, false);
}
