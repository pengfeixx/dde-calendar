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
#include "ut_alldayeventview.h"
#include "../dialog_stub.h"

#include <QTest>
#include <QEvent>
#include <QMenu>
#include <QGraphicsView>

//创建测试数据
QVector<ScheduleDataInfo> getTestScheduleDataInfo()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    ScheduleDataInfo info1;
    info1.setID(1);
    info1.setType(2);
    info1.setAllDay(true);
    info1.setRecurID(2);
    info1.setTitleName("测试1");
    QDateTime ignoreDate = currentTime.addDays(2);
    QVector<QDateTime> ignoreDateList;
    ignoreDateList.append(ignoreDate);
    info1.setIgnoreTime(ignoreDateList);
    QDateTime begindate = currentTime;
    QDateTime enddate = currentTime.addSecs(60 * 60);
    info1.setBeginDateTime(begindate);
    info1.setEndDateTime(enddate);

    ScheduleDataInfo info2;
    info2.setID(1);
    info2.setType(2);
    info2.setAllDay(true);
    info2.setRecurID(2);
    info2.setTitleName("测试2");
    QDateTime ignoreDate2 = currentTime.addDays(3);
    QVector<QDateTime> ignoreDateList2;
    ignoreDateList2.append(ignoreDate2);
    info2.setIgnoreTime(ignoreDateList2);
    QDateTime begindate2 = currentTime.addSecs(60 * 60);
    QDateTime enddate2 = currentTime.addSecs(60 * 60 * 2);
    info2.setBeginDateTime(begindate2);
    info2.setEndDateTime(enddate2);

    ScheduleDataInfo info3;
    info3.setID(1);
    info3.setType(2);
    info3.setAllDay(true);
    info3.setRecurID(2);
    info3.setTitleName("测试3");
    QDateTime ignoreDate3 = currentTime.addDays(4);
    QVector<QDateTime> ignoreDateList3;
    ignoreDateList3.append(ignoreDate3);
    info3.setIgnoreTime(ignoreDateList3);
    QDateTime begindate3 = currentTime.addSecs(60 * 60 * 2);
    QDateTime enddate3 = currentTime.addSecs(60 * 60 * 3);
    info3.setBeginDateTime(begindate3);
    info3.setEndDateTime(enddate3);

    QVector<ScheduleDataInfo> infoList;
    infoList.append(info1);
    infoList.append(info2);
    infoList.append(info3);

    return infoList;
}

void ut_alldayeventview::SetUp()
{
    cAllDayEventWeekView = new CAllDayEventWeekView();
    //添加测试数据
    QVector<QVector<ScheduleDataInfo>> vlistData;
    QVector<ScheduleDataInfo> infoList1;
    infoList1.append(getTestScheduleDataInfo().at(0));
    infoList1.append(getTestScheduleDataInfo().at(1));
    QVector<ScheduleDataInfo> infoList2;
    infoList2.append(getTestScheduleDataInfo().at(2));
    vlistData.append(infoList1);
    vlistData.append(infoList2);
    cAllDayEventWeekView->setInfo(getTestScheduleDataInfo());
    QDate currentdate = QDate::currentDate();
    cAllDayEventWeekView->setRange(1000, 55, currentdate.addDays(-1), currentdate.addDays(5), 0);
}

void ut_alldayeventview::TearDown()
{
    delete cAllDayEventWeekView;
    cAllDayEventWeekView = nullptr;
}

//void CAllDayEventWeekView::setTheMe(int type)
TEST_F(ut_alldayeventview, setTheMe)
{
    int type = 1;
    cAllDayEventWeekView->setTheMe();
    cAllDayEventWeekView->setTheMe(type);
}

//bool CAllDayEventWeekView::MeetCreationConditions(const QDateTime &date)
TEST_F(ut_alldayeventview, MeetCreationConditions_001)
{
    QDateTime currentTime = QDateTime::currentDateTime();
    //设置点击位置时间
    cAllDayEventWeekView->m_PressDate = currentTime;
    QDateTime date = currentTime.addDays(3);
    EXPECT_TRUE(cAllDayEventWeekView->MeetCreationConditions(date));
}

TEST_F(ut_alldayeventview, MeetCreationConditions_002)
{
    QDateTime currentTime = QDateTime::currentDateTime();
    //设置点击位置时间
    cAllDayEventWeekView->m_PressDate = currentTime;
    QDateTime date = currentTime.addDays(10);
    EXPECT_FALSE(cAllDayEventWeekView->MeetCreationConditions(date));
}

