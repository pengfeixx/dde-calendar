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
#include "ut_graphicsview.h"
#include "graphicsItem/scheduleitem.h"
#include "../third-party_stub/stub.h"

void ut_graphicsview::SetUp()
{
    //周视图
    cGraphicsView = new CGraphicsView(nullptr, CGraphicsView::WeekPos);
    //设置最小高度
    cGraphicsView->setMinimumHeight(300);
    QDateTime currentDateTime = QDateTime::currentDateTime();
    //时间段为当前时间往前一周
    cGraphicsView->setRange(1000, 800, currentDateTime.date(), currentDateTime.date().addDays(7), 0);
    cGraphicsView->setTime(currentDateTime.time());
    cGraphicsView->setCurrentDate(currentDateTime);
    QVector<ScheduleDataInfo> nonAllInfo;
    ScheduleDataInfo info;
    for (int i = 0; i < 7; ++i) {
        info.setAllDay(false);
        info.setTitleName("test");
        info.setID(i);
        info.setType(2);
        info.setBeginDateTime(currentDateTime.addDays(i));
        info.setEndDateTime(currentDateTime.addDays(i).addSecs(60 * 60 * 30));
        nonAllInfo.append(info);
    }
    //设置费全体人称
    cGraphicsView->setInfo(nonAllInfo);
}

void ut_graphicsview::TearDown()
{
    delete cGraphicsView;
    cGraphicsView = nullptr;
}

//void CGraphicsView::setMargins(int left, int top, int right, int bottom)
TEST_F(ut_graphicsview, setMargins)
{
    int left = 50;
    int top = 50;
    int right = 50;
    int bottom = 50;
    cGraphicsView->setMargins(left, top, right, bottom);
    EXPECT_EQ(cGraphicsView->m_margins.left(), left);
    EXPECT_EQ(cGraphicsView->m_margins.right(), right);
    EXPECT_EQ(cGraphicsView->m_margins.bottom(), bottom);
}

//void CGraphicsView::setTheMe(int type)
TEST_F(ut_graphicsview, setTheMe_001)
{
    QColor weekColor = "#00429A";
    weekColor.setAlphaF(0.05);
    int type = 0;
    cGraphicsView->setTheMe(type);
    EXPECT_EQ(cGraphicsView->m_weekcolor, weekColor);
}

TEST_F(ut_graphicsview, setTheMe_002)
{
    QColor weekColor = "#4F9BFF";
    weekColor.setAlphaF(0.1);
    int type = 2;
    cGraphicsView->setTheMe(type);
    EXPECT_EQ(cGraphicsView->m_weekcolor, weekColor);
}

//bool CGraphicsView::MeetCreationConditions(const QDateTime &date)
TEST_F(ut_graphicsview, MeetCreationConditions_001)
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    cGraphicsView->m_PressDate = currentDateTime.addDays(3);
    EXPECT_TRUE(cGraphicsView->MeetCreationConditions(currentDateTime));
}

TEST_F(ut_graphicsview, MeetCreationConditions_002)
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    cGraphicsView->m_PressDate = currentDateTime.addDays(8);
    EXPECT_FALSE(cGraphicsView->MeetCreationConditions(currentDateTime));
}

//void CGraphicsView::setRange(int w, int h, QDate begindate, QDate enddate, int rightMargin)
TEST_F(ut_graphicsview, setRange_001)
{
    int w = 20;
    int h = 20;
    QDate begindate(2020, 11, 11);
    QDate enddate(2020, 11, 31);
    int rightMargin = 10;

    cGraphicsView->setRange(w, h, begindate, enddate, rightMargin);
    EXPECT_EQ(cGraphicsView->m_beginDate, begindate);
    EXPECT_EQ(cGraphicsView->m_endDate, enddate);
    cGraphicsView->setRange(begindate, enddate);
}

TEST_F(ut_graphicsview, setRange_002)
{
    QDate begindate(2020, 11, 11);
    QDate enddate(2020, 11, 31);
    cGraphicsView->setRange(begindate, enddate);
    EXPECT_EQ(cGraphicsView->m_beginDate, begindate);
    EXPECT_EQ(cGraphicsView->m_endDate, enddate);
}

//void CGraphicsView::setCurrentDate(const QDateTime &currentDate)
TEST_F(ut_graphicsview, setCurrentDate)
{
    QDateTime date = QDateTime::currentDateTime();
    cGraphicsView->setCurrentDate(date);
    EXPECT_EQ(date, cGraphicsView->m_currentDateTime);
}

