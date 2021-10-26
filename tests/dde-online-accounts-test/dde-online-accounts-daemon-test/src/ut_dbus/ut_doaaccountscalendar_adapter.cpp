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
#include "ut_doaaccountscalendar_adapter.h"
#include "dbus/doaaccounts_adapter.h"
#include "controller/doaqqprovider.h"

ut_doaaccountscalendar_adapter::ut_doaaccountscalendar_adapter()
{
    doaAccountsadapter = new DOAAccountsadapter();
}

void ut_doaaccountscalendar_adapter::SetUp()
{

    doaAccountsCalendardapter = new DOAAccountsCalendardapter(doaAccountsadapter);
}

void ut_doaaccountscalendar_adapter::TearDown()
{
    delete doaAccountsadapter;
}

TEST_F(ut_doaaccountscalendar_adapter, ut_doaaccountscalendar_adapter_url_001)
{
    doaAccountsadapter->setDoaProvider(new DOAQQProvider(doaAccountsadapter));
    doaAccountsadapter->getDoaProvider()->setUri("1233455");
    EXPECT_EQ(doaAccountsCalendardapter->url(), "1233455");
}
