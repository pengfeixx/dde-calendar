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
#include "ut_monthgraphiview.h"

#include "../dialog_stub.h"

#include <QTest>
#include <QEvent>
#include <QMenu>

void ut_monthgraphiview::SetUp()
{
    cMonthGraphiview = new CMonthGraphicsview();
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QDate currentDate = currentDateTime.date();
    QVector<QDate> datelist;
    QMap<QDate, QVector<ScheduleDataInfo>> mapInfo;
    QVector<ScheduleDataInfo> infoVector;
    ScheduleDataInfo info;
    for (int i = 0; i < 42; ++i) {
        infoVector.clear();
        info.setType(1);
        info.setAllDay(false);
        info.setBeginDateTime(currentDateTime);
        info.setEndDateTime(currentDateTime.addSecs(60 * 60 * 30));
        info.setTitleName(QString("自动测试%1").arg(i));
        datelist.append(currentDate.addDays(i));
        mapInfo[currentDate.addDays(i)] = infoVector;
    }
    cMonthGraphiview->setDate(datelist);
    cMonthGraphiview->setCurrentDate(currentDate);
}

void ut_monthgraphiview::TearDown()
{
    delete cMonthGraphiview;
}

//void CMonthGraphiview::setTheMe(int type)
TEST_F(ut_monthgraphiview, setTheMe_001)
{
    int type = 1;
    cMonthGraphiview->setTheMe(type);
    EXPECT_EQ(type, cMonthGraphiview->m_themetype);
}

TEST_F(ut_monthgraphiview, setTheMe_002)
{
    int type = 2;
    cMonthGraphiview->setTheMe(type);
    EXPECT_EQ(type, cMonthGraphiview->m_themetype);
}

//void CMonthGraphiview::setLunarInfo(const QMap<QDate, CaHuangLiDayInfo> &lunarCache)
TEST_F(ut_monthgraphiview, setLunarInfo)
{
    QMap<QDate, CaHuangLiDayInfo> lunarCache = QMap<QDate, CaHuangLiDayInfo> {};
    cMonthGraphiview->setLunarInfo(lunarCache);
    EXPECT_EQ(lunarCache.size(), cMonthGraphiview->m_lunarCache.size());
}

//void CMonthGraphiview::setLunarVisible(bool visible)
TEST_F(ut_monthgraphiview, setLunarVisible)
{
    bool visible = false;
    cMonthGraphiview->setLunarVisible(visible);
    EXPECT_EQ(visible, CMonthDayItem::m_LunarVisible);
}

//void CMonthGraphiview::setScheduleInfo(const QMap<QDate, QVector<ScheduleDataInfo> > &info)
TEST_F(ut_monthgraphiview, setScheduleInfo)
{
    QMap<QDate, QVector<ScheduleDataInfo> > info = QMap<QDate, QVector<ScheduleDataInfo> > {};
    cMonthGraphiview->setScheduleInfo(info);
    EXPECT_EQ(cMonthGraphiview->m_schedulelistdata, info);
}

//void CMonthGraphiview::setSelectSearchSchedule(const ScheduleDataInfo &scheduleInfo)
TEST_F(ut_monthgraphiview, setSelectSearchSchedule)
{
    ScheduleDataInfo scheduleInfo = ScheduleDataInfo{};
    cMonthGraphiview->setSelectSearchSchedule(scheduleInfo);
}

//QPointF CMonthGraphiview::getItemPos(const QPoint &p, const QRectF &itemRect)
TEST_F(ut_monthgraphiview, getItemPos)
{
    //转换item内坐标
    QPoint p(100, 100);
    QRectF itemRect(20, 50, 100, 100);
    QPointF getPos = cMonthGraphiview->getItemPos(p, itemRect);
    EXPECT_EQ(getPos, QPointF(100 - 20, 100 - 50));
}

//QDateTime CMonthGraphiview::getPosDate(const QPoint &p)
TEST_F(ut_monthgraphiview, getPosDate)
{
    QPoint p(0, 0);
    QDateTime datetime = cMonthGraphiview->getPosDate(p);
    EXPECT_EQ(datetime.date(), QDate::currentDate());
}

////void CMonthGraphiview::upDateInfoShow(const CMonthGraphiview::DragStatus &status, const ScheduleDataInfo &info)
//TEST_F(ut_monthgraphiview, upDateInfoShow)
//{
//    ScheduleDataInfo info = ScheduleDataInfo{};
//    cMonthGraphiview->upDateInfoShow(CMonthGraphiview::DragStatus::IsCreate, info);
//}

//mouseDoubleClickEvent
TEST_F(ut_monthgraphiview, mouseDoubleClickEvent)
{
    Stub stub;
    calendarDDialogExecStub(stub);
    QTest::mouseDClick(cMonthGraphiview->viewport(), Qt::LeftButton);
}
