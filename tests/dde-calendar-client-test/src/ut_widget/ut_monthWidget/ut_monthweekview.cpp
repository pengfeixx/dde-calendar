/*
* Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
*
* Author:     zhengxiaokang <zhengxiaokang@uniontech.com>
*
* Maintainer: zhengxiaokang <zhengxiaokang@uniontech.com>
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
#include "ut_monthweekview.h"
#include <QDate>

ut_monthweekview::ut_monthweekview()
{
}

void ut_monthweekview::SetUp()
{
    mMonthWeekView = new CMonthWeekView();
    mWeekRect = new WeekRect();
}

void ut_monthweekview::TearDown()
{
    delete mMonthWeekView;
    mMonthWeekView = nullptr;
    delete mWeekRect;
    mWeekRect = nullptr;
}

//void CMonthWeekView::setFirstDay(const Qt::DayOfWeek weekday)
TEST_F(ut_monthweekview, setFirstDay)
{
    Qt::DayOfWeek week = Qt::DayOfWeek::Friday;
    mMonthWeekView->setFirstDay(week);
    EXPECT_EQ(week, mMonthWeekView->m_firstWeek);
}

//void CMonthWeekView::setTheMe(int type)
TEST_F(ut_monthweekview, setTheMe_001)
{
    int type = 1;
    QColor color("#75C18E");
    color.setAlphaF(0.1);
    mMonthWeekView->setTheMe(type);
    EXPECT_EQ(color, mMonthWeekView->m_backgroundColor);
}

TEST_F(ut_monthweekview, setTheMe_002)
{
    int type = 2;
    QColor color("#82AEC1");
    color.setAlphaF(0.1);
    mMonthWeekView->setTheMe(type);
    EXPECT_EQ(color, mMonthWeekView->m_backgroundColor);
}

//void CMonthWeekView::setCurrentDate(const QDate &currentDate)
TEST_F(ut_monthweekview, setCurrentDate)
{
    QDate currentDate = QDate::currentDate();
    mMonthWeekView->setCurrentDate(currentDate);
    Qt::DayOfWeek week = static_cast<Qt::DayOfWeek>(currentDate.dayOfWeek());
    EXPECT_EQ(week, mMonthWeekView->m_currentWeek);
}

//void WeekRect::setWeek(const Qt::DayOfWeek &showWeek, const bool &showLine)
TEST_F(ut_monthweekview, setWeek)
{
    Qt::DayOfWeek showWeek = Qt::Sunday;
    bool showLine = true;
    mWeekRect->setWeek(showWeek, showLine);
    EXPECT_EQ(showLine, mWeekRect->m_showLine);
    EXPECT_EQ(mWeekRect->m_showWeek, showWeek);
}

//void WeekRect::setRect(const QRectF &rectF)
TEST_F(ut_monthweekview, setRect)
{
    QRectF rect(215, 51, 695, 95);
    mWeekRect->setRect(rect);
    EXPECT_EQ(rect, mWeekRect->m_rectF);
}

//void WeekRect::setTheMe(int type)
TEST_F(ut_monthweekview, setRectTheMe_001)
{
    int type = 1;
    QColor testColor("#6F6F6F");
    mWeekRect->setTheMe(type);
    EXPECT_EQ(testColor, mWeekRect->m_testColor);
}

TEST_F(ut_monthweekview, setRectTheMe_002)
{
    int type = 2;
    QColor testColor("#C0C6D4");
    mWeekRect->setTheMe(type);
    EXPECT_EQ(testColor, mWeekRect->m_testColor);
}
