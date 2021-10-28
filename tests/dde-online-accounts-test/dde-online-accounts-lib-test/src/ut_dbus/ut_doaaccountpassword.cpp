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
#include "ut_doaaccountpassword.h"
#include "../../third-party_stub/stub.h"

static bool dbuscallresult = false;
static bool dbuscallresultmsg = false;

void ut_doaaccountpassword::SetUp()
{
    doaAccountPassword = new DOAAccountPassword("/com/test/doa");
}

void ut_doaaccountpassword::TearDown()
{
    delete doaAccountPassword;
    doaAccountPassword = nullptr;
}

bool ut_doaaccountpassword::stub_callWithCallback(const QString &method,
                                                    const QList<QVariant> &args,
                                                    QObject *receiver, const char *member, const char *errorSlot)
{
    dbuscallresultmsg = !dbuscallresult;
    return  dbuscallresult;
}

TEST_F(ut_doaaccountpassword, ut_doaaccountmanagedbus_getPassword_001)
{
    Stub st;
    st.set((bool (QDBusAbstractInterface::*)(const QString &,
                                             const QList<QVariant> &,
                                             QObject *, const char *, const char *))ADDR(QDBusAbstractInterface, callWithCallback), ADDR(ut_doaaccountpassword, stub_callWithCallback));
    dbuscallresult = false;
    doaAccountPassword->getPassword();
    EXPECT_EQ(dbuscallresultmsg, !dbuscallresult);
}

TEST_F(ut_doaaccountpassword, ut_doaaccountmanagedbus_getPassword_002)
{
    Stub st;
    st.set((bool (QDBusAbstractInterface::*)(const QString &,
                                             const QList<QVariant> &,
                                             QObject *, const char *, const char *))ADDR(QDBusAbstractInterface, callWithCallback), ADDR(ut_doaaccountpassword, stub_callWithCallback));
    dbuscallresult = true;
    doaAccountPassword->getPassword();
    EXPECT_EQ(dbuscallresultmsg, !dbuscallresult);
}

TEST_F(ut_doaaccountpassword, ut_doaaccountmanagedbus_changePassword_001)
{
    Stub st;
    st.set((bool (QDBusAbstractInterface::*)(const QString &,
                                             const QList<QVariant> &,
                                             QObject *, const char *, const char *))ADDR(QDBusAbstractInterface, callWithCallback), ADDR(ut_doaaccountpassword, stub_callWithCallback));
    dbuscallresult = false;
    doaAccountPassword->changePassword("12345");
    EXPECT_EQ(dbuscallresultmsg, !dbuscallresult);
}

TEST_F(ut_doaaccountpassword, ut_doaaccountmanagedbus_changePassword_002)
{
    Stub st;
    st.set((bool (QDBusAbstractInterface::*)(const QString &,
                                             const QList<QVariant> &,
                                             QObject *, const char *, const char *))ADDR(QDBusAbstractInterface, callWithCallback), ADDR(ut_doaaccountpassword, stub_callWithCallback));
    dbuscallresult = true;
    doaAccountPassword->changePassword("12345");
    EXPECT_EQ(dbuscallresultmsg, !dbuscallresult);
}

TEST_F(ut_doaaccountpassword, ut_doaaccountmanagedbus_slotDBusError_001)
{
    QDBusError error;
    doaAccountPassword->slotDBusError(error);
}
