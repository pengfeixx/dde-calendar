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
#include "ut_doaaccount.h"
#include "../../third-party_stub/stub.h"
#include "dbus/doaaccountdbus.h"
#include "dbus/doaaccountpassword.h"
#include "aesencryption.h"

#include <QDebug>
#include <QSignalSpy>

ut_doaaccount::ut_doaaccount()
{

}

static QString resultMsg = "";
static bool resultbool = false;
void ut_doaaccount::SetUp()
{
    doaAccount = new DOAAccount();
}

void ut_doaaccount::TearDown()
{
    delete doaAccount;
    doaAccount = nullptr;
}

bool ut_doaaccount::stub_resutlMsg()
{
    resultMsg = "resultMsg";
    return false;
}

bool ut_doaaccount::stub_resultFalse()
{
    return resultbool;
}

TEST_F(ut_doaaccount, ut_doaaccount_getAccountName_001)
{
    doaAccount->setAccountName("1234@qq.com");
    EXPECT_EQ(doaAccount->getAccountName(), "1234@qq.com");
}

TEST_F(ut_doaaccount, ut_doaaccount_setAccountName_001)
{
    doaAccount->setAccountName("1234@qq.com");
    EXPECT_EQ(doaAccount->getAccountName(), "1234@qq.com");
}

TEST_F(ut_doaaccount, ut_doaaccount_getAccountPassword_001)
{
    doaAccount->setAccountPassword("1234@qq.com");
    EXPECT_EQ(doaAccount->getAccountPassword(), "1234@qq.com");
}

TEST_F(ut_doaaccount, ut_doaaccount_setAccountPassword_001)
{
    doaAccount->setAccountPassword("1234@qq.com");
    EXPECT_EQ(doaAccount->getAccountPassword(), "1234@qq.com");
}

TEST_F(ut_doaaccount, ut_doaaccount_getUserName_001)
{
    doaAccount->setUserName("1234@qq.com");
    EXPECT_EQ(doaAccount->getUserName(), "1234@qq.com");
}

TEST_F(ut_doaaccount, ut_doaaccount_setUserName_001)
{
    doaAccount->setUserName("1234@qq.com");
    EXPECT_EQ(doaAccount->getUserName(), "1234@qq.com");
}

TEST_F(ut_doaaccount, ut_doaaccount_getUrl_001)
{
    doaAccount->setUrl("1234@qq.com");
    EXPECT_EQ(doaAccount->getUrl(), "1234@qq.com");
}

TEST_F(ut_doaaccount, ut_doaaccount_setUrl_001)
{
    doaAccount->setUrl("1234@qq.com");
    EXPECT_EQ(doaAccount->getUrl(), "1234@qq.com");
}

TEST_F(ut_doaaccount, ut_doaaccount_getPath_001)
{
    doaAccount->setPath("1234@qq.com");
    EXPECT_EQ(doaAccount->getPath(), "1234@qq.com");
}

TEST_F(ut_doaaccount, ut_doaaccount_setPath_001)
{
    doaAccount->setPath("1234@qq.com");
    EXPECT_EQ(doaAccount->getPath(), "1234@qq.com");
}

TEST_F(ut_doaaccount, ut_doaaccount_getProtocol_001)
{
    doaAccount->setProtocol(DOAAccount::AccountProtocol::Protocol_CalDav);
    EXPECT_EQ(doaAccount->getProtocol(), DOAAccount::AccountProtocol::Protocol_CalDav);
}

TEST_F(ut_doaaccount, ut_doaaccount_setProtocol_001)
{
    doaAccount->setProtocol(DOAAccount::AccountProtocol::Protocol_CalDav);
    EXPECT_EQ(doaAccount->getProtocol(), DOAAccount::AccountProtocol::Protocol_CalDav);
}

TEST_F(ut_doaaccount, ut_doaaccount_getAccountID_001)
{
    doaAccount->setAccountID("1234@qq.com");
    EXPECT_EQ(doaAccount->getAccountID(), "1234@qq.com");
}

TEST_F(ut_doaaccount, ut_doaaccount_setAccountID_001)
{
    doaAccount->setAccountID("1234@qq.com");
    EXPECT_EQ(doaAccount->getAccountID(), "1234@qq.com");
}