//bool CAllDayEventWeekView::IsEqualtime(const QDateTime &timeFirst, const QDateTime &timeSecond)
TEST_F(ut_alldayeventview, IsEqualtime_001)
{
    //对比两时间是否为同一天
    QDateTime currentTime = QDateTime::currentDateTime();
    QDateTime testTime = currentTime;
    EXPECT_TRUE(cAllDayEventWeekView->IsEqualtime(testTime, currentTime));
}

TEST_F(ut_alldayeventview, IsEqualtime_002)
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QDateTime testTime = currentTime.addDays(5);
    EXPECT_FALSE(cAllDayEventWeekView->IsEqualtime(testTime, currentTime));
}

//void CAllDayEventWeekView::setDayData(const QVector<QVector<ScheduleDataInfo>> &vlistData)
TEST_F(ut_alldayeventview, setDayData)
{
    QVector<QVector<ScheduleDataInfo>> vlistData;

    QVector<ScheduleDataInfo> infoList1;
    infoList1.append(getTestScheduleDataInfo().at(0));
    infoList1.append(getTestScheduleDataInfo().at(1));

    QVector<ScheduleDataInfo> infoList2;
    infoList2.append(getTestScheduleDataInfo().at(2));

    vlistData.append(infoList1);
    vlistData.append(infoList2);

    cAllDayEventWeekView->setDayData(vlistData);
    EXPECT_EQ(vlistData, cAllDayEventWeekView->m_vlistData);
}


//void CAllDayEventWeekView::setInfo(const QVector<ScheduleDataInfo> &info)
TEST_F(ut_alldayeventview, setInfo)
{
    cAllDayEventWeekView->setInfo(getTestScheduleDataInfo());
    EXPECT_EQ(cAllDayEventWeekView->m_scheduleInfo, getTestScheduleDataInfo());
}

//void CAllDayEventWeekView::slotDoubleEvent()
TEST_F(ut_alldayeventview, slotDoubleEvent)
{
    cAllDayEventWeekView->slotDoubleEvent();
    EXPECT_TRUE(cAllDayEventWeekView->m_updateDflag);
}

//void CAllDayEventWeekView::createItemWidget(int index, bool average)
TEST_F(ut_alldayeventview, createItemWidget)
{
    QVector<QVector<ScheduleDataInfo>> vlistData;

    QVector<ScheduleDataInfo> infoList1;
    infoList1.append(getTestScheduleDataInfo().at(0));
    infoList1.append(getTestScheduleDataInfo().at(1));

    QVector<ScheduleDataInfo> infoList2;
    infoList2.append(getTestScheduleDataInfo().at(2));

    vlistData.append(infoList1);
    vlistData.append(infoList2);
    //设置准备的数据
    cAllDayEventWeekView->setDayData(vlistData);

    int w = 1000;
    int h = 900;
    QDate begindate(2020, 12, 01);
    QDate enddate(2020, 12, 21);
    int rightmagin = 2;
    //设置显示范围
    cAllDayEventWeekView->setRange(w, h, begindate, enddate, rightmagin);

    int index = 0;
    bool average = true;
    cAllDayEventWeekView->createItemWidget(index, average);

    EXPECT_EQ(cAllDayEventWeekView->m_Scene->items().size(), 12);
}

//void CAllDayEventWeekView::updateItemHeightByFontSize()
TEST_F(ut_alldayeventview, updateItemHeightByFontSize)
{
    int w = 1000;
    int h = 900;
    QDate begindate(2020, 12, 01);
    QDate enddate(2020, 12, 21);
    int rightmagin = 2;
    //设置显示范围
    cAllDayEventWeekView->setRange(w, h, begindate, enddate, rightmagin);

    cAllDayEventWeekView->updateItemHeightByFontSize();
    EXPECT_GT(cAllDayEventWeekView->itemHeight, 10);
}

//
TEST_F(ut_alldayeventview, getPixmap)
{
    cAllDayEventWeekView->setFixedSize(500, 800);
    QPixmap pixmap(cAllDayEventWeekView->size());
    pixmap = cAllDayEventWeekView->grab();
    EXPECT_EQ(pixmap.size(), cAllDayEventWeekView->size());
}

