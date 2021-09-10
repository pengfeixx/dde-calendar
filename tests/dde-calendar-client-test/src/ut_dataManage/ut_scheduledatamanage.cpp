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
#include "ut_scheduledatamanage.h"

ut_scheduledatamanage::ut_scheduledatamanage()
{
}

void ut_scheduledatamanage::SetUp()
{
    datamanage = new CScheduleDataManage();
}

void ut_scheduledatamanage::TearDown()
{
    delete datamanage;
    datamanage = nullptr;
}

//CSchedulesColor CScheduleDataManage::getScheduleColorByType(int type)
TEST_F(ut_scheduledatamanage, getScheduleColorByType_001)
{
    datamanage->setTheMe(1);
    CSchedulesColor color = datamanage->getScheduleColorByType(1);
    EXPECT_EQ(color.type, 1);
    EXPECT_EQ(color.textColor, QColor("#000000"));
}

TEST_F(ut_scheduledatamanage, getScheduleColorByType_002)
{
    datamanage->setTheMe(1);
    CSchedulesColor color = datamanage->getScheduleColorByType(8);
    EXPECT_EQ(color.type, -1);
}

//void CScheduleDataManage::setTheMe(int type)
TEST_F(ut_scheduledatamanage, setTheMe_001)
{
    datamanage->setTheMe(1);
    EXPECT_EQ(1, datamanage->m_theme);
}

TEST_F(ut_scheduledatamanage, setTheMe_002)
{
    datamanage->setTheMe(2);
    EXPECT_EQ(2, datamanage->m_theme);
}

//CScheduleDataManage *CScheduleDataManage::getScheduleDataManage()
TEST_F(ut_scheduledatamanage, getScheduleDataManage)
{
    EXPECT_NE(datamanage->getScheduleDataManage(), nullptr);
}

//QColor CScheduleDataManage::getSystemActiveColor()
TEST_F(ut_scheduledatamanage, getSystemActiveColor)
{
    QColor color = DGuiApplicationHelper::instance()->applicationPalette().highlight().color();
    EXPECT_EQ(color, datamanage->getSystemActiveColor());
}