TEST_F(ut_doaaccount, ut_doaaccount_getAccountState_001)
{
    doaAccount->setAccountState(DOAAccount::AccountState::Account_Success);
    EXPECT_EQ(doaAccount->getAccountState(), DOAAccount::AccountState::Account_Success);
}

TEST_F(ut_doaaccount, ut_doaaccount_setAccountState_001)
{
    doaAccount->setAccountState(DOAAccount::AccountState::Account_Success);
    EXPECT_EQ(doaAccount->getAccountState(), DOAAccount::AccountState::Account_Success);
}

TEST_F(ut_doaaccount, ut_doaaccount_getAddAccountDateTime_001)
{
    QDateTime currdate = QDateTime::currentDateTime();
    doaAccount->setAddAccountDateTime(currdate);
    EXPECT_EQ(doaAccount->getAddAccountDateTime(), currdate);
}

TEST_F(ut_doaaccount, ut_doaaccount_setAddAccountDateTime_001)
{
    QDateTime currdate = QDateTime::currentDateTime();
    doaAccount->setAddAccountDateTime(currdate);
    EXPECT_EQ(doaAccount->getAddAccountDateTime(), currdate);
}

TEST_F(ut_doaaccount, ut_doaaccount_setAccountDBusPath_001)
{
    doaAccount->setAccountDBusPath("/com/test/uos");
    EXPECT_EQ(doaAccount->m_DBusPath, "/com/test/uos");
}

TEST_F(ut_doaaccount, ut_doaaccount_addApplyObject_001)
{
    DOAApplyToObject applyObject;
    applyObject.setAppName("dde-calendar");
    applyObject.setIsApply(true);
    doaAccount->addApplyObject(applyObject);
    EXPECT_EQ(doaAccount->getApplyObject().count(), 1);
    doaAccount->addApplyObject(applyObject);
    EXPECT_EQ(doaAccount->getApplyObject().count(), 1);

}

TEST_F(ut_doaaccount, ut_doaaccount_setAccountInfo_001)
{
    DOAAccountList::AccountInfo accountInfo;
    accountInfo.accountName = "1234@qq.com";
    accountInfo.accountID = "1234";
    accountInfo.accountAddTime = QDateTime::fromString("2021-10-12 13:11:15", "yyyy-MM-dd hh:mm:ss");
    doaAccount->setAccountInfo(accountInfo);
    EXPECT_EQ(doaAccount->getAccountID(), "1234");
}

TEST_F(ut_doaaccount, ut_doaaccount_setAccountInfo_002)
{
    DOAAccountList::AccountInfo accountInfo;
    accountInfo.accountName = "1234@qq.com";
    accountInfo.accountID = "1234";
    accountInfo.accountAddTime = QDateTime::fromString("2021-10-12 13:11:15", "yyyy-MM-dd hh:mm:ss");
    accountInfo.applyToCalendarState.isValid = true;
    doaAccount->setAccountInfo(accountInfo);
    EXPECT_EQ(doaAccount->getAccountID(), "1234");
    EXPECT_EQ(doaAccount->getApplyObject().at(0).appName(), "dde-calendar");
}

TEST_F(ut_doaaccount, ut_doaaccount_setAccountInfo_003)
{
    DOAAccountList::AccountInfo accountInfo;
    accountInfo.accountName = "1234@qq.com";
    accountInfo.accountID = "1234";
    accountInfo.accountAddTime = QDateTime::fromString("2021-10-12 13:11:15", "yyyy-MM-dd hh:mm:ss");
    accountInfo.applyToEMailState.isValid = true;
    doaAccount->setAccountInfo(accountInfo);
    EXPECT_EQ(doaAccount->getApplyObject().at(0).appName(), "deepin-mail");
}

TEST_F(ut_doaaccount, ut_doaaccount_updateUserName_001)
{
    Stub st;
    st.set(ADDR(DOAAccountDBus, setUserName), ADDR(ut_doaaccount, stub_resutlMsg));
    resultMsg = "updateUserName";
    doaAccount->updateUserName("123456");
    EXPECT_EQ(resultMsg, "updateUserName");
}

