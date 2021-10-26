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
#include "ut_accountdb.h"
#include "../../third-party_stub/stub.h"

#include <QDebug>
#include <QFile>
#include <QSqlQuery>
#include <QUuid>
#include <QSignalSpy>

static int callcnt = 0;

ut_accountdb::ut_accountdb()
{

}

void ut_accountdb::SetUp()
{

    db = new AccountDB;
}

void ut_accountdb::TearDown()
{
    delete db;
    db = nullptr;
}

bool ut_accountdb::stub_resultAllFalse()
{
    return false;
}

bool ut_accountdb::stub_resultTrue()
{
    return true;
}

bool ut_accountdb::stub_result()
{
    if(callcnt == 0){
        callcnt++;
        return true;
    }else {
        return false;
    }
}


QString ut_accountdb::stub_writableLocation(QStandardPaths::StandardLocation type)
{
    return "/tmp";
}

QString ut_accountdb::firstremovedbfile()
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

TEST_F(ut_accountdb, ut_accountdb_initDb_001)
{
    Stub s;
    s.set(ADDR(QStandardPaths, writableLocation), ADDR(ut_accountdb, stub_writableLocation));

    QString dbpath = firstremovedbfile();
    db->initDb();
    QFile file(dbpath);
    EXPECT_EQ(file.exists(), true);
}

TEST_F(ut_accountdb, ut_accountdb_initAccountTable_001)
{
    Stub s;
    s.set(ADDR(QStandardPaths, writableLocation), ADDR(ut_accountdb, stub_writableLocation));
    s.set((bool (QSqlQuery::*)(const QString &))ADDR(QSqlQuery, exec), ADDR(ut_accountdb, stub_resultAllFalse));
    QString dbpath = firstremovedbfile();
    db->initDb();
    s.reset((bool (QSqlQuery::*)(const QString &))ADDR(QSqlQuery, exec));

    QString sql = "select count(1) from sqlite_master where type='table' and name ='AccountInfo' order by name";

    //创建数据库
    QSqlDatabase dbtmp = QSqlDatabase::addDatabase("QSQLITE", QUuid::createUuid().toString(QUuid::WithoutBraces));
    dbtmp.setDatabaseName(dbpath);
    dbtmp.open();

    QSqlQuery query(dbtmp);

    query.exec(sql);
    query.next();
    int icount = query.value(0).toInt();
    query.next();
    EXPECT_EQ(icount, 0);
    dbtmp.close();
}

TEST_F(ut_accountdb, ut_accountdb_initAccountTable_002)
{
    Stub s;
    s.set(ADDR(QStandardPaths, writableLocation), ADDR(ut_accountdb, stub_writableLocation));
    s.set((bool (QSqlQuery::*)(const QString &))ADDR(QSqlQuery, exec), ADDR(ut_accountdb, stub_result));
    QString dbpath = firstremovedbfile();
    db->initDb();
}

TEST_F(ut_accountdb, ut_accountdb_addAccount_001)
{
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
    Stub st;
    st.set((bool (QSqlDatabase::*)())ADDR(QSqlDatabase, transaction), ADDR(ut_accountdb, stub_resultAllFalse));
    st.set(ADDR(QStandardPaths, writableLocation), ADDR(ut_accountdb, stub_writableLocation));
    QString dbpath = firstremovedbfile();
    db->initDb();

    EXPECT_EQ(db->addAccount(accinfo), false);
}

TEST_F(ut_accountdb, ut_accountdb_addAccount_002)
{
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
    Stub st;
    st.set(ADDR(QStandardPaths, writableLocation), ADDR(ut_accountdb, stub_writableLocation));
    st.set((bool (QSqlQuery::*)())ADDR(QSqlQuery, prepare), ADDR(ut_accountdb, stub_resultAllFalse));
    QString dbpath = firstremovedbfile();
    db->initDb();

    EXPECT_EQ(db->addAccount(accinfo), false);
}

TEST_F(ut_accountdb, ut_accountdb_addAccount_003)
{
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
    Stub st;
    st.set(ADDR(QStandardPaths, writableLocation), ADDR(ut_accountdb, stub_writableLocation));
    st.set((bool (QSqlQuery::*)())ADDR(QSqlQuery, exec), ADDR(ut_accountdb, stub_resultAllFalse));
    QString dbpath = firstremovedbfile();
    db->initDb();

    EXPECT_EQ(db->addAccount(accinfo), false);
}

