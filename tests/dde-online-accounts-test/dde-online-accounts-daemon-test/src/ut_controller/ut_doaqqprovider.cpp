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
#include "ut_doaqqprovider.h"
#include "../../third-party_stub/stub.h"
#include "aesencryption.h"

#include <QNetworkRequest>


static DOAProvider::LoginState m_loginstate = DOAProvider::SUCCESS;
static DOAProvider::LoginState m_getPropnameloginstate = DOAProvider::SUCCESS;
static QNetworkReply::NetworkError m_error = QNetworkReply::NoError;
static int m_httpcode = 301;
static QString m_aedirection = "";
static int callcnt = 0;

void ut_doaqqprovider::SetUp()
{
    doaqqprovider = new DOAQQProvider();
}

void ut_doaqqprovider::TearDown()
{
    delete doaqqprovider;
    doaqqprovider = nullptr;
}

DOAProvider::LoginState ut_doaqqprovider::getCalendarUri()
{
    return m_loginstate;
}

DOAProvider::LoginState ut_doaqqprovider::getPropname()
{
    return m_getPropnameloginstate;
}

bool ut_doaqqprovider::stub_resultFalse()
{
    if(callcnt == 0){
        callcnt++;
        return false;
    }else {
        return true;
    }
}

bool ut_doaqqprovider::stub_resultAllFalse()
{
    return false;
}

bool ut_doaqqprovider::stub_resultTrue()
{
    return true;
}

QNetworkReply::NetworkError ut_doaqqprovider::error()
{
    return m_error;
}

QVariant ut_doaqqprovider::attribute(QNetworkRequest::Attribute code)
{
    if(QNetworkRequest::HttpStatusCodeAttribute == code){
        return m_httpcode;
    }else if(QNetworkRequest::RedirectionTargetAttribute == code){
        return  m_aedirection;
    }
    return "";
}

TEST_F(ut_doaqqprovider, ut_accountdbmanager_login_001)
{
    EXPECT_EQ(doaqqprovider->login(), DOAProvider::AccountNameEmpty);
}

TEST_F(ut_doaqqprovider, ut_accountdbmanager_login_002)
{
    doaqqprovider->setAccountName("qq");
    EXPECT_EQ(doaqqprovider->login(), DOAProvider::PassWordEmpty);
}

TEST_F(ut_doaqqprovider, ut_accountdbmanager_login_003)
{
    doaqqprovider->setAccountName("qq");
    doaqqprovider->setAccountPassword("qq");
    EXPECT_EQ(doaqqprovider->login(), DOAProvider::AccountNameError);
}

TEST_F(ut_doaqqprovider, ut_accountdbmanager_login_004)
{
    doaqqprovider->setAccountName("@qq.com");
    doaqqprovider->setAccountPassword("qq");
    Stub s;
    s.set(ADDR(DOAQQProvider, getCalendarUri), ADDR(ut_doaqqprovider, getCalendarUri));
    m_loginstate = DOAProvider::ServerError;
    EXPECT_EQ(doaqqprovider->login(), m_loginstate);
}

TEST_F(ut_doaqqprovider, ut_accountdbmanager_login_005)
{
    doaqqprovider->setAccountName("@qq.com");
    doaqqprovider->setAccountPassword("qq");
    Stub s;
    s.set(ADDR(DOAQQProvider, getCalendarUri), ADDR(ut_doaqqprovider, getCalendarUri));
    s.set(ADDR(DOAQQProvider, getPropname), ADDR(ut_doaqqprovider, getCalendarUri));
    m_loginstate = DOAProvider::SUCCESS;
    EXPECT_EQ(doaqqprovider->login(), m_loginstate);
}

TEST_F(ut_doaqqprovider, ut_accountdbmanager_login_006)
{
    doaqqprovider->setAccountName("@qq.com");
    doaqqprovider->setAccountPassword("qq");
    Stub s;
    s.set(ADDR(DOAQQProvider, getCalendarUri), ADDR(ut_doaqqprovider, getCalendarUri));
    s.set(ADDR(DOAQQProvider, getPropname), ADDR(ut_doaqqprovider, getPropname));
    m_loginstate = DOAProvider::SUCCESS;
    m_getPropnameloginstate = DOAProvider::ServerError;
    EXPECT_EQ(doaqqprovider->login(), m_getPropnameloginstate);
}


TEST_F(ut_doaqqprovider, ut_accountdbmanager_getCalendarUri_001)
{
    doaqqprovider->setAccountName("412112@qq.com");
    doaqqprovider->setAccountPassword("qqqqqq");

    callcnt = 0;
    Stub s;
    s.set(ADDR(QTimer, isActive), ADDR(ut_doaqqprovider, stub_resultTrue));
    m_error = QNetworkReply::HostNotFoundError;
    s.set((QNetworkReply::NetworkError (QNetworkReply::*)() const)ADDR(QNetworkReply, error), ADDR(ut_doaqqprovider, error));

    EXPECT_EQ(doaqqprovider->getCalendarUri(), DOAProvider::ServerError);
}

