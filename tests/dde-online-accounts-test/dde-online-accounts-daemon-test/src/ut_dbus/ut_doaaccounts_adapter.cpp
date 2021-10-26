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
#include "ut_doaaccounts_adapter.h"
#include "doaprovider.h"
#include "doaqqprovider.h"
#include "../../third-party_stub/stub.h"

static DOAProvider::LoginState m_doaloginstate = DOAProvider::SUCCESS;
static QString m_stubmsg = "";

void ut_doaaccounts_adapter::SetUp()
{
    doaAccountsadapter = new DOAAccountsadapter();
}

void ut_doaaccounts_adapter::TearDown()
{
    delete doaAccountsadapter;
    doaAccountsadapter = nullptr;
}

bool ut_doaaccounts_adapter::stub_resultAllFalse()
{
    return false;
}

bool ut_doaaccounts_adapter::stub_resultTrue()
{
    return true;
}

DOAProvider::LoginState ut_doaaccounts_adapter::login()
{
    return m_doaloginstate;
}


void ut_doaaccounts_adapter::sendPropertiesChanged()
{
    m_stubmsg = "uostest2021";
}



TEST_F(ut_doaaccounts_adapter, ut_doaaccounts_adapter_onNetWorkChange_001)
{
    Stub s;
    s.set(ADDR(DOAAccountsadapter, CheckAccountState), ADDR(ut_doaaccounts_adapter, stub_resultAllFalse));
    doaAccountsadapter->onNetWorkChange(true);
    EXPECT_EQ(doaAccountsadapter->networkerror, false);
}

TEST_F(ut_doaaccounts_adapter, ut_doaaccounts_adapter_onNetWorkChange_002)
{
    Stub s;
    s.set(ADDR(DOAAccountsadapter, CheckAccountState), ADDR(ut_doaaccounts_adapter, stub_resultAllFalse));
    doaAccountsadapter->onNetWorkChange(false);
    EXPECT_EQ(doaAccountsadapter->networkerror, true);
}

TEST_F(ut_doaaccounts_adapter, ut_doaaccounts_adapter_slotAutoCheck_001)
{
    Stub s;
    s.set(ADDR(DOAAccountsadapter, CheckAccountState), ADDR(ut_doaaccounts_adapter, stub_resultAllFalse));
    doaAccountsadapter->slotAutoCheck();
    EXPECT_EQ(doaAccountsadapter->isAutoCheck, true);
}

TEST_F(ut_doaaccounts_adapter, ut_doaaccounts_adapter_CheckAccountState_001)
{
    doaAccountsadapter->m_doaProvider = new DOAQQProvider(doaAccountsadapter);
    doaAccountsadapter->m_doaProvider->setAccountID("123456");
    doaAccountsadapter->m_doaProvider->setAccountName("123456@qq.com");
    doaAccountsadapter->m_doaProvider->setAccountPassword("123456");
    Stub s;
    s.set(ADDR(DOAQQProvider, getCalendarUri), ADDR(ut_doaaccounts_adapter, login));
    s.set(ADDR(DOAQQProvider, getPropname), ADDR(ut_doaaccounts_adapter, login));
    m_doaloginstate = DOAProvider::NetWorkError;
    doaAccountsadapter->onNetWorkChange(true);
    doaAccountsadapter->CheckAccountState();
    EXPECT_EQ(doaAccountsadapter->m_doaProvider->getAccountStat(), m_doaloginstate);
    m_doaloginstate = DOAProvider::Checking;
    doaAccountsadapter->CheckAccountState();
}