//slotCreate
TEST_F(ut_alldayeventview, slotCreate)
{
    calendarDDialogExecReturn = 1;
    Stub stub;
    calendarDDialogExecStub(stub);
    bool update = false;
    QObject::connect(cAllDayEventWeekView, &CAllDayEventWeekView::signalsUpdateSchedule, [&]() {
        update = true;
    });

    cAllDayEventWeekView->slotCreate(QDateTime::currentDateTime());
    EXPECT_TRUE(update);
}

//getDragScheduleInfoBeginTime
TEST_F(ut_alldayeventview, getDragScheduleInfoBeginTime_001)
{
    QDateTime currentTime = QDateTime::currentDateTime();
    cAllDayEventWeekView->m_InfoEndTime = currentTime.addDays(1);
    QDateTime getTime = cAllDayEventWeekView->getDragScheduleInfoBeginTime(currentTime);
    EXPECT_EQ(getTime.date(), currentTime.date());
}

TEST_F(ut_alldayeventview, getDragScheduleInfoBeginTime_002)
{
    QDateTime currentTime = QDateTime::currentDateTime();
    cAllDayEventWeekView->m_InfoEndTime = currentTime.addDays(-1);
    QDateTime getTime = cAllDayEventWeekView->getDragScheduleInfoBeginTime(currentTime);
    EXPECT_EQ(getTime.date(), cAllDayEventWeekView->m_InfoEndTime.date());
}

bool fontsize = false;
void updateItemHeightByFontSize_Stub()
{
    fontsize = true;
}
//changeEvent
TEST_F(ut_alldayeventview, changeEvent)
{
    Stub stub;
    stub.set(ADDR(CAllDayEventWeekView, updateItemHeightByFontSize), updateItemHeightByFontSize_Stub);
    QEvent event(QEvent::FontChange);
    QApplication::sendEvent(cAllDayEventWeekView, &event);
    EXPECT_TRUE(fontsize);
}

//mousePressEvent
TEST_F(ut_alldayeventview, mousePressEvent)
{
    QMouseEvent event(QEvent::MouseButtonPress, QPointF(32, 13), QPointF(646, 438), QPointF(646, 438),
                      Qt::LeftButton, Qt::LeftButton, Qt::NoModifier, Qt::MouseEventSynthesizedByQt);
    QApplication::sendEvent(cAllDayEventWeekView->viewport(), &event);
    //    EXPECT_TRUE(sceneUpdate);
    EXPECT_EQ(cAllDayEventWeekView->m_touchState, DragInfoGraphicsView::TS_PRESS);
}

TEST_F(ut_alldayeventview, JudgeIsCreate_001)
{
    QPointF point(32, 13);
    cAllDayEventWeekView->m_PressPos = QPoint(60, 50);
    EXPECT_TRUE(cAllDayEventWeekView->JudgeIsCreate(point));
}

TEST_F(ut_alldayeventview, JudgeIsCreate_002)
{
    QPointF point(60, 51);
    cAllDayEventWeekView->m_PressPos = QPoint(60, 50);
    EXPECT_FALSE(cAllDayEventWeekView->JudgeIsCreate(point));
}

static QAction *action = nullptr;
QAction *stub_exec(void *obj, const QPoint &pos, QAction *at = nullptr)
{
    Q_UNUSED(obj)
    Q_UNUSED(pos)
    Q_UNUSED(at)
    return action;
}

//RightClickToCreate
TEST_F(ut_alldayeventview, RightClickToCreate)
{
    Stub stub;
    stub.set((QAction * (QMenu::*)(const QPoint &, QAction *)) ADDR(QMenu, exec), stub_exec);
    cAllDayEventWeekView->RightClickToCreate(nullptr, QPoint(30, 50));
    QTime time = QTime::currentTime();
    EXPECT_EQ(time.hour(), cAllDayEventWeekView->m_createDate.time().hour());
}

