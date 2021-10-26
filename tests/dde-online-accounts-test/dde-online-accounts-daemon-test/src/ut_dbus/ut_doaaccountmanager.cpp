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
#include "ut_doaaccountmanager.h"
#include "aesencryption.h"
#include "doaaccounts_adapter.h"
#include "doaqqprovider.h"
#include "qjsonutils.h"
#include "../../third-party_stub/stub.h"

#include <QSignalSpy>

static DOAProvider::LoginState m_doaloginstate = DOAProvider::SUCCESS;

static int callcnt = 0;

void ut_doaaccountmanager::SetUp()
{
    Stub s;
    s.set(ADDR(QStandardPaths, writableLocation), ADDR(ut_doaaccountmanager, stub_writableLocation));
    firstremovedbfile();
    doaAccountManager = new DOAAccountManager();
}

void ut_doaaccountmanager::TearDown()
{
    delete doaAccountManager;
    doaAccountManager = nullptr;
}

bool ut_doaaccountmanager::stub_resultAllFalse()
{
    return false;
}

bool ut_doaaccountmanager::stub_resultTrue()
{
    return true;
}

QString ut_doaaccountmanager::stub_getAccountID()
{
    return "/123456/qq/com";
}

QString ut_doaaccountmanager::stub_getAccountName()
{
    return "123456@qq.com";
}

QString ut_doaaccountmanager::stub_getAccountIDCall()
{
    if(callcnt == 0){
        callcnt++;
        return "123456@qq.com";
    }else {
        return "";
    }

}

DOAProvider::LoginState ut_doaaccountmanager::login()
{
    return m_doaloginstate;
}

bool ut_doaaccountmanager::stub_result()
{
    if(callcnt == 0){
        callcnt++;
        return true;
    }else {
        return false;
    }
}

QString ut_doaaccountmanager::stub_writableLocation(QStandardPaths::StandardLocation type)
{
    return "/tmp";
}

QString ut_doaaccountmanager::firstremovedbfile()
{
    QString dbdir = QStandardPaths::writableLocation(QStandardPaths::HomeLocation).append("/.local/share/deepin/dde-online-accounts");
    QString databasePath1 = dbdir.append("/accounts.db");
    qWarning() << "db file:" << databasePath1;
    QFile::remove(databasePath1);

    QFile file(databasePath1);

    if (!file.exists()) {
        qWarning() << "delete file success";
    }

    return databasePath1;
}

TEST_F(ut_doaaccountmanager, ut_doaaccountmanager_creatAllAccountDbusFromDB_001)
{
    Stub s;
    s.set(ADDR(AccountDB, queryAccountList), ADDR(ut_doaaccountmanager, stub_resultAllFalse));
    doaAccountManager->creatAllAccountDbusFromDB();
}

TEST_F(ut_doaaccountmanager, ut_doaaccountmanager_passwordPro_001)
{
    Stub s;
    s.set(ADDR(AESEncryption, ecb_encrypt), ADDR(ut_doaaccountmanager, stub_resultAllFalse));
    EXPECT_EQ(doaAccountManager->passwordPro(""), "");
}

TEST_F(ut_doaaccountmanager, ut_doaaccountmanager_passwordPro_002)
{
    //123456
    //dc354b248cd53cdc434251524c53a961
    EXPECT_EQ(doaAccountManager->passwordPro("09e27c91f856253e3434d2a3f736fbb9"), "dc354b248cd53cdc434251524c53a961");
}

TEST_F(ut_doaaccountmanager, ut_doaaccountmanager_passwordPro_003)
{
    callcnt = 0;
    Stub s;
    s.set(ADDR(AESEncryption, ecb_encrypt), ADDR(ut_doaaccountmanager, stub_result));
    EXPECT_EQ(doaAccountManager->passwordPro(""), "");
}

