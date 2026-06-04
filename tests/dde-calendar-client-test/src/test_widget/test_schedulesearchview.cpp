// SPDX-FileCopyrightText: 2019 - 2026 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "test_schedulesearchview.h"
#include "../third-party_stub/stub.h"
#include "../third-party_stub/addr_pri.h"
#include "dataManage/schedulemanager.h"
#include "constants.h"
#include "../testscheduledata.h"
#include "../dialog_stub.h"
#include <QContextMenuEvent>

DSchedule::List getScheduleDInfo()
{
    DSchedule::List scheduleDate;
    QDateTime currentDateTime = QDateTime::currentDateTime();

    DSchedule::Ptr schedule1 = DSchedule::Ptr(new DSchedule());
    schedule1->setUid("1");
    schedule1->setDtStart(currentDateTime);
    schedule1->setDtEnd(currentDateTime.addSecs(60 * 60));
    schedule1->setSummary("scheduleOne");
    schedule1->setAllDay(true);
    schedule1->setScheduleTypeID("1");

    DSchedule::Ptr schedule2 = DSchedule::Ptr(new DSchedule());
    schedule2->setUid("2");
    schedule2->setDtStart(currentDateTime.addDays(1));
    schedule2->setDtEnd(currentDateTime.addDays(1).addSecs(60 * 60));
    schedule2->setSummary("scheduleTwo");
    schedule2->setAllDay(true);
    schedule2->setScheduleTypeID("2");

    DSchedule::Ptr schedule3 = DSchedule::Ptr(new DSchedule());
    schedule3->setUid("3");
    schedule3->setDtStart(currentDateTime.addDays(2));
    schedule3->setDtEnd(currentDateTime.addDays(2).addSecs(60 * 60));
    schedule3->setSummary("scheduleThree");
    schedule3->setAllDay(false);
    schedule3->setScheduleTypeID("3");

    DSchedule::Ptr schedule4 = DSchedule::Ptr(new DSchedule());
    schedule4->setUid("4");
    schedule4->setDtStart(currentDateTime.addDays(3));
    schedule4->setDtEnd(currentDateTime.addDays(3).addSecs(60 * 60));
    schedule4->setSummary("scheduleFour");
    schedule4->setAllDay(false);
    schedule4->setScheduleTypeID("1");

    DSchedule::Ptr schedule5 = DSchedule::Ptr(new DSchedule());
    schedule5->setUid("5");
    schedule5->setDtStart(currentDateTime.addDays(4));
    schedule5->setDtEnd(currentDateTime.addDays(4).addSecs(60 * 60));
    schedule5->setSummary("scheduleFive");
    schedule5->setAllDay(false);
    schedule5->setScheduleTypeID("2");

    DSchedule::Ptr scheduleFes = DSchedule::Ptr(new DSchedule());
    scheduleFes->setUid("6");
    scheduleFes->setDtStart(currentDateTime.addDays(5));
    scheduleFes->setDtEnd(currentDateTime.addDays(5).addSecs(60 * 60));
    scheduleFes->setSummary("scheduleFestival");
    scheduleFes->setAllDay(true);
    scheduleFes->setScheduleTypeID("4");

    scheduleDate.append(schedule1);
    scheduleDate.append(schedule2);
    scheduleDate.append(schedule3);
    scheduleDate.append(schedule4);
    scheduleDate.append(schedule5);
    scheduleDate.append(scheduleFes);
    return scheduleDate;
}