TEST_F(ut_doaaccounts_adapter, ut_doaaccounts_adapter_CheckAccountState_002)
{
    doaAccountsadapter->m_doaProvider = new DOAQQProvider(doaAccountsadapter);
    doaAccountsadapter->m_doaProvider->setAccountID("123456");
    doaAccountsadapter->m_doaProvider->setAccountName("123456@qq.com");
    doaAccountsadapter->m_doaProvider->setAccountPassword("123456");
    Stub s;
    m_doaloginstate = DOAProvider::NetWorkError;
    doaAccountsadapter->onNetWorkChange(false);
    doaAccountsadapter->CheckAccountState();
    EXPECT_EQ(doaAccountsadapter->m_doaProvider->getAccountStat(), m_doaloginstate);
}

TEST_F(ut_doaaccounts_adapter, ut_doaaccounts_adapter_CheckAccountState_003)
{
    doaAccountsadapter->m_doaProvider = new DOAQQProvider(doaAccountsadapter);
    doaAccountsadapter->m_doaProvider->setAccountID("123456");
    doaAccountsadapter->m_doaProvider->setAccountName("123456@qq.com");
    doaAccountsadapter->m_doaProvider->setAccountPassword("123456");
    doaAccountsadapter->m_doaProvider->setAccountStat(DOAProvider::NetWorkError);
    Stub s;
    s.set(ADDR(DOAAccountsadapter, sendPropertiesChanged), ADDR(ut_doaaccounts_adapter, sendPropertiesChanged));
    m_doaloginstate = DOAProvider::NetWorkError;
    doaAccountsadapter->onNetWorkChange(false);
    m_stubmsg = "uostest";
    doaAccountsadapter->CheckAccountState();
    EXPECT_EQ(m_stubmsg, "uostest2021");
}

TEST_F(ut_doaaccounts_adapter, ut_doaaccounts_adapter_CheckAccountState_004)
{
    doaAccountsadapter->m_doaProvider = new DOAQQProvider(doaAccountsadapter);
    doaAccountsadapter->m_doaProvider->setAccountID("123456");
    doaAccountsadapter->m_doaProvider->setAccountName("123456@qq.com");
    doaAccountsadapter->m_doaProvider->setAccountPassword("123456");
    doaAccountsadapter->m_doaProvider->setAccountStat(DOAProvider::NetWorkError);
    Stub s;
    s.set(ADDR(DOAAccountsadapter, sendPropertiesChanged), ADDR(ut_doaaccounts_adapter, sendPropertiesChanged));
    m_doaloginstate = DOAProvider::NetWorkError;
    doaAccountsadapter->onNetWorkChange(false);
    doaAccountsadapter->slotAutoCheck();
    doaAccountsadapter->CheckAccountState();
    EXPECT_EQ(doaAccountsadapter->isAutoCheck, false);
}

TEST_F(ut_doaaccounts_adapter, ut_doaaccounts_adapter_calendarDisabled_001)
{
    doaAccountsadapter->m_doaProvider = new DOAQQProvider(doaAccountsadapter);
    doaAccountsadapter->m_doaProvider->setCalendarDisabled(true);

    EXPECT_EQ(doaAccountsadapter->calendarDisabled(), true);
}

TEST_F(ut_doaaccounts_adapter, ut_doaaccounts_adapter_setCalendarDisabled_001)
{
    doaAccountsadapter->m_doaProvider = new DOAQQProvider(doaAccountsadapter);
    doaAccountsadapter->m_checkAccountCalendarTimer.start(1200);
    doaAccountsadapter->setCalendarDisabled(true);
    EXPECT_EQ(doaAccountsadapter->m_checkAccountCalendarTimer.isActive(), false);
}

TEST_F(ut_doaaccounts_adapter, ut_doaaccounts_adapter_setCalendarDisabled_002)
{
    doaAccountsadapter->m_doaProvider = new DOAQQProvider(doaAccountsadapter);
    doaAccountsadapter->m_doaProvider->setCalendarDisabled(true);
    doaAccountsadapter->setCalendarDisabled(false);
    EXPECT_EQ(doaAccountsadapter->m_checkAccountCalendarTimer.isActive(), true);
}

