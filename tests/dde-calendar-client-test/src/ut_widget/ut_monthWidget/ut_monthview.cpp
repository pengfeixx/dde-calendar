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
#include "ut_monthview.h"
#include "view/graphicsItem/draginfoitem.h"
#include "../third-party_stub/stub.h"

ut_monthview::ut_monthview()
{
}

void ut_monthview::SetUp()
{
    mMonthView = new CMonthView();
}

void ut_monthview::TearDown()
{
    delete mMonthView;
    mMonthView = nullptr;
}

QVector<ScheduleDataInfo> getMonthViewScheduleDInfo()
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

QVector<QDate> MonthviewGetDayList()
{
    QVector<QDate> dateList {};
    QDate currentDate = QDate::currentDate();
    for (int i = 0; i < 42; i++) {
        dateList.append(currentDate.addDays(i));
    }

    return dateList;
}

QMap<QDate, CaHuangLiDayInfo> MonthViewGetHuangLiDayInfo()
{
    QMap<QDate, CaHuangLiDayInfo> huangLiDayinfo {};
    CaHuangLiDayInfo huangLiInfo1 {};
    huangLiInfo1.mGanZhiYear = "辛丑牛年"; //年干支
    huangLiInfo1.mGanZhiMonth = "庚寅月"; //月干支
    huangLiInfo1.mGanZhiDay = "辛卯日"; //日干支
    huangLiInfo1.mLunarMonthName = "正月"; //农历月名称
    huangLiInfo1.mLunarDayName = "初一"; //农历日名称
    huangLiInfo1.mLunarLeapMonth = 4; //闰月
    huangLiInfo1.mZodiac = "牛"; //生肖
    huangLiInfo1.mTerm = ""; //农历节气
    huangLiInfo1.mSolarFestival = "国庆节"; //阳历节日
    huangLiInfo1.mLunarFestival = "除夕"; //农历节日
    huangLiInfo1.mSuit = "嫁娶"; //黄历宜
    huangLiInfo1.mAvoid = "入土"; //黄历忌

    huangLiDayinfo.insert(QDate::currentDate(), huangLiInfo1);
    return huangLiDayinfo;
}

//void CMonthView::setTheMe(int type)
TEST_F(ut_monthview, setTheMe)
{
    mMonthView->setTheMe(1);
    mMonthView->setTheMe(2);
}

bool setSearch = false;
void setSelectSearchSchedule_stub(void *obj, const ScheduleDataInfo &scheduleInfo)
{
    Q_UNUSED(obj)
    Q_UNUSED(scheduleInfo)
    setSearch = true;
}

//void CMonthView::setSelectSchedule(const ScheduleDataInfo &scheduleInfo)
TEST_F(ut_monthview, setSelectSchedule)
{
    typedef void (*StubSetSearch)(CMonthGraphicsview *, const ScheduleDataInfo &);
    StubSetSearch setseardch = (StubSetSearch)((void (CMonthGraphicsview::*)(const ScheduleDataInfo &))(&CMonthGraphicsview::setSelectSearchSchedule));
    ScheduleDataInfo scheduleinfo = getMonthViewScheduleDInfo().first();
    Stub stub;
    stub.set(setseardch, setSelectSearchSchedule_stub);
    mMonthView->setSelectSchedule(scheduleinfo);
    EXPECT_TRUE(setSearch);
}

//void CMonthView::slotScheduleRemindWidget(const bool isShow, const ScheduleDataInfo &out)
TEST_F(ut_monthview, slotScheduleRemindWidget_001)
{
    ScheduleDataInfo scheduleinfo = getMonthViewScheduleDInfo().first();
    mMonthView->slotScheduleRemindWidget(true, scheduleinfo);
    EXPECT_EQ(mMonthView->m_remindWidget->m_ScheduleInfo, scheduleinfo);
}

TEST_F(ut_monthview, slotScheduleRemindWidget_002)
{
    ScheduleDataInfo scheduleinfo = getMonthViewScheduleDInfo().first();
    mMonthView->slotScheduleRemindWidget(false, scheduleinfo);
    EXPECT_FALSE(mMonthView->m_remindWidget->m_ScheduleInfo.isValid());
}

