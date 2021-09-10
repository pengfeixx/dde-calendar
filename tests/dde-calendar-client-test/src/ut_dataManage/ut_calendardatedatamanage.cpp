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
#include "ut_calendardatedatamanage.h"

#include <QDebug>

ut_calendardatedatamanage::ut_calendardatedatamanage()
{
}

void ut_calendardatedatamanage::SetUp()
{
    calendarDateDataManager = new CalendarDateDataManager();
}

void ut_calendardatedatamanage::TearDown()
{
    delete calendarDateDataManager;
    calendarDateDataManager = nullptr;
}

/**
 *本类是为获取当前日期的类,所拿到的数据会根据当前时间不断变化,因此暂时不做返回值判断
 */

//void CalendarDateDataManager::setSelectDate(const QDate &selectDate, const bool isSwitchYear)
TEST_F(ut_calendardatedatamanage, setSelectDate)
{
    QDate selectDate = QDate::currentDate().addYears(1);
    bool isSwitchYear = true;
    calendarDateDataManager->setSelectDate(selectDate, isSwitchYear);
    EXPECT_EQ(selectDate, calendarDateDataManager->m_selectDate);
}

//QDate CalendarDateDataManager::getSelectDate() const
TEST_F(ut_calendardatedatamanage, getSelectDate)
{
    QDate selectDate = QDate::currentDate().addYears(1);
    bool isSwitchYear = true;
    calendarDateDataManager->setSelectDate(selectDate, isSwitchYear);
    EXPECT_EQ(selectDate, calendarDateDataManager->getSelectDate());
}

//void CalendarDateDataManager::setCurrentDateTime(const QDateTime &currentDateTime)
TEST_F(ut_calendardatedatamanage, setCurrentDateTime)
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    calendarDateDataManager->setCurrentDateTime(currentDateTime);
    EXPECT_EQ(currentDateTime, calendarDateDataManager->m_currentDateTime);
}

//QDateTime CalendarDateDataManager::getCurrentDate() const
TEST_F(ut_calendardatedatamanage, getCurrentDate)
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    calendarDateDataManager->setCurrentDateTime(currentDateTime);
    currentDateTime = calendarDateDataManager->getCurrentDate();
    EXPECT_EQ(currentDateTime, calendarDateDataManager->getCurrentDate());
}

//QMap<int, QVector<QDate> > CalendarDateDataManager::getYearDate()
TEST_F(ut_calendardatedatamanage, getYearDate)
{
    QMap<int, QVector<QDate>> dateTime = calendarDateDataManager->getYearDate();
    EXPECT_EQ(dateTime.size(), 12);
}

TEST_F(ut_calendardatedatamanage, getMonthDate)
{
    int year = 2021;
    int month = 2;
    QVector<QDate> monthDate = calendarDateDataManager->getMonthDate(year, month);
    EXPECT_EQ(42, monthDate.size());
}

//QVector<QDate> CalendarDateDataManager::getWeekDate(const QDate &date)
TEST_F(ut_calendardatedatamanage, getWeekDate)
{
    QDate date = QDate::currentDate();
    QVector<QDate> dateV = calendarDateDataManager->getWeekDate(date);
    EXPECT_EQ(7, dateV.size());
}

//void CalendarDateDataManager::setWeekFirstDay(const Qt::DayOfWeek &firstDay)
TEST_F(ut_calendardatedatamanage, setWeekFirstDay)
{
    Qt::DayOfWeek firstDay(Qt::Sunday);
    calendarDateDataManager->setWeekFirstDay(firstDay);
    EXPECT_EQ(firstDay, calendarDateDataManager->m_weekFirstDay);
}

// Qt::DayOfWeek CalendarDateDataManager::getWeekFirstDay()
TEST_F(ut_calendardatedatamanage, getWeekFirstDay)
{
    Qt::DayOfWeek firstDay(Qt::Sunday);

    Qt::DayOfWeek getfirstDay;
    getfirstDay = calendarDateDataManager->getWeekFirstDay();
    //qInfo() << getfirstDay;
    EXPECT_EQ(firstDay, getfirstDay);
}

//void CalendarDateDataManager::setWeekDayFormatByID(const int &weekDayFormatID)
TEST_F(ut_calendardatedatamanage, setWeekDayFormatByID_001)
{
    int setWeekDayFormatByID = 0;
    calendarDateDataManager->setWeekDayFormatByID(setWeekDayFormatByID);
    EXPECT_EQ("dddd", calendarDateDataManager->m_weekDayFormat);
}