QMap<QDate, DSchedule::List> getMapScheduleDInfo(int getDays)
{
    QDate currentDate = QDate::currentDate();
    DSchedule::List scheduleInfo;
    QMap<QDate, DSchedule::List> scheduleDateInof;
    switch (getDays) {
    case 0: {
        scheduleInfo.append(getScheduleDInfo().at(0));
        scheduleDateInof[currentDate] = scheduleInfo;
    } break;
    case 1: {
        scheduleInfo.append(getScheduleDInfo().at(1));
        scheduleDateInof[currentDate.addDays(1)] = scheduleInfo;
    } break;
    case 2: {
        scheduleInfo.append(getScheduleDInfo().at(2));
        scheduleDateInof[currentDate.addDays(2)] = scheduleInfo;
    } break;
    default: {
        scheduleInfo.append(getScheduleDInfo().at(3));
        scheduleDateInof[currentDate.addDays(3)] = scheduleInfo;
        scheduleInfo.append(getScheduleDInfo().at(4));
        scheduleDateInof[currentDate.addDays(4)] = scheduleInfo;
        scheduleInfo.append(getScheduleDInfo().at(5));
        scheduleDateInof[currentDate.addDays(5)] = scheduleInfo;
    } break;
    }
    return scheduleDateInof;
}

static QAction* schedulesearchview_stub_QMenu_exec()
{
    return nullptr;
}

test_schedulesearchview::test_schedulesearchview()
{
}

test_schedulesearchview::~test_schedulesearchview()
{
}

void test_schedulesearchview::SetUp()
{
    mScheduleSearchView = new CScheduleSearchView();
    mScheduleSearchDateItem = new CScheduleSearchDateItem();
    mScheduleListWidget = new CScheduleListWidget();
    mScheduleSearchItem = new CScheduleSearchItem();
}

void test_schedulesearchview::TearDown()
{
    delete mScheduleSearchView;
    mScheduleSearchView = nullptr;
    delete mScheduleSearchDateItem;
    mScheduleSearchDateItem = nullptr;
    delete mScheduleListWidget;
    mScheduleListWidget = nullptr;
    delete mScheduleSearchItem;
    mScheduleSearchItem = nullptr;
}

//void CScheduleSearchView::setTheMe(int type)
TEST_F(test_schedulesearchview, setTheMe)
{
    int type = 1;
    mScheduleSearchView->setTheMe(type);

    type = 2;
    mScheduleSearchView->setTheMe(type);
}

//void CScheduleSearchView::clearSearch()
TEST_F(test_schedulesearchview, clearSearch)
{
    DSchedule::Ptr schedule1 = DSchedule::Ptr(new DSchedule());
    schedule1->setUid("1");
    schedule1->setDtStart(QDateTime(QDate(2021, 1, 1), QTime(0, 0, 0)));
    schedule1->setDtEnd(QDateTime(QDate(2021, 1, 2), QTime(23, 59, 59)));
    schedule1->setSummary("schedule test one");
    schedule1->setAllDay(true);
    mScheduleSearchView->createItemWidget(schedule1, QDate(2021, 1, 1), 1);

    mScheduleSearchView->clearSearch();
}

//void CScheduleSearchView::setMaxWidth(const int w)
TEST_F(test_schedulesearchview, setMacWidth)
{
    mScheduleSearchView->setMaxWidth(44);
}

//void CScheduleSearchView::slotsetSearch()
TEST_F(test_schedulesearchview, slotsetSearch)
{
    //    mScheduleSearchView->slotsetSearch("jie");
}

//void CScheduleSearchView::createItemWidget(DSchedule::Ptr info, QDate date, int rtype)
TEST_F(test_schedulesearchview, createItemWidget)
{
    DSchedule::Ptr scheduleinof = getScheduleDInfo().first();
    mScheduleSearchView->createItemWidget(scheduleinof, QDate::currentDate(), 3);
}

//QListWidgetItem *CScheduleSearchView::createItemWidget(QDate date)
TEST_F(test_schedulesearchview, createItemWidgetDate)
{
    mScheduleSearchView->createItemWidget(QDate::currentDate());
}

//void CScheduleSearchView::slotSelectSchedule(const DSchedule::Ptr &scheduleInfo)
TEST_F(test_schedulesearchview, slotSelectSchedule)
{
    DSchedule::Ptr scheduleinof = getScheduleDInfo().first();
    mScheduleSearchView->slotSelectSchedule(scheduleinof);
}

//void CScheduleSearchView::updateSearch()
TEST_F(test_schedulesearchview, updateSearch)
{
    mScheduleSearchView->updateSearch();
}

