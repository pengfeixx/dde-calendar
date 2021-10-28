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
#include "ut_doaaccountmanagedbus.h"
#include "../../third-party_stub/stub.h"

#include <QSignalSpy>

static bool dbuscallresult = false;
static bool dbuscallresultmsg = false;

void ut_doaaccountmanagedbus::SetUp()
{
    doaaccountmanagedbus = new DOAAccountManageDBus();
}

void ut_doaaccountmanagedbus::TearDown()
{
    delete doaaccountmanagedbus;
    doaaccountmanagedbus = nullptr;
}

QDBusMessage::MessageType ut_doaaccountmanagedbus::stub_type()
{
    return QDBusMessage::MessageType::SignalMessage;
}


QString ut_doaaccountmanagedbus::stub_path()
{
    return DBUS_PATH;
}

QString ut_doaaccountmanagedbus::stub_interface()
{
    return DBUS_INTEERFACENAME;
}

QString ut_doaaccountmanagedbus::stub_member()
{
    return "InterfaceAccountInfo";
}

bool ut_doaaccountmanagedbus::stub_callWithCallback(const QString &method,
                                                    const QList<QVariant> &args,
                                                    QObject *receiver, const char *member, const char *errorSlot)
{
    dbuscallresultmsg = !dbuscallresult;
    return  dbuscallresult;
}

TEST_F(ut_doaaccountmanagedbus, ut_doaaccountmanagedbus_addAccount_001)
{
    AddAccountInfo addinfo;
    addinfo.UUID ="1234";
    addinfo.accountPassword="123456";
    addinfo.accountName="123456@qq.com";
    Stub st;
    st.set((bool (QDBusAbstractInterface::*)(const QString &,
                                             const QList<QVariant> &,
                                             QObject *, const char *, const char *))ADDR(QDBusAbstractInterface, callWithCallback), ADDR(ut_doaaccountmanagedbus, stub_callWithCallback));
    dbuscallresult = false;
    doaaccountmanagedbus->addAccount(addinfo);
    EXPECT_EQ(dbuscallresultmsg, !dbuscallresult);
}

TEST_F(ut_doaaccountmanagedbus, ut_doaaccountmanagedbus_addAccount_002)
{
    AddAccountInfo addinfo;
    addinfo.UUID ="1234";
    addinfo.accountPassword="123456";
    addinfo.accountName="123456@qq.com";
    Stub st;
    st.set((bool (QDBusAbstractInterface::*)(const QString &,
                                             const QList<QVariant> &,
                                             QObject *, const char *, const char *))ADDR(QDBusAbstractInterface, callWithCallback), ADDR(ut_doaaccountmanagedbus, stub_callWithCallback));
    dbuscallresult = true;
    doaaccountmanagedbus->addAccount(addinfo);
    EXPECT_EQ(dbuscallresultmsg, !dbuscallresult);
}

TEST_F(ut_doaaccountmanagedbus, ut_doaaccountmanagedbus_getAccountList_001)
{
    Stub st;
    st.set((bool (QDBusAbstractInterface::*)(const QString &,
                                             const QList<QVariant> &,
                                             QObject *, const char *, const char *))ADDR(QDBusAbstractInterface, callWithCallback), ADDR(ut_doaaccountmanagedbus, stub_callWithCallback));
    dbuscallresult = false;
    doaaccountmanagedbus->getAccountList();
    EXPECT_EQ(dbuscallresultmsg, !dbuscallresult);
}

TEST_F(ut_doaaccountmanagedbus, ut_doaaccountmanagedbus_getAccountList_002)
{
    Stub st;
    st.set((bool (QDBusAbstractInterface::*)(const QString &,
                                             const QList<QVariant> &,
                                             QObject *, const char *, const char *))ADDR(QDBusAbstractInterface, callWithCallback), ADDR(ut_doaaccountmanagedbus, stub_callWithCallback));
    dbuscallresult = true;
    doaaccountmanagedbus->getAccountList();
    EXPECT_EQ(dbuscallresultmsg, !dbuscallresult);
}

TEST_F(ut_doaaccountmanagedbus, ut_doaaccountmanagedbus_loginCancle_001)
{
    Stub st;
    st.set((bool (QDBusAbstractInterface::*)(const QString &,
                                             const QList<QVariant> &,
                                             QObject *, const char *, const char *))ADDR(QDBusAbstractInterface, callWithCallback), ADDR(ut_doaaccountmanagedbus, stub_callWithCallback));
    dbuscallresult = false;
    doaaccountmanagedbus->loginCancle("12345");
    EXPECT_EQ(dbuscallresultmsg, !dbuscallresult);
}

TEST_F(ut_doaaccountmanagedbus, ut_doaaccountmanagedbus_loginCancle_002)
{
    Stub st;
    st.set((bool (QDBusAbstractInterface::*)(const QString &,
                                             const QList<QVariant> &,
                                             QObject *, const char *, const char *))ADDR(QDBusAbstractInterface, callWithCallback), ADDR(ut_doaaccountmanagedbus, stub_callWithCallback));
    dbuscallresult = true;
    doaaccountmanagedbus->loginCancle("12345");
    EXPECT_EQ(dbuscallresultmsg, !dbuscallresult);
}

