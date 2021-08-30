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
#include "ut_calendarhuangli.h"
#include "../third-party_stub/stub.h"
#include "config.h"
#include <QSqlDatabase>
#include <QDebug>

bool stub_OpenHuangliDB(void *obj, const QString &dbpath)
{
    Q_UNUSED(dbpath);
    HuangLiDataBase *o = reinterpret_cast<HuangLiDataBase *>(obj);
    QString name;
    {
        name = QSqlDatabase::database().connectionName();
    }
    o->m_database.removeDatabase(name);
    o->m_database = QSqlDatabase::addDatabase("QSQLITE");
    o->m_database.setDatabaseName(HL_DATABASE_DIR);
    return o->m_database.open();
}

ut_calendarhuangli::ut_calendarhuangli()
{
}

void ut_calendarhuangli::SetUp()
{
    Stub stub;
    stub.set(ADDR(HuangLiDataBase, OpenHuangliDatabase), stub_OpenHuangliDB);
    calendarHuangLi = new CalendarHuangLi();
}

void ut_calendarhuangli::TearDown()
{
    if (calendarHuangLi->m_database->m_database.isOpen()) {
        calendarHuangLi->m_database->m_database.close();
    }
    delete calendarHuangLi;
    calendarHuangLi = nullptr;
}

//QString CalendarHuangLi::GetFestivalMonth(quint32 year, quint32 month)
TEST_F(ut_calendarhuangli, GetFestivalMonth)
{
    QDate currentDate(2021, 1, 1);
    QString fesMonth;
    fesMonth = calendarHuangLi->GetFestivalMonth(currentDate.year(), currentDate.month());
    EXPECT_NE(fesMonth, "");
}

//QString CalendarHuangLi::GetHuangLiDay(quint32 year, quint32 month, quint32 day)
TEST_F(ut_calendarhuangli, GetHuangLiDay)
{
    QDate currentDate(2021, 1, 1);
    QDate testDate;
    QString fesMonth;
    for (int i = 0; i < 100; ++i) {
        testDate = currentDate.addDays(i);
        fesMonth = calendarHuangLi->GetHuangLiDay(testDate.year(), testDate.month(), testDate.day());
        EXPECT_NE(fesMonth, "");
    }
}

//QString CalendarHuangLi::GetHuangLiMonth(quint32 year, quint32 month, bool fill)
TEST_F(ut_calendarhuangli, GetHuangLiMonth_01)
{
    QDate currentDate(2021, 1, 1);
    QDate testDate;
    QString fesMonth;
    for (int i = 0; i < 100; ++i) {
        testDate = currentDate.addMonths(i);
        fesMonth = calendarHuangLi->GetHuangLiMonth(testDate.year(), testDate.month(), true);
        EXPECT_NE(fesMonth, "");
    }
}

TEST_F(ut_calendarhuangli, GetHuangLiMonth_02)
{
    QDate currentDate(2021, 1, 1);
    QDate testDate;
    QString fesMonth;
    for (int i = 0; i < 100; ++i) {
        testDate = currentDate.addMonths(i);
        fesMonth = calendarHuangLi->GetHuangLiMonth(testDate.year(), testDate.month(), false);
        EXPECT_NE(fesMonth, "");
    }
}

//CaLunarDayInfo CalendarHuangLi::GetLunarInfoBySolar(quint32 year, quint32 month, quint32 day)
TEST_F(ut_calendarhuangli, GetLunarInfoBySolar)
{
    CaLunarDayInfo huangliDayInfo;

    QDate currentDate = QDate::currentDate();
    QDate testDate;
    QString fesMonth;
    for (int i = 0; i < 100; ++i) {
        testDate = currentDate.addDays(i);
        huangliDayInfo = calendarHuangLi->GetLunarInfoBySolar(testDate.year(), testDate.month(), testDate.day());
        EXPECT_NE(huangliDayInfo.mGanZhiDay, "");
    }
}

//CaLunarMonthInfo CalendarHuangLi::GetLunarCalendarMonth(quint32 year, quint32 month, bool fill)
TEST_F(ut_calendarhuangli, GetLunarCalendarMonth_01)
{
    quint32 year = 2020;
    quint32 month = 12;
    bool fill = false;
    CaLunarMonthInfo monthInfo = calendarHuangLi->GetLunarCalendarMonth(year, month, fill);
    EXPECT_NE(monthInfo.mCaLunarDayInfo.size(), 0);
}

TEST_F(ut_calendarhuangli, GetLunarCalendarMonth_02)
{
    quint32 year = 2020;
    quint32 month = 12;
    bool fill = true;
    CaLunarMonthInfo monthInfo = calendarHuangLi->GetLunarCalendarMonth(year, month, fill);
    EXPECT_NE(monthInfo.mCaLunarDayInfo.size(), 0);
}