//void CGraphicsView::setInfo(const QVector<ScheduleDataInfo> &info)
TEST_F(ut_graphicsview, setInfo)
{
    QVector<ScheduleDataInfo> infos = QVector<ScheduleDataInfo> {};
    cGraphicsView->setInfo(infos);
    EXPECT_EQ(infos, cGraphicsView->m_scheduleInfo);
}

//void CGraphicsView::upDateInfoShow(const CGraphicsView::DragStatus &status, const ScheduleDataInfo &info)
TEST_F(ut_graphicsview, upDateInfoShow_001)
{
    //测试拖拽日程更新显示
    ScheduleDataInfo info;
    info.setID(8);
    info.setType(2);
    QDateTime currentDateTime = QDateTime::currentDateTime();
    info.setBeginDateTime(currentDateTime);
    info.setEndDateTime(currentDateTime.addSecs(60 * 60));
    info.setTitleName("uttest");
    info.setAllDay(false);
    cGraphicsView->upDateInfoShow();
    int itemNum = cGraphicsView->m_Scene->items().size();

    cGraphicsView->upDateInfoShow(CGraphicsView::DragStatus::IsCreate, info);
    EXPECT_GT(cGraphicsView->m_Scene->items().size(), itemNum);
}

TEST_F(ut_graphicsview, upDateInfoShow_002)
{
    //测试拖拽日程更新显示
    ScheduleDataInfo info = cGraphicsView->m_scheduleInfo.at(0);

    info.setTitleName("uttest");
    cGraphicsView->upDateInfoShow();
    int itemNum = cGraphicsView->m_Scene->items().size();

    cGraphicsView->upDateInfoShow(CGraphicsView::DragStatus::ChangeEnd, info);
    EXPECT_EQ(cGraphicsView->m_Scene->items().size(), itemNum);
}

TEST_F(ut_graphicsview, upDateInfoShow_003)
{
    //测试拖拽日程更新显示
    ScheduleDataInfo info = cGraphicsView->m_scheduleInfo.at(0);

    info.setTitleName("uttest");
    cGraphicsView->upDateInfoShow();
    int itemNum = cGraphicsView->m_Scene->items().size();

    cGraphicsView->upDateInfoShow(CGraphicsView::DragStatus::ChangeBegin, info);
    EXPECT_EQ(cGraphicsView->m_Scene->items().size(), itemNum);
}

TEST_F(ut_graphicsview, upDateInfoShow_004)
{
    //测试拖拽日程更新显示
    ScheduleDataInfo info = cGraphicsView->m_scheduleInfo.at(0);

    info.setTitleName("uttest");
    cGraphicsView->upDateInfoShow();
    int itemNum = cGraphicsView->m_Scene->items().size();

    cGraphicsView->upDateInfoShow(CGraphicsView::DragStatus::ChangeWhole, info);
    EXPECT_GT(cGraphicsView->m_Scene->items().size(), itemNum);
}

//QDateTime CGraphicsView::getPosDate(const QPoint &p)
TEST_F(ut_graphicsview, getPosDate)
{
    QDateTime dateTime;
    QPoint point(50, 40);
    dateTime = cGraphicsView->getPosDate(point);
    EXPECT_EQ(dateTime.date(), QDate::currentDate());
}

//void CGraphicsView::ShowSchedule(DragInfoItem *infoitem)
//TEST_F(ut_graphicsview, ShowSchedule)
//{
//    QPoint point(50, 40);
//    QGraphicsItem *listItem = itemAt(point);
//    DragInfoItem *infoitem = dynamic_cast<DragInfoItem *>(listItem);
//    CScheduleItem *scheduleitem = dynamic_cast<CScheduleItem *>(infoitem);
//    qInfo() << scheduleitem->getType();
//    cGraphicsView->ShowSchedule(infoitem);
//}

//void CGraphicsView::addScheduleItem(const ScheduleDataInfo &info, QDate date, int index, int totalNum, int type, int viewtype, int maxnum)
TEST_F(ut_graphicsview, addScheduleItem)
{
    ScheduleDataInfo info = ScheduleDataInfo{};
    QDate date = QDate::currentDate();
    int index = 1;
    int totalNum = 2;
    int type = 2;
    int viewtype = 1;
    int maxnum = 3;
    int itemNum = cGraphicsView->m_vScheduleItem.size();
    cGraphicsView->addScheduleItem(info, date, index, totalNum, type, viewtype, maxnum);
    EXPECT_EQ(itemNum + 1, cGraphicsView->m_vScheduleItem.size());
}

