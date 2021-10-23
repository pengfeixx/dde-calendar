/*
* Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
*
* Author:     hejinghai <hejinghai@uniontech.com>
*
* Maintainer: hejinghai <hejinghai@uniontech.com>
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
#include "ut_configsettings.h"

ut_configsettings::ut_configsettings()
{
}

ut_configsettings::~ut_configsettings()
{
}

void ut_configsettings::SetUp()
{
    conf = CConfigSettings::getInstance();
}

void ut_configsettings::TearDown()
{

}

QString syncstr = "";
void stub_Handle()
{
    syncstr = "sync";
}

void setValue_stub(void *obj, const QString &key, const QVariant &value)
{
    Q_UNUSED(obj)
    Q_UNUSED(key)
    syncstr = value.toString();
}

//void CConfigSettings::sync()
TEST_F(ut_configsettings, sync)
{
    Stub stub;
    stub.set(ADDR(QSettings, sync), stub_Handle);
    conf->sync();
    ASSERT_EQ(syncstr, "sync");
}

TEST_F(ut_configsettings, setOption)
{
    Stub stub;
    stub.set(ADDR(QSettings, setValue), setValue_stub);
    conf->setOption("base.state", 0);
    ASSERT_EQ(syncstr, "0");
}