TEST_F(ut_doaaccountmanager, ut_doaaccountmanager_onSelectAccountResult_001)
{
    AccountResultList result;

    AccountInfo accinfo;
    accinfo.m_isSSL = true;
    accinfo.m_accountID = "1234";
    accinfo.m_accountURL = "https://dav.qq.com";
    accinfo.m_accountName = "1234@qq.com";
    accinfo.m_accountType = "CALDAV";
    accinfo.m_accountDbusPath = "/com/doa/tests/1234";
    accinfo.m_accountUserName = "1234";
    accinfo.m_accountProviderType = "QQ";
    accinfo.m_calendarDisabled = true;

    AccountInfo accinfo1;
    accinfo1.m_isSSL = true;
    accinfo1.m_accountID = "1235";
    accinfo1.m_accountURL = "https://dav.qq.com";
    accinfo1.m_accountName = "1235@qq.com";
    accinfo1.m_accountType = "CALDAV";
    accinfo1.m_accountDbusPath = "/com/doa/tests/1235";
    accinfo1.m_accountUserName = "1235";
    accinfo1.m_accountProviderType = "QQ";
    accinfo1.m_calendarDisabled = true;

    result << accinfo << accinfo1;
    doaAccountManager->onSelectAccountResult(result);

    EXPECT_EQ(doaAccountManager->m_doaProviderMap.count(), 2);
}

TEST_F(ut_doaaccountmanager, ut_doaaccountmanager_getAllAccount_001)
{
    AccountResultList result;

    AccountInfo accinfo;
    accinfo.m_isSSL = true;
    accinfo.m_accountID = "1234";
    accinfo.m_accountURL = "https://dav.qq.com";
    accinfo.m_accountName = "1234@qq.com";
    accinfo.m_accountType = "CALDAV";
    accinfo.m_accountDbusPath = "/com/doa/tests/1234";
    accinfo.m_accountUserName = "1234";
    accinfo.m_accountProviderType = "QQ";
    accinfo.m_calendarDisabled = true;

    AccountInfo accinfo1;
    accinfo1.m_isSSL = true;
    accinfo1.m_accountID = "1235";
    accinfo1.m_accountURL = "https://dav.qq.com";
    accinfo1.m_accountName = "1235@qq.com";
    accinfo1.m_accountType = "CALDAV";
    accinfo1.m_accountDbusPath = "/com/doa/tests/1235";
    accinfo1.m_accountUserName = "1235";
    accinfo1.m_accountProviderType = "QQ";
    accinfo1.m_calendarDisabled = true;

    result << accinfo << accinfo1;
    doaAccountManager->onSelectAccountResult(result);

    EXPECT_EQ(doaAccountManager->getAllAccount().contains("1235@qq.com"), true);
    EXPECT_EQ(doaAccountManager->getAllAccount().contains("1234@qq.com"), true);
}

TEST_F(ut_doaaccountmanager, ut_doaaccountmanager_creatAccountDbus_001)
{
    DOAAccountsadapter *accountadapter = new DOAAccountsadapter;
    DOAProvider *doaprovider = new DOAQQProvider(accountadapter);
    accountadapter->setDoaProvider(doaprovider);
    doaAccountManager->creatAccountDbus(accountadapter);
    EXPECT_EQ(accountadapter->objectName(), "accountAdapter");
    delete accountadapter;
}

TEST_F(ut_doaaccountmanager, ut_doaaccountmanager_loginCancle_001)
{
    DOAProvider *doaprovider = new DOAQQProvider();
    doaprovider->setAccountID("1234");
    doaAccountManager->m_doaProviderLoginingMap.insert(doaprovider->getAccountID(), doaprovider);
    doaAccountManager->loginCancle(doaprovider->getAccountID());
    EXPECT_EQ(doaAccountManager->m_doaProviderMap.count(), 0);

    delete doaprovider;
}

TEST_F(ut_doaaccountmanager, ut_doaaccountmanager_addAccount_001)
{
    QString addData;
    EXPECT_EQ(doaAccountManager->addAccount(addData), DOAProvider::DatatError);
}

TEST_F(ut_doaaccountmanager, ut_doaaccountmanager_addAccount_002)
{
    QString addData;
    Stub s;
    s.set(ADDR(QJsonUtils, jsonString2DoaProvider), ADDR(ut_doaaccountmanager, stub_resultTrue));
    EXPECT_EQ(doaAccountManager->addAccount(addData), DOAProvider::DatatError);
}

