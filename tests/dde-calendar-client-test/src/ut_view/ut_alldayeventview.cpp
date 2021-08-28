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
TEST_F(ut_alldayeventview, MeetCreationConditions)
{
    QString begin = "2020-12-01 12:24:36";
    QDateTime date = QDateTime::fromString(begin, "yyyy-MM-dd hh:mm:ss");
    cAllDayEventWeekView->MeetCreationConditions(date);
}

//bool CAllDayEventWeekView::IsEqualtime(const QDateTime &timeFirst, const QDateTime &timeSecond)
TEST_F(ut_alldayeventview, IsEqualtime)
{
    QString begin = "2020-12-01 12:24:36";
    QDateTime begindate = QDateTime::fromString(begin, "yyyy-MM-dd hh:mm:ss");
    QString end = "2020-12-21 12:24:36";
    QDateTime enddate = QDateTime::fromString(end, "yyyy-MM-dd hh:mm:ss");

    bool getBool = cAllDayEventWeekView->IsEqualtime(begindate, enddate);
    assert(false == getBool);

    enddate = QDateTime::fromString(begin, "yyyy-MM-dd hh:mm:ss");
    getBool = cAllDayEventWeekView->IsEqualtime(begindate, enddate);
    assert(true == getBool);
}

//void CAllDayEventWeekView::setRange(int w, int h, QDate begindate, QDate enddate, int rightmagin)
TEST_F(ut_alldayeventview, setRange)
{
    int w = 3;
    int h = 2;
    QDate begindate(2020, 12, 01);
    QDate enddate(2020, 12, 21);
    int rightmagin = 2;
    cAllDayEventWeekView->setRange(w, h, begindate, enddate, rightmagin);
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
}


//void CAllDayEventWeekView::setInfo(const QVector<ScheduleDataInfo> &info)
TEST_F(ut_alldayeventview, setInfo)
{
    cAllDayEventWeekView->setInfo(getTestScheduleDataInfo());
}

//void CAllDayEventWeekView::slotDoubleEvent()
TEST_F(ut_alldayeventview, slotDoubleEvent)
{
    cAllDayEventWeekView->slotDoubleEvent();
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

    cAllDayEventWeekView->setDayData(vlistData);

    int w = 1000;
    int h = 900;
    QDate begindate(2020, 12, 01);
    QDate enddate(2020, 12, 21);
    int rightmagin = 2;
    cAllDayEventWeekView->setRange(w, h, begindate, enddate, rightmagin);

    int index = 0;
    bool average = true;
    cAllDayEventWeekView->createItemWidget(index, average);
    cAllDayEventWeekView->updateHeight();
    //setSelectSearchSchedule
    cAllDayEventWeekView->setSelectSearchSchedule(getTestScheduleDataInfo().at(1));
}

//void CAllDayEventWeekView::updateItemHeightByFontSize()
TEST_F(ut_alldayeventview, updateItemHeightByFontSize)
{
    cAllDayEventWeekView->updateItemHeightByFontSize();
}


//void CAllDayEventWeekView::upDateInfoShow(const DragStatus &status, const ScheduleDataInfo &info)
TEST_F(ut_alldayeventview, upDateInfoShow)
{
    cAllDayEventWeekView->setInfo(getTestScheduleDataInfo());
    cAllDayEventWeekView->upDateInfoShow(DragInfoGraphicsView::DragStatus::ChangeEnd, getTestScheduleDataInfo().at(1));
    cAllDayEventWeekView->upDateInfoShow(DragInfoGraphicsView::DragStatus::ChangeBegin, getTestScheduleDataInfo().at(1));
    cAllDayEventWeekView->upDateInfoShow(DragInfoGraphicsView::DragStatus::ChangeWhole, getTestScheduleDataInfo().at(1));
    cAllDayEventWeekView->upDateInfoShow(DragInfoGraphicsView::DragStatus::IsCreate, getTestScheduleDataInfo().at(1));
}

