/*
   * Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
   *
   * Author:     chenhaifeng <chenhaifeng@uniontech.com>
   *
   * Maintainer: chenhaifeng <chenhaifeng@uniontech.com>
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
#include "ut_scheduleview.h"

#include "../third-party_stub/stub.h"
#include "alldayeventview.h"
#include "graphicsview.h"

ut_scheduleview::ut_scheduleview()
{
}

void ut_scheduleview::SetUp()
{
    mScheduleView = new CScheduleView();
}

void ut_scheduleview::TearDown()
{
    delete mScheduleView;
    mScheduleView = nullptr;
}

QVector<ScheduleDataInfo> getScheduleData()
{
    ScheduleDataInfo schedule1, schedule2;

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
    schedule2.setAllDay(false);
    schedule2.setType(2);
    schedule2.setRecurID(0);

    QVector<ScheduleDataInfo> scheduleList{};
    scheduleList.append(schedule1);
    scheduleList.append(schedule2);
    return scheduleList;
}

//void CScheduleView::setviewMargin(int left, int top, int right, int bottom)
TEST_F(ut_scheduleview, setviewMargin)
{
    mScheduleView->setviewMargin(8, 8, 4, 4);
    EXPECT_EQ(mScheduleView->m_leftMargin, 8);
    EXPECT_EQ(mScheduleView->m_topMargin, 8);
    EXPECT_EQ(mScheduleView->m_rightMargin, 4);
}

//void CScheduleView::setRange(int w, int h, QDate begin, QDate end)
TEST_F(ut_scheduleview, setRange_001)
{
    QDate current = QDate::currentDate();
    mScheduleView->setRange(4, 4, current, current.addDays(1));
    EXPECT_EQ(current, mScheduleView->m_beginDate);
    EXPECT_EQ(current.addDays(1), mScheduleView->m_endDate);
    EXPECT_EQ(2, mScheduleView->m_TotalDay);
}

//void CScheduleView::setRange(QDate begin, QDate end)
TEST_F(ut_scheduleview, setRange_002)
{
    QDate current = QDate::currentDate();
    mScheduleView->setRange(current, current.addDays(1));
    EXPECT_EQ(current, mScheduleView->m_beginDate);
    EXPECT_EQ(current.addDays(1), mScheduleView->m_endDate);
}

//void CScheduleView::setTheMe(int type)
TEST_F(ut_scheduleview, setTheMe_001)
{
    mScheduleView->setTheMe(1);
    QColor color("#303030");
    EXPECT_EQ(color, mScheduleView->m_ALLDayColor);
}

TEST_F(ut_scheduleview, setTheMe_002)
{
    mScheduleView->setTheMe(2);
    QColor color("#7D7D7D");
    EXPECT_EQ(color, mScheduleView->m_ALLDayColor);
}

//void CScheduleView::setTime(QTime time)
TEST_F(ut_scheduleview, setTime)
{
    QTime currentTime = QTime::currentTime();
    mScheduleView->setTime(currentTime);
}

//void CScheduleView::setSelectSchedule(const ScheduleDataInfo &scheduleInfo)
TEST_F(ut_scheduleview, setSelectSchedule_001)
{
    ScheduleDataInfo scheduleinfo = getScheduleData().first();
    mScheduleView->setSelectSchedule(scheduleinfo);
    EXPECT_EQ(DragInfoItem::getPressSchedule(), scheduleinfo);
}

TEST_F(ut_scheduleview, setSelectSchedule_002)
{
    ScheduleDataInfo scheduleinfo = getScheduleData().at(1);
    mScheduleView->setSelectSchedule(scheduleinfo);
    EXPECT_EQ(DragInfoItem::getPressSchedule(), scheduleinfo);
}

//void CScheduleView::updateHeight()
TEST_F(ut_scheduleview, updateHeight)
{
    mScheduleView->setFixedSize(500, 400);
    mScheduleView->updateHeight();
    EXPECT_GT(mScheduleView->m_graphicsView->height(), 0);
    EXPECT_GT(mScheduleView->m_alldaylist->height(), 0);
}

//bool CScheduleView::IsDragging()
TEST_F(ut_scheduleview, IsDragging)
{
    EXPECT_FALSE(mScheduleView->IsDragging());
}

//void CScheduleView::setCurrentDate(const QDateTime &currentDate)
TEST_F(ut_scheduleview, setCurrentDate)
{
    QDateTime currentTime = QDateTime::currentDateTime();
    mScheduleView->setCurrentDate(currentTime);
    EXPECT_EQ(mScheduleView->m_graphicsView->m_currentDateTime, currentTime);
}

//void CScheduleView::setShowScheduleInfo(const QMap<QDate, QVector<ScheduleDataInfo> > &scheduleInfo)
TEST_F(ut_scheduleview, setShowScheduleInfo)
{
    QMap<QDate, QVector<ScheduleDataInfo> > dateInfoMap;
    dateInfoMap.insert(QDate::currentDate(), getScheduleData());
    mScheduleView->setShowScheduleInfo(dateInfoMap);
    EXPECT_EQ(dateInfoMap, mScheduleView->m_showSchedule);
}

//void CScheduleView::setDate(QDate date)
TEST_F(ut_scheduleview, setDate)
{
    QDate current = QDate::currentDate();
    mScheduleView->setDate(current);
    EXPECT_EQ(current, mScheduleView->m_currteDate);
}

//void CScheduleView::slotupdateSchedule()
TEST_F(ut_scheduleview, slotupdateSchedule)
{
    QDate current = QDate::currentDate();
    QDate endDate = current.addDays(5);
    mScheduleView->setRange(current, endDate);
    mScheduleView->slotupdateSchedule();
    EXPECT_EQ(mScheduleView->m_alldaylist->m_scheduleInfo.size(), 0);
    EXPECT_EQ(mScheduleView->m_graphicsView->m_scheduleInfo.size(), 0);
}

//void CScheduleView::slotPosHours(QVector<int> vPos, QVector<int> vHours, int currentTimeType)
TEST_F(ut_scheduleview, slotPosHours)
{
    QVector<int> pos;
    pos.append(1);
    pos.append(2);
    pos.append(3);
    pos.append(4);

    QVector<int> hours;
    hours.append(4);
    hours.append(8);
    hours.append(16);
    hours.append(20);

    mScheduleView->slotPosHours(pos, hours, 1);
    EXPECT_EQ(pos, mScheduleView->m_vPos);
    EXPECT_EQ(hours, mScheduleView->m_vHours);
    EXPECT_EQ(1, mScheduleView->m_currentTimeType);
}

//void CScheduleView::slotCurrentScheduleDate(QDate date)
TEST_F(ut_scheduleview, slotCurrentScheduleDate)
{
    mScheduleView->m_viewPos = ScheduleViewPos::WeekPos;
    QDate currentDate = QDate::currentDate();
    mScheduleView->slotCurrentScheduleDate(currentDate);
    QObject::connect(mScheduleView, &CScheduleView::signalsCurrentScheduleDate, [=](QDate date) {
        EXPECT_EQ(currentDate, date);
    });
}

//void CScheduleView::slotScheduleShow(const bool isShow, const ScheduleDataInfo &out)
TEST_F(ut_scheduleview, slotScheduleShow_001)
{
    mScheduleView->slotScheduleShow(false, getScheduleData().first());
    EXPECT_TRUE(mScheduleView->m_ScheduleRemindWidget->isHidden());
}

TEST_F(ut_scheduleview, slotScheduleShow_002)
{
    mScheduleView->slotScheduleShow(true, getScheduleData().first());
    EXPECT_FALSE(mScheduleView->m_ScheduleRemindWidget->isHidden());
    //    mScheduleView->slotScheduleShow(true, getScheduleData().at(1));
}

//void CScheduleView::slotUpdatePaint(const int topM)
TEST_F(ut_scheduleview, slotUpdatePaint)
{
    const int top = 4;
    mScheduleView->slotUpdatePaint(top);
    EXPECT_EQ(top, mScheduleView->m_topMargin);
}

//void CScheduleView::slotUpdateScene()
TEST_F(ut_scheduleview, slotUpdateScene)
{
    mScheduleView->slotUpdateScene();
    EXPECT_EQ(mScheduleView->m_alldaylist->m_PressScheduleInfo, ScheduleDataInfo());
    EXPECT_EQ(mScheduleView->m_graphicsView->m_PressScheduleInfo, ScheduleDataInfo());
}

//void CScheduleView::updateSchedule()
TEST_F(ut_scheduleview, updateSchedule)
{
    QDate current = QDate::currentDate();
    QDate endDate = current.addDays(5);
    mScheduleView->setRange(current, endDate);
    mScheduleView->updateSchedule();
    EXPECT_EQ(mScheduleView->m_alldaylist->m_scheduleInfo.size(), 0);
    EXPECT_EQ(mScheduleView->m_graphicsView->m_scheduleInfo.size(), 0);
}

//void CScheduleView::updateAllday()
TEST_F(ut_scheduleview, updateAllday)
{
    mScheduleView->setFixedSize(500, 500);
    QDate current = QDate::currentDate();
    QDate endDate = current.addDays(5);
    mScheduleView->setRange(current, endDate);
    int height = mScheduleView->m_graphicsView->height();
    mScheduleView->updateAllday();
    EXPECT_EQ(height, mScheduleView->m_graphicsView->height());
}

int testHeight(bool isDay, int height)
{
    qreal h = 0;
    if (isDay) {
        h = 24 * (0.0968 * height + 0.5);
    } else {
        h = 24 * (0.083 * height + 0.5);
    }
    h = h < 500 ? 1035 : h;
    return qRound(h);
}

//int CScheduleView::scheduleViewHeight()
TEST_F(ut_scheduleview, scheduleViewHeight_001)
{
    mScheduleView->setFixedSize(500, 1500);
    mScheduleView->m_viewPos = ScheduleViewPos::DayPos;
    int h = testHeight(true, mScheduleView->height());
    EXPECT_EQ(h, mScheduleView->scheduleViewHeight());
}

TEST_F(ut_scheduleview, scheduleViewHeight_002)
{
    mScheduleView->setFixedSize(500, 1500);
    mScheduleView->m_viewPos = ScheduleViewPos::WeekPos;
    int h = testHeight(false, mScheduleView->height());
    EXPECT_EQ(h, mScheduleView->scheduleViewHeight());
}

//getPixmap
TEST_F(ut_scheduleview, getPixmap)
{
    QVector<int> pos;
    pos.append(1);
    pos.append(2);
    pos.append(3);
    pos.append(4);

    QVector<int> hours;
    hours.append(4);
    hours.append(8);
    hours.append(16);
    hours.append(20);

    mScheduleView->slotPosHours(pos, hours, 1);

    mScheduleView->setFixedSize(800, 500);
    QPixmap pixmap(mScheduleView->size());
    mScheduleView->render(&pixmap);
    EXPECT_EQ(pixmap.size(), mScheduleView->size());
}