TEST_F(ut_doaaccountmanager, ut_doaaccountmanager_addAccount_003)
{
    DOAAccountsadapter *accountadapter = new DOAAccountsadapter();
    accountadapter->setDoaProvider(new DOAQQProvider);
    accountadapter->getDoaProvider()->setAccountID("123456");
    accountadapter->getDoaProvider()->setAccountName("123456");
    doaAccountManager->m_doaProviderMap.insert("12345", accountadapter);

    QString addData;
    Stub s;
    s.set(ADDR(QJsonUtils, jsonString2DoaProvider), ADDR(ut_doaaccountmanager, stub_resultTrue));
    s.set(ADDR(DOAProvider, getAccountID), ADDR(ut_doaaccountmanager, stub_getAccountID));
    s.set(ADDR(DOAProvider, getAccountName), ADDR(ut_doaaccountmanager, stub_getAccountName));
    EXPECT_EQ(doaAccountManager->addAccount(addData), DOAProvider::RepeatLogin);
    delete accountadapter;
}

TEST_F(ut_doaaccountmanager, ut_doaaccountmanager_addAccount_004)
{
    QString addData;
    Stub s;
    s.set(ADDR(QJsonUtils, jsonString2DoaProvider), ADDR(ut_doaaccountmanager, stub_resultTrue));
    s.set(ADDR(DOAProvider, getAccountID), ADDR(ut_doaaccountmanager, stub_getAccountID));
    s.set(ADDR(DOAProvider, getAccountName), ADDR(ut_doaaccountmanager, stub_getAccountName));
    s.set(ADDR(DOAProvider, getAccountPassword), ADDR(ut_doaaccountmanager, stub_getAccountID));
    s.set(ADDR(DOAQQProvider, getCalendarUri), ADDR(ut_doaaccountmanager, login));
    s.set(ADDR(DOAQQProvider, getPropname), ADDR(ut_doaaccountmanager, login));
    m_doaloginstate = DOAProvider::NetWorkError;
    EXPECT_EQ(doaAccountManager->addAccount(addData), DOAProvider::NetWorkError);
}

TEST_F(ut_doaaccountmanager, ut_doaaccountmanager_addAccount_005)
{
    QString addData;
    Stub s;
    s.set(ADDR(QJsonUtils, jsonString2DoaProvider), ADDR(ut_doaaccountmanager, stub_resultTrue));
    s.set(ADDR(DOAProvider, getAccountID), ADDR(ut_doaaccountmanager, stub_getAccountID));
    s.set(ADDR(DOAProvider, getAccountName), ADDR(ut_doaaccountmanager, stub_getAccountName));
    s.set(ADDR(DOAProvider, getAccountPassword), ADDR(ut_doaaccountmanager, stub_getAccountID));
    s.set(ADDR(DOAQQProvider, getCalendarUri), ADDR(ut_doaaccountmanager, login));
    s.set(ADDR(DOAQQProvider, getPropname), ADDR(ut_doaaccountmanager, login));
    s.set(ADDR(AESEncryption, ecb_encrypt), ADDR(ut_doaaccountmanager, stub_resultAllFalse));
    m_doaloginstate = DOAProvider::SUCCESS;
    EXPECT_EQ(doaAccountManager->addAccount(addData), DOAProvider::PassWordError);
}

TEST_F(ut_doaaccountmanager, ut_doaaccountmanager_addAccount_006)
{
    QString addData;
    Stub s;
    s.set(ADDR(QJsonUtils, jsonString2DoaProvider), ADDR(ut_doaaccountmanager, stub_resultTrue));
    s.set(ADDR(DOAProvider, getAccountID), ADDR(ut_doaaccountmanager, stub_getAccountID));
    s.set(ADDR(DOAProvider, getAccountName), ADDR(ut_doaaccountmanager, stub_getAccountName));
    s.set(ADDR(DOAProvider, getAccountPassword), ADDR(ut_doaaccountmanager, stub_getAccountID));
    s.set(ADDR(DOAQQProvider, getCalendarUri), ADDR(ut_doaaccountmanager, login));
    s.set(ADDR(DOAQQProvider, getPropname), ADDR(ut_doaaccountmanager, login));
    s.set(ADDR(AESEncryption, ecb_encrypt), ADDR(ut_doaaccountmanager, stub_result));
    m_doaloginstate = DOAProvider::SUCCESS;
    EXPECT_EQ(doaAccountManager->addAccount(addData), DOAProvider::PassWordError);
}

