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
#include "ut_doaprovider.h"


void ut_doaprovider::SetUp()
{
    doaqqprovider = new DOAQQProvider();
}

void ut_doaprovider::TearDown()
{
    delete doaqqprovider;
    doaqqprovider = nullptr;
}

TEST_F(ut_doaprovider, ut_doaprovider_getAccountName_001)
{
    doaqqprovider->setAccountName("1234");
    EXPECT_EQ(doaqqprovider->getAccountName(), "1234");
}

TEST_F(ut_doaprovider, ut_doaprovider_setAccountName_001)
{
    doaqqprovider->setAccountName("1234");
    EXPECT_EQ(doaqqprovider->getAccountName(), "1234");
}

TEST_F(ut_doaprovider, ut_doaprovider_getAccountPassword_001)
{
    doaqqprovider->setAccountPassword("1234");
    EXPECT_EQ(doaqqprovider->getAccountPassword(), "1234");
}

TEST_F(ut_doaprovider, ut_doaprovider_setAccountPassword_001)
{
    doaqqprovider->setAccountPassword("1234");
    EXPECT_EQ(doaqqprovider->getAccountPassword(), "1234");
}

TEST_F(ut_doaprovider, ut_doaprovider_getUrl_001)
{
    doaqqprovider->setUrl("1234");
    EXPECT_EQ(doaqqprovider->getUrl(), "1234");
}

TEST_F(ut_doaprovider, ut_doaprovider_setUrl_001)
{
    doaqqprovider->setUrl("1234");
    EXPECT_EQ(doaqqprovider->getUrl(), "1234");
}

TEST_F(ut_doaprovider, ut_doaprovider_getPath_001)
{
    doaqqprovider->setPath("1234");
    EXPECT_EQ(doaqqprovider->getPath(), "1234");
}

TEST_F(ut_doaprovider, ut_doaprovider_setPath_001)
{
    doaqqprovider->setPath("1234");
    EXPECT_EQ(doaqqprovider->getPath(), "1234");
}

TEST_F(ut_doaprovider, ut_doaprovider_getProtocol_001)
{
    doaqqprovider->setProtocol(DOAProvider::CALDAV);
    EXPECT_EQ(doaqqprovider->getProtocol(), DOAProvider::CALDAV);
}

TEST_F(ut_doaprovider, ut_doaprovider_setProtocol_001)
{
    doaqqprovider->setProtocol(DOAProvider::CALDAV);
    EXPECT_EQ(doaqqprovider->getProtocol(), DOAProvider::CALDAV);
}

TEST_F(ut_doaprovider, ut_doaprovider_getDisplayName_001)
{
    doaqqprovider->setDisplayName("DOAProvider::CALDAV");
    EXPECT_EQ(doaqqprovider->getDisplayName(), "DOAProvider::CALDAV");
}

TEST_F(ut_doaprovider, ut_doaprovider_setDisplayName_001)
{
    doaqqprovider->setDisplayName("DOAProvider::CALDAV");
    EXPECT_EQ(doaqqprovider->getDisplayName(), "DOAProvider::CALDAV");
}

TEST_F(ut_doaprovider, ut_doaprovider_getUri_001)
{
    doaqqprovider->setUri("DOAProvider::CALDAV");
    EXPECT_EQ(doaqqprovider->getUri(), "DOAProvider::CALDAV");
}

TEST_F(ut_doaprovider, ut_doaprovider_setUri_001)
{
    doaqqprovider->setUri("DOAProvider::CALDAV");
    EXPECT_EQ(doaqqprovider->getUri(), "DOAProvider::CALDAV");
}

TEST_F(ut_doaprovider, ut_doaprovider_getCreateTime_001)
{
    doaqqprovider->setCreateTime("DOAProvider::CALDAV");
    EXPECT_EQ(doaqqprovider->getCreateTime(), "DOAProvider::CALDAV");
}

TEST_F(ut_doaprovider, ut_doaprovider_setCreateTime_001)
{
    doaqqprovider->setCreateTime("DOAProvider::CALDAV");
    EXPECT_EQ(doaqqprovider->getCreateTime(), "DOAProvider::CALDAV");
}

TEST_F(ut_doaprovider, ut_doaprovider_getAccountStat_001)
{
    doaqqprovider->setAccountStat(DOAProvider::NetWorkError);
    EXPECT_EQ(doaqqprovider->getAccountStat(), DOAProvider::NetWorkError);
}

TEST_F(ut_doaprovider, ut_doaprovider_setAccountStat_001)
{
    doaqqprovider->setAccountStat(DOAProvider::NetWorkError);
    EXPECT_EQ(doaqqprovider->getAccountStat(), DOAProvider::NetWorkError);
}

TEST_F(ut_doaprovider, ut_doaprovider_getAccountID_001)
{
    doaqqprovider->setAccountID("122345");
    EXPECT_EQ(doaqqprovider->getAccountID(), "122345");
}

TEST_F(ut_doaprovider, ut_doaprovider_setAccountID_001)
{
    doaqqprovider->setAccountID("122345");
    EXPECT_EQ(doaqqprovider->getAccountID(), "122345");
}

TEST_F(ut_doaprovider, ut_doaprovider_getLoginType_001)
{
    doaqqprovider->setLoginType(DOAProvider::AUTO);
    EXPECT_EQ(doaqqprovider->getLoginType(), DOAProvider::AUTO);
}

TEST_F(ut_doaprovider, ut_doaprovider_setLoginType_001)
{
    doaqqprovider->setLoginType(DOAProvider::AUTO);
    EXPECT_EQ(doaqqprovider->getLoginType(), DOAProvider::AUTO);
}

TEST_F(ut_doaprovider, ut_doaprovider_getProviderName_001)
{
    doaqqprovider->setProviderName(DOAProvider::QQ);
    EXPECT_EQ(doaqqprovider->getProviderName(), DOAProvider::QQ);
}

TEST_F(ut_doaprovider, ut_doaprovider_setProviderName_001)
{
    doaqqprovider->setProviderName(DOAProvider::QQ);
    EXPECT_EQ(doaqqprovider->getProviderName(), DOAProvider::QQ);
}

TEST_F(ut_doaprovider, ut_doaprovider_getCalendarDisabled_001)
{
    doaqqprovider->setCalendarDisabled(true);
    EXPECT_EQ(doaqqprovider->getCalendarDisabled(), true);
}

TEST_F(ut_doaprovider, ut_doaprovider_setCalendarDisabled_001)
{
    doaqqprovider->setCalendarDisabled(true);
    EXPECT_EQ(doaqqprovider->getCalendarDisabled(), true);
}

TEST_F(ut_doaprovider, ut_doaprovider_getSSL_001)
{
    doaqqprovider->setSSL(true);
    EXPECT_EQ(doaqqprovider->getSSL(), true);
}

TEST_F(ut_doaprovider, ut_doaprovider_setSSL_001)
{
    doaqqprovider->setSSL(true);
    EXPECT_EQ(doaqqprovider->getSSL(), true);
}
