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
#include "ut_scheduleitem.h"

#include "../third-party_stub/stub.h"

#include <DFontSizeManager>

#include <QPainter>

ut_scheduleitem::ut_scheduleitem()
{
}

void ut_scheduleitem::SetUp()
{
    QRectF rectf(0, 0, 200, 50);
    mScheduleItem = new CScheduleItem(rectf);
}

void ut_scheduleitem::TearDown()
{
    delete mScheduleItem;
    mScheduleItem = nullptr;
}

QVector<ScheduleDataInfo> getScheduleItemDInfo()
{
    QVector<ScheduleDataInfo> scheduleDate {};
    ScheduleDataInfo schedule1, schedule2, schedule3, schedule4, schedule5, scheduleFes;
    QDateTime currentDateTime = QDateTime::currentDateTime();

    schedule1.setID(1);
    schedule1.setBeginDateTime(currentDateTime);
    schedule1.setEndDateTime(currentDateTime.addDays(1));
    schedule1.setTitleName("scheduleOne");
    schedule1.setAllDay(true);
    schedule1.setType(1);
    schedule1.setRecurID(0);

    schedule2.setID(2);
    schedule2.setBeginDateTime(currentDateTime.addDays(1));
    schedule2.setEndDateTime(currentDateTime.addDays(1).addSecs(60 * 60));
    schedule2.setTitleName("scheduleTwo");
    schedule2.setAllDay(true);
    schedule2.setType(2);
    schedule2.setRecurID(0);

    schedule3.setID(3);
    schedule3.setBeginDateTime(currentDateTime.addDays(2));
    schedule3.setEndDateTime(currentDateTime.addDays(2).addSecs(60 * 60));
    schedule3.setTitleName("scheduleThree");
    schedule3.setAllDay(false);
    schedule3.setType(3);
    schedule3.setRecurID(0);

    schedule4.setID(4);
    schedule4.setBeginDateTime(currentDateTime.addDays(3));
    schedule4.setEndDateTime(currentDateTime.addDays(3).addSecs(60 * 60));
    schedule4.setTitleName("scheduleFour");
    schedule4.setAllDay(false);
    schedule4.setType(1);
    schedule4.setRecurID(0);

    schedule5.setID(5);
    schedule5.setBeginDateTime(currentDateTime.addDays(4));
    schedule5.setEndDateTime(currentDateTime.addDays(4).addSecs(60 * 60));
    schedule5.setTitleName("scheduleFive");
    schedule5.setAllDay(false);
    schedule5.setType(2);
    schedule5.setRecurID(0);

    scheduleFes.setID(6);
    scheduleFes.setBeginDateTime(currentDateTime.addDays(5));
    scheduleFes.setEndDateTime(currentDateTime.addDays(5).addSecs(60 * 60));
    scheduleFes.setTitleName("scheduleFestival");
    scheduleFes.setAllDay(true);
    scheduleFes.setType(4);
    scheduleFes.setRecurID(0);

    scheduleDate.append(schedule1);
    scheduleDate.append(schedule2);
    scheduleDate.append(schedule3);
    scheduleDate.append(schedule4);
    scheduleDate.append(schedule5);
    scheduleDate.append(scheduleFes);
    return scheduleDate;
}

//void CScheduleItem::setData(const ScheduleDataInfo &info, QDate date, int totalNum)
TEST_F(ut_scheduleitem, setData)
{
    ScheduleDataInfo scheduleinfo = getScheduleItemDInfo().first();
    int totalNum = 4;
    QDate date = QDate::currentDate();
    mScheduleItem->setData(scheduleinfo, date, totalNum);
    EXPECT_EQ(mScheduleItem->m_vScheduleInfo, scheduleinfo);
    EXPECT_EQ(totalNum, mScheduleItem->m_totalNum);
}

//bool CScheduleItem::hasSelectSchedule(const ScheduleDataInfo &info)
TEST_F(ut_scheduleitem, hasSelectSchedule)
{
    ScheduleDataInfo scheduleinfo1 = getScheduleItemDInfo().first();
    ScheduleDataInfo scheduleinfo2 = getScheduleItemDInfo().at(1);
    mScheduleItem->setData(scheduleinfo1, QDate::currentDate(), 4);
    bool res = mScheduleItem->hasSelectSchedule(scheduleinfo1);
    EXPECT_TRUE(res);
    res = mScheduleItem->hasSelectSchedule(scheduleinfo2);
    EXPECT_FALSE(res);
}

//void CScheduleItem::splitText(QFont font, int w, int h, QString str, QStringList &liststr, QFontMetrics &fontm)
TEST_F(ut_scheduleitem, splitText_001)
{
    QFont font = DFontSizeManager::instance()->get(DFontSizeManager::T7, QFont::Medium);
    QString str = "Test length statement";
    QStringList strlist;
    QFontMetrics fontmetrics(font);
    int width = 20; //item显示内容宽度
    int height = 50; //item显示内容高度
    mScheduleItem->splitText(font, width, height, str, strlist, fontmetrics);
    ASSERT_GT(strlist.size(), 0);
    EXPECT_LT(strlist.at(0).size(), str.size());
}

TEST_F(ut_scheduleitem, splitText_002)
{
    QFont font = DFontSizeManager::instance()->get(DFontSizeManager::T7, QFont::Medium);
    QString str = "Test length statement";
    QStringList strlist;
    QFontMetrics fontmetrics(font);
    int width = 600; //item显示内容宽度
    int height = 100; //item显示内容高度
    mScheduleItem->splitText(font, width, height, str, strlist, fontmetrics);
    ASSERT_GT(strlist.size(), 0);
    EXPECT_EQ(strlist.at(0).size(), str.size());
}

bool getItemFocus_Stub()
{
    return true;
}

//paintBackground
TEST_F(ut_scheduleitem, paintBackground_001)
{
    QRectF rectf(0, 0, 100, 100);
    mScheduleItem->setRect(rectf);
    mScheduleItem->setData(getScheduleItemDInfo().first(), QDate::currentDate(), 4);
    QPixmap pixmap(rectf.toRect().size());
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    mScheduleItem->m_vHighflag = true;
    mScheduleItem->m_vSelectflag = false;
    mScheduleItem->paintBackground(&painter, pixmap.rect(), true);
    EXPECT_EQ(pixmap.size(), rectf.toRect().size());
}

TEST_F(ut_scheduleitem, paintBackground_002)
{
    QRectF rectf(0, 0, 100, 100);
    mScheduleItem->setRect(rectf);
    mScheduleItem->setData(getScheduleItemDInfo().first(), QDate::currentDate(), 4);
    QPixmap pixmap(rectf.toRect().size());
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    mScheduleItem->m_vHighflag = true;

    Stub stub;
    stub.set(ADDR(CFocusItem, getItemFocus), getItemFocus_Stub);
    mScheduleItem->m_vSelectflag = true;
    mScheduleItem->paintBackground(&painter, pixmap.rect(), true);
    EXPECT_EQ(pixmap.size(), rectf.toRect().size());
}