//void CGraphicsView::scheduleClassificationType(QVector<ScheduleDataInfo> &scheduleInfolist, QList<ScheduleclassificationInfo> &info)
TEST_F(ut_graphicsview, scheduleClassificationType)
{
    QVector<ScheduleDataInfo> scheduleInfolist {};
    QDateTime currentDateTime = QDateTime::currentDateTime();
    for (int i = 0; i < 10; ++i) {
        ScheduleDataInfo info;
        info.setID(8 + i);
        info.setAllDay(false);
        info.setBeginDateTime(currentDateTime.addDays(i));
        info.setEndDateTime(currentDateTime.addDays(i).addSecs(60 * 60));
        info.setTitleName("test");
        info.setType(2);
        scheduleInfolist.append(info);
    }
    QList<ScheduleclassificationInfo> info {};
    cGraphicsView->scheduleClassificationType(scheduleInfolist, info);
    EXPECT_GT(info.size(), 0);
}

//void CGraphicsView::slotDoubleEvent(int type)
TEST_F(ut_graphicsview, slotDoubleEvent)
{
    int type = 1;
    cGraphicsView->slotDoubleEvent(type);
    EXPECT_TRUE(cGraphicsView->m_updateDflag);
}

//void CGraphicsView::slotScrollBar()
TEST_F(ut_graphicsview, slotScrollBar)
{
    int isShow = false;
    QObject::connect(cGraphicsView, &CGraphicsView::signalScheduleShow, [&]() {
        isShow = true;
    });
    cGraphicsView->slotScrollBar();
    EXPECT_TRUE(isShow);
}

//void CGraphicsView::slotUpdateScene()
TEST_F(ut_graphicsview, slotUpdateScene)
{
    cGraphicsView->slotUpdateScene();
    EXPECT_FALSE(cGraphicsView->m_PressScheduleInfo.isValid());
}

//void CGraphicsView::scrollBarValueChangedSlot()
TEST_F(ut_graphicsview, scrollBarValueChangedSlot)
{
    bool posUpdate = false;
    QObject::connect(cGraphicsView, &CGraphicsView::signalsPosHours, [&]() {
        posUpdate = true;
    });
    cGraphicsView->scrollBarValueChangedSlot();
    EXPECT_TRUE(posUpdate);
}

//ScheduleDataInfo CGraphicsView::getScheduleInfo(const QDateTime &beginDate, const QDateTime &endDate)
TEST_F(ut_graphicsview, getScheduleInfo)
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QDateTime endDateTime = currentDateTime.addSecs(60 * 60);
    ScheduleDataInfo info = cGraphicsView->getScheduleInfo(currentDateTime, endDateTime);
    EXPECT_EQ(currentDateTime, info.getBeginDateTime());
    EXPECT_EQ(endDateTime, info.getEndDateTime());
}

//bool CGraphicsView::IsEqualtime(const QDateTime &timeFirst, const QDateTime &timeSecond)
TEST_F(ut_graphicsview, IsEqualtime_001)
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QDateTime endDateTime = currentDateTime.addSecs(60 * 60);
    EXPECT_FALSE(cGraphicsView->IsEqualtime(currentDateTime, endDateTime));
}

TEST_F(ut_graphicsview, IsEqualtime_002)
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QDateTime endDateTime = currentDateTime.addSecs(50);
    EXPECT_TRUE(cGraphicsView->IsEqualtime(currentDateTime, endDateTime));
}

//bool CGraphicsView::JudgeIsCreate(const QPointF &pos)
TEST_F(ut_graphicsview, JudgeIsCreate_001)
{
    QPointF pos(20, 20);
    cGraphicsView->m_PressPos = QPoint(10, 10);
    bool getBool = cGraphicsView->JudgeIsCreate(pos);
    EXPECT_FALSE(getBool);
}

TEST_F(ut_graphicsview, JudgeIsCreate_002)
{
    QPointF pos(20, 20);
    cGraphicsView->m_PressPos = QPoint(50, 10);
    bool getBool = cGraphicsView->JudgeIsCreate(pos);
    EXPECT_TRUE(getBool);
}

