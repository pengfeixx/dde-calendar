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
#include "ut_method_interface.h"

#include <QVector>
#include <QDebug>
#include <QtGlobal>


//QString GetLunarMonthName(int lunarmonthname, bool isleap)
TEST(ut_method_interface, GetLunarMonthName)
{
    QString lunarName;
    QString lunarMonthNamesStr;
    for (int i = 1; i < 13; ++i) {
        lunarName = GetLunarMonthName(i, false);
        lunarMonthNamesStr = lunarMonthNames[i - 1] + "月";
        EXPECT_EQ(lunarName, lunarMonthNamesStr);

        lunarName = GetLunarMonthName(i, true);
        lunarMonthNamesStr = "闰" + lunarMonthNames[i - 1] + "月";
        EXPECT_EQ(lunarName, lunarMonthNamesStr);
    }
}

//QString GetLunarDayName(int lundayname)
TEST(ut_method_interface, GetLunarDayName)
{
    QString lunarDayName;
    for (int i = 1; i < 31; ++i) {
        lunarDayName = GetLunarDayName(i);
        EXPECT_EQ(lunarDayName, lunarDayNames[i - 1]);
    }
}

//QString GetLunarDayFestival(int monthname, int lunarday, int lunarmonthdays, int solarterm)
TEST(ut_method_interface, GetLunarDayFestival)
{
    QVector<int> monthV = {1, 1, 5, 7, 8, 9, 12, 12, 12, 12, 4, 4};
    QVector<int> dayV = {1, 15, 5, 7, 15, 9, 8, 29, 29, 30, 2, 3};
    int lunarmonthdays = 30;
    QVector<int> solartermV = {1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1};

    QVector<QString> strV = {"春节", "元宵节", "端午节", "七夕节", "中秋节", "重阳节", "腊八节", "", "清明节", "除夕", "", "清明节"};
    QString dayFestival;
    for (int i = 0; i < strV.size(); ++i) {
        dayFestival = GetLunarDayFestival(monthV.at(i), dayV.at(i), lunarmonthdays, solartermV.at(i));
        EXPECT_EQ(dayFestival, strV.at(i)) << "dayFestival:" << dayFestival.toStdString() << " strV:" << strV.at(i).toStdString() << i;
    }
}

//QString GetSolarTermName(int order)
TEST(ut_method_interface, GetSolarTermName)
{
    for (int i = 0; i < SolarTermNames.size(); ++i) {
        EXPECT_EQ(SolarTermNames.at(i), GetSolarTermName(i));
    }
    EXPECT_EQ(GetSolarTermName(SolarTermNames.size()), "");
}

//QString GetGanZhiMonth(int year, int monthzhi)
TEST(ut_method_interface, GetGanZhiMonth)
{
    QString ganzhi;
    int num;
    for (int year = 1900; year < 2150; ++year) {
        for (int month = 1; month < 13; ++month) {
            num = (year - 1900) * 12 + month + 12;
            ganzhi = TianGan[num % 10] + DiZhi[num % 12];
            EXPECT_EQ(ganzhi, GetGanZhiMonth(year, month)) << "ganzhi:" << ganzhi.toStdString() << "getGanZhi:" << GetGanZhiMonth(year, month).toStdString();
        }
    }
}

//QString GetGanZhiYear(int lunaryear)
TEST(ut_method_interface, GetGanZhiYear)
{
    QString ganzhi;
    int num;
    for (int year = 1900; year < 2150; ++year) {
        num = year - 1864;
        ganzhi = TianGan[num % 10] + DiZhi[num % 12];
        EXPECT_EQ(ganzhi, GetGanZhiYear(year)) << "ganzhi:" << ganzhi.toStdString() << "getGanZhi:" << GetGanZhiYear(year).toStdString();
    }
}

//QString GetGanZhiDay(int year, int month, int day)
TEST(ut_method_interface, GetGanZhiDay)
{
    int dayCyclical;
    QDate currentDate = QDate::currentDate();
    QDate testDate;
    QString ganzhi;
    for (int i = 0; i < 100; ++i) {
        testDate = currentDate.addDays(i);
        dayCyclical = int(QDateTime(QDate(testDate.year(), testDate.month(), testDate.day()), QTime(0, 0, 0, 0), Qt::TimeSpec::UTC).toMSecsSinceEpoch() / 1000 / 86400) + 29219 + 18;
        ganzhi = TianGan[dayCyclical % 10] + DiZhi[dayCyclical % 12];
        EXPECT_EQ(ganzhi, GetGanZhiDay(testDate.year(), testDate.month(), testDate.day())) << "ganzhi:" << ganzhi.toStdString() << "getGanZhi:" << GetGanZhiDay(testDate.year(), testDate.month(), testDate.day()).toStdString();
    }
}

//QString GetYearZodiac(int lunaryear)
TEST(ut_method_interface, GetYearZodiac)
{
    QString zodiac;
    for (int year = 2000; year < 2100; ++year) {
        zodiac = Animals[(year - 4) % 12];
        EXPECT_EQ(zodiac, GetYearZodiac(year)) << "zodiac:" << zodiac.toStdString() << " GetYearZodiac:" << GetYearZodiac(year).toStdString();
    }
}