TEST_F(ut_doaaccount, ut_doaaccount_updateUserName_002)
{
    Stub st;
    st.set(ADDR(DOAAccountDBus, setUserName), ADDR(ut_doaaccount, stub_resutlMsg));
    resultMsg = "updateUserName";
    doaAccount->createDBus();
    doaAccount->m_accountDBus = (DOAAccountDBus*)doaAccount;
    doaAccount->updateUserName("123456");
    EXPECT_EQ(resultMsg, "resultMsg");
}

TEST_F(ut_doaaccount, ut_doaaccount_updatePassword_001)
{
    Stub st;
    st.set(ADDR(DOAAccountPassword, changePassword), ADDR(ut_doaaccount, stub_resutlMsg));
    resultMsg = "updatePassword";
    doaAccount->updatePassword("123456");
    EXPECT_EQ(resultMsg, "updatePassword");
}

TEST_F(ut_doaaccount, ut_doaaccount_updatePassword_002)
{
    Stub st;
    st.set(ADDR(DOAAccountPassword, changePassword), ADDR(ut_doaaccount, stub_resutlMsg));
    resultMsg = "updateUserName";
    doaAccount->createDBus();
    doaAccount->m_passwordDBus = (DOAAccountPassword*)doaAccount;
    doaAccount->updatePassword("123456");
    EXPECT_EQ(resultMsg, "resultMsg");
    EXPECT_EQ(doaAccount->getAccountPassword(), "123456");
}

TEST_F(ut_doaaccount, ut_doaaccount_updateApplyTo_001)
{
    DOAApplyToObject applyObject;
    applyObject.setAppName("dde-calendar");
    applyObject.setIsApply(true);
    doaAccount->addApplyObject(applyObject);
    Stub st;
    st.set(ADDR(DOAAccountDBus, setCalendarDisabled), ADDR(ut_doaaccount, stub_resutlMsg));
    resultMsg = "updateApplyTo";
    doaAccount->updateApplyTo(applyObject);
    EXPECT_EQ(resultMsg, "updateApplyTo");
    EXPECT_EQ(doaAccount->getApplyObject().at(0).isApply(), true);
}

TEST_F(ut_doaaccount, ut_doaaccount_updateApplyTo_002)
{
    DOAApplyToObject applyObject;
    applyObject.setAppName("dde-calendar");
    applyObject.setIsApply(false);
    doaAccount->addApplyObject(applyObject);
    Stub st;
    st.set(ADDR(DOAAccountDBus, setCalendarDisabled), ADDR(ut_doaaccount, stub_resutlMsg));

    resultMsg = "updateUserName";
    doaAccount->createDBus();
    doaAccount->m_accountDBus = (DOAAccountDBus*)doaAccount;
    doaAccount->updateApplyTo(applyObject);
    EXPECT_EQ(resultMsg, "resultMsg");
    EXPECT_EQ(doaAccount->getApplyObject().at(0).isApply(), false);
}

TEST_F(ut_doaaccount, ut_doaaccount_slotAccountStatus_001)
{
    Stub st;
    st.set(ADDR(DOAAccountPassword, getPassword), ADDR(ut_doaaccount, stub_resutlMsg));
    resultMsg = "updateApplyTo";
    doaAccount->slotAccountStatus(2);
    EXPECT_EQ(resultMsg, "updateApplyTo");
    EXPECT_EQ(doaAccount->m_state, DOAAccount::AccountState::Account_ServerException);
}

TEST_F(ut_doaaccount, ut_doaaccount_slotAccountStatus_002)
{
    Stub st;
    st.set(ADDR(DOAAccountPassword, getPassword), ADDR(ut_doaaccount, stub_resutlMsg));
    resultMsg = "updateApplyTo";
    doaAccount->createDBus();
    doaAccount->m_passwordDBus = (DOAAccountPassword*)doaAccount;
    doaAccount->slotAccountStatus(5);
    EXPECT_EQ(resultMsg, "resultMsg");
    EXPECT_EQ(doaAccount->m_state, DOAAccount::AccountState::Account_AuthenticationFailed);
}