TEST_F(ut_calendardatedatamanage, setWeekDayFormatByID_002)
{
    int setWeekDayFormatByID = 1;
    calendarDateDataManager->setWeekDayFormatByID(setWeekDayFormatByID);
    EXPECT_EQ("ddd", calendarDateDataManager->m_weekDayFormat);
}

//QString CalendarDateDataManager::getWeekDayFormat() const
TEST_F(ut_calendardatedatamanage, getWeekDayFormat)
{
    int setWeekDayFormatByID = 1;
    calendarDateDataManager->setWeekDayFormatByID(setWeekDayFormatByID);
    EXPECT_EQ("ddd", calendarDateDataManager->getWeekDayFormat());
}

//ShowDateRange CalendarDateDataManager::getShowDateRange() const
TEST_F(ut_calendardatedatamanage, getShowDateRange)
{
    ShowDateRange showDateR;
    showDateR = calendarDateDataManager->getShowDateRange();
    QDate currentDate = QDate::currentDate();
    EXPECT_GT(showDateR.stopDate, currentDate);
}

//int CalendarDateDataManager::getWeekNumOfYear(const QDate &date)
TEST_F(ut_calendardatedatamanage, getWeekNumOfYear)
{
    QDate currentDate = QDate::currentDate();
    int weekNum = calendarDateDataManager->getWeekNumOfYear(currentDate);
    EXPECT_GT(weekNum, 0);
}

TEST_F(ut_calendardatedatamanage, setDateFormatChanged_001)
{
    calendarDateDataManager->setDateFormatChanged(0);
    EXPECT_EQ("yyyy/M/d", calendarDateDataManager->m_dateFormat);
}

TEST_F(ut_calendardatedatamanage, setDateFormatChanged_002)
{
    calendarDateDataManager->setDateFormatChanged(1);
    EXPECT_EQ("yyyy-M-d", calendarDateDataManager->m_dateFormat);
}

TEST_F(ut_calendardatedatamanage, setDateFormatChanged_003)
{
    calendarDateDataManager->setDateFormatChanged(2);
    EXPECT_EQ("yyyy.M.d", calendarDateDataManager->m_dateFormat);
}

TEST_F(ut_calendardatedatamanage, setDateFormatChanged_004)
{
    calendarDateDataManager->setDateFormatChanged(3);
    EXPECT_EQ("yyyy/MM/dd", calendarDateDataManager->m_dateFormat);
}

TEST_F(ut_calendardatedatamanage, setDateFormatChanged_005)
{
    calendarDateDataManager->setDateFormatChanged(4);
    EXPECT_EQ("yyyy-MM-dd", calendarDateDataManager->m_dateFormat);
}

TEST_F(ut_calendardatedatamanage, setDateFormatChanged_006)
{
    calendarDateDataManager->setDateFormatChanged(5);
    EXPECT_EQ("yyyy.MM.dd", calendarDateDataManager->m_dateFormat);
}

TEST_F(ut_calendardatedatamanage, setDateFormatChanged_007)
{
    calendarDateDataManager->setDateFormatChanged(6);
    EXPECT_EQ("yy/M/d", calendarDateDataManager->m_dateFormat);
}

TEST_F(ut_calendardatedatamanage, setDateFormatChanged_008)
{
    calendarDateDataManager->setDateFormatChanged(7);
    EXPECT_EQ("yy-M-d", calendarDateDataManager->m_dateFormat);
}

TEST_F(ut_calendardatedatamanage, setDateFormatChanged_009)
{
    calendarDateDataManager->setDateFormatChanged(8);
    EXPECT_EQ("yy.M.d", calendarDateDataManager->m_dateFormat);
}

TEST_F(ut_calendardatedatamanage, setDateFormatChanged_010)
{
    calendarDateDataManager->setDateFormatChanged(9);
    EXPECT_EQ("yyyy-MM-dd", calendarDateDataManager->m_dateFormat);
}

//setTimeFormatChanged
TEST_F(ut_calendardatedatamanage, setTimeFormatChanged_001)
{
    calendarDateDataManager->setTimeFormatChanged(0);
    EXPECT_EQ(0, calendarDateDataManager->m_timeFormatValue);
    EXPECT_EQ("h:mm", calendarDateDataManager->m_timeFormat);
}

TEST_F(ut_calendardatedatamanage, setTimeFormatChanged)
{
    calendarDateDataManager->setTimeFormatChanged(1);
    EXPECT_EQ(1, calendarDateDataManager->m_timeFormatValue);
    EXPECT_EQ("hh:mm", calendarDateDataManager->m_timeFormat);
}
