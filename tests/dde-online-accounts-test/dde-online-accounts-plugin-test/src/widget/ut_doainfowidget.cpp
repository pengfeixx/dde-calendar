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
#include "ut_doainfowidget.h"

#include <QSignalSpy>

ut_doainfowidget::ut_doainfowidget()
{

}

void ut_doainfowidget::SetUp()
{
    doaInfoWidget = new DOAInfoWidget();
}

void ut_doainfowidget::TearDown()
{
    delete doaInfoWidget;
    doaInfoWidget = nullptr;
}

TEST_F(ut_doainfowidget, ut_doainfowidget_setShowData_001)
{
    doaInfoWidget->m_displayName = "1234";
    doaInfoWidget->setShowData("1234", "www.uniontech.com", "uos", "uos");
    EXPECT_EQ(doaInfoWidget->m_displayName, "1234");
}

TEST_F(ut_doainfowidget, ut_doainfowidget_setShowData_002)
{
    doaInfoWidget->m_password = "uos";
    doaInfoWidget->setShowData("1234", "www.uniontech.com", "uos", "uos");
    EXPECT_EQ(doaInfoWidget->m_password, "uos");
}

TEST_F(ut_doainfowidget, ut_doainfowidget_setShowData_003)
{
    doaInfoWidget->m_password = "uos";
    doaInfoWidget->setShowData("12345", "www.uniontech.com", "uos", "uos1");
    EXPECT_EQ(doaInfoWidget->m_password, "uos1");
}

TEST_F(ut_doainfowidget, ut_doainfowidget_setShowData_004)
{
    doaInfoWidget->m_displayName = "1234";
    doaInfoWidget->setShowData("12345", "www.uniontech.com", "uos", "uos1");
    EXPECT_EQ(doaInfoWidget->m_displayName, "12345");
}

TEST_F(ut_doainfowidget, ut_doainfowidget_slotUserNameFocusChanged_001)
{
    doaInfoWidget->m_userName->setText("123456789012345678901234567890123");
    doaInfoWidget->slotUserNameFocusChanged(false);

    EXPECT_EQ(doaInfoWidget->m_userName->isAlert(), true);
}

TEST_F(ut_doainfowidget, ut_doainfowidget_slotUserNameFocusChanged_002)
{
    doaInfoWidget->m_displayName = "12345678";
    doaInfoWidget->slotUserNameFocusChanged(false);

    EXPECT_EQ(doaInfoWidget->m_userName->text(), "12345678");
}

TEST_F(ut_doainfowidget, ut_doainfowidget_slotUserNameFocusChanged_003)
{
    doaInfoWidget->m_displayName = "12345678";
    doaInfoWidget->m_userName->setText("12345678");
    QSignalSpy spy(doaInfoWidget, SIGNAL(signalUpdateUserName(const QString &)));
    doaInfoWidget->slotUserNameFocusChanged(false);

    EXPECT_EQ(spy.count(), 0);
}

TEST_F(ut_doainfowidget, ut_doainfowidget_slotUserNameFocusChanged_004)
{
    doaInfoWidget->m_userName->setText("12345678");
    QSignalSpy spy(doaInfoWidget, SIGNAL(signalUpdateUserName(const QString &)));
    doaInfoWidget->slotUserNameFocusChanged(false);

    EXPECT_EQ(spy.count(), 1);
}

TEST_F(ut_doainfowidget, ut_doainfowidget_slotUserNameTextChanged_001)
{
    doaInfoWidget->m_userName->setAlert(true);
    doaInfoWidget->slotUserNameTextChanged("12345678");
    EXPECT_EQ(doaInfoWidget->m_userName->isAlert(), false);
}