static QAction *action = nullptr;
QAction *graphicsViewExec_stub(void *obj, const QPoint &pos, QAction *at = nullptr)
{
    Q_UNUSED(obj)
    Q_UNUSED(pos)
    Q_UNUSED(at)
    return action;
}

//void CGraphicsView::RightClickToCreate(QGraphicsItem *listItem, const QPoint &pos)
TEST_F(ut_graphicsview, RightClickToCreate)
{
    Stub stub;
    stub.set((QAction * (QMenu::*)(const QPoint &, QAction *)) ADDR(QMenu, exec), graphicsViewExec_stub);
    QPoint pos(20, 20);
    cGraphicsView->RightClickToCreate(nullptr, pos);

    EXPECT_EQ(QDate::currentDate(), cGraphicsView->m_createDate.date());
}

//QDateTime CGraphicsView::getDragScheduleInfoBeginTime(const QDateTime &moveDateTime)
TEST_F(ut_graphicsview, getDragScheduleInfoBeginTime_001)
{
    QDateTime currentDate = QDateTime::currentDateTime();
    cGraphicsView->m_InfoEndTime = currentDate.addSecs(60 * 60);

    QDateTime getDateTime = cGraphicsView->getDragScheduleInfoBeginTime(currentDate);
    EXPECT_EQ(currentDate, getDateTime);
}

TEST_F(ut_graphicsview, getDragScheduleInfoBeginTime_002)
{
    QDateTime currentDate = QDateTime::currentDateTime();
    cGraphicsView->m_InfoEndTime = currentDate.addSecs(2);

    QDateTime getDateTime = cGraphicsView->getDragScheduleInfoBeginTime(currentDate);
    EXPECT_EQ(cGraphicsView->m_InfoEndTime.addSecs(-1800), getDateTime);
}

//QDateTime CGraphicsView::getDragScheduleInfoEndTime(const QDateTime &moveDateTime)
TEST_F(ut_graphicsview, getDragScheduleInfoEndTime_001)
{
    QDateTime currentDate = QDateTime::currentDateTime();
    cGraphicsView->m_InfoBeginTime = currentDate.addSecs(-2);

    QDateTime getDateTime = cGraphicsView->getDragScheduleInfoEndTime(currentDate);
    EXPECT_EQ(cGraphicsView->m_InfoBeginTime.addSecs(1800), getDateTime);
}

TEST_F(ut_graphicsview, getDragScheduleInfoEndTime_002)
{
    QDateTime currentDate = QDateTime::currentDateTime();
    cGraphicsView->m_InfoBeginTime = currentDate.addSecs(-60 * 60);

    QDateTime getDateTime = cGraphicsView->getDragScheduleInfoEndTime(currentDate);
    EXPECT_EQ(currentDate, getDateTime);
}

QPointF viewPos;
void ViewcenterOn_Stub(void *obj, const QPointF &pos)
{
    Q_UNUSED(obj)
    viewPos = pos;
}
//void CGraphicsView::keepCenterOnScene()
TEST_F(ut_graphicsview, keepCenterOnScene)
{
    Stub stub;
    stub.set((void (QGraphicsView::*)(const QPointF &))ADDR(QGraphicsView, centerOn), ViewcenterOn_Stub);
    cGraphicsView->keepCenterOnScene();
    qreal x = cGraphicsView->viewport()->width() / 2;
    EXPECT_GT(viewPos.x(), x - 0.0001);
    EXPECT_LT(viewPos.x(), x + 0.0001);
}

//void CGraphicsView::setTime(QTime time)
TEST_F(ut_graphicsview, setTime)
{
    QTime time = QTime::currentTime();
    cGraphicsView->setTime(time);
    Stub stub;
    stub.set((void (QGraphicsView::*)(const QPointF &))ADDR(QGraphicsView, centerOn), ViewcenterOn_Stub);
    qreal x = cGraphicsView->viewport()->width() / 2;
    EXPECT_GT(viewPos.x(), x - 0.0001);
    EXPECT_LT(viewPos.x(), x + 0.0001);
}

//void CGraphicsView::updateInfo()
TEST_F(ut_graphicsview, updateInfo)
{
    cGraphicsView->m_DragStatus = CGraphicsView::IsCreate;
    cGraphicsView->updateInfo();
}

////void CGraphicsView::mousePressEvent(QMouseEvent *event)
//TEST_F(ut_graphicsview, mousePressEvent)
//{
//    QMouseEvent *event;
//    cGraphicsView->mousePressEvent(event);
//    assert(1 == 1);
//}
