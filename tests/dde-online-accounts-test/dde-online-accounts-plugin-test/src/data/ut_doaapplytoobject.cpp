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
#include "ut_doaapplytoobject.h"

ut_doaapplytoobject::ut_doaapplytoobject()
{

}

void ut_doaapplytoobject::SetUp()
{
    doaApplyToObject = new DOAApplyToObject();
}

void ut_doaapplytoobject::TearDown()
{
    delete doaApplyToObject;
    doaApplyToObject = nullptr;
}

TEST_F(ut_doaapplytoobject, ut_doaapplytoobject_appName_001)
{
    doaApplyToObject->setAppName("12345");
    EXPECT_EQ(doaApplyToObject->appName(), "12345");
}

TEST_F(ut_doaapplytoobject, ut_doaapplytoobject_setAppName_002)
{
    doaApplyToObject->setAppName("12345");
    EXPECT_EQ(doaApplyToObject->appName(), "12345");
}

TEST_F(ut_doaapplytoobject, ut_doaapplytoobject_isApply_001)
{
    doaApplyToObject->setIsApply(true);
    EXPECT_EQ(doaApplyToObject->isApply(), true);
}

TEST_F(ut_doaapplytoobject, ut_doaapplytoobject_setIsApply_002)
{
    doaApplyToObject->setIsApply(true);
    EXPECT_EQ(doaApplyToObject->isApply(), true);
}

TEST_F(ut_doaapplytoobject, ut_doaapplytoobject_operator__001)
{
    DOAApplyToObject app;
    app.setAppName("12345");
    app.setIsApply(true);

    DOAApplyToObject app1;
    app1.setAppName("12345");
    app1.setIsApply(true);

    doaApplyToObject->setAppName("12345");
    doaApplyToObject->setIsApply(true);

    EXPECT_EQ(app1 == app, true);
}

TEST_F(ut_doaapplytoobject, ut_doaapplytoobject_operator__002)
{
    DOAApplyToObject app;
    app.setAppName("12346");
    app.setIsApply(true);

    DOAApplyToObject app1;
    app1.setAppName("12345");
    app1.setIsApply(true);

    EXPECT_EQ(app1 == app, false);
}

TEST_F(ut_doaapplytoobject, ut_doaapplytoobject_operator__003)
{
    DOAApplyToObject app;
    app.setAppName("12346");
    app.setIsApply(true);

    DOAApplyToObject app1;
    app1.setAppName("12346");
    app1.setIsApply(false);

    EXPECT_EQ(app1 == app, false);
}

TEST_F(ut_doaapplytoobject, ut_doaapplytoobject_operator__004)
{
    DOAApplyToObject app;
    app.setAppName("12345");
    app.setIsApply(true);

    DOAApplyToObject app1;
    app1.setAppName("12346");
    app1.setIsApply(false);

    EXPECT_EQ(app1 == app, false);
}
