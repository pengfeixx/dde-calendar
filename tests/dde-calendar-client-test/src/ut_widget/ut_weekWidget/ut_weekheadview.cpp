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
#include "ut_weekheadview.h"
#include "../third-party_stub/stub.h"
#include "customWidget/customframe.h"

ut_weekheadview::ut_weekheadview()
{
    mWeekHeadView = new CWeekHeadView();
}

ut_weekheadview::~ut_weekheadview()
{
    delete mWeekHeadView;
    mWeekHeadView = nullptr;
}

QMap<QDate, CaHuangLiDayInfo> getHuangLiDayInfo()
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

QVector<QDate> getDayList()
{
    QVector<QDate> dateList {};
    QDate currentDate = QDate::currentDate();
    dateList.append(currentDate);
    dateList.append(currentDate.addDays(1));
    dateList.append(currentDate.addDays(2));
    dateList.append(currentDate.addDays(3));
    dateList.append(currentDate.addDays(4));
    dateList.append(currentDate.addDays(5));
    dateList.append(currentDate.addDays(6));

    return dateList;
}
//void CWeekHeadView::setTheMe(int type)
TEST_F(ut_weekheadview, setTheMe)
{
    mWeekHeadView->setTheMe(1);
    ASSERT_EQ(QString::number(mWeekHeadView->m_backgroundShowColor.alphaF(), 'f', 2), "0.40");
    mWeekHeadView->setTheMe(2);
    ASSERT_EQ(QString::number(mWeekHeadView->m_backgroundColor.alphaF(), 'f', 2), "0.10");
}

//void CWeekHeadView::setWeekDay(QVector<QDate> vDays, const QDate &selectDate)
TEST_F(ut_weekheadview, setWeekDay)
{
    QVector<QDate> dateList {};
    dateList.append(getDayList().first());
    mWeekHeadView->setWeekDay(dateList, QDate::currentDate());
    mWeekHeadView->setWeekDay(getDayList(), QDate::currentDate());
    QLocale locale;
    ASSERT_EQ(mWeekHeadView->m_monthLabel->m_text, locale.monthName(QDate::currentDate().month(), QLocale::ShortFormat));
}

//void CWeekHeadView::setLunarVisible(bool visible)
TEST_F(ut_weekheadview, setLunarvisible)
{
    mWeekHeadView->setLunarVisible(false);
    ASSERT_EQ(mWeekHeadView->m_showState, CWeekHeadView::ShowLunarFestivalHighlight);
    mWeekHeadView->setLunarVisible(true);
    ASSERT_EQ(mWeekHeadView->m_showState, CWeekHeadView::Normal);
}

//const QString CWeekHeadView::getCellDayNum(int pos)
TEST_F(ut_weekheadview, getCellDayNum)
{
    mWeekHeadView->setWeekDay(getDayList(), QDate::currentDate());
    QString str = mWeekHeadView->getCellDayNum(4);
    EXPECT_EQ(str, QString::number(getDayList().at(4).day()));
}

//const QDate CWeekHeadView::getCellDate(int pos)
TEST_F(ut_weekheadview, getCellDate)
{
    mWeekHeadView->setWeekDay(getDayList(), QDate::currentDate());
    QDate date = mWeekHeadView->getCellDate(4);
    ASSERT_EQ(date, QDate::currentDate().addDays(4));
}

//const QString CWeekHeadView::getLunar(int pos)
TEST_F(ut_weekheadview, getLunar)
{
    mWeekHeadView->setWeekDay(getDayList(), QDate::currentDate());
    mWeekHeadView->setHunagLiInfo(getHuangLiDayInfo());
    QString str = mWeekHeadView->getLunar(1);
    ASSERT_EQ(str, "");
}

TEST_F(ut_weekheadview, getPixmap)
{
    mWeekHeadView->setWeekDay(getDayList(), QDate::currentDate());
    mWeekHeadView->setFixedSize(600, 80);
    QPixmap pixmap(mWeekHeadView->size());
    mWeekHeadView->render(&pixmap);
    ASSERT_EQ(pixmap.size(), mWeekHeadView->size());
}