TEST_F(ut_doaaccountmanagedbus, ut_doaaccountmanagedbus_accountListChangeHandle_001)
{
    QString msg = "{\"iterfacecontent\":{\"accountid\":\"accounts_1632279519\"},\"iterfaceoper\":\"DEL\",\"stat\":\"1\"}";
    Stub st;
    st.set((bool (QDBusAbstractInterface::*)(const QString &,
                                             const QList<QVariant> &,
                                             QObject *, const char *, const char *))ADDR(QDBusAbstractInterface, callWithCallback), ADDR(ut_doaaccountmanagedbus, stub_callWithCallback));
    QSignalSpy spy(doaaccountmanagedbus, SIGNAL(signalAddAccountInfo(const DOAAccountList::AccountInfo &)));
    doaaccountmanagedbus->accountListChangeHandle(msg);

    EXPECT_EQ(spy.count(), 0);
}

TEST_F(ut_doaaccountmanagedbus, ut_doaaccountmanagedbus_accountListChangeHandle_002)
{
    QString msg = "{\"iterfacecontent\":{\"accountid\":\"accounts_1632279519\"},\"iterfaceoper\":\"DEL\",\"stat\":\"0\"}";
    Stub st;
    st.set((bool (QDBusAbstractInterface::*)(const QString &,
                                             const QList<QVariant> &,
                                             QObject *, const char *, const char *))ADDR(QDBusAbstractInterface, callWithCallback), ADDR(ut_doaaccountmanagedbus, stub_callWithCallback));
    QSignalSpy spy(doaaccountmanagedbus, SIGNAL(signalDeleteAccount(const QString &)));
    doaaccountmanagedbus->accountListChangeHandle(msg);
    EXPECT_EQ(spy.count(), 1);
}

TEST_F(ut_doaaccountmanagedbus, ut_doaaccountmanagedbus_accountListChangeHandle_003)
{
    QString addstr = "{\"iterfacecontent\":{\"accountdbuspath\":"
                     "\"/com/dde/onlineaccount/accounts/accounts_1632292662\","
                     "\"accountflag\":1,\"accountid\":"
                     "\"accounts_1632292662\",\"accountname\":\"41124@qq.com\","
                     "\"accountstat\":0,\"accounttype\":1,\"accounturi\":"
                     "\"https://dav.qq.com/calendar/\",\"accounturl\":"
                     "\"https://dav.qq.com\",\"calendardisable\":false,\"createtime\":\"2021-09-22T14:37:42+08:00\","
                     "\"username\":\"412124@qq.com\"},\"iterfaceoper\":\"ADD\",\"stat\":\"0\"}";
    Stub st;
    st.set((bool (QDBusAbstractInterface::*)(const QString &,
                                             const QList<QVariant> &,
                                             QObject *, const char *, const char *))ADDR(QDBusAbstractInterface, callWithCallback), ADDR(ut_doaaccountmanagedbus, stub_callWithCallback));
    QSignalSpy spy(doaaccountmanagedbus, SIGNAL(signalAddAccountInfo(const DOAAccountList::AccountInfo &)));
    doaaccountmanagedbus->accountListChangeHandle(addstr);
    EXPECT_EQ(spy.count(), 1);
}

TEST_F(ut_doaaccountmanagedbus, ut_doaaccountmanagedbus_propertyChanged_001)
{
    QDBusMessage busmsg;
    busmsg << "1234";

    Stub st;
    st.set(ADDR(QDBusMessage, type), ADDR(ut_doaaccountmanagedbus, stub_type));
    st.set(ADDR(QDBusMessage, path), ADDR(ut_doaaccountmanagedbus, stub_path));
    st.set(ADDR(QDBusMessage, interface), ADDR(ut_doaaccountmanagedbus, stub_interface));
    st.set(ADDR(QDBusMessage, member), ADDR(ut_doaaccountmanagedbus, stub_member));
    st.set(ADDR(DOAAccountManageDBus, accountListChangeHandle), ADDR(ut_doaaccountmanagedbus, stub_callWithCallback));

    dbuscallresult = false;
    doaaccountmanagedbus->propertyChanged(busmsg);
    EXPECT_EQ(dbuscallresultmsg, !dbuscallresult);
}

TEST_F(ut_doaaccountmanagedbus, ut_doaaccountmanagedbus_propertyChanged_002)
{
    QDBusMessage busmsg;
    busmsg << "1234";

    Stub st;
    st.set(ADDR(DOAAccountManageDBus, accountListChangeHandle), ADDR(ut_doaaccountmanagedbus, stub_callWithCallback));

    dbuscallresult = false;
    dbuscallresultmsg = false;
    doaaccountmanagedbus->propertyChanged(busmsg);
    EXPECT_EQ(dbuscallresultmsg, dbuscallresult);
}

TEST_F(ut_doaaccountmanagedbus, ut_doaaccountmanagedbus_slotGetAccountList_001)
{
    QString strmsg;

    QSignalSpy spy(doaaccountmanagedbus, SIGNAL(signalGetAccountList(const DOAAccountList::AccountInfoList &)));
    doaaccountmanagedbus->slotGetAccountList(strmsg);
    EXPECT_EQ(spy.count(), 1);
}

TEST_F(ut_doaaccountmanagedbus, ut_doaaccountmanagedbus_slotDBusError_001)
{
    QDBusError error;
    doaaccountmanagedbus->slotDBusError(error);
}
