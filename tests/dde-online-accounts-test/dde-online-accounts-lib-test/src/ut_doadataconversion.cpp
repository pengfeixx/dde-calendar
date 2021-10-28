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
#include "ut_doadataconversion.h"
#include "doadataconversion.h"

#include <QtDebug>
#include <QJsonObject>

ut_doadataconversion::ut_doadataconversion()
{

}

TEST_F(ut_doadataconversion, ut_doadataconversion_addAccountInfoToJson_001)
{
    AddAccountInfo info;
    info.UUID = "1234";
    info.loginModel = 1;
    info.accountName = "1234@qq.com";
    info.accountPassword = "123456";
    info.type = 1;

    QString jsonstr = addAccountInfoToJson(info);
    qWarning() << jsonstr;
    EXPECT_EQ(jsonstr, "{\"accountname\":\"1234@qq.com\",\"accountpassword\":\"123456\",\"accounttype\":1,\"accounturl\":\"\",\"logintype\":1,\"uuid\":\"1234\"}");
}

TEST_F(ut_doadataconversion, ut_doadataconversion_accountListJsonToAccountInfoList_001)
{
    QString accountList = "{\"accountcnt\":1,\"accountlist\":[{\"accountdbuspath\":"
                          "\"/com/dde/onlineaccount/accounts/accounts_1631073537\","
                          "\"accountflag\":1,\"accountid\":\"accounts_1631073537\","
                          "\"accountname\":\"412124@qq.com\",\"accountstat\":0,"
                          "\"accounttype\":1,\"accounturi\":\"https://dav.qq.com/calendar/\","
                          "\"calendardisable\":false,\"username\":\"412124@qq.com\"}],\"stat\":\"0\"}";
    DOAAccountList::AccountInfoList ainfolist = accountListJsonToAccountInfoList(accountList);
    EXPECT_EQ(ainfolist.accountCount, 1);
    EXPECT_EQ(ainfolist.m_infoList[0].accountName, "412124@qq.com");
}

TEST_F(ut_doadataconversion, ut_doadataconversion_accountListJsonToAccountInfoList_002)
{
    QString accountList = "\"accountcnt\":1,\"accountlist\":[{\"accountdbuspath\":"
                          "\"/com/dde/onlineaccount/accounts/accounts_1631073537\","
                          "\"accountflag\":1,\"accountid\":\"accounts_1631073537\","
                          "\"accountname\":\"412124@qq.com\",\"accountstat\":0,"
                          "\"accounttype\":1,\"accounturi\":\"https://dav.qq.com/calendar/\","
                          "\"calendardisable\":false,\"username\":\"412124@qq.com\"}],\"stat\":\"0\"}";
    DOAAccountList::AccountInfoList ainfolist = accountListJsonToAccountInfoList(accountList);
    EXPECT_EQ(ainfolist.accountCount, 0);
}

TEST_F(ut_doadataconversion, ut_doadataconversion_fromeConverDateTime_001)
{
    QDateTime dtime = fromeConverDateTime("2021-10-22T14:57:40+08:00");
    qWarning() << dtime.toString("yyyy-MM-dd hh:mm:ss");
    EXPECT_EQ(dtime.toString("yyyy-MM-dd hh:mm:ss"), "2021-10-22 14:57:40");
}

TEST_F(ut_doadataconversion, ut_doadataconversion_accountJsonObjectToInfo_001)
{
    QJsonObject jsonobject;
    jsonobject.insert("accountid", "123456");
    jsonobject.insert("accountname", "123456.qq.com");
    jsonobject.insert("accountstat", 0);
    jsonobject.insert("accountdbuspath", "/com/test/doa");
    jsonobject.insert("accounttype", "CALDAV");
    jsonobject.insert("accountflag", "QQ");
    jsonobject.insert("username", "123456");
    jsonobject.insert("createtime", "2021-10-22T14:57:40+08:00");
    jsonobject.insert("accounturl", "https://dav.qq.com");

    DOAAccountList::AccountInfo accountinfo = accountJsonObjectToInfo(jsonobject);

    EXPECT_EQ(accountinfo.accountName, "123456.qq.com");
    EXPECT_EQ(accountinfo.accountAddTime.toString("yyyy-MM-dd hh:mm:ss"), "2021-10-22 14:57:40");
    EXPECT_EQ(accountinfo.displayName, "123456");
}

TEST_F(ut_doadataconversion, ut_doadataconversion_accountListChangeParameterAnalysis_001)
{
    QString msg = "{\"iterfacecontent\":{\"accountid\":\"accounts_1632279519\"},\"iterfaceoper\":\"DEL\",\"stat\":\"0\"}";
    QList<QVariant> parmetrList = accountListChangeParameterAnalysis(msg);
    qWarning()<<parmetrList;
    EXPECT_EQ(parmetrList[0].toString(), "DEL");
    QJsonObject jsono = parmetrList[2].toJsonObject();
    QString accountid = jsono.value("accountid").toString();
    EXPECT_EQ(accountid, "accounts_1632279519");
}

TEST_F(ut_doadataconversion, ut_doadataconversion_accountListChangeParameterAnalysis_002)
{
    QString msg = "\"iterfacecontent\":{\"accountid\":\"accounts_1632279519\"},\"iterfaceoper\":\"DEL\",\"stat\":\"0\"}";
    QList<QVariant> parmetrList = accountListChangeParameterAnalysis(msg);
    qWarning()<<parmetrList;
    EXPECT_EQ(parmetrList.count(), 0);

}


TEST_F(ut_doadataconversion, ut_doadataconversion_remvoeAccountJsonObjectToInfo_001)
{
    QJsonObject jsono;
    jsono.insert("accountid", "accounts_1632279519");
    EXPECT_EQ(remvoeAccountJsonObjectToInfo(jsono), "accounts_1632279519");
}

TEST_F(ut_doadataconversion, ut_doadataconversion_accountJsonObjectToInfo_002)
{
    QString addstr = "{\"iterfacecontent\":{\"accountdbuspath\":"
                     "\"/com/dde/onlineaccount/accounts/accounts_1632292662\","
                     "\"accountflag\":1,\"accountid\":"
                     "\"accounts_1632292662\",\"accountname\":\"41124@qq.com\","
                     "\"accountstat\":0,\"accounttype\":1,\"accounturi\":"
                     "\"https://dav.qq.com/calendar/\",\"accounturl\":"
                     "\"https://dav.qq.com\",\"calendardisable\":false,\"createtime\":\"2021-09-22T14:37:42+08:00\","
                     "\"username\":\"412124@qq.com\"},\"iterfaceoper\":\"ADD\",\"stat\":\"0\"}";
    QList<QVariant> parmetrList = accountListChangeParameterAnalysis(addstr);
    qWarning()<<parmetrList;
    EXPECT_EQ(parmetrList[0].toString(), "ADD");
    QJsonObject jsono = parmetrList[2].toJsonObject();
    DOAAccountList::AccountInfo accountinfo = accountJsonObjectToInfo(parmetrList[2]);

    EXPECT_EQ(accountinfo.accountID, "accounts_1632292662");
    EXPECT_EQ(accountinfo.displayName, "412124@qq.com");
}