TEST_F(ut_accountdb, ut_accountdb_addAccount_004)
{
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
    callcnt = 0;
    Stub st;
    st.set(ADDR(QStandardPaths, writableLocation), ADDR(ut_accountdb, stub_writableLocation));
    st.set((bool (QSqlQuery::*)(const QString &))ADDR(QSqlQuery, exec), ADDR(ut_accountdb, stub_result));
    QString dbpath = firstremovedbfile();
    db->initDb();

    EXPECT_EQ(db->addAccount(accinfo), false);
}

TEST_F(ut_accountdb, ut_accountdb_addAccount_005)
{
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
    callcnt = 0;
    Stub st;
    st.set(ADDR(QStandardPaths, writableLocation), ADDR(ut_accountdb, stub_writableLocation));
    QString dbpath = firstremovedbfile();
    db->initDb();

    EXPECT_EQ(db->addAccount(accinfo), true);

    //创建数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", QUuid::createUuid().toString(QUuid::WithoutBraces));
    db.setDatabaseName(dbpath);
    db.open();

    QSqlQuery query(db);

    QString sql = "select count(1) from accountinfo where AccountName ='1234@qq.com' ";
    query.exec(sql);
    query.next();
    int icount = query.value(0).toInt();
    query.next();
    db.close();

    EXPECT_EQ(icount, 1);
}

TEST_F(ut_accountdb, ut_accountdb_deleteAccount_001)
{
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
    callcnt = 0;
    Stub st;
    st.set(ADDR(QStandardPaths, writableLocation), ADDR(ut_accountdb, stub_writableLocation));
    QString dbpath = firstremovedbfile();
    db->initDb();

    db->addAccount(accinfo);

    st.set((bool (QSqlQuery::*)(const QString &))ADDR(QSqlQuery, exec), ADDR(ut_accountdb, stub_resultAllFalse));
    db->deleteAccount("1234");
    st.reset((bool (QSqlQuery::*)(const QString &))ADDR(QSqlQuery, exec));

    //创建数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", QUuid::createUuid().toString(QUuid::WithoutBraces));
    db.setDatabaseName(dbpath);
    db.open();

    QSqlQuery query(db);

    QString sql = "select count(1) from accountinfo where AccountName ='1234@qq.com' ";
    query.exec(sql);
    query.next();
    int icount = query.value(0).toInt();
    query.next();
    db.close();

    EXPECT_EQ(icount, 1);
}

TEST_F(ut_accountdb, ut_accountdb_deleteAccount_002)
{
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
    callcnt = 0;
    Stub st;
    st.set(ADDR(QStandardPaths, writableLocation), ADDR(ut_accountdb, stub_writableLocation));
    QString dbpath = firstremovedbfile();
    db->initDb();

    db->addAccount(accinfo);
    db->deleteAccount("1234");
    //创建数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", QUuid::createUuid().toString(QUuid::WithoutBraces));
    db.setDatabaseName(dbpath);
    db.open();

    QSqlQuery query(db);

    QString sql = "select count(1) from accountinfo where AccountName ='1234@qq.com' ";
    query.exec(sql);
    query.next();
    int icount = query.value(0).toInt();
    query.next();
    EXPECT_EQ(icount, 0);

    sql = "select count(1) from accountsyncobject where accountid ='1234' ";
    query.exec(sql);
    query.next();
    icount = query.value(0).toInt();
    query.next();
    db.close();
    EXPECT_EQ(icount, 0);
}

TEST_F(ut_accountdb, ut_accountdb_updateProperty_001)
{
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
    callcnt = 0;
    Stub st;
    st.set(ADDR(QStandardPaths, writableLocation), ADDR(ut_accountdb, stub_writableLocation));
    QString dbpath = firstremovedbfile();
    db->initDb();

    db->addAccount(accinfo);
    db->updateProperty("1234", "CalendarDisable", false);
    //创建数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", QUuid::createUuid().toString(QUuid::WithoutBraces));
    db.setDatabaseName(dbpath);
    db.open();

    QSqlQuery query(db);

    QString sql = "select IsEnable from accountsyncobject where accountid ='1234' ";
    query.exec(sql);
    query.next();
    bool icount = query.value(0).toBool();
    query.next();
    EXPECT_EQ(icount, false);
}