TEST_F(ut_doaaccounts_adapter, ut_doaaccounts_adapter_id_001)
{
    doaAccountsadapter->m_doaProvider = new DOAQQProvider(doaAccountsadapter);
    doaAccountsadapter->m_doaProvider->setAccountID("12345");

    EXPECT_EQ(doaAccountsadapter->id(), "12345");
}

TEST_F(ut_doaaccounts_adapter, ut_doaaccounts_adapter_status_001)
{
    doaAccountsadapter->m_doaProvider = new DOAQQProvider(doaAccountsadapter);
    doaAccountsadapter->m_doaProvider->setAccountStat(DOAProvider::NetWorkError);

    EXPECT_EQ(doaAccountsadapter->status(), "13");
}

TEST_F(ut_doaaccounts_adapter, ut_doaaccounts_adapter_userName_001)
{
    doaAccountsadapter->m_doaProvider = new DOAQQProvider(doaAccountsadapter);
    doaAccountsadapter->m_doaProvider->setDisplayName("12345");

    EXPECT_EQ(doaAccountsadapter->userName(), "12345");
}

TEST_F(ut_doaaccounts_adapter, ut_doaaccounts_adapter_setUserName_001)
{
    doaAccountsadapter->m_doaProvider = new DOAQQProvider(doaAccountsadapter);
    doaAccountsadapter->m_doaProvider->setDisplayName("12345");
    Stub s;
    s.set(ADDR(DOAAccountsadapter, sendPropertiesChanged), ADDR(ut_doaaccounts_adapter, sendPropertiesChanged));
    QString uname = "123445";
    m_stubmsg = "uostest";
    doaAccountsadapter->setUserName(uname);
    EXPECT_EQ(doaAccountsadapter->userName(), "123445");
    EXPECT_EQ(m_stubmsg, "uostest2021");
}

TEST_F(ut_doaaccounts_adapter, ut_doaaccounts_adapter_providerType_001)
{
    doaAccountsadapter->m_doaProvider = new DOAQQProvider(doaAccountsadapter);
    doaAccountsadapter->m_doaProvider->setProtocol(DOAProvider::CALDAV);

    EXPECT_EQ(doaAccountsadapter->providerType(), "CALDAV");
}

TEST_F(ut_doaaccounts_adapter, ut_doaaccounts_adapter_providerName_001)
{
    doaAccountsadapter->m_doaProvider = new DOAQQProvider(doaAccountsadapter);
    doaAccountsadapter->m_doaProvider->setProviderName(DOAProvider::QQ);

    EXPECT_EQ(doaAccountsadapter->providerName(), "QQ");
}

TEST_F(ut_doaaccounts_adapter, ut_doaaccounts_adapter_remove_001)
{
    doaAccountsadapter->m_doaProvider = new DOAQQProvider(doaAccountsadapter);
    doaAccountsadapter->m_checkAccountCalendarTimer.start(1200);
    doaAccountsadapter->Remove();
    EXPECT_EQ(doaAccountsadapter->m_checkAccountCalendarTimer.isActive(), false);
}

TEST_F(ut_doaaccounts_adapter, ut_doaaccounts_adapter_loginCancle_001)
{
    doaAccountsadapter->m_doaProvider = new DOAQQProvider(doaAccountsadapter);
    Stub s;
    s.set(ADDR(DOAAccountsadapter, loginCancle), ADDR(ut_doaaccounts_adapter, sendPropertiesChanged));
    m_stubmsg = "uostest";
    doaAccountsadapter->loginCancle();
    EXPECT_EQ(m_stubmsg, "uostest2021");
}

TEST_F(ut_doaaccounts_adapter, ut_doaaccounts_adapter_setDoaProvider_001)
{
    doaAccountsadapter->m_doaProvider = new DOAQQProvider(doaAccountsadapter);
    EXPECT_TRUE(doaAccountsadapter->m_doaProvider);
    doaAccountsadapter->setDoaProvider(nullptr);
    EXPECT_FALSE(doaAccountsadapter->m_doaProvider);
}