bool updateP = false;
void updatePaint_stub(int m)
{
    Q_UNUSED(m)
    updateP = true;
}
//MoveInfoProcess
TEST_F(ut_alldayeventview, MoveInfoProcess_001)
{
    Stub stub;
    stub.set(ADDR(CAllDayEventWeekView, signalUpdatePaint), updatePaint_stub);
    ScheduleDataInfo info;
    QDateTime currentTime = QDateTime::currentDateTime();
    info.setBeginDateTime(currentTime);
    info.setEndDateTime(currentTime.addDays(1));
    info.setAllDay(true);
    cAllDayEventWeekView->MoveInfoProcess(info, QPointF(0, 0));
    EXPECT_TRUE(updateP);
    info.setAllDay(false);
    cAllDayEventWeekView->MoveInfoProcess(info, QPointF(0, 0));
}

TEST_F(ut_alldayeventview, MoveInfoProcess_002)
{
    Stub stub;
    stub.set(ADDR(CAllDayEventWeekView, signalUpdatePaint), updatePaint_stub);
    ScheduleDataInfo info;
    QDateTime currentTime = QDateTime::currentDateTime();
    info.setBeginDateTime(currentTime);
    info.setEndDateTime(currentTime.addDays(1));
    info.setAllDay(false);
    cAllDayEventWeekView->MoveInfoProcess(info, QPointF(0, 0));
    EXPECT_TRUE(updateP);
}

//getDragScheduleInfoEndTime
TEST_F(ut_alldayeventview, getDragScheduleInfoEndTime_001)
{
    QDateTime currentTime = QDateTime::currentDateTime();
    cAllDayEventWeekView->m_InfoBeginTime = currentTime.addDays(3);
    QDateTime getDate = cAllDayEventWeekView->getDragScheduleInfoEndTime(currentTime);
    EXPECT_EQ(getDate.date(), cAllDayEventWeekView->m_InfoBeginTime.date());
}

TEST_F(ut_alldayeventview, getDragScheduleInfoEndTime_002)
{
    QDateTime currentTime = QDateTime::currentDateTime();
    cAllDayEventWeekView->m_InfoBeginTime = currentTime.addDays(-3);
    QDateTime getDate = cAllDayEventWeekView->getDragScheduleInfoEndTime(currentTime);
    EXPECT_EQ(getDate.date(), currentTime.date()) << "getDate" << getDate.date().day();
}

//slotUpdateScene
TEST_F(ut_alldayeventview, slotUpdateScene)
{
    cAllDayEventWeekView->slotUpdateScene();
    EXPECT_FALSE(cAllDayEventWeekView->m_PressScheduleInfo.isValid());
}

TEST_F(ut_alldayeventview, updateInfo)
{
    QDateTime currentDate = QDateTime::currentDateTime();
    cAllDayEventWeekView->m_DragScheduleInfo.setID(2);
    cAllDayEventWeekView->m_DragScheduleInfo.setType(1);
    cAllDayEventWeekView->m_DragScheduleInfo.setBeginDateTime(currentDate);
    cAllDayEventWeekView->m_DragScheduleInfo.setEndDateTime(currentDate.addDays(1));
    cAllDayEventWeekView->m_DragScheduleInfo.setTitleName("uttest");
    cAllDayEventWeekView->m_DragScheduleInfo.setIsMoveInfo(true);
    cAllDayEventWeekView->updateInfo();
    EXPECT_FALSE(cAllDayEventWeekView->m_DragScheduleInfo.getIsMoveInfo());
}

//mouseDoubleClickEvent
TEST_F(ut_alldayeventview, mouseDoubleClickEvent)
{
    Stub stub;
    calendarDDialogExecStub(stub);
    QTest::mouseDClick(cAllDayEventWeekView->viewport(), Qt::LeftButton);
    QTime currentTime = QTime::currentTime();
    EXPECT_EQ(currentTime.hour(), cAllDayEventWeekView->m_createDate.time().hour());
}

//
TEST_F(ut_alldayeventview, setSceneRect)
{
    qreal x = 20;
    qreal y = 20;
    qreal w = 1000;
    qreal h = 1500;
    cAllDayEventWeekView->setSceneRect(x, y, w, h);
    QRectF sceneRect = cAllDayEventWeekView->m_Scene->sceneRect();
    EXPECT_GT(sceneRect.x(), x - 0.00001);
    EXPECT_LT(sceneRect.x(), x + 0.00001);

    EXPECT_GT(sceneRect.y(), y - 0.00001);
    EXPECT_LT(sceneRect.y(), y + 0.00001);

    EXPECT_GT(sceneRect.width(), w - 0.00001);
    EXPECT_LT(sceneRect.width(), w + 0.00001);

    EXPECT_GT(sceneRect.height(), h - 0.00001);
    EXPECT_LT(sceneRect.height(), h + 0.00001);
}

