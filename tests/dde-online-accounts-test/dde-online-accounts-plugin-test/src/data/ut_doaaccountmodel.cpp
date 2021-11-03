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
#include "ut_doaaccountmodel.h"
#include "../../third-party_stub/stub.h"
#include "consts.h"

#include <QSignalSpy>

ut_doaaccountmodel::ut_doaaccountmodel()
{

}

static QString resultMsg = "";

void ut_doaaccountmodel::SetUp()
{
    doaAccountModel = new DOAAccountModel();
}

void ut_doaaccountmodel::TearDown()
{
    delete doaAccountModel;
    doaAccountModel = nullptr;
}

void ut_doaaccountmodel::stub_resutlMsg()
{
    resultMsg = "resultMsg";
}

TEST_F(ut_doaaccountmodel, ut_doaaccountmodel_state_001)
{
    doaAccountModel->setState(DOAAccountModel::Account_Details);
    EXPECT_EQ(doaAccountModel->state(), DOAAccountModel::Account_Details);
}

TEST_F(ut_doaaccountmodel, ut_doaaccountmodel_setState_001)
{
    QSignalSpy spy(doaAccountModel, SIGNAL(signalChangeState()));
    doaAccountModel->setState(DOAAccountModel::Account_Details);
    EXPECT_EQ(doaAccountModel->state(), DOAAccountModel::Account_Details);
    EXPECT_EQ(spy.count(), 1);
}

TEST_F(ut_doaaccountmodel, ut_doaaccountmodel_setState_002)
{
    QSignalSpy spy(doaAccountModel, SIGNAL(signalChangeState()));
    doaAccountModel->setState(DOAAccountModel::Account_Details);
    doaAccountModel->setState(DOAAccountModel::Account_Init);
    EXPECT_EQ(doaAccountModel->state(), DOAAccountModel::Account_Init);
    EXPECT_EQ(spy.count(), 2);
}

TEST_F(ut_doaaccountmodel, ut_doaaccountmodel_setState_003)
{
    QSignalSpy spy(doaAccountModel, SIGNAL(signalChangeState()));
    doaAccountModel->setState(DOAAccountModel::Account_Details);
    doaAccountModel->setState(DOAAccountModel::Account_Details);
    EXPECT_EQ(doaAccountModel->state(), DOAAccountModel::Account_Details);
    EXPECT_EQ(spy.count(), 1);
}

TEST_F(ut_doaaccountmodel, ut_doaaccountmodel_getAccount_001)
{
    DOAAccount doaa;
    doaa.setAccountID("12345");
    doaa.setAccountName("12345@qq.com");
    doaAccountModel->m_accounts["12345"] = &doaa;
    DOAAccount * doatmp = doaAccountModel->getAccount("12346");

    EXPECT_EQ(doatmp, nullptr);
}

TEST_F(ut_doaaccountmodel, ut_doaaccountmodel_getAccount_002)
{
    DOAAccount doaa;
    doaa.setAccountID("12345");
    doaa.setAccountName("12345@qq.com");
    doaAccountModel->m_accounts["12345"] = &doaa;
    DOAAccount * doatmp = doaAccountModel->getAccount("12345");

    EXPECT_EQ(doatmp->getAccountName(), "12345@qq.com");
}

TEST_F(ut_doaaccountmodel, ut_doaaccountmodel_getAccountMap_001)
{
    DOAAccount doaa;
    doaa.setAccountID("12345");
    doaa.setAccountName("12345@qq.com");
    doaAccountModel->m_accounts["12345"] = &doaa;
    QMap<QString, DOAAccount *> doamap = doaAccountModel->getAccountMap();
    EXPECT_EQ(doamap["12345"]->getAccountName(), "12345@qq.com");
}

TEST_F(ut_doaaccountmodel, ut_doaaccountmodel_getAccountMap_002)
{
    QMap<QString, DOAAccount *> doamap = doaAccountModel->getAccountMap();
    EXPECT_EQ(doamap.count(), 0);
}

TEST_F(ut_doaaccountmodel, ut_doaaccountmodel_setCurrentAccountByID_001)
{
    DOAAccount doaa;
    doaa.setAccountID("12345");
    doaa.setAccountName("12345@qq.com");
    doaAccountModel->m_accounts["12345"] = &doaa;
    doaAccountModel->setCurrentAccountByID("12345");

    EXPECT_EQ(doaAccountModel->m_currentAccount->getAccountID(), "12345");
}

