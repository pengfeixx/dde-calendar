/*
* Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
*
* Author:     chenhaifeng  <chenhaifeng@uniontech.com>
*
* Maintainer: chenhaifeng  <chenhaifeng@uniontech.com>
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
#include "ut_daywindow.h"

#include "customWidget/customframe.h"

ut_dayWindow::ut_dayWindow()
{
}

void ut_dayWindow::SetUp()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    m_dayWindow = new CDayWindow();
    m_dayWindow->setCurrentDateTime(currentTime);
    m_dayWindow->setSelectDate(currentTime.date());
}

void ut_dayWindow::TearDown()
{
    delete m_dayWindow;
    m_dayWindow = nullptr;
}

//测试paintevent
TEST_F(ut_dayWindow, getPixmap)
{
    m_dayWindow->setFixedSize(800, 600);
    QPixmap pixmap(m_dayWindow->size());
    m_dayWindow->render(&pixmap);
    EXPECT_EQ(pixmap.size(), m_dayWindow->size());
}

//setTheme
TEST_F(ut_dayWindow, setTheme_001)
{
    int type = 1;
    QColor groundColor("#FFFFFF");
    m_dayWindow->setTheMe(type);
    EXPECT_EQ(groundColor, m_dayWindow->m_leftground->m_bnormalColor);
}

TEST_F(ut_dayWindow, setTheme_002)
{
    int type = 2;
    QColor groundColor("#282828");
    m_dayWindow->setTheMe(type);
    EXPECT_EQ(groundColor, m_dayWindow->m_leftground->m_bnormalColor);
}

//setSearchWFlag
TEST_F(ut_dayWindow, setSearchWFlag)
{
    bool flag = true;
    m_dayWindow->setSearchWFlag(flag);
    EXPECT_EQ(flag, m_dayWindow->m_searchFlag);
}

//slotChangeSelectDate
TEST_F(ut_dayWindow, slotChangeSelectDate)
{
    QDate currentDate = QDate::currentDate();

    m_dayWindow->slotChangeSelectDate(currentDate);
    EXPECT_EQ(m_dayWindow->getSelectDate(), currentDate);
}

//slotSwitchPrePage
TEST_F(ut_dayWindow, slotSwitchPrePage)
{
    QDate selectDate = m_dayWindow->getSelectDate();
    m_dayWindow->slotSwitchPrePage();
    EXPECT_EQ(selectDate.addDays(-1), m_dayWindow->getSelectDate());
}

//slotSwitchNextPage
TEST_F(ut_dayWindow, slotSwitchNextPage)
{
    QDate selectDate = m_dayWindow->getSelectDate();
    m_dayWindow->slotSwitchNextPage();
    EXPECT_EQ(selectDate.addDays(1), m_dayWindow->getSelectDate());
}