QPointF viewOn;
void centerOn_Stub(void *obj, const QPointF &pos)
{
    Q_UNUSED(obj)
    viewOn = pos;
}
//slotPosOnView
TEST_F(ut_alldayeventview, slotPosOnView)
{
    Stub stub;
    stub.set((void (QGraphicsView::*)(const QPointF &))ADDR(QGraphicsView, centerOn), centerOn_Stub);
    //设置视图显示位置
    qreal y = 2;
    cAllDayEventWeekView->slotPosOnView(y);
    QPointF setPoint(cAllDayEventWeekView->m_Scene->width() / 2, y);
    EXPECT_EQ(viewOn, setPoint);
}

//mouseReleaseEvent
TEST_F(ut_alldayeventview, mouseReleaseEvent_001)
{
    cAllDayEventWeekView->m_touchState = CAllDayEventWeekView::TS_PRESS;
    //鼠标释放事件
    QMouseEvent event(QEvent::MouseButtonRelease, QPointF(32, 13), QPointF(646, 438), QPointF(646, 438),
                      Qt::RightButton, Qt::RightButton, Qt::NoModifier, Qt::MouseEventSynthesizedByQt);
    QApplication::sendEvent(cAllDayEventWeekView->viewport(), &event);
    EXPECT_EQ(cAllDayEventWeekView->m_touchState, CAllDayEventWeekView::TS_PRESS);
}

//mouseReleaseEvent
TEST_F(ut_alldayeventview, mouseReleaseEvent_002)
{
    cAllDayEventWeekView->m_touchState = CAllDayEventWeekView::TS_PRESS;
    cAllDayEventWeekView->m_TouchBeginTime = QDateTime::currentDateTime().toMSecsSinceEpoch() - 10;
    QMouseEvent event(QEvent::MouseButtonRelease, QPointF(32, 13), QPointF(646, 438), QPointF(646, 438),
                      Qt::LeftButton, Qt::LeftButton, Qt::NoModifier, Qt::MouseEventSynthesizedByQt);
    QApplication::sendEvent(cAllDayEventWeekView->viewport(), &event);
    EXPECT_EQ(cAllDayEventWeekView->m_touchState, CAllDayEventWeekView::TS_NONE);
}

//mouseMoveEvent
TEST_F(ut_alldayeventview, mouseMoveEvent)
{
    cAllDayEventWeekView->m_touchState = DragInfoGraphicsView::TS_PRESS;
    QTest::mouseMove(cAllDayEventWeekView->viewport());
    EXPECT_EQ(cAllDayEventWeekView->m_touchState, CAllDayEventWeekView::TS_PRESS);
}

//wheelEvent
TEST_F(ut_alldayeventview, wheelEvent)
{
    QEvent event(QEvent::Wheel);
    QApplication::sendEvent(cAllDayEventWeekView->viewport(), &event);
}

//contextMenuEvent
TEST_F(ut_alldayeventview, contextMenuEvent_001)
{
    //    QEvent event(QEvent::ContextMenu);

    Stub stub;
    stub.set((QAction * (QMenu::*)(const QPoint &, QAction *)) ADDR(QMenu, exec), stub_exec);
    calendarDDialogExecStub(stub);
    QList<QGraphicsItem *> item = cAllDayEventWeekView->scene()->items();
    //模拟右击

    QContextMenuEvent event(QContextMenuEvent::Mouse, QPoint(20, 20), QPoint(120, 120), Qt::NoModifier);
    QApplication::sendEvent(cAllDayEventWeekView->viewport(), &event);
    EXPECT_FALSE(cAllDayEventWeekView->m_press);
    EXPECT_EQ(cAllDayEventWeekView->m_DragStatus, CAllDayEventWeekView::NONE);

    action = cAllDayEventWeekView->m_editAction;
    QApplication::sendEvent(cAllDayEventWeekView->viewport(), &event);

    action = cAllDayEventWeekView->m_deleteAction;
    QApplication::sendEvent(cAllDayEventWeekView->viewport(), &event);

    //模拟右击
    if (item.size() > 0) {
        QPoint itemPoint = cAllDayEventWeekView->mapFromScene(item.at(0)->scenePos());
        QContextMenuEvent event(QContextMenuEvent::Mouse, itemPoint, cAllDayEventWeekView->mapToGlobal(itemPoint), Qt::NoModifier);
        QApplication::sendEvent(cAllDayEventWeekView->viewport(), &event);
    }
}

