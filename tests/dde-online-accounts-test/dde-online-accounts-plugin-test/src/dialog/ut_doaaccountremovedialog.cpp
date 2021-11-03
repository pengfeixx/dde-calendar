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
#include "ut_doaaccountremovedialog.h"

#include <QSignalSpy>

ut_doaaccountremovedialog::ut_doaaccountremovedialog()
{

}

void ut_doaaccountremovedialog::SetUp()
{
    doaAccountRemoveDialog = new DOAAccountRemoveDialog();
}

void ut_doaaccountremovedialog::TearDown()
{
    delete doaAccountRemoveDialog;
    doaAccountRemoveDialog = nullptr;
}

TEST_F(ut_doaaccountremovedialog, ut_doaaccountremovedialog_initWidget_001)
{
    EXPECT_EQ(doaAccountRemoveDialog->buttonCount(), 2);
    EXPECT_EQ(doaAccountRemoveDialog->getButtonIndexByText("Cancel button"), 1);
}

TEST_F(ut_doaaccountremovedialog, ut_doaaccountremovedialog_slotbuttonClicked_001)
{
    QSignalSpy spy(doaAccountRemoveDialog,SIGNAL(signalDeleteAccount()));
    doaAccountRemoveDialog->slotbuttonClicked(0, "Cancel button");
    EXPECT_EQ(spy.count(), 0);
}

TEST_F(ut_doaaccountremovedialog, ut_doaaccountremovedialog_slotbuttonClicked_002)
{
    QSignalSpy spy(doaAccountRemoveDialog,SIGNAL(signalDeleteAccount()));
    doaAccountRemoveDialog->slotbuttonClicked(1, "Cancel button");
    EXPECT_EQ(spy.count(), 1);
}