TEST_F(ut_doaaccountmodel, ut_doaaccountmodel_setCurrentAccountByID_002)
{
    DOAAccount doaa;
    doaa.setAccountID("12345");
    doaa.setAccountName("12345@qq.com");
    doaAccountModel->m_accounts["12345"] = &doaa;
    DOAAccount doaa1;
    doaa1.setAccountID("123451");
    doaa1.setAccountName("123451@qq.com");
    doaAccountModel->m_accounts["123451"] = &doaa1;
    doaAccountModel->setCurrentAccountByID("12345");
    doaAccountModel->setCurrentAccountByID("12345");
    EXPECT_EQ(doaAccountModel->m_currentAccount->getAccountID(), "12345");
}

TEST_F(ut_doaaccountmodel, ut_doaaccountmodel_setCurrentAccountByID_003)
{
    DOAAccount doaa;
    doaa.setAccountID("12345");
    doaa.setAccountName("12345@qq.com");
    doaAccountModel->m_accounts["12345"] = &doaa;

    doaAccountModel->setCurrentAccountByID("123451");
    EXPECT_EQ(doaAccountModel->m_currentAccount, nullptr);
}

TEST_F(ut_doaaccountmodel, ut_doaaccountmodel_getCurrentAccount_001)
{
    DOAAccount doaa;
    doaa.setAccountID("12345");
    doaa.setAccountName("12345@qq.com");
    doaAccountModel->m_accounts["12345"] = &doaa;
    doaAccountModel->setCurrentAccountByID("12345");

    EXPECT_EQ(doaAccountModel->getCurrentAccount()->getAccountID(), "12345");
}

TEST_F(ut_doaaccountmodel, ut_doaaccountmodel_createAccount_001)
{
    DOAAccountList::AccountInfo accountinfo;

    accountinfo.accountID ="12345";
    accountinfo.accountName = "12345@qq.com";

    DOAAccount *doaa = doaAccountModel->createAccount(accountinfo);

    EXPECT_EQ(doaa->getAccountID(), "12345");
}

TEST_F(ut_doaaccountmodel, ut_doaaccountmodel_slotAddAccount_001)
{
    AddAccountInfo accountinfo;
    Stub st;
    st.set(ADDR(DOAAccountManageDBus, addAccount), ADDR(ut_doaaccountmodel, stub_resutlMsg));
    resultMsg = "slotAddAccount";
    doaAccountModel->slotAddAccount(accountinfo);
    EXPECT_EQ(resultMsg, "resultMsg");
}

TEST_F(ut_doaaccountmodel, ut_doaaccountmodel_slotCancleLogin_001)
{
    Stub st;
    st.set(ADDR(DOAAccountManageDBus, loginCancle), ADDR(ut_doaaccountmodel, stub_resutlMsg));
    resultMsg = "slotCancleLogin";
    doaAccountModel->slotCancleLogin("123434");

    EXPECT_EQ(resultMsg, "resultMsg");
}

TEST_F(ut_doaaccountmodel, ut_doaaccountmodel_slotGetAccountList_001)
{
    DOAAccountList::AccountInfoList infoList;
    infoList.accountCount = 2;
    infoList.interfaceStatus = 0;

    DOAAccountList::AccountInfo accountInfo;
    accountInfo.accountName = "1234@qq.com";
    accountInfo.accountID = "1234";
    accountInfo.accountAddTime = QDateTime::fromString("2021-10-12 13:11:15", "yyyy-MM-dd hh:mm:ss");
    infoList.m_infoList.append(accountInfo);
    DOAAccountList::AccountInfo accountInfo1;
    accountInfo1.accountName = "12341@qq.com";
    accountInfo1.accountID = "12341";
    accountInfo1.accountAddTime = QDateTime::fromString("2021-10-11 13:11:15", "yyyy-MM-dd hh:mm:ss");
    infoList.m_infoList.append(accountInfo1);
    doaAccountModel->slotGetAccountList(infoList);
    EXPECT_EQ(doaAccountModel->m_currentAccount->getAccountID(), "1234");
}

TEST_F(ut_doaaccountmodel, ut_doaaccountmodel_slotGetAccountList_002)
{
    DOAAccountList::AccountInfoList infoList;
    infoList.accountCount = 0;
    infoList.interfaceStatus = 0;
    doaAccountModel->slotGetAccountList(infoList);
    EXPECT_EQ(doaAccountModel->m_state, DOAAccountModel::Account_Init);
}

TEST_F(ut_doaaccountmodel, ut_doaaccountmodel_slotGetAccountInfo_001)
{
    DOAAccountList::AccountInfo accountInfo;
    accountInfo.accountName = "1234@qq.com";
    accountInfo.accountID = "1234";
    accountInfo.accountAddTime = QDateTime::fromString("2021-10-12 13:11:15", "yyyy-MM-dd hh:mm:ss");
    doaAccountModel->slotGetAccountInfo(accountInfo);
    EXPECT_EQ(doaAccountModel->m_currentAccount->getAccountID(), "1234");
}

