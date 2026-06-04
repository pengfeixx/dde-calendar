// SPDX-FileCopyrightText: 2019 - 2026 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "test_monthgraphiview.h"
#include "../third-party_stub/stub.h"
#include "../dialog_stub.h"
#include "view/graphicsItem/cmonthscheduleitem.h"
#include "widget/monthWidget/monthscheduleview.h"

static void monthgraphiview_stub_void()
{
}

test_monthgraphiview::test_monthgraphiview()
{
    cMonthGraphiview = new CMonthGraphicsview();
}

test_monthgraphiview::~test_monthgraphiview()
{
    delete cMonthGraphiview;
}

//void CMonthGraphicsview::setTheMe(int type)
TEST_F(test_monthgraphiview, setTheMe)
{
    int type = 1;
    cMonthGraphiview->setTheMe();
    cMonthGraphiview->setTheMe(type);
}

//void CMonthGraphicsview::setDate(const QVector<QDate> &showDate)
TEST_F(test_monthgraphiview, setDate)
{
    QVector<QDate> showDate;
    QDate date1(2020, 10, 1);
    QDate date2(2020, 12, 1);
    for (int i = 0; i < 42; ++i) {
        if (i % 2 == 0) {
            showDate.append(date1);
        } else {
            showDate.append(date2);
        }
    }
    std::cout << showDate.size() << std::endl;
    cMonthGraphiview->setDate(showDate);
}

//void CMonthGraphicsview::setLunarInfo(const QMap<QDate, CaHuangLiDayInfo> &lunarCache)
TEST_F(test_monthgraphiview, setLunarInfo)
{
    QMap<QDate, CaHuangLiDayInfo> lunarCache = QMap<QDate, CaHuangLiDayInfo> {};
    cMonthGraphiview->setLunarInfo(lunarCache);
}

//void CMonthGraphicsview::setLunarVisible(bool visible)
TEST_F(test_monthgraphiview, setLunarVisible)
{
    bool visible = false;
    cMonthGraphiview->setLunarVisible(visible);
}

//void CMonthGraphicsview::setScheduleInfo(const QMap<QDate, DSchedule::List> &info)
TEST_F(test_monthgraphiview, setScheduleInfo)
{
    QMap<QDate, DSchedule::List> info = QMap<QDate, DSchedule::List> {};
    cMonthGraphiview->setScheduleInfo(info);
}

//void CMonthGraphicsview::setSelectSearchSchedule(const DSchedule::Ptr &scheduleInfo)
TEST_F(test_monthgraphiview, setSelectSearchSchedule)
{
    DSchedule::Ptr scheduleInfo = DSchedule::Ptr(new DSchedule());
    scheduleInfo->setUid("1");
    scheduleInfo->setSummary("test");
    cMonthGraphiview->setSelectSearchSchedule(scheduleInfo);
}

//QPointF CMonthGraphicsview::getItemPos(const QPoint &p, const QRectF &itemRect)
TEST_F(test_monthgraphiview, getItemPos)
{
    QPoint p(100, 100);
    QRectF itemRect;
    cMonthGraphiview->getItemPos(p, itemRect);
}

//QDateTime CMonthGraphicsview::getPosDate(const QPoint &p)
TEST_F(test_monthgraphiview, getPosDate_01)
{
    QPoint p(100, 100);
    cMonthGraphiview->getPosDate(p);
}

TEST_F(test_monthgraphiview, getPosDate_02)
{
    QPoint p(-100, -1);
    cMonthGraphiview->getPosDate(p);
}

TEST_F(test_monthgraphiview, getPosDate_03)
{
    QPoint p(-1, -1);
    cMonthGraphiview->setSceneRect(-2, -2, 100, 100);
    cMonthGraphiview->getPosDate(p);
}

////void CMonthGraphicsview::upDateInfoShow(const CMonthGraphicsview::DragStatus &status, const DSchedule::Ptr &info)
TEST_F(test_monthgraphiview, upDateInfoShow_01)
{
    Stub stub;
    stub.set(ADDR(CWeekScheduleView, addData), monthgraphiview_stub_void);
    stub.set(ADDR(CWeekScheduleView, changeDate), monthgraphiview_stub_void);
    DSchedule::Ptr info;
    cMonthGraphiview->upDateInfoShow(CMonthGraphicsview::IsCreate, info);
    cMonthGraphiview->upDateInfoShow(CMonthGraphicsview::ChangeBegin, info);
    cMonthGraphiview->upDateInfoShow(CMonthGraphicsview::ChangeEnd, info);
    cMonthGraphiview->upDateInfoShow(CMonthGraphicsview::ChangeWhole, info);
    cMonthGraphiview->upDateInfoShow(CMonthGraphicsview::NONE, info);

}

