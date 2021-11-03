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
#include "ut_doaonlineaccount.h"
#include "../../third-party_stub/stub.h"
#include "doadataconversion.h"

ut_doaonlineaccount::ut_doaonlineaccount()
{

}

void ut_doaonlineaccount::SetUp()
{
    doaOnlineAccount = new DOAOnlineAccount();
}

void ut_doaonlineaccount::TearDown()
{
    delete doaOnlineAccount;
    doaOnlineAccount = nullptr;
}

static QString resultMsg = "";
void ut_doaonlineaccount::stub_resutlMsg()
{
    resultMsg = "resultMsg";
}

TEST_F(ut_doaonlineaccount, ut_doaonlineaccount_icon_001)
{
    QIcon icon = doaOnlineAccount->icon();
}

TEST_F(ut_doaonlineaccount, ut_doaonlineaccount_name_001)
{
    EXPECT_EQ(doaOnlineAccount->name(), "onlineaccount");
}

TEST_F(ut_doaonlineaccount, ut_doaonlineaccount_availPage_001)
{
    QStringList pageList = doaOnlineAccount->availPage();
    EXPECT_EQ(pageList.count(), 3);
}

TEST_F(ut_doaonlineaccount, ut_doaonlineaccount_translationPath_001)
{
    QString translationPath = doaOnlineAccount->translationPath();
    EXPECT_EQ(translationPath, ":/translations/dde-online-accounts-plugin_%1.ts");
}

TEST_F(ut_doaonlineaccount, ut_doaonlineaccount_load_001)
{
    resultMsg = "load";
    Stub st;
    st.set(ADDR(DOAAccountListWidget, slotGetAccountListSuccess), ADDR(ut_doaonlineaccount, stub_resutlMsg));
    doaOnlineAccount->m_accountListWidget = new DOAAccountListWidget();
    doaOnlineAccount->m_accountListWidget->setModel(doaOnlineAccount->m_accountModel);
    doaOnlineAccount->load("ADD");
    delete doaOnlineAccount->m_accountListWidget;
    EXPECT_EQ(resultMsg, "resultMsg");

}

TEST_F(ut_doaonlineaccount, ut_doaonlineaccount_load_002)
{
    resultMsg = "load";
    Stub st;
    st.set(remvoeAccountJsonObjectToInfo, ADDR(ut_doaonlineaccount, stub_resutlMsg));
    doaOnlineAccount->m_accountListWidget = new DOAAccountListWidget();
    doaOnlineAccount->m_accountListWidget->setModel(doaOnlineAccount->m_accountModel);
    doaOnlineAccount->load("DEL");
    EXPECT_EQ(resultMsg, "load");
}
