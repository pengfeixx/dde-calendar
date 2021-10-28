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
#include "ut_qjsonutils.h"
#include "qjsonutils.h"
#include "doaqqprovider.h"

#include <QtDBus>
#include <QVariant>


TEST_F(ut_qjsonutils, ut_qjsonutils_getJsonString_001)
{
    QMap<QString, QVariant> addAccountMap;
    addAccountMap.insert("accountname", "123456");
    addAccountMap.insert("stat", 0);
    addAccountMap.insert("accountid", "123456");
    addAccountMap.insert("accountdbuspath", "com.test.doa");
    addAccountMap.insert("accounttype", "CALDAV");
    addAccountMap.insert("accountflag", "QQ");
    addAccountMap.insert("username", "123456");
    addAccountMap.insert("accountstat", 0);
    addAccountMap.insert("calendardisable", 1);
    addAccountMap.insert("accounturi", "dav.qq.com");
    addAccountMap.insert("iterfaceoper", "ADD");


    QString jsonstr = QJsonUtils::getJsonString(addAccountMap);
    qWarning() << jsonstr;
    EXPECT_EQ(jsonstr, "{\"accountdbuspath\":\"com.test.doa\",\"accountflag\":\"QQ\",\"accountid\":\"123456\",\"accountname\":\"123456\",\"accountstat\":0,\"accounttype\":\"CALDAV\",\"accounturi\":\"dav.qq.com\",\"calendardisable\":1,\"iterfaceoper\":\"ADD\",\"stat\":0,\"username\":\"123456\"}");
}

TEST_F(ut_qjsonutils, ut_qjsonutils_getJsonString_002)
{
    QMap<QString, QVariant> addAccountMap;

    QString jsonstr = QJsonUtils::getJsonString(addAccountMap);
    qWarning() << jsonstr;
    EXPECT_EQ(jsonstr, "");
}

TEST_F(ut_qjsonutils, ut_qjsonutils_doaProvider2JsonObject_001)
{
    DOAProvider *doa = new DOAQQProvider;
    doa->setAccountID("123456");
    doa->setAccountName("123456");

    QJsonObject jsonobject = QJsonUtils::doaProvider2JsonObject(doa);

    EXPECT_EQ(jsonobject["accountid"].toString(), "123456");
    delete doa;

}

TEST_F(ut_qjsonutils, ut_qjsonutils_doaProvider2String_001)
{
    DOAProvider *doa = new DOAQQProvider();
    doa->setAccountID("123456");
    doa->setAccountName("123456");

    QString jsonstr = QJsonUtils::doaProvider2String(doa, QJsonUtils::ADD);
    qWarning() << jsonstr;
    EXPECT_EQ(jsonstr, "{\"iterfacecontent\":{\"accountdbuspath\":\"\",\"accountflag\":1,\"accountid\":\"123456\",\"accountname\":\"123456\",\"accountstat\":3,\"accounttype\":1,\"accounturi\":\"\",\"accounturl\":\"https://dav.qq.com\",\"calendardisable\":false,\"createtime\":\"\",\"username\":\"\"},\"iterfaceoper\":\"ADD\",\"stat\":\"0\"}");
    delete  doa;
}

TEST_F(ut_qjsonutils, ut_qjsonutils_doaProvider2String_002)
{
    DOAProvider *doa = new DOAQQProvider();
    doa->setAccountID("123456");
    doa->setAccountName("123456");

    QString jsonstr = QJsonUtils::doaProvider2String(doa, QJsonUtils::DEL);
    qWarning() << jsonstr;
    EXPECT_EQ(jsonstr, "{\"iterfacecontent\":{\"accountid\":\"123456\"},\"iterfaceoper\":\"DEL\",\"stat\":\"0\"}");
    delete  doa;
}

TEST_F(ut_qjsonutils, ut_qjsonutils_doaProvider2String_003)
{
    DOAProvider *doa = new DOAQQProvider();
    doa->setAccountID("123456");
    doa->setAccountName("123456");

    QString jsonstr = QJsonUtils::doaProvider2String(doa, QJsonUtils::MODIFY);
    qWarning() << jsonstr;
    EXPECT_EQ(jsonstr, "{}");
    delete  doa;
}

