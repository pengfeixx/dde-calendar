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
#include "ut_doaaccountinfowidget.h"
#include "../../third-party_stub/stub.h"
#include "data/doaaccountmodel.h"
#include "dialog/doaaccountremovedialog.h"

#include <QSignalSpy>

ut_doaaccountinfowidget::ut_doaaccountinfowidget()
{

}

static QString resultMsg = "";

void ut_doaaccountinfowidget::stub_slotUpdateCurrentAccount()
{
    resultMsg = "resultMsg";
}

int ut_doaaccountinfowidget::stub_slotDialogExec()
{
    resultMsg = "resultMsg";
    return 0;
}

void ut_doaaccountinfowidget::SetUp()
{
    doaAccountInfoWidget = new DOAAccountInfoWidget();
}

void ut_doaaccountinfowidget::TearDown()
{
    delete doaAccountInfoWidget;
    doaAccountInfoWidget = nullptr;
}

TEST_F(ut_doaaccountinfowidget, ut_doaaccountinfowidget_setModel_001)
{
    DOAAccountModel modele;
    doaAccountInfoWidget->setModel(&modele);
    EXPECT_EQ(doaAccountInfoWidget->m_accountModel, &modele);
    DOAAccountModel modele1;
    doaAccountInfoWidget->setModel(&modele1);
    EXPECT_EQ(doaAccountInfoWidget->m_accountModel, &modele1);
}

TEST_F(ut_doaaccountinfowidget, ut_doaaccountinfowidget_setModel_002)
{
    Stub st;
    st.set(ADDR(DOAAccountInfoWidget, slotUpdateCurrentAccount),ADDR(ut_doaaccountinfowidget, stub_slotUpdateCurrentAccount));
    doaAccountInfoWidget->setModel(nullptr);
    EXPECT_EQ(doaAccountInfoWidget->m_accountModel, nullptr);
}

TEST_F(ut_doaaccountinfowidget, ut_doaaccountinfowidget_initData_001)
{
    QSignalSpy spy(doaAccountInfoWidget->m_errorWidget, SIGNAL(sign_EventQuit()));
    doaAccountInfoWidget->initData();
    EXPECT_EQ(spy.count(), 1);
}

TEST_F(ut_doaaccountinfowidget, ut_doaaccountinfowidget_slotTryAgain_001)
{
    DOAAccountModel modele;
    doaAccountInfoWidget->setModel(&modele);
    Stub st;
    st.set(ADDR(DOAAccount, slotCheckState),ADDR(ut_doaaccountinfowidget, stub_slotUpdateCurrentAccount));
    resultMsg = "slotTryAgain";
    doaAccountInfoWidget->slotTryAgain();
    EXPECT_EQ(resultMsg, "slotTryAgain");
}

TEST_F(ut_doaaccountinfowidget, ut_doaaccountinfowidget_slotTryAgain_002)
{
    DOAAccountModel modele;
    modele.m_currentAccount = new DOAAccount(doaAccountInfoWidget);
    doaAccountInfoWidget->setModel(&modele);
    Stub st;
    st.set(ADDR(DOAAccount, slotCheckState),ADDR(ut_doaaccountinfowidget, stub_slotUpdateCurrentAccount));
    resultMsg = "slotTryAgain";
    doaAccountInfoWidget->slotTryAgain();
    EXPECT_EQ(resultMsg, "resultMsg");
}

TEST_F(ut_doaaccountinfowidget, ut_doaaccountinfowidget_slotUpdateCurrentAccount_001)
{
    DOAAccountModel modele;
    doaAccountInfoWidget->setModel(&modele);
    doaAccountInfoWidget->slotUpdateCurrentAccount();
    EXPECT_EQ(doaAccountInfoWidget->m_accountInfo->m_displayName, "");
}

TEST_F(ut_doaaccountinfowidget, ut_doaaccountinfowidget_slotUpdateCurrentAccount_002)
{
    DOAAccountModel modele;
    modele.m_currentAccount = new DOAAccount(doaAccountInfoWidget);
    modele.m_currentAccount->setUserName("12345");
    doaAccountInfoWidget->setModel(&modele);
    doaAccountInfoWidget->slotUpdateCurrentAccount();
    EXPECT_EQ(doaAccountInfoWidget->m_accountInfo->m_displayName, "12345");
}

TEST_F(ut_doaaccountinfowidget, ut_doaaccountinfowidget_slotDeleteCurrentAccount_001)
{

}