//void CScheduleSearchDateItem::setBackgroundColor(QColor color1)
TEST_F(test_schedulesearchview, setBachgroundColor)
{
    QColor color1(240, 100, 100);
    mScheduleSearchDateItem->setBackgroundColor(color1);
}

//void CScheduleSearchDateItem::setText(QColor tcolor, QFont font)
TEST_F(test_schedulesearchview, setText)
{
    QColor color(240, 100, 100);
    QFont font;
    font.setWeight(QFont::Medium);
    font.setPixelSize(DDECalendar::FontSizeTwelve);
    mScheduleSearchDateItem->setText(color, font);
}

//void CScheduleSearchDateItem::setDate(QDate date)
TEST_F(test_schedulesearchview, setDate)
{
    mScheduleSearchDateItem->setDate(QDate::currentDate());
}

//void CScheduleSearchItem::setBackgroundColor(QColor color1)
TEST_F(test_schedulesearchview, setBackGroundColor)
{
    QColor color(240, 100, 100);
    mScheduleSearchItem->setBackgroundColor(color);
}

//void CScheduleSearchItem::setText(QColor tcolor, QFont font)
TEST_F(test_schedulesearchview, setItemText)
{
    QColor color(240, 100, 100);
    QFont font;
    font.setWeight(QFont::Medium);
    font.setPixelSize(DDECalendar::FontSizeTwelve);
    mScheduleSearchItem->setText(color, font);
}

//void CScheduleSearchItem::setTimeC(QColor tcolor, QFont font)
TEST_F(test_schedulesearchview, setTimeC)
{
    QColor color(240, 100, 100);
    QFont font;
    font.setWeight(QFont::Medium);
    font.setPixelSize(DDECalendar::FontSizeTwelve);
    mScheduleSearchItem->setTimeC(color, font);
}

//void CScheduleSearchItem::setData(DSchedule::Ptr vScheduleInfo, QDate date)
TEST_F(test_schedulesearchview, setItemDate)
{
    DSchedule::Ptr scheduleinfo = getScheduleDInfo().first();
    mScheduleSearchItem->setData(scheduleinfo, QDate::currentDate());
}

//void CScheduleSearchItem::setRoundtype(int rtype)
TEST_F(test_schedulesearchview, setRoundtype)
{
    mScheduleSearchItem->setRoundtype(3);
    mScheduleSearchItem->setRoundtype(2);
}

//void CScheduleSearchItem::setTheMe(int type)
TEST_F(test_schedulesearchview, setItemTheMe)
{
    mScheduleSearchItem->setTheMe(1);
    mScheduleSearchItem->setTheMe(2);
}

//void CScheduleSearchItem::slotEdit()
TEST_F(test_schedulesearchview, slotEdit_01)
{
    Stub stub;
    calendarDDialogExecStub(stub);
    DSchedule::Ptr scheduleinfo = getScheduleDInfo().first();
    CScheduleSearchItem item;
    item.setData(scheduleinfo, QDate::currentDate());
    item.slotEdit();
}

//void CScheduleSearchItem::slotDelete()
TEST_F(test_schedulesearchview, slotDelete_01)
{
    Stub stub;
    calendarDDialogExecStub(stub);
    DSchedule::Ptr scheduleinfo = getScheduleDInfo().first();
    CScheduleSearchItem item;
    item.setData(scheduleinfo, QDate::currentDate());
    item.slotDelete();
}

TEST_F(test_schedulesearchview, slotTimeFormatChanged_01)
{
    mScheduleSearchItem->slotTimeFormatChanged(1);
    EXPECT_EQ(mScheduleSearchItem->m_timeFormat, "hh:mm");
}

TEST_F(test_schedulesearchview, slotTimeFormatChanged_02)
{
    mScheduleSearchItem->slotTimeFormatChanged(0);
    EXPECT_EQ(mScheduleSearchItem->m_timeFormat, "h:mm");
}