//
TEST_F(ut_alldayeventview, getPixmap)
{
    cAllDayEventWeekView->setFixedSize(500, 800);
    QPixmap pixmap(cAllDayEventWeekView->size());
    pixmap = cAllDayEventWeekView->grab();
}

//
TEST_F(ut_alldayeventview, eventTest)
{
    QTest::keyEvent(QTest::Press, cAllDayEventWeekView, Qt::Key::Key_Enter);
    cAllDayEventWeekView->setFixedSize(500, 100);
    QTest::mouseDClick(cAllDayEventWeekView, Qt::LeftButton, Qt::NoModifier, QPoint(200, 50));
}

//slotCreate
TEST_F(ut_alldayeventview, slotCreate)
{
    calendarDDialogExecReturn = 1;
    Stub stub;
    calendarDDialogExecStub(stub);
    cAllDayEventWeekView->slotCreate(QDateTime::currentDateTime());
}

//getDragScheduleInfoBeginTime
TEST_F(ut_alldayeventview, getDragScheduleInfoBeginTime)
{
    cAllDayEventWeekView->getDragScheduleInfoBeginTime(QDateTime::currentDateTime());
}

//changeEvent
TEST_F(ut_alldayeventview, changeEvent)
{
    QEvent event(QEvent::FontChange);
    QApplication::sendEvent(cAllDayEventWeekView, &event);
}

//mousePressEvent
TEST_F(ut_alldayeventview, mousePressEvent)
{
    QMouseEvent event(QEvent::MouseButtonPress, QPointF(32, 13), QPointF(646, 438), QPointF(646, 438),
                      Qt::LeftButton, Qt::LeftButton, Qt::NoModifier, Qt::MouseEventSynthesizedByQt);
    QApplication::sendEvent(cAllDayEventWeekView->viewport(), &event);
}

TEST_F(ut_alldayeventview, JudgeIsCreate)
{
    QPointF point(32, 13);
    cAllDayEventWeekView->JudgeIsCreate(point);
}

static QAction *action = nullptr;
QAction *stub_exec(const QPoint &pos, QAction *at = nullptr)
{
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
}

//MoveInfoProcess
TEST_F(ut_alldayeventview, MoveInfoProcess)
{
    ScheduleDataInfo info;
    QDateTime currentTime = QDateTime::currentDateTime();
    info.setBeginDateTime(currentTime);
    info.setEndDateTime(currentTime.addDays(1));
    info.setAllDay(true);
    cAllDayEventWeekView->MoveInfoProcess(info, QPointF(0, 0));
    info.setAllDay(false);
    cAllDayEventWeekView->MoveInfoProcess(info, QPointF(0, 0));
}

//getDragScheduleInfoEndTime
TEST_F(ut_alldayeventview, getDragScheduleInfoEndTime)
{
    cAllDayEventWeekView->getDragScheduleInfoEndTime(QDateTime::currentDateTime());
}

//slotUpdateScene
TEST_F(ut_alldayeventview, slotUpdateScene)
{
    cAllDayEventWeekView->slotUpdateScene();
}

TEST_F(ut_alldayeventview, updateInfo)
{
    cAllDayEventWeekView->updateInfo();
    cAllDayEventWeekView->m_DragStatus = DragInfoGraphicsView::IsCreate;
    cAllDayEventWeekView->updateInfo();
}

//mouseDoubleClickEvent
TEST_F(ut_alldayeventview, mouseDoubleClickEvent)
{
    Stub stub;
    calendarDDialogExecStub(stub);
    QTest::mouseDClick(cAllDayEventWeekView->viewport(), Qt::LeftButton);
}

//
TEST_F(ut_alldayeventview, setSceneRect)
{
    cAllDayEventWeekView->setSceneRect(20, 20, 1000, 1500);
    cAllDayEventWeekView->updateBackgroundShowItem();
}

//slotPosOnView
TEST_F(ut_alldayeventview, slotPosOnView)
{
    cAllDayEventWeekView->slotPosOnView(1);
}

