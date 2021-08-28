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
    QDate selectDate(2020, 12, 25);
    bool isSwitchYear = true;
    calendarDateDataManager->setSelectDate(selectDate, isSwitchYear);

    isSwitchYear = false;
    calendarDateDataManager->setSelectDate(selectDate, isSwitchYear);
}

//QDate CalendarDateDataManager::getSelectDate() const
TEST_F(ut_calendardatedatamanage, getSelectDate)
{
    QDate selectDate;
    selectDate = calendarDateDataManager->getSelectDate();
    //qInfo() << selectDate;
}

//void CalendarDateDataManager::setCurrentDateTime(const QDateTime &currentDateTime)
TEST_F(ut_calendardatedatamanage, setCurrentDateTime)
{
    QDate date(2020, 12, 25);
    QDateTime currentDateTime(date);
    calendarDateDataManager->setCurrentDateTime(currentDateTime);
}

//QDateTime CalendarDateDataManager::getCurrentDate() const
TEST_F(ut_calendardatedatamanage, getCurrentDate)
{
    QDateTime currentDateTime;
    currentDateTime = calendarDateDataManager->getCurrentDate();
}

//QMap<int, QVector<QDate> > CalendarDateDataManager::getYearDate()
TEST_F(ut_calendardatedatamanage, getYearDate)
{
    QMap<int, QVector<QDate> > dateTime;
    dateTime = calendarDateDataManager->getYearDate();
}

//QVector<QDate> CalendarDateDataManager::getWeekDate(const QDate &date)
TEST_F(ut_calendardatedatamanage, getWeekDate)
{
    QDate selectDate(2020, 12, 25);
    QVector<QDate> dateV = calendarDateDataManager->getWeekDate(selectDate);
}

//void CalendarDateDataManager::setWeekFirstDay(const Qt::DayOfWeek &firstDay)
TEST_F(ut_calendardatedatamanage, setWeekFirstDay)
{
    Qt::DayOfWeek firstDay(Qt::Sunday);
    calendarDateDataManager->setWeekFirstDay(firstDay);
}

// Qt::DayOfWeek CalendarDateDataManager::getWeekFirstDay()
TEST_F(ut_calendardatedatamanage, getWeekFirstDay)
{
    Qt::DayOfWeek firstDay(Qt::Sunday);

    Qt::DayOfWeek getfirstDay;
    getfirstDay = calendarDateDataManager->getWeekFirstDay();
    //qInfo() << getfirstDay;
    assert(firstDay == getfirstDay);
}

//void CalendarDateDataManager::setWeekDayFormatByID(const int &weekDayFormatID)
TEST_F(ut_calendardatedatamanage, setWeekDayFormatByID)
{
    int setWeekDayFormatByID = 0;
    calendarDateDataManager->setWeekDayFormatByID(setWeekDayFormatByID);

    setWeekDayFormatByID = 1;
    calendarDateDataManager->setWeekDayFormatByID(setWeekDayFormatByID);
}

//QString CalendarDateDataManager::getWeekDayFormat() const
TEST_F(ut_calendardatedatamanage, getWeekDayFormat)
{
    QString getWEKfomat;
    calendarDateDataManager->getWeekDayFormat();
}

//ShowDateRange CalendarDateDataManager::getShowDateRange() const
TEST_F(ut_calendardatedatamanage, getShowDateRange)
{
    ShowDateRange showDateR;
    showDateR = calendarDateDataManager->getShowDateRange();
}

//int CalendarDateDataManager::getWeekNumOfYear(const QDate &date)
TEST_F(ut_calendardatedatamanage, getWeekNumOfYear)
{
    //2020-12-25 为第52周
    const int weeknum = 52;
    QDate date(2020, 12, 25);
    int weekNum = 0;
    weekNum = calendarDateDataManager->getWeekNumOfYear(date);
    assert(weeknum == weekNum);
}

TEST_F(ut_calendardatedatamanage, setDateFormatChanged)
{
    for (int i = 0; i < 10; ++i) {
        calendarDateDataManager->setDateFormatChanged(i);
    }
}

//setTimeFormatChanged
TEST_F(ut_calendardatedatamanage, setTimeFormatChanged)
{
    calendarDateDataManager->setTimeFormatChanged(0);
    calendarDateDataManager->setTimeFormatChanged(1);
}