TEST_F(test_schedulesearchview, slotSchotCutClicked_01)
{
    Stub stub;
    stub.set((QAction*(QMenu::*)(const QPoint &, QAction *))ADDR(QMenu, exec), schedulesearchview_stub_QMenu_exec);
    CScheduleSearchItem item;
    item.slotSchotCutClicked();
}

TEST_F(test_schedulesearchview, contextMenuEvent_01)
{
    Stub stub;
    stub.set((QAction*(QMenu::*)(const QPoint &, QAction *))ADDR(QMenu, exec), schedulesearchview_stub_QMenu_exec);
    CScheduleSearchItem item;

    QContextMenuEvent event(QContextMenuEvent::Mouse, QPoint());
    item.contextMenuEvent(&event);
}

TEST_F(test_schedulesearchview, mouseDoubleClickEvent_01)
{
    Stub stub;
    calendarDDialogExecStub(stub);
    CScheduleSearchItem item;

    QMouseEvent event(QEvent::MouseButtonDblClick, QPointF(), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    item.mouseDoubleClickEvent(&event);
}

TEST_F(test_schedulesearchview, mousePressEvent_01)
{
    CScheduleSearchItem item;
    QMouseEvent event(QEvent::MouseButtonDblClick, QPointF(), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    item.mousePressEvent(&event);
    EXPECT_FALSE(item.m_tabFocus);
}

TEST_F(test_schedulesearchview, mouseReleaseEvent_01)
{
    CScheduleSearchItem item;
    QMouseEvent event(QEvent::MouseButtonDblClick, QPointF(), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    item.mouseReleaseEvent(&event);
    EXPECT_EQ(item.m_mouseStatus, CScheduleSearchItem::M_HOVER);
}

TEST_F(test_schedulesearchview, enterEvent_01)
{
    CScheduleSearchItem item;
    QEnterEvent event(QPointF(0, 0), QPointF(0, 0), QPointF(0, 0));
    item.enterEvent(&event);
    EXPECT_EQ(item.m_mouseStatus, CScheduleSearchItem::M_HOVER);
}

TEST_F(test_schedulesearchview, focusOutEvent_01)
{
    CScheduleSearchItem item;
    QFocusEvent event(QEvent::FocusOut, Qt::TabFocusReason);
    item.focusOutEvent(&event);
}

TEST_F(test_schedulesearchview, focusInEvent_01)
{
    CScheduleSearchItem item;
    QFocusEvent event(QEvent::FocusIn, Qt::TabFocusReason);
    item.focusInEvent(&event);
}

TEST_F(test_schedulesearchview, keyPressEvent_01)
{
    Stub stub;
    calendarDDialogExecStub(stub);
    CScheduleSearchItem item;
    QKeyEvent event(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);
    item.keyPressEvent(&event);
}

TEST_F(test_schedulesearchview, keyPressEvent_02)
{
    CScheduleSearchItem item;
    QKeyEvent event(QEvent::KeyPress, Qt::Key_M, Qt::AltModifier);
    item.keyPressEvent(&event);
}

//const DSchedule::Ptr &getData() const
TEST_F(test_schedulesearchview, getDate)
{
    mScheduleSearchItem->getData();
}

QMap<QDate, DSchedule::List> stub_getAllSearchedScheduleMap(void *obj)
{
    Q_UNUSED(obj)
    QMap<QDate, DSchedule::List> searchScheduleInfo;
    searchScheduleInfo[QDate::currentDate()] = TestDataInfo::getScheduleItemDInfo();
    return searchScheduleInfo;
}

//
TEST_F(test_schedulesearchview, getPixmap)
{
    Stub stub;

    stub.set((QMap<QDate, DSchedule::List>(ScheduleManager::*)())ADDR(ScheduleManager, getAllSearchedScheduleMap), stub_getAllSearchedScheduleMap);

    mScheduleSearchView->slotsetSearch("xjrc");
    mScheduleSearchView->setFixedSize(300, 800);
    QPixmap pixmap(mScheduleListWidget->size());
    pixmap = mScheduleSearchView->grab();
}