TEST_F(ut_qjsonutils, ut_qjsonutils_jsonString2DoaProvider_001)
{
    QString jsonstr = "{\"logintype\":\"1\",\"accounttype\":\"1\",\"accountname\":\"12345@qq.com\",\"accountpassword\":\"123334\",\"accounturl\":\"https://dav.qq.com/calendar\",\"uuid\":\"123334\"}";

    DOAProvider *doapro = new DOAQQProvider();
    QJsonUtils::jsonString2DoaProvider(jsonstr, doapro);

    EXPECT_EQ(doapro->getAccountName(), "12345@qq.com");
    EXPECT_EQ(doapro->getLoginType(), DOAProvider::AUTO);
    EXPECT_EQ(doapro->getProtocol(), DOAProvider::CALDAV);
    EXPECT_EQ(doapro->getAccountPassword(), "123334");
    EXPECT_EQ(doapro->getUrl(), "https://dav.qq.com");
    EXPECT_EQ(doapro->getUri(), "https://dav.qq.com/calendar");
    EXPECT_EQ(doapro->getSSL(), true);
    delete  doapro;
}

TEST_F(ut_qjsonutils, ut_qjsonutils_jsonString2DoaProvider_002)
{
    QString jsonstr = "{\"logintype\":\"1\",\"accounttype\":\"1\",\"accountname\":\"12345@qq.com\",\"accountpassword\":\"123334\",\"accounturl\":\"http://dav.qq.com/calendar\",\"uuid\":\"123334\"}";

    DOAProvider *doapro = new DOAQQProvider();
    QJsonUtils::jsonString2DoaProvider(jsonstr, doapro);

    EXPECT_EQ(doapro->getSSL(), false);

    delete  doapro;
}


TEST_F(ut_qjsonutils, ut_qjsonutils_jsonString2DoaProvider_003)
{
    QString jsonstr = "\"logintype\":\"1\",\"accounttype\":\"1\",\"accountname\":\"12345@qq.com\",\"accountpassword\":\"123334\",\"accounturl\":\"\"}";

    DOAProvider *doapro = new DOAQQProvider();
    bool ret = QJsonUtils::jsonString2DoaProvider(jsonstr, doapro);

    EXPECT_EQ(ret, false);
    delete  doapro;
}


TEST_F(ut_qjsonutils, ut_qjsonutils_jsonString2DoaProvider_004)
{
    QString jsonstr = "{\"logintype\":\"1\",\"accounttype\":\"1\",\"accountname\":\"12345@qq.com\",\"accountpassword\":\"123334\",\"accounturl\":\"\"}";

    bool ret = QJsonUtils::jsonString2DoaProvider(jsonstr, nullptr);

    EXPECT_EQ(ret, false);
}


TEST_F(ut_qjsonutils, ut_qjsonutils_jsonString2DoaProvider_005)
{
    QString jsonstr = "{\"logintype\":\"1\",\"accounttype\":\"1\",\"accountname\":\"12345@qq.com\",\"accountpassword\":\"123334\",\"accounturl\":\"http://dav.qq.com\",\"uuid\":\"123334\"}";

    DOAProvider *doapro = new DOAQQProvider();
    QJsonUtils::jsonString2DoaProvider(jsonstr, doapro);

    EXPECT_EQ(doapro->getUrl(), "http://dav.qq.com");
    EXPECT_EQ(doapro->getUri(), "");

    delete  doapro;
}

TEST_F(ut_qjsonutils, ut_qjsonutils_jsonString2DoaProvider_006)
{
    QString jsonstr = "{\"logintype\":\"1\",\"accounttype\":\"1\",\"accountname\":\"12345@qq.com\",\"accountpassword\":\"123334\",\"accounturl\":\"http://dav.qq.com:8080\",\"uuid\":\"123334\"}";

    DOAProvider *doapro = new DOAQQProvider();
    QJsonUtils::jsonString2DoaProvider(jsonstr, doapro);

    EXPECT_EQ(doapro->getAccountPort(), "8080");

    delete  doapro;
}

TEST_F(ut_qjsonutils, ut_qjsonutils_accountAddJsonArray_001)
{
    QJsonArray jsonarray;
    QJsonUtils::accountAddJsonArray(nullptr, jsonarray);

    EXPECT_EQ(jsonarray.count(), 0);
}

TEST_F(ut_qjsonutils, ut_qjsonutils_accountAddJsonArray_002)
{
    DOAProvider *doa = new DOAQQProvider();
    doa->setAccountID("123456");
    doa->setAccountName("123456");

    QJsonArray jsonarray;
    QJsonUtils::accountAddJsonArray(doa, jsonarray);


    EXPECT_EQ(jsonarray.count(), 1);
    delete  doa;
}