TEST_F(ut_doaaccountmanager, ut_doaaccountmanager_addAccount_007)
{
    QString addData;
    QSignalSpy spy(doaAccountManager, SIGNAL(InterfaceAccountInfo(const QString &)));

    Stub s;
    s.set(ADDR(QJsonUtils, jsonString2DoaProvider), ADDR(ut_doaaccountmanager, stub_resultTrue));
    s.set(ADDR(DOAProvider, getAccountID), ADDR(ut_doaaccountmanager, stub_getAccountID));
    s.set(ADDR(DOAProvider, getAccountName), ADDR(ut_doaaccountmanager, stub_getAccountName));
    s.set(ADDR(DOAProvider, getAccountPassword), ADDR(ut_doaaccountmanager, stub_getAccountID));
    s.set(ADDR(DOAQQProvider, getCalendarUri), ADDR(ut_doaaccountmanager, login));
    s.set(ADDR(DOAQQProvider, getPropname), ADDR(ut_doaaccountmanager, login));
    s.set(ADDR(AESEncryption, ecb_encrypt), ADDR(ut_doaaccountmanager, stub_resultTrue));
    s.set(ADDR(AccountDB, addAccount), ADDR(ut_doaaccountmanager, stub_resultAllFalse));
    m_doaloginstate = DOAProvider::SUCCESS;

    EXPECT_EQ(doaAccountManager->addAccount(addData), DOAProvider::DBError);
}

TEST_F(ut_doaaccountmanager, ut_doaaccountmanager_addAccount_008)
{
    QString addData;
    Stub s;
    s.set(ADDR(QJsonUtils, jsonString2DoaProvider), ADDR(ut_doaaccountmanager, stub_resultTrue));
    s.set(ADDR(DOAProvider, getAccountID), ADDR(ut_doaaccountmanager, stub_getAccountID));
    s.set(ADDR(DOAProvider, getAccountName), ADDR(ut_doaaccountmanager, stub_getAccountName));
    s.set(ADDR(DOAProvider, getAccountPassword), ADDR(ut_doaaccountmanager, stub_getAccountID));
    s.set(ADDR(DOAQQProvider, getCalendarUri), ADDR(ut_doaaccountmanager, login));
    s.set(ADDR(DOAQQProvider, getPropname), ADDR(ut_doaaccountmanager, login));
    s.set(ADDR(AESEncryption, ecb_encrypt), ADDR(ut_doaaccountmanager, stub_resultTrue));
    s.set(ADDR(AccountDB, addAccount), ADDR(ut_doaaccountmanager, stub_resultTrue));
    s.set(ADDR(DOAQQProvider, getPath), ADDR(ut_doaaccountmanager, stub_getAccountID));
    m_doaloginstate = DOAProvider::SUCCESS;
    EXPECT_EQ(doaAccountManager->addAccount(addData), 0);
}

TEST_F(ut_doaaccountmanager, ut_doaaccountmanager_addAccount_009)
{
    callcnt = 0;
    QString addData;
    Stub s;
    s.set(ADDR(QJsonUtils, jsonString2DoaProvider), ADDR(ut_doaaccountmanager, stub_resultTrue));
    s.set(ADDR(DOAProvider, getAccountID), ADDR(ut_doaaccountmanager, stub_getAccountIDCall));
    s.set(ADDR(DOAProvider, getAccountName), ADDR(ut_doaaccountmanager, stub_getAccountName));
    s.set(ADDR(DOAProvider, getAccountPassword), ADDR(ut_doaaccountmanager, stub_getAccountID));
    s.set(ADDR(DOAQQProvider, getCalendarUri), ADDR(ut_doaaccountmanager, login));
    s.set(ADDR(DOAQQProvider, getPropname), ADDR(ut_doaaccountmanager, login));
    s.set(ADDR(AESEncryption, ecb_encrypt), ADDR(ut_doaaccountmanager, stub_resultTrue));
    s.set(ADDR(AccountDB, addAccount), ADDR(ut_doaaccountmanager, stub_resultTrue));
    m_doaloginstate = DOAProvider::SUCCESS;
    EXPECT_EQ(doaAccountManager->addAccount(addData), 0);
}

