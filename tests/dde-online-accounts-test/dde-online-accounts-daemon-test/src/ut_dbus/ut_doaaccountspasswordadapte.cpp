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
#include "ut_doaaccountspasswordadapte.h"
#include "controller/doaqqprovider.h"
#include "aesencryption.h"
#include "../../third-party_stub/stub.h"

static int callcnt = 0;

ut_doaaccountspasswordadapte::ut_doaaccountspasswordadapte()
{
    doaAccountsadapter = new DOAAccountsadapter();
}

void ut_doaaccountspasswordadapte::SetUp()
{
    doaAccountsPassWordadapter = new DOAAccountsPassWordadapter(doaAccountsadapter);
}

void ut_doaaccountspasswordadapte::TearDown()
{
    delete doaAccountsadapter;
}

bool ut_doaaccountspasswordadapte::stub_resultAllFalse()
{
    return false;
}

bool ut_doaaccountspasswordadapte::stub_resultTrue()
{
    return true;
}

bool ut_doaaccountspasswordadapte::stub_result()
{
    if(callcnt == 0){
        callcnt++;
        return true;
    }else {
        return false;
    }
}

TEST_F(ut_doaaccountspasswordadapte, ut_doaaccountspasswordadapte_getPassword_001)
{
    doaAccountsadapter->setDoaProvider(new DOAQQProvider(doaAccountsadapter));
    doaAccountsadapter->getDoaProvider()->setAccountPassword("1233455");
    EXPECT_EQ(doaAccountsPassWordadapter->getPassword(), "1233455");
}

TEST_F(ut_doaaccountspasswordadapte, ut_doaaccountspasswordadapte_ChangePassword_001)
{
    QString password;
    EXPECT_EQ(doaAccountsPassWordadapter->ChangePassword(password), false);
}

TEST_F(ut_doaaccountspasswordadapte, ut_doaaccountspasswordadapte_ChangePassword_002)
{
    doaAccountsadapter->setDoaProvider(new DOAQQProvider(doaAccountsadapter));
    QString password = "123456";
    Stub s;
    s.set(ADDR(AESEncryption, ecb_encrypt), ADDR(ut_doaaccountspasswordadapte, stub_resultAllFalse));

    EXPECT_EQ(doaAccountsPassWordadapter->ChangePassword(password), false);
}

TEST_F(ut_doaaccountspasswordadapte, ut_doaaccountspasswordadapte_ChangePassword_003)
{
    doaAccountsadapter->setDoaProvider(new DOAQQProvider(doaAccountsadapter));
    QString password = "dc354b248cd53cdc434251524c53a961";

    //123456
    //dc354b248cd53cdc434251524c53a961 TKEY
    //09e27c91f856253e3434d2a3f736fbb9 SKEY
    doaAccountsPassWordadapter->ChangePassword(password);

    EXPECT_EQ(doaAccountsadapter->getDoaProvider()->getAccountPassword(), "dc354b248cd53cdc434251524c53a961");
}

TEST_F(ut_doaaccountspasswordadapte, ut_doaaccountspasswordadapte_ChangePassword_004)
{
    doaAccountsadapter->setDoaProvider(new DOAQQProvider(doaAccountsadapter));
    QString password = "123456";
    Stub s;
    s.set(ADDR(AESEncryption, ecb_encrypt), ADDR(ut_doaaccountspasswordadapte, stub_result));

    EXPECT_EQ(doaAccountsPassWordadapter->ChangePassword(password), false);
}