//QVector<double> get25SolarTermJDs(int year, int start)
TEST(ut_method_interface, get25SolarTermJDs)
{
    int year = 0;
    int start = 0;
    QVector<double> jds = get25SolarTermJDs(year, start);
    EXPECT_NE(jds.size(), 0);
}

//double GetSolarTermJD(int year, int order)
TEST(ut_method_interface, GetSolarTermJD)
{
    int year = 2020;
    int order = 0; //春分 3月20日
    for (int i = 0; i < 100; ++i) {
        double jd = GetSolarTermJD(year + i, order + i);
        EXPECT_GT(jd, 0);
    }
}

//bool IsLeapYear(int year)
TEST(ut_method_interface, IsLeapYear)
{
    int leapYear = 2020; // 闰年
    int notLeapYear = 2019; // 非闰年
    EXPECT_TRUE(IsLeapYear(leapYear));
    EXPECT_FALSE(IsLeapYear(notLeapYear));
}

// int GetSolarMonthDays(int year, int month)
TEST(ut_method_interface, GetSolarMonthDays)
{
    QDate currentDate = QDate::currentDate();
    QDate testDate;
    for (int i = 0; i < 100; ++i) {
        testDate = currentDate.addMonths(i);
        EXPECT_EQ(testDate.daysInMonth(), GetSolarMonthDays(testDate.year(), testDate.month()));
    }
}

//int GetWeekday(int y, int m, int d)
TEST(ut_method_interface, GetWeekday)
{
    QDate currentDate = QDate::currentDate();
    QDate testDate;
    for (int i = 0; i < 100; ++i) {
        testDate = currentDate.addMonths(i);
        EXPECT_EQ(testDate.dayOfWeek() % 7, GetWeekday(testDate.year(), testDate.month(), testDate.day()));
    }
}

//double DmsToDegrees(int degrees, int mintues, double seconds)
TEST(ut_method_interface, DmsToDegrees)
{
    int degrees = 4;
    int mintues = 3;
    double seconds = 7200;
    double degress = DmsToDegrees(degrees, mintues, seconds);
    EXPECT_GT(degress, 0);
}

//double DmsToSeconds(int d, int m, double s)
TEST(ut_method_interface, DmsToSeconds)
{
    int d = 4;
    int m = 3;
    double s = 7200;
    double degress = DmsToSeconds(d, m, s);
    EXPECT_GT(degress, 0);
}

//double DmsToRadians(int d, int m, int s)
TEST(ut_method_interface, DmsToRadians)
{
    int d = 4;
    int m = 3;
    int s = 7200;
    double degress = DmsToRadians(d, m, s);
    EXPECT_GT(degress, 0);
}

//QDateTime GetDateTimeFromJulianDay(double jd)
TEST(ut_method_interface, GetDateTimeFromJulianDay)
{
    int year = 2020;
    int order = 0; //春分 3月20日
    double jd = GetSolarTermJD(year, order);

    QString strJulianDay = "周五 3月 20 03:49:33 2020 GMT";
    QDateTime julianDay = GetDateTimeFromJulianDay(jd);
    EXPECT_EQ(julianDay.date().year(), year);
}

//double GetDeltaT(int year, int month)
TEST(ut_method_interface, GetDeltaT)
{
    const int count = 15;
    const int year[count] = {-501, 0, 1599, 1699, 1799,
                             1859, 1899, 1919, 1940, 1960,
                             1985, 2004, 2049, 2149, 2150
                            };
    const int mouth = 6;
    for (int i = 0; i < count; ++i) {
        EXPECT_NE(GetDeltaT(year[i], mouth), 0);
    }
}

//double JDBeijingTime2UTC(double bjtJD)
TEST(ut_method_interface, JDBeijingTime2UTC)
{
    double bjtJD = 1.01;
    double utc = JDBeijingTime2UTC(bjtJD);
    EXPECT_GT(bjtJD, utc);
}

//QString GetSolarDayFestival(int year, int month, int day)
TEST(ut_method_interface, GetSolarDayFestival)
{
    int year = 2020;
    // 建军节
    int month = 8;
    int day = 1;
    QString getFesStr = GetSolarDayFestival(year, month, day);
    EXPECT_EQ("建军节", getFesStr);

    // 儿童节
    month = 6;
    day = 1;
    getFesStr = GetSolarDayFestival(year, month, day);
    EXPECT_EQ("儿童节", getFesStr);
}

//double CalcEarthObliquityNutation(double dt)
TEST(ut_method_interface, CalcEarthObliquityNutation)
{
    double julianDay = 1;
    double dt = GetJulianCentury(julianDay);
    EXPECT_NE(CalcEarthObliquityNutation(dt), 0);
}

//double lightAberration()
TEST(ut_method_interface, lightAberration)
{
    EXPECT_GT(lightAberration(), 0);
}