TEST_F(ut_doaaccountmanager, ut_doaaccountmanager_onRemoveAccount_001)
{
    DOAAccountsadapter *accountadapter = new DOAAccountsadapter();
    accountadapter->setDoaProvider(new DOAQQProvider);
    accountadapter->getDoaProvider()->setAccountID("123456");
    accountadapter->getDoaProvider()->setAccountName("123456");
    doaAccountManager->m_doaProviderMap.insert("123456", accountadapter);
    Stub s;
    s.set(ADDR(AccountDB, deleteAccount), ADDR(ut_doaaccountmanager, stub_resultTrue));

    doaAccountManager->onRemoveAccount(accountadapter);
    EXPECT_EQ(doaAccountManager->m_doaProviderMap.count(), 0);
    delete accountadapter;
}

TEST_F(ut_doaaccountmanager, ut_doaaccountmanager_onChangeProperty_001)
{
    DOAProvider *doa = new DOAQQProvider(doaAccountManager);
    doa->setAccountID("123456");
    doa->setAccountName("123456");

    Stub s;
    s.set(ADDR(AccountDB, updateProperty), ADDR(ut_doaaccountmanager, stub_resultTrue));

    doaAccountManager->onChangeProperty("CalendarDisable", doa);
    doaAccountManager->onChangeProperty("UserName", doa);
    doaAccountManager->onChangeProperty("Status", doa);
    doaAccountManager->onChangeProperty("Password", doa);
}

TEST_F(ut_doaaccountmanager, ut_doaaccountmanager_onChangeProperty_002)
{
    DOAProvider *doa = new DOAQQProvider(doaAccountManager);
    doa->setAccountID("123456");
    doa->setAccountName("123456");

    Stub s;
    s.set(ADDR(AccountDB, updateProperty), ADDR(ut_doaaccountmanager, stub_resultTrue));

    doaAccountManager->onChangeProperty("UserName", doa);
}

TEST_F(ut_doaaccountmanager, ut_doaaccountmanager_onChangeProperty_003)
{
    DOAProvider *doa = new DOAQQProvider(doaAccountManager);
    doa->setAccountID("123456");
    doa->setAccountName("123456");

    Stub s;
    s.set(ADDR(AccountDB, updateProperty), ADDR(ut_doaaccountmanager, stub_resultTrue));

    doaAccountManager->onChangeProperty("Status", doa);
}

TEST_F(ut_doaaccountmanager, ut_doaaccountmanager_onChangeProperty_004)
{
    DOAProvider *doa = new DOAQQProvider(doaAccountManager);
    doa->setAccountID("123456");
    doa->setAccountName("123456");

    Stub s;
    s.set(ADDR(AccountDB, updateProperty), ADDR(ut_doaaccountmanager, stub_resultTrue));

    doaAccountManager->onChangeProperty("Password", doa);
}

TEST_F(ut_doaaccountmanager, ut_doaaccountmanager_onAddResult_001)
{
    DOAAccountsadapter *accountadapter = new DOAAccountsadapter(doaAccountManager);
    accountadapter->setDoaProvider(new DOAQQProvider);
    accountadapter->getDoaProvider()->setAccountID("123456");
    accountadapter->getDoaProvider()->setAccountName("123456");
    doaAccountManager->m_doaProviderMap.insert("123456", accountadapter);
    doaAccountManager->onAddResult("123456", true);
}

TEST_F(ut_doaaccountmanager, ut_doaaccountmanager_onAddResult_002)
{
    DOAAccountsadapter *accountadapter = new DOAAccountsadapter(doaAccountManager);
    accountadapter->setDoaProvider(new DOAQQProvider);
    accountadapter->getDoaProvider()->setAccountID("123456");
    accountadapter->getDoaProvider()->setAccountName("123456");
    doaAccountManager->m_doaProviderMap.insert("123456", accountadapter);
    doaAccountManager->onAddResult("123456", false);
}

TEST_F(ut_doaaccountmanager, ut_doaaccountmanager_netWorkStateNotify_001)
{
    QSignalSpy spy(doaAccountManager, SIGNAL(sign_netWorkChange(bool)));
    doaAccountManager->netWorkStateNotify(DOANetWorkDBus::Active);
    EXPECT_EQ(spy.count(), 1);
}

TEST_F(ut_doaaccountmanager, ut_doaaccountmanager_netWorkStateNotify_002)
{
    QSignalSpy spy(doaAccountManager, SIGNAL(sign_netWorkChange(bool)));
    doaAccountManager->netWorkStateNotify(DOANetWorkDBus::Active);
    doaAccountManager->netWorkStateNotify(DOANetWorkDBus::Disconnect);
    EXPECT_EQ(spy.count(), 2);
}
