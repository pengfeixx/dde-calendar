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
#include "ut_doaaccountdbus.h"
#include "../../third-party_stub/stub.h"

#include <QDBusReply>
#include <QDBusMessage>
#include <QDBusInterface>
#include <QDebug>

ut_doaaccountdbus::ut_doaaccountdbus()
{

}

bool ut_doaaccountdbus::stub_resultAllFalse()
{
    return false;
}

bool ut_doaaccountdbus::stub_resultTrue()
{
    return true;
}

static QVariant commresult;

QVariant ut_doaaccountdbus::stub_resultQVariant()
{
    return commresult;
}


static QString stub_globmsg = "";
QDBusMessage ut_doaaccountdbus::stub_reply()
{
    QDBusMessage bus;
    QList<QVariant> arguments;
    arguments << "1234";
    bus.setArguments(arguments);
    return bus;
}

QDBusMessage::MessageType ut_doaaccountdbus::stub_type()
{
    stub_globmsg = "doadbustest";
    return QDBusMessage::MessageType::ReplyMessage;
}

bool ut_doaaccountdbus::stub_setPropertyByName(const char *porpertyName, const QVariant &value)
{
    return true;
}

QDBusPendingCall ut_doaaccountdbus::stub_asyncCallWithArgumentList(const QString &method,
                                           const QList<QVariant> &args)
{
    return QDBusPendingCall::fromError(QDBusConnection::sessionBus().lastError());
}

void ut_doaaccountdbus::SetUp()
{
    doaaccountdbus = new DOAAccountDBus("/com/test/doa");
}

void ut_doaaccountdbus::TearDown()
{
    delete doaaccountdbus;
    doaaccountdbus = nullptr;
}

TEST_F(ut_doaaccountdbus, ut_doaaccountdbus_remove_001)
{
    EXPECT_EQ(doaaccountdbus->remove(), false);
}

TEST_F(ut_doaaccountdbus, ut_doaaccountdbus_remove_002)
{
    Stub st;
    st.set(ADDR(QDBusMessage, type), ADDR(ut_doaaccountdbus, stub_type));
    doaaccountdbus->remove();
    EXPECT_EQ(stub_globmsg, "doadbustest");
}

TEST_F(ut_doaaccountdbus, ut_doaaccountdbus_checkAccountState_002)
{
    Stub st;
    st.set(ADDR(QDBusAbstractInterface, asyncCallWithArgumentList), ADDR(ut_doaaccountdbus, stub_asyncCallWithArgumentList));
    doaaccountdbus->checkAccountState();
    EXPECT_EQ(stub_globmsg, "doadbustest");
}

TEST_F(ut_doaaccountdbus, ut_doaaccountdbus_getCalendarDisabled_003)
{
    Stub st;
    st.set(ADDR(DOAAccountDBus, getPropertyByName), ADDR(ut_doaaccountdbus, stub_resultQVariant));
    commresult = true;
    EXPECT_EQ(doaaccountdbus->getCalendarDisabled(), true);
}

TEST_F(ut_doaaccountdbus, ut_doaaccountdbus_setCalendarDisabled_001)
{
    Stub st;
    st.set(ADDR(DOAAccountDBus, setPropertyByName), ADDR(ut_doaaccountdbus, stub_setPropertyByName));
    commresult = true;
    EXPECT_EQ(doaaccountdbus->setCalendarDisabled(true), true);
}

TEST_F(ut_doaaccountdbus, ut_doaaccountdbus_getUserName_001)
{
    Stub st;
    st.set(ADDR(DOAAccountDBus, getPropertyByName), ADDR(ut_doaaccountdbus, stub_resultQVariant));
    commresult = "1234";
    EXPECT_EQ(doaaccountdbus->getUserName(), "1234");
}

TEST_F(ut_doaaccountdbus, ut_doaaccountdbus_setUserName_001)
{
    Stub st;
    //st.set(ADDR(QDBusPendingCall, reply), ADDR(ut_doaaccountdbus, stub_reply));
    st.set(ADDR(DOAAccountDBus, setPropertyByName), ADDR(ut_doaaccountdbus, stub_setPropertyByName));
    commresult = true;
    EXPECT_EQ(doaaccountdbus->setUserName("1234"), true);
}

TEST_F(ut_doaaccountdbus, ut_doaaccountdbus_getAccountID_001)
{
    Stub st;
    st.set(ADDR(DOAAccountDBus, getPropertyByName), ADDR(ut_doaaccountdbus, stub_resultQVariant));
    commresult = "1234";
    EXPECT_EQ(doaaccountdbus->getAccountID(), "1234");
}

TEST_F(ut_doaaccountdbus, ut_doaaccountdbus_getProviderName_001)
{
    Stub st;
    st.set(ADDR(DOAAccountDBus, getPropertyByName), ADDR(ut_doaaccountdbus, stub_resultQVariant));
    commresult = 1234;
    EXPECT_EQ(doaaccountdbus->getProviderName(), 1234);
}

TEST_F(ut_doaaccountdbus, ut_doaaccountdbus_getProviderType_001)
{
    Stub st;
    st.set(ADDR(DOAAccountDBus, getPropertyByName), ADDR(ut_doaaccountdbus, stub_resultQVariant));
    commresult = 1234;
    EXPECT_EQ(doaaccountdbus->getProviderType(), 1234);
}

TEST_F(ut_doaaccountdbus, ut_doaaccountdbus_getPropertyByName_001)
{
    Stub st;
    st.set(ADDR(QDBusInterface, property), ADDR(ut_doaaccountdbus, stub_resultQVariant));
    commresult = "1234";
    EXPECT_EQ(doaaccountdbus->getPropertyByName("1234"), "1234");
}

TEST_F(ut_doaaccountdbus, ut_doaaccountdbus_setPropertyByName_001)
{
    Stub st;
    st.set(ADDR(QDBusInterface, setProperty), ADDR(ut_doaaccountdbus, stub_setPropertyByName));
    EXPECT_EQ(doaaccountdbus->setPropertyByName("1234", "1234"), true);
}

TEST_F(ut_doaaccountdbus, ut_doaaccountdbus_propertiesChanged_001)
{
    QDBusMessage dbusmsg;
    dbusmsg << "1234";
    doaaccountdbus->propertiesChanged(dbusmsg);
}

TEST_F(ut_doaaccountdbus, ut_doaaccountdbus_propertiesChanged_002)
{
    QDBusMessage dbusmsg;
    dbusmsg << "com.dde.onlineaccount.account1"<<"1234"<<"1234";
    doaaccountdbus->propertiesChanged(dbusmsg);
}

TEST_F(ut_doaaccountdbus, ut_doaaccountdbus_propertiesChanged_003)
{
    QVariantMap vmap;
    vmap.insert("CalendarDisabled", true);
    QDBusMessage dbusmsg;
    dbusmsg << "com.dde.onlineaccount.account"<<vmap<<"1234" ;
    doaaccountdbus->propertiesChanged(dbusmsg);
}