TEST_F(ut_doaqqprovider, ut_accountdbmanager_getCalendarUri_002)
{
    doaqqprovider->setAccountName("412112@qq.com");
    doaqqprovider->setAccountPassword("qqqqqq");

    callcnt = 0;
    Stub s;
    s.set(ADDR(QTimer, isActive), ADDR(ut_doaqqprovider, stub_resultTrue));
    m_error = QNetworkReply::NoError;
    s.set((QNetworkReply::NetworkError (QNetworkReply::*)() const)ADDR(QNetworkReply, error), ADDR(ut_doaqqprovider, error));
    s.set((QVariant (QNetworkReply::*)(QNetworkRequest::Attribute) const)ADDR(QNetworkReply, attribute), ADDR(ut_doaqqprovider, attribute));

    m_httpcode = 301;
    m_aedirection = "/calendar";
    EXPECT_EQ(doaqqprovider->getCalendarUri(), DOAProvider::SUCCESS);
    EXPECT_TRUE(doaqqprovider->getUri().contains("/calendar"));
}



TEST_F(ut_doaqqprovider, ut_accountdbmanager_getPropname_001)
{
    doaqqprovider->setAccountName("412112@qq.com");
    doaqqprovider->setAccountPassword("qqqqqq");

    callcnt = 0;
    Stub s;
    s.set(ADDR(QTimer, isActive), ADDR(ut_doaqqprovider, stub_resultFalse));
    s.set(ADDR(AESEncryption, ecb_encrypt), ADDR(ut_doaqqprovider, stub_resultTrue));
    m_error = QNetworkReply::HostNotFoundError;
    m_httpcode = 404;
    s.set((QNetworkReply::NetworkError (QNetworkReply::*)() const)ADDR(QNetworkReply, error), ADDR(ut_doaqqprovider, error));

    EXPECT_EQ(doaqqprovider->getPropname(), DOAProvider::ServerError);
}


TEST_F(ut_doaqqprovider, ut_accountdbmanager_getPropname_002)
{
    doaqqprovider->setAccountName("412112@qq.com");
    doaqqprovider->setAccountPassword("qqqqqq");

    callcnt = 0;
    Stub s;
    s.set(ADDR(QTimer, isActive), ADDR(ut_doaqqprovider, stub_resultFalse));

    EXPECT_EQ(doaqqprovider->getPropname(), DOAProvider::PassWordError);
}



TEST_F(ut_doaqqprovider, ut_accountdbmanager_getPropname_003)
{
    doaqqprovider->setAccountName("412112@qq.com");
    doaqqprovider->setAccountPassword("qqqqqq");

    callcnt = 0;
    Stub s;
    s.set(ADDR(AESEncryption, ecb_encrypt), ADDR(ut_doaqqprovider, stub_resultTrue));
    s.set(ADDR(QTimer, isActive), ADDR(ut_doaqqprovider, stub_resultFalse));
    m_error = QNetworkReply::NoError;
    s.set((QNetworkReply::NetworkError (QNetworkReply::*)() const)ADDR(QNetworkReply, error), ADDR(ut_doaqqprovider, error));
    s.set((QVariant (QNetworkReply::*)(QNetworkRequest::Attribute) const)ADDR(QNetworkReply, attribute), ADDR(ut_doaqqprovider, attribute));

    m_httpcode = 207;

    EXPECT_EQ(doaqqprovider->getPropname(), DOAProvider::SUCCESS);
}


TEST_F(ut_doaqqprovider, ut_accountdbmanager_getPropname_007)
{
    doaqqprovider->setAccountName("412112@qq.com");
    doaqqprovider->setAccountPassword("qqqqqq");

    callcnt = 0;
    Stub s;
    s.set(ADDR(QTimer, isActive), ADDR(ut_doaqqprovider, stub_resultFalse));
    s.set(ADDR(AESEncryption, ecb_encrypt), ADDR(ut_doaqqprovider, stub_resultTrue));
    m_error = QNetworkReply::HostNotFoundError;
    m_httpcode = 407;
    s.set((QNetworkReply::NetworkError (QNetworkReply::*)() const)ADDR(QNetworkReply, error), ADDR(ut_doaqqprovider, error));
    s.set((QVariant (QNetworkReply::*)(QNetworkRequest::Attribute) const)ADDR(QNetworkReply, attribute), ADDR(ut_doaqqprovider, attribute));

    EXPECT_EQ(doaqqprovider->getPropname(), DOAProvider::AuthenticationFailed);
}

TEST_F(ut_doaqqprovider, ut_accountdbmanager_loginCancel_001)
{
    QNetworkRequest request;
    doaqqprovider->m_reply = doaqqprovider->m_manager->get(request);
    doaqqprovider->loginCancel();
    EXPECT_EQ(doaqqprovider->isUserCancle, true);
}

TEST_F(ut_doaqqprovider, ut_accountdbmanager_timeouthandle_001)
{
    doaqqprovider->isUserCancle = true;
    QNetworkRequest request;
    doaqqprovider->m_reply = doaqqprovider->m_manager->get(request);
    EXPECT_EQ(doaqqprovider->timeouthandle(), DOAProvider::UserCancel);
}

TEST_F(ut_doaqqprovider, ut_accountdbmanager_timeouthandle_002)
{
    doaqqprovider->isUserCancle = false;
    QNetworkRequest request;
    doaqqprovider->m_reply = doaqqprovider->m_manager->get(request);
    EXPECT_EQ(doaqqprovider->timeouthandle(), DOAProvider::TIMEOUT);
}