TEST_F(ut_doaaccountmodel, ut_doaaccountmodel_slotGetAccountInfo_002)
{
    DOAAccountList::AccountInfo accountInfo;
    accountInfo.accountName = "1234@qq.com";
    accountInfo.accountID = "1234";
    accountInfo.accountAddTime = QDateTime::fromString("2021-10-12 13:11:15", "yyyy-MM-dd hh:mm:ss");
    doaAccountModel->slotGetAccountInfo(accountInfo);
    DOAAccountList::AccountInfo accountInfo1;
    accountInfo1.accountName = "12345@qq.com";
    accountInfo1.accountID = "1234";
    accountInfo1.accountAddTime = QDateTime::fromString("2021-10-18 13:11:15", "yyyy-MM-dd hh:mm:ss");
    doaAccountModel->slotGetAccountInfo(accountInfo1);
    EXPECT_EQ(doaAccountModel->m_currentAccount->getAccountName(), "1234@qq.com");
}

TEST_F(ut_doaaccountmodel, ut_doaaccountmodel_slotGetDeleteAccountID_001)
{
    DOAAccountList::AccountInfo accountInfo;
    accountInfo.accountName = "1234@qq.com";
    accountInfo.accountID = "1234";
    accountInfo.accountAddTime = QDateTime::fromString("2021-10-12 13:11:15", "yyyy-MM-dd hh:mm:ss");
    doaAccountModel->slotGetAccountInfo(accountInfo);
    EXPECT_EQ(doaAccountModel->m_accounts.count(), 1);
    doaAccountModel->slotGetDeleteAccountID("12345");
    EXPECT_EQ(doaAccountModel->m_accounts.count(), 1);
}

TEST_F(ut_doaaccountmodel, ut_doaaccountmodel_slotGetDeleteAccountID_002)
{
    DOAAccountList::AccountInfo accountInfo;
    accountInfo.accountName = "1234@qq.com";
    accountInfo.accountID = "1234";
    accountInfo.accountAddTime = QDateTime::fromString("2021-10-12 13:11:15", "yyyy-MM-dd hh:mm:ss");
    doaAccountModel->slotGetAccountInfo(accountInfo);
    DOAAccountList::AccountInfo accountInfo1;
    accountInfo1.accountName = "12345@qq.com";
    accountInfo1.accountID = "12345";
    accountInfo1.accountAddTime = QDateTime::fromString("2021-10-18 13:11:15", "yyyy-MM-dd hh:mm:ss");
    doaAccountModel->slotGetAccountInfo(accountInfo1);
    EXPECT_EQ(doaAccountModel->m_accounts.count(), 2);
    doaAccountModel->slotGetDeleteAccountID("12345");
    EXPECT_EQ(doaAccountModel->m_accounts.count(), 1);
    EXPECT_EQ(doaAccountModel->m_currentAccount->getAccountName(), "1234@qq.com");
}

TEST_F(ut_doaaccountmodel, ut_doaaccountmodel_slotGetDeleteAccountID_003)
{
    DOAAccountList::AccountInfo accountInfo;
    accountInfo.accountName = "1234@qq.com";
    accountInfo.accountID = "1234";
    accountInfo.accountAddTime = QDateTime::fromString("2021-10-12 13:11:15", "yyyy-MM-dd hh:mm:ss");
    doaAccountModel->slotGetAccountInfo(accountInfo);
    DOAAccountList::AccountInfo accountInfo1;
    accountInfo1.accountName = "12345@qq.com";
    accountInfo1.accountID = "12345";
    accountInfo1.accountAddTime = QDateTime::fromString("2021-10-18 13:11:15", "yyyy-MM-dd hh:mm:ss");
    doaAccountModel->slotGetAccountInfo(accountInfo1);
    EXPECT_EQ(doaAccountModel->m_accounts.count(), 2);
    doaAccountModel->slotGetDeleteAccountID("12345");
    EXPECT_EQ(doaAccountModel->m_accounts.count(), 1);
    EXPECT_EQ(doaAccountModel->m_currentAccount->getAccountName(), "1234@qq.com");
}