static void sendMousePress(QWidget *widget, const QPoint &point, Qt::MouseButton button = Qt::LeftButton)
{
    QMouseEvent event(QEvent::MouseButtonPress, point, widget->mapToGlobal(point), button, {}, {});
    QApplication::sendEvent(widget, &event);
}

static void sendMouseMove(QWidget *widget, const QPoint &point, Qt::MouseButton button = Qt::NoButton, Qt::MouseButtons buttons = {})
{
    QTest::mouseMove(widget, point);
    QMouseEvent event(QEvent::MouseMove, point, widget->mapToGlobal(point), button, buttons, {});
    QApplication::sendEvent(widget, &event);
    QApplication::processEvents();
}

static void sendMouseRelease(QWidget *widget, const QPoint &point, Qt::MouseButton button = Qt::LeftButton)
{
    QMouseEvent event(QEvent::MouseButtonRelease, point, widget->mapToGlobal(point), button, {}, {});
    QApplication::sendEvent(widget, &event);
}

//交互测试
TEST_F(ut_alldayeventview, interactive_001)
{
    Stub stub;
    calendarDDialogExecStub(stub);
    QList<QGraphicsItem *> item = cAllDayEventWeekView->scene()->items();
    //模拟点击释放
    ASSERT_GT(item.size(), 0);
    QPoint itemPoint = cAllDayEventWeekView->mapFromScene(item.at(0)->scenePos());
    sendMousePress(cAllDayEventWeekView->viewport(), itemPoint);
    sendMouseRelease(cAllDayEventWeekView->viewport(), itemPoint);

    EXPECT_FALSE(cAllDayEventWeekView->m_press);
    EXPECT_EQ(cAllDayEventWeekView->m_DragStatus, CAllDayEventWeekView::NONE);
}

TEST_F(ut_alldayeventview, interactive_002)
{
    Stub stub;
    calendarDDialogExecStub(stub);
    QList<QGraphicsItem *> item = cAllDayEventWeekView->scene()->items();

    //模拟点击移动
    ASSERT_GT(item.size(), 0);
    QPoint itemPoint = cAllDayEventWeekView->mapFromScene(item.at(0)->scenePos());
    sendMousePress(cAllDayEventWeekView->viewport(), itemPoint);
    sendMouseMove(cAllDayEventWeekView->viewport(), cAllDayEventWeekView->viewport()->rect().center(), Qt::LeftButton, Qt::LeftButton);
    sendMouseRelease(cAllDayEventWeekView->viewport(), cAllDayEventWeekView->viewport()->rect().center());

    EXPECT_FALSE(cAllDayEventWeekView->m_press);
    EXPECT_EQ(cAllDayEventWeekView->m_DragStatus, CAllDayEventWeekView::NONE);
}

//slotContextMenu
TEST_F(ut_alldayeventview, slotContextMenu)
{
    Stub stub;
    calendarDDialogExecStub(stub);
    stub.set((QAction * (QMenu::*)(const QPoint &, QAction *)) ADDR(QMenu, exec), stub_exec);
    action = nullptr;
    QList<QGraphicsItem *> item = cAllDayEventWeekView->scene()->items();

    ASSERT_GT(item.size(), 0);
    CAllDayScheduleItem focusItem(QRectF(0, 0, 1, 1));
    QDateTime currentTime = QDateTime::currentDateTime();
    ScheduleDataInfo info;
    info.setType(2);
    info.setBeginDateTime(currentTime);
    info.setEndDateTime(currentTime.addSecs(60 * 60));
    info.setTitleName("uttest");
    CGraphicsScene *scent = qobject_cast<CGraphicsScene *>(cAllDayEventWeekView->scene());

    ASSERT_NE(scent, nullptr);

    bool update = false;
    QObject::connect(cAllDayEventWeekView, &CAllDayEventWeekView::signalsUpdateSchedule, [&]() {
        update = true;
    });
    calendarDDialogExecReturn = 1;
    action = cAllDayEventWeekView->m_editAction;
    cAllDayEventWeekView->slotContextMenu(&focusItem);
    EXPECT_TRUE(update);
}