TEST_F(test_monthgraphiview, slideEvent_01)
{
    QPointF pos(1, 1);
    QPointF stopPos(2, 2);
    cMonthGraphiview->slideEvent(pos, stopPos);
}

TEST_F(test_monthgraphiview, mouseDoubleClickEvent_01)
{
    QMouseEvent event(QEvent::MouseButtonDblClick, QPointF(0, 0), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    cMonthGraphiview->mouseDoubleClickEvent(&event);
}

TEST_F(test_monthgraphiview, mouseDoubleClickEvent_02)
{
    QMouseEvent event(QEvent::MouseButtonDblClick, QPointF(0, 0), Qt::RightButton, Qt::RightButton, Qt::NoModifier);
    cMonthGraphiview->mouseDoubleClickEvent(&event);
}

TEST_F(test_monthgraphiview, mouseDoubleClickEvent_03)
{
    QMouseEvent event(QEvent::MouseButtonDblClick, QPointF(1, 1), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    cMonthGraphiview->mouseDoubleClickEvent(&event);
}

TEST_F(test_monthgraphiview, resizeEvent_01)
{
    QResizeEvent event(QSize(50, 50), QSize(100, 100));
    cMonthGraphiview->resizeEvent(&event);
}

TEST_F(test_monthgraphiview, changeEvent_01)
{
    QEvent event(QEvent::FontChange);
    cMonthGraphiview->changeEvent(&event);
}

TEST_F(test_monthgraphiview, wheelEvent_01)
{
    QWheelEvent event(QPointF(1, 1), QPointF(1, 1), QPoint(0, 0), QPoint(0, 120), Qt::NoButton, Qt::NoModifier, Qt::ScrollUpdate, false);
    cMonthGraphiview->wheelEvent(&event);
}

TEST_F(test_monthgraphiview, updateBackgroundShowItem_01)
{
    cMonthGraphiview->updateBackgroundShowItem();
}

TEST_F(test_monthgraphiview, DISABLED_setDragPixmap_01)
{
    QDrag drag(cMonthGraphiview);
    CMonthScheduleItem item(QRect(0, 0, 10, 10));
    cMonthGraphiview->setDragPixmap(&drag, &item);
}

TEST_F(test_monthgraphiview, MeetCreationConditions_01)
{
    QDateTime date;
    EXPECT_TRUE(cMonthGraphiview->MeetCreationConditions(date));
}

TEST_F(test_monthgraphiview, IsEqualtime_01)
{
    QDateTime date;
    EXPECT_TRUE(cMonthGraphiview->IsEqualtime(date, date));
}

TEST_F(test_monthgraphiview, JudgeIsCreate_01)
{
    EXPECT_FALSE(cMonthGraphiview->JudgeIsCreate(QPointF(1, 1)));
}

TEST_F(test_monthgraphiview, RightClickToCreate_01)
{
    QPoint pos(1, 1);
    cMonthGraphiview->RightClickToCreate(nullptr, pos);
}

TEST_F(test_monthgraphiview, MoveInfoProcess_01)
{
    QPointF pos(1, 1);
    DSchedule::Ptr info;
    cMonthGraphiview->MoveInfoProcess(info, pos);
}

TEST_F(test_monthgraphiview, MoveInfoProcess_02)
{
    QPointF pos(1, -1);
    DSchedule::Ptr info;
    cMonthGraphiview->MoveInfoProcess(info, pos);
}

TEST_F(test_monthgraphiview, getDragScheduleInfoBeginTime_02)
{
    QPointF pos(1, -1);
    QDateTime time;
    cMonthGraphiview->m_InfoEndTime = time;
    EXPECT_EQ(cMonthGraphiview->getDragScheduleInfoBeginTime(time), time);
}

TEST_F(test_monthgraphiview, getDragScheduleInfoEndTime_02)
{
    QPointF pos(1, -1);
    QDateTime time;
    cMonthGraphiview->m_InfoEndTime = time;
    EXPECT_EQ(cMonthGraphiview->getDragScheduleInfoEndTime(time), time);
}

TEST_F(test_monthgraphiview, slotCreate_02)
{
    Stub stub;
    calendarDDialogExecStub(stub);

    QPointF pos(1, -1);
    QDateTime time;
    cMonthGraphiview->m_InfoEndTime = time;
    cMonthGraphiview->slotCreate(time);
}