//void CMonthView::setFirstWeekday(Qt::DayOfWeek weekday)
TEST_F(ut_monthview, setFirstWeekday)
{
    Qt::DayOfWeek weekday = Qt::Sunday;
    mMonthView->setFirstWeekday(weekday);
    EXPECT_EQ(weekday, mMonthView->m_firstWeekDay);
}

//void CMonthView::setShowDate(const QVector<QDate> &showDate)
TEST_F(ut_monthview, setShowDate)
{
    QVector<QDate> showDate = MonthviewGetDayList();
    mMonthView->setShowDate(showDate);
    EXPECT_EQ(mMonthView->m_showDate, showDate);
}

bool lunarUpdate = false;
void setLunarInfo_Stub(const QMap<QDate, CaHuangLiDayInfo> &lunarCache)
{
    Q_UNUSED(lunarCache);
    lunarUpdate = true;
}
//void CMonthView::setHuangLiInfo(const QMap<QDate, CaHuangLiDayInfo> &huangLiInfo)
TEST_F(ut_monthview, setHuangLiInfo)
{
    Stub stub;
    stub.set(ADDR(CMonthGraphicsview, setLunarInfo), setLunarInfo_Stub);
    mMonthView->setHuangLiInfo(MonthViewGetHuangLiDayInfo());
    EXPECT_TRUE(lunarUpdate);
}

bool festivalupDate = false;
void setFestival_Stub(const QMap<QDate, int> &festivalInfo)
{
    Q_UNUSED(festivalInfo)
    festivalupDate = true;
}
//void CMonthView::setFestival(const QMap<QDate, int> &festivalInfo)
TEST_F(ut_monthview, setFestival)
{
    QMap<QDate, int> festivalInfo {};
    festivalInfo.insert(QDate::currentDate(), 1);
    festivalInfo.insert(QDate::currentDate().addDays(1), 2);
    Stub stub;
    stub.set(ADDR(CMonthGraphicsview, setFestival), setFestival_Stub);
    mMonthView->setFestival(festivalInfo);
    EXPECT_TRUE(festivalupDate);
}

//void CMonthView::setScheduleInfo(const QMap<QDate, QVector<ScheduleDataInfo> > &scheduleInfo)
TEST_F(ut_monthview, setScheduleInfo)
{
    QMap<QDate, QVector<ScheduleDataInfo>> scheduleinfo {};
    scheduleinfo.insert(QDate::currentDate(), getMonthViewScheduleDInfo());
    mMonthView->setScheduleInfo(scheduleinfo);
    EXPECT_EQ(scheduleinfo, mMonthView->m_monthGraphicsView->m_schedulelistdata);
}

//void CMonthView::setSearchScheduleInfo(const QVector<ScheduleDataInfo> &searchScheduleInfo)
TEST_F(ut_monthview, setSearchScheduleInfo)
{
    QVector<ScheduleDataInfo> info = getMonthViewScheduleDInfo();
    mMonthView->setSearchScheduleInfo(info);
    EXPECT_EQ(DragInfoItem::m_searchScheduleInfo, info);
}

//void CMonthView::setCurrentDate(const QDate &currentDate)
TEST_F(ut_monthview, setCurrentDate)
{
    QDate currentDate = QDate::currentDate();
    mMonthView->setCurrentDate(currentDate);
    EXPECT_EQ(currentDate, mMonthView->m_monthGraphicsView->getCurrentDate());
}

//ScheduleDataInfo CMonthView::getScheduleInfo(const QDate &beginDate, const QDate &endDate)
TEST_F(ut_monthview, getScheduleInfo_001)
{
    QDate currentDate = QDate::currentDate();
    QDate endDate = currentDate.addDays(5);
    ScheduleDataInfo info = mMonthView->getScheduleInfo(currentDate, endDate);
    EXPECT_EQ(info.getBeginDateTime().date(), currentDate);
    EXPECT_EQ(info.getEndDateTime().date(), endDate);
}

TEST_F(ut_monthview, getScheduleInfo_002)
{
    QDate currentDate = QDate::currentDate();
    QDate endDate = currentDate.addDays(5);
    ScheduleDataInfo info = mMonthView->getScheduleInfo(endDate, currentDate);
    EXPECT_EQ(info.getBeginDateTime().date(), currentDate);
    EXPECT_EQ(info.getEndDateTime().date(), endDate);
}
