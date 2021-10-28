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
#include "ut_doanetworkdbus.h"
#include "../../third-party_stub/stub.h"

#include <QDBusInterface>

void ut_doanetworkdbus::SetUp()
{
    doaNetWorkDBus = new DOANetWorkDBus();
}

void ut_doanetworkdbus::TearDown()
{
    delete doaNetWorkDBus;
    doaNetWorkDBus = nullptr;
}

static QVariant commresult;

QVariant ut_doanetworkdbus::stub_resultQVariant()
{
    return commresult;
}

TEST_F(ut_doanetworkdbus, ut_doanetworkdbus_getNetWorkState_001)
{
    Stub st;
    st.set(ADDR(DOANetWorkDBus, getPropertyByName), ADDR(ut_doanetworkdbus, stub_resultQVariant));
    commresult = 70;
    EXPECT_EQ(doaNetWorkDBus->getNetWorkState(), DOANetWorkDBus::Active);
}


TEST_F(ut_doanetworkdbus, ut_doanetworkdbus_getNetWorkState_002)
{
    Stub st;
    st.set(ADDR(DOANetWorkDBus, getPropertyByName), ADDR(ut_doanetworkdbus, stub_resultQVariant));
    commresult = 40;
    EXPECT_EQ(doaNetWorkDBus->getNetWorkState(), DOANetWorkDBus::Disconnect);
}

TEST_F(ut_doanetworkdbus, ut_doanetworkdbus_getPropertyByName_001)
{
    Stub st;
    st.set(ADDR(QDBusInterface, property), ADDR(ut_doanetworkdbus, stub_resultQVariant));
    commresult = "1234";
    EXPECT_EQ(doaNetWorkDBus->getPropertyByName("1234"), "1234");
}


TEST_F(ut_doanetworkdbus, ut_doanetworkdbus_propertiesChanged_001)
{
    QDBusMessage dbusmsg;
    dbusmsg << "1234";
    doaNetWorkDBus->propertiesChanged(dbusmsg);
}

TEST_F(ut_doanetworkdbus, ut_doanetworkdbus_propertiesChanged_002)
{
    QDBusMessage dbusmsg;
    dbusmsg << "1234" <<"1234"<<"1234";
    doaNetWorkDBus->propertiesChanged(dbusmsg);
}

TEST_F(ut_doanetworkdbus, ut_doanetworkdbus_propertiesChanged_003)
{
    QVariantMap vmap;
    vmap.insert("State", 70);
    QDBusMessage dbusmsg;
    dbusmsg << NETWORK_DBUS_INTEERFACENAME <<vmap<<"1234" ;
    doaNetWorkDBus->propertiesChanged(dbusmsg);
}
