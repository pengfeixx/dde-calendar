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
#include "ut_doaapplytowidget.h"

ut_doaapplytowidget::ut_doaapplytowidget()
{

}

void ut_doaapplytowidget::SetUp()
{
    doaApplyToWidget = new DOAApplyToWidget();
}

void ut_doaapplytowidget::TearDown()
{
    delete doaApplyToWidget;
    doaApplyToWidget = nullptr;
}


TEST_F(ut_doaapplytowidget, ut_doaapplytowidget_addApp_001)
{
    DOAApplyToObject app;
    doaApplyToWidget->addApp(app);
    EXPECT_EQ(doaApplyToWidget->m_itemVector.count(), 1);
}

TEST_F(ut_doaapplytowidget, ut_doaapplytowidget_clearApp_001)
{
    doaApplyToWidget->clearApp();
    EXPECT_EQ(doaApplyToWidget->m_itemVector.count(), 0);
}
