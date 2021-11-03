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
#include "ut_doaapplytoitem.h"
#include <QSignalSpy>

ut_doaapplytoitem::ut_doaapplytoitem()
{

}

void ut_doaapplytoitem::SetUp()
{
    doaApplyToItem = new DOAApplyToItem();
}

void ut_doaapplytoitem::TearDown()
{
    delete doaApplyToItem;
    doaApplyToItem = nullptr;
}

TEST_F(ut_doaapplytoitem, ut_doaapplytoitem_setApplyObject_001)
{
    DOAApplyToObject app;
    app.setIsApply(false);
    doaApplyToItem->setApplyObject(app);
    EXPECT_EQ(doaApplyToItem->m_switchBtn->isChecked(), false);
}

TEST_F(ut_doaapplytoitem, ut_doaapplytoitem_changeState_001)
{
    DOAApplyToObject app;
    app.setIsApply(false);
    doaApplyToItem->setApplyObject(app);
    QSignalSpy spy(doaApplyToItem, SIGNAL(signalChange(const DOAApplyToObject &)));
    doaApplyToItem->changeState(false);

    EXPECT_EQ(spy.count(), 0);
}

TEST_F(ut_doaapplytoitem, ut_doaapplytoitem_changeState_002)
{
    DOAApplyToObject app;
    app.setIsApply(false);
    doaApplyToItem->setApplyObject(app);
    QSignalSpy spy(doaApplyToItem, SIGNAL(signalChange(const DOAApplyToObject &)));
    doaApplyToItem->changeState(true);

    EXPECT_EQ(spy.count(), 1);
}