TEST_F(ut_accountdb, ut_accountdb_updateProperty_002)
{
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
    callcnt = 0;
    Stub st;
    st.set(ADDR(QStandardPaths, writableLocation), ADDR(ut_accountdb, stub_writableLocation));
    QString dbpath = firstremovedbfile();
    db->initDb();

    db->addAccount(accinfo);
    db->updateProperty("1234", "UserName", "1235");
    //创建数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", QUuid::createUuid().toString(QUuid::WithoutBraces));
    db.setDatabaseName(dbpath);
    db.open();

    QSqlQuery query(db);

    QString sql = "select UserName from accountinfo where accountid ='1234' ";
    query.exec(sql);
    query.next();
    QString uname = query.value(0).toString();
    query.next();
    EXPECT_EQ(uname, "1235");
}

TEST_F(ut_accountdb, ut_accountdb_updateProperty_003)
{
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
    accinfo.m_state = 13;
    callcnt = 0;
    Stub st;
    st.set(ADDR(QStandardPaths, writableLocation), ADDR(ut_accountdb, stub_writableLocation));
    QString dbpath = firstremovedbfile();
    db->initDb();

    db->addAccount(accinfo);
    db->updateProperty("1234", "Status", 1);
    //创建数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", QUuid::createUuid().toString(QUuid::WithoutBraces));
    db.setDatabaseName(dbpath);
    db.open();

    QSqlQuery query(db);

    QString sql = "select State from accountinfo where accountid ='1234' ";
    query.exec(sql);
    query.next();
    int state = query.value(0).toInt();
    query.next();
    EXPECT_EQ(state, 1);
}

TEST_F(ut_accountdb, ut_accountdb_updateProperty_004)
{
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
    accinfo.m_state = 13;
    callcnt = 0;
    Stub st;
    st.set(ADDR(QStandardPaths, writableLocation), ADDR(ut_accountdb, stub_writableLocation));
    QString dbpath = firstremovedbfile();
    db->initDb();

    db->addAccount(accinfo);
    db->updateProperty("1234", "Password", "13445");
    //创建数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", QUuid::createUuid().toString(QUuid::WithoutBraces));
    db.setDatabaseName(dbpath);
    db.open();

    QSqlQuery query(db);

    QString sql = "select AccountPassword from accountinfo where accountid ='1234' ";
    query.exec(sql);
    query.next();
    QString Password = query.value(0).toString();
    query.next();
    EXPECT_EQ(Password, "13445");
}

TEST_F(ut_accountdb, ut_accountdb_updateProperty_005)
{
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
    callcnt = 0;
    Stub st;
    st.set(ADDR(QStandardPaths, writableLocation), ADDR(ut_accountdb, stub_writableLocation));
    QString dbpath = firstremovedbfile();
    db->initDb();

    db->addAccount(accinfo);
    st.set((bool (QSqlQuery::*)(const QString &))ADDR(QSqlQuery, exec), ADDR(ut_accountdb, stub_resultAllFalse));
    db->updateProperty("1234", "UserName", "1235");
    st.reset((bool (QSqlQuery::*)(const QString &))ADDR(QSqlQuery, exec));
    //创建数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", QUuid::createUuid().toString(QUuid::WithoutBraces));
    db.setDatabaseName(dbpath);
    db.open();

    QSqlQuery query(db);

    QString sql = "select UserName from accountinfo where accountid ='1234' ";
    query.exec(sql);
    query.next();
    QString uname = query.value(0).toString();
    query.next();
    EXPECT_EQ(uname, "1234");
}

TEST_F(ut_accountdb, ut_accountdb_queryAccountList_001)
{
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
    callcnt = 0;
    Stub st;
    st.set(ADDR(QStandardPaths, writableLocation), ADDR(ut_accountdb, stub_writableLocation));
    QString dbpath = firstremovedbfile();
    db->initDb();

    db->addAccount(accinfo);
    QSignalSpy spy(db, SIGNAL(selectAccountResult(const AccountResultList &)));
    db->queryAccountList();
    QVariantList arguments = spy.at(0);
    EXPECT_EQ(arguments.count(), 1);
    EXPECT_EQ(spy.count(), 1);
}

