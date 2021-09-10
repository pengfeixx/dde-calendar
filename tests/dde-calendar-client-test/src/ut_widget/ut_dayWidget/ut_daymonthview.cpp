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
#include "ut_daymonthview.h"

#include "dayWidget/dayhuangliview.h"

ut_daymonthview::ut_daymonthview()
{
}

void ut_daymonthview::SetUp()
{
    mDayMonthView = new CDayMonthView();
    currentDateTime = QDateTime::currentDateTime();
}

void ut_daymonthview::TearDown()
{
    delete mDayMonthView;
    mDayMonthView = nullptr;
}

QVector<QDate> dayMonthviewGetDayList()
{
    QVector<QDate> dateList {};
    QDate currentDate = QDate::currentDate();
    for (int i = 0; i < 42; i++) {
        dateList.append(currentDate.addDays(i));
    }

    return dateList;
}

QMap<QDate, CaHuangLiDayInfo> dayMonthViewGetHuangLiDayInfo()
{
    QMap<QDate, CaHuangLiDayInfo> huangLiDayInfo {};
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

    huangLiDayInfo.insert(QDate::currentDate(), huangLiInfo1);
    return huangLiDayInfo;
}

QVector<bool> dayMonthViewGetLineFlag()
{
    QVector<bool> flags {};
    for (int i = 0; i < 42; i++) {
        flags.append(true);
    }
    return flags;
}

//void CDayMonthView::setShowDate(const QVector<QDate> &showDate, const QDate &selectDate, const QDate &currentDate)
TEST_F(ut_daymonthview, setShowDate)
{
    QDate selectDate = currentDateTime.date().addDays(2);
    mDayMonthView->setShowDate(dayMonthviewGetDayList(), selectDate, currentDateTime.date());
    EXPECT_EQ(mDayMonthView->m_selectDate, selectDate);
    EXPECT_EQ(mDayMonthView->m_currentDate, currentDateTime.date());
}

//void CDayMonthView::setLunarVisible(bool visible)
TEST_F(ut_daymonthview, setLunarVisible)
{
    bool isVisible = false;
    mDayMonthView->setLunarVisible(isVisible);
    EXPECT_EQ(isVisible, mDayMonthView->m_huanglistate);
    EXPECT_EQ(isVisible, mDayMonthView->m_yiLabel->isVisible());
    EXPECT_EQ(isVisible, mDayMonthView->m_jiLabel->isVisible());
    EXPECT_EQ(isVisible, mDayMonthView->m_currentLuna->isVisible());
    EXPECT_EQ(isVisible, mDayMonthView->m_splitline->isVisible());
}

//void CDayMonthView::setTheMe(int type)
TEST_F(ut_daymonthview, setTheMe_001)
{
    int type = 1;
    QColor currentMouthColor("#3B3B3B");
    mDayMonthView->setTheMe(type);
    EXPECT_EQ(currentMouthColor, mDayMonthView->m_currentMouth->m_tnormalColor);
}

TEST_F(ut_daymonthview, setTheMe_002)
{
    int type = 2;
    QColor currentMouthColor("#C0C6D4");
    mDayMonthView->setTheMe(type);
    EXPECT_EQ(currentMouthColor, mDayMonthView->m_currentMouth->m_tnormalColor);
}

//void CDayMonthView::setSearchFlag(bool flag)
TEST_F(ut_daymonthview, setSearchFlag)
{
    bool flag = true;
    mDayMonthView->setSearchFlag(flag);
    EXPECT_EQ(flag, mDayMonthView->m_searchflag);
}

//void CDayMonthView::setHuangLiInfo(const CaHuangLiDayInfo &huangLiInfo)
TEST_F(ut_daymonthview, setHuangLiInfo)
{
    CaHuangLiDayInfo huangliInfo = dayMonthViewGetHuangLiDayInfo().value(currentDateTime.date());
    mDayMonthView->setHuangLiInfo(huangliInfo);
    EXPECT_EQ(huangliInfo.mSuit, mDayMonthView->m_huangLiInfo.mSuit);
}

//void CDayMonthView::setHasScheduleFlag(const QVector<bool> &hasScheduleFlag)
TEST_F(ut_daymonthview, setHasScheduleFlag)
{
    QVector<bool> hasScheduleFlag = dayMonthViewGetLineFlag();
    mDayMonthView->setHasScheduleFlag(hasScheduleFlag);
    EXPECT_EQ(hasScheduleFlag, mDayMonthView->m_dayMonthWidget->m_vlineflag);
}

//void CDayMonthView::updateDateLunarDay()
TEST_F(ut_daymonthview, updateDateLunarDay)
{
    CaHuangLiDayInfo huangliInfo = dayMonthViewGetHuangLiDayInfo().value(currentDateTime.date());
    mDayMonthView->setHuangLiInfo(huangliInfo);
    mDayMonthView->updateDateLunarDay();
    EXPECT_EQ(huangliInfo.mSuit, mDayMonthView->m_yiLabel->toolTip());
    EXPECT_EQ(huangliInfo.mAvoid, mDayMonthView->m_jiLabel->toolTip());
}

//void CDayMonthView::changeSelectDate(const QDate &date)
TEST_F(ut_daymonthview, changeSelectDate)
{
    bool update = false;
    QObject::connect(mDayMonthView, &CDayMonthView::signalChangeSelectDate, [&]() {
        update = true;
    });
    mDayMonthView->changeSelectDate(QDate::currentDate());
    EXPECT_TRUE(update);
}

//void CDayMonthView::slotprev()
TEST_F(ut_daymonthview, slotprev)
{
    QDate selectDate = currentDateTime.date().addDays(2);
    mDayMonthView->m_selectDate = selectDate;
    QDate changeDate = currentDateTime.date();
    QObject::connect(mDayMonthView, &CDayMonthView::signalChangeSelectDate, [&](const QDate &date) {
        changeDate = date;
    });
    mDayMonthView->slotprev();
    EXPECT_EQ(changeDate, selectDate.addMonths(-1));
}

//void CDayMonthView::slotnext()
TEST_F(ut_daymonthview, slotnext)
{
    QDate selectDate = currentDateTime.date().addDays(2);
    mDayMonthView->m_selectDate = selectDate;
    QDate changeDate = currentDateTime.date();
    QObject::connect(mDayMonthView, &CDayMonthView::signalChangeSelectDate, [&](const QDate &date) {
        changeDate = date;
    });
    mDayMonthView->slotnext();
    EXPECT_EQ(changeDate, selectDate.addMonths(1));
}

//void CDayMonthView::slottoday()
TEST_F(ut_daymonthview, slottoday)
{
    mDayMonthView->m_currentDate = currentDateTime.date().addDays(2);
    QDate changeDate = currentDateTime.date();
    QObject::connect(mDayMonthView, &CDayMonthView::signalChangeSelectDate, [&](const QDate &date) {
        changeDate = date;
    });
    mDayMonthView->slottoday();
    EXPECT_EQ(changeDate, currentDateTime.date().addDays(2));
}