TEST_F(ut_doaaccount, ut_doaaccount_slotGetPassword_001)
{
    QString data = "12345678";
    QString data1= "13fcae1172e248c9de16ca4b8f8b87b2";
    doaAccount->slotGetPassword(data1);
    EXPECT_EQ(doaAccount->m_accountPassword, data);
}

TEST_F(ut_doaaccount, ut_doaaccount_slotGetPassword_002)
{
    QSignalSpy spy(doaAccount,SIGNAL(signalPasswordChanged(const QString &)));
    QString data = "12345678";
    QString data1= "13fcae1172e248c9de16ca4b8f8b87b2";
    doaAccount->m_accountPassword = "12345678";
    doaAccount->slotGetPassword(data1);
    EXPECT_EQ(doaAccount->m_accountPassword, data);
    EXPECT_EQ(spy.count(), 0);
}

TEST_F(ut_doaaccount, ut_doaaccount_slotRemove_001)
{
    Stub st;
    st.set(ADDR(DOAAccountDBus, remove), ADDR(ut_doaaccount, stub_resutlMsg));
    resultMsg = "slotRemove";
    doaAccount->createDBus();
    doaAccount->m_accountDBus = (DOAAccountDBus*)doaAccount;
    doaAccount->slotRemove();
    EXPECT_EQ(resultMsg, "resultMsg");
}

TEST_F(ut_doaaccount, ut_doaaccount_slotRemove_002)
{
    Stub st;
    st.set(ADDR(DOAAccountDBus, remove), ADDR(ut_doaaccount, stub_resutlMsg));
    resultMsg = "slotRemove";
    doaAccount->slotRemove();
    EXPECT_EQ(resultMsg, "slotRemove");
}

TEST_F(ut_doaaccount, ut_doaaccount_slotUserNameChanged_001)
{
    doaAccount->m_displayName = "123456";
    doaAccount->slotUserNameChanged("12345");
    EXPECT_EQ(doaAccount->m_displayName, "12345");
}

TEST_F(ut_doaaccount, ut_doaaccount_slotUserNameChanged_002)
{
    QSignalSpy spy(doaAccount,SIGNAL(signalUserNameChanged(const QString &)));
    doaAccount->m_displayName = "123456";
    doaAccount->slotUserNameChanged("123456");
    EXPECT_EQ(doaAccount->m_displayName, "123456");
    EXPECT_EQ(spy.count(), 0);
}

TEST_F(ut_doaaccount, ut_doaaccount_slotCheckState_001)
{
    Stub st;
    st.set(ADDR(DOAAccountDBus, checkAccountState), ADDR(ut_doaaccount, stub_resutlMsg));
    resultMsg = "slotCheckState";
    doaAccount->createDBus();
    doaAccount->m_accountDBus = (DOAAccountDBus*)doaAccount;
    doaAccount->slotCheckState();
    EXPECT_EQ(resultMsg, "resultMsg");
}

TEST_F(ut_doaaccount, ut_doaaccount_slotCheckState_002)
{
    Stub st;
    st.set(ADDR(DOAAccountDBus, checkAccountState), ADDR(ut_doaaccount, stub_resutlMsg));
    resultMsg = "slotCheckState";
    doaAccount->slotCheckState();
    EXPECT_EQ(resultMsg, "slotCheckState");
}

TEST_F(ut_doaaccount, ut_doaaccount_createDBus_001)
{
    Stub st;
    st.set(ADDR(QDBusAbstractInterface, isValid), ADDR(ut_doaaccount, stub_resultFalse));
    doaAccount->createDBus();
    EXPECT_EQ(doaAccount->m_accountDBus, nullptr);
    EXPECT_EQ(doaAccount->m_passwordDBus, nullptr);
}

TEST_F(ut_doaaccount, ut_doaaccount_createDBus_002)
{
    Stub st;
    st.set(ADDR(QDBusAbstractInterface, isValid), ADDR(ut_doaaccount, stub_resultFalse));
    resultbool = true;
    doaAccount->createDBus();
    EXPECT_TRUE(doaAccount->m_accountDBus);
    EXPECT_TRUE(doaAccount->m_passwordDBus);
}