TEST_F(ut_doaaccountinfowidget, ut_doaaccountinfowidget_slotUpdateUserName_001)
{
    DOAAccountModel modele;
    doaAccountInfoWidget->setModel(&modele);
    Stub st;
    st.set(ADDR(DOAAccount, updateUserName), ADDR(ut_doaaccountinfowidget, stub_slotUpdateCurrentAccount));
    resultMsg = "slotUpdateUserName";
    doaAccountInfoWidget->slotUpdateUserName("1234");
    EXPECT_EQ(resultMsg, "slotUpdateUserName");
}

TEST_F(ut_doaaccountinfowidget, ut_doaaccountinfowidget_slotUpdateUserName_002)
{
    DOAAccountModel modele;
    modele.m_currentAccount = new DOAAccount(doaAccountInfoWidget);
    doaAccountInfoWidget->setModel(&modele);
    Stub st;
    st.set(ADDR(DOAAccount, updateUserName), ADDR(ut_doaaccountinfowidget, stub_slotUpdateCurrentAccount));
    resultMsg = "slotUpdateUserName";
    doaAccountInfoWidget->slotUpdateUserName("1234");
    EXPECT_EQ(resultMsg, "resultMsg");
}

TEST_F(ut_doaaccountinfowidget, ut_doaaccountinfowidget_slotUpdatePassword_001)
{
    DOAAccountModel modele;
    doaAccountInfoWidget->setModel(&modele);
    Stub st;
    st.set(ADDR(DOAAccount, updatePassword), ADDR(ut_doaaccountinfowidget, stub_slotUpdateCurrentAccount));
    resultMsg = "slotUpdatePassword";
    doaAccountInfoWidget->slotUpdatePassword("1234");
    EXPECT_EQ(resultMsg, "slotUpdatePassword");
}

TEST_F(ut_doaaccountinfowidget, ut_doaaccountinfowidget_slotUpdatePassword_002)
{
    DOAAccountModel modele;
    modele.m_currentAccount = new DOAAccount(doaAccountInfoWidget);
    doaAccountInfoWidget->setModel(&modele);
    Stub st;
    st.set(ADDR(DOAAccount, updatePassword), ADDR(ut_doaaccountinfowidget, stub_slotUpdateCurrentAccount));
    resultMsg = "slotUpdatePassword";
    doaAccountInfoWidget->slotUpdatePassword("1234");
    EXPECT_EQ(resultMsg, "resultMsg");
}

TEST_F(ut_doaaccountinfowidget, ut_doaaccountinfowidget_slotShowErrorMsg_001)
{
    DOAAccountModel modele;
    modele.m_currentAccount = new DOAAccount(doaAccountInfoWidget);
    doaAccountInfoWidget->setModel(&modele);
    Stub st;
    st.set(ADDR(DOAErrorWidget, setErrorMsg), ADDR(ut_doaaccountinfowidget, stub_slotUpdateCurrentAccount));
    resultMsg = "slotShowErrorMsg";
    doaAccountInfoWidget->slotShowErrorMsg();
    EXPECT_EQ(resultMsg, "resultMsg");
}

TEST_F(ut_doaaccountinfowidget, ut_doaaccountinfowidget_slotUpdateApplyToItem_001)
{
    DOAAccountModel modele;
    doaAccountInfoWidget->setModel(&modele);
    DOAApplyToObject app;
    Stub st;
    st.set(ADDR(DOAAccount, updateApplyTo), ADDR(ut_doaaccountinfowidget, stub_slotUpdateCurrentAccount));
    resultMsg = "slotUpdateApplyToItem";
    doaAccountInfoWidget->slotUpdateApplyToItem(app);
    EXPECT_EQ(resultMsg, "slotUpdateApplyToItem");
}

TEST_F(ut_doaaccountinfowidget, ut_doaaccountinfowidget_slotUpdateApplyToItem_002)
{
    DOAApplyToObject app;
    DOAAccountModel modele;
    modele.m_currentAccount = new DOAAccount(doaAccountInfoWidget);
    doaAccountInfoWidget->setModel(&modele);
    Stub st;
    st.set(ADDR(DOAAccount, updateApplyTo), ADDR(ut_doaaccountinfowidget, stub_slotUpdateCurrentAccount));
    resultMsg = "slotUpdateApplyToItem";
    doaAccountInfoWidget->slotUpdateApplyToItem(app);
    EXPECT_EQ(resultMsg, "resultMsg");
}

TEST_F(ut_doaaccountinfowidget, ut_doaaccountinfowidget_slotPropertyChanged_001)
{

}

TEST_F(ut_doaaccountinfowidget, ut_doaaccountinfowidget_slotPropertyChanged_002)
{

}