TEST_F(ut_doaaccountmodel, ut_doaaccountmodel_slotGetDeleteAccountID_004)
{
    DOAAccountList::AccountInfo accountInfo;
    accountInfo.accountName = "1234@qq.com";
    accountInfo.accountID = "1234";
    accountInfo.accountAddTime = QDateTime::fromString("2021-10-12 13:11:15", "yyyy-MM-dd hh:mm:ss");
    doaAccountModel->slotGetAccountInfo(accountInfo);
    DOAAccountList::AccountInfo accountInfo1;
    accountInfo1.accountName = "12345@qq.com";
    accountInfo1.accountID = "12345";
    accountInfo1.accountAddTime = QDateTime::fromString("2021-10-18 13:11:15", "yyyy-MM-dd hh:mm:ss");
    doaAccountModel->slotGetAccountInfo(accountInfo1);
    DOAAccountList::AccountInfo accountInfo2;
    accountInfo2.accountName = "123456@qq.com";
    accountInfo2.accountID = "123456";
    accountInfo2.accountAddTime = QDateTime::fromString("2021-10-20 13:11:15", "yyyy-MM-dd hh:mm:ss");
    doaAccountModel->slotGetAccountInfo(accountInfo2);
    EXPECT_EQ(doaAccountModel->m_accounts.count(), 3);
    doaAccountModel->slotGetDeleteAccountID("12345");
    EXPECT_EQ(doaAccountModel->m_accounts.count(), 2);
    EXPECT_EQ(doaAccountModel->m_currentAccount->getAccountName(), "123456@qq.com");
}

TEST_F(ut_doaaccountmodel, ut_doaaccountmodel_slotGetDeleteAccountID_005)
{
    DOAAccountList::AccountInfo accountInfo;
    accountInfo.accountName = "1234@qq.com";
    accountInfo.accountID = "1234";
    accountInfo.accountAddTime = QDateTime::fromString("2021-10-12 13:11:15", "yyyy-MM-dd hh:mm:ss");
    doaAccountModel->slotGetAccountInfo(accountInfo);

    EXPECT_EQ(doaAccountModel->m_accounts.count(), 1);
    doaAccountModel->slotGetDeleteAccountID("1234");
    EXPECT_EQ(doaAccountModel->m_accounts.count(), 0);
    EXPECT_EQ(doaAccountModel->m_state, DOAAccountModel::Account_Init);
}

TEST_F(ut_doaaccountmodel, ut_doaaccountmodel_slotAccountPasswordChange_001)
{
    DOAAccountList::AccountInfo accountInfo;
    accountInfo.accountName = "1234@qq.com";
    accountInfo.accountID = "1234";
    accountInfo.accountAddTime = QDateTime::fromString("2021-10-12 13:11:15", "yyyy-MM-dd hh:mm:ss");
    doaAccountModel->slotGetAccountInfo(accountInfo);
    DOAAccountList::AccountInfo accountInfo1;
    accountInfo1.accountName = "12345@qq.com";
    accountInfo1.accountID = "12345";
    accountInfo1.accountAddTime = QDateTime::fromString("2021-10-18 13:11:15", "yyyy-MM-dd hh:mm:ss");
    doaAccountModel->slotGetAccountInfo(accountInfo1);
    DOAAccountList::AccountInfo accountInfo2;
    accountInfo2.accountName = "123456@qq.com";
    accountInfo2.accountID = "123456";
    accountInfo2.accountAddTime = QDateTime::fromString("2021-10-20 13:11:15", "yyyy-MM-dd hh:mm:ss");
    doaAccountModel->slotGetAccountInfo(accountInfo2);
    EXPECT_EQ(doaAccountModel->m_accounts.count(), 3);
    QSignalSpy spy(doaAccountModel, SIGNAL(signalPasswordChanged(const QString &)));
    doaAccountModel->slotAccountPasswordChange("123456");
    EXPECT_EQ(spy.count(), 1);
}

TEST_F(ut_doaaccountmodel, ut_doaaccountmodel_slotAccountPasswordChange_002)
{
    DOAAccountList::AccountInfo accountInfo;
    accountInfo.accountName = "1234@qq.com";
    accountInfo.accountID = "1234";
    accountInfo.accountAddTime = QDateTime::fromString("2021-10-12 13:11:15", "yyyy-MM-dd hh:mm:ss");
    doaAccountModel->slotGetAccountInfo(accountInfo);
    DOAAccountList::AccountInfo accountInfo1;
    accountInfo1.accountName = "12345@qq.com";
    accountInfo1.accountID = "12345";
    accountInfo1.accountAddTime = QDateTime::fromString("2021-10-18 13:11:15", "yyyy-MM-dd hh:mm:ss");
    doaAccountModel->slotGetAccountInfo(accountInfo1);
    DOAAccountList::AccountInfo accountInfo2;
    accountInfo2.accountName = "123456@qq.com";
    accountInfo2.accountID = "123456";
    accountInfo2.accountAddTime = QDateTime::fromString("2021-10-20 13:11:15", "yyyy-MM-dd hh:mm:ss");
    doaAccountModel->slotGetAccountInfo(accountInfo2);
    EXPECT_EQ(doaAccountModel->m_accounts.count(), 3);
    QSignalSpy spy(doaAccountModel, SIGNAL(signalPasswordChanged(const QString &)));
    doaAccountModel->slotAccountPasswordChange("1234");
    EXPECT_EQ(spy.count(), 0);
}