//mouseReleaseEvent
TEST_F(ut_alldayeventview, mouseReleaseEvent)
{
    QMouseEvent event(QEvent::MouseButtonRelease, QPointF(32, 13), QPointF(646, 438), QPointF(646, 438),
                      Qt::RightButton, Qt::RightButton, Qt::NoModifier, Qt::MouseEventSynthesizedByQt);
    QApplication::sendEvent(cAllDayEventWeekView->viewport(), &event);
}

//mouseReleaseEvent
TEST_F(ut_alldayeventview, mouseReleaseEvent1)
{
    cAllDayEventWeekView->m_TouchBeginTime = QDateTime::currentDateTime().toMSecsSinceEpoch() - 10;
    QMouseEvent event(QEvent::MouseButtonRelease, QPointF(32, 13), QPointF(646, 438), QPointF(646, 438),
                      Qt::LeftButton, Qt::LeftButton, Qt::NoModifier, Qt::MouseEventSynthesizedByQt);
    QApplication::sendEvent(cAllDayEventWeekView->viewport(), &event);
}

//mouseMoveEvent
TEST_F(ut_alldayeventview, mouseMoveEvent)
{
    cAllDayEventWeekView->m_touchState = DragInfoGraphicsView::TS_PRESS;
    QTest::mouseMove(cAllDayEventWeekView->viewport());
}

//wheelEvent
TEST_F(ut_alldayeventview, wheelEvent)
{
    QEvent event(QEvent::Wheel);
    QApplication::sendEvent(cAllDayEventWeekView->viewport(), &event);
}

//contextMenuEvent
TEST_F(ut_alldayeventview, contextMenuEvent)
{
    //    QEvent event(QEvent::ContextMenu);

    Stub stub;
    stub.set((QAction * (QMenu::*)(const QPoint &, QAction *)) ADDR(QMenu, exec), stub_exec);
    calendarDDialogExecStub(stub);
    QList<QGraphicsItem *> item = cAllDayEventWeekView->scene()->items();
    //模拟右击

    QContextMenuEvent event(QContextMenuEvent::Mouse, QPoint(20, 20), QPoint(120, 120), Qt::NoModifier);
    QApplication::sendEvent(cAllDayEventWeekView->viewport(), &event);

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
TEST_F(ut_alldayeventview, interactive)
{
    Stub stub;
    calendarDDialogExecStub(stub);
    QList<QGraphicsItem *> item = cAllDayEventWeekView->scene()->items();
    //模拟点击释放
    if (item.size() > 0) {
        QPoint itemPoint = cAllDayEventWeekView->mapFromScene(item.at(0)->scenePos());
        sendMousePress(cAllDayEventWeekView->viewport(), itemPoint);
        sendMouseRelease(cAllDayEventWeekView->viewport(), itemPoint);
    }

    //模拟点击移动
    if (item.size() > 0) {
        QPoint itemPoint = cAllDayEventWeekView->mapFromScene(item.at(0)->scenePos());
        sendMousePress(cAllDayEventWeekView->viewport(), itemPoint);
        sendMouseMove(cAllDayEventWeekView->viewport(), cAllDayEventWeekView->viewport()->rect().center(), Qt::LeftButton, Qt::LeftButton);
        sendMouseRelease(cAllDayEventWeekView->viewport(), cAllDayEventWeekView->viewport()->rect().center());
    }
}

//slotContextMenu
TEST_F(ut_alldayeventview, slotContextMenu)
{
    Stub stub;
    calendarDDialogExecStub(stub);
    stub.set((QAction * (QMenu::*)(const QPoint &, QAction *)) ADDR(QMenu, exec), stub_exec);
    action = nullptr;
    QList<QGraphicsItem *> item = cAllDayEventWeekView->scene()->items();
    if (item.size() > 0) {
        CFocusItem *focusItem = dynamic_cast<CFocusItem *>(item.at(0));
        CGraphicsScene *scent = qobject_cast<CGraphicsScene *>(cAllDayEventWeekView->scene());
        if (scent && focusItem) {
            scent->signalContextMenu(focusItem);
        }
    }
}
