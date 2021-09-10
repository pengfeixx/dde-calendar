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
#include "ut_myscheduleview.h"

#include "../dialog_stub.h"
#include "../cscheduledbusstub.h"

#include <DPalette>

#include <QEvent>
#include <QApplication>

QVector<ScheduleDataInfo> getScheduleViewData()
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
    schedule2.setAllDay(true);
    schedule2.setType(2);
    schedule2.setRecurID(0);

    QVector<ScheduleDataInfo> scheduleList{};
    scheduleList.append(schedule1);
    scheduleList.append(schedule2);
    return scheduleList;
}

ut_myscheduleview::ut_myscheduleview()
{
}

void ut_myscheduleview::SetUp()
{
    ScheduleDataInfo scheduleinfo = getScheduleViewData().first();
    mScheduleView = new CMyScheduleView(scheduleinfo);
}

void ut_myscheduleview::TearDown()
{
    delete mScheduleView;
    mScheduleView = nullptr;
}

//void CMyScheduleView::setLabelTextColor(const int type)
TEST_F(ut_myscheduleview, setLabelTextColor_001)
{
    DGUI_USE_NAMESPACE
    mScheduleView->setLabelTextColor(1);
    QColor titleColor = "#000000";
    titleColor.setAlphaF(0.9);
    EXPECT_EQ(titleColor, mScheduleView->m_Title->palette().color(DPalette::WindowText));
}

TEST_F(ut_myscheduleview, setLabelTextColor_002)
{
    DGUI_USE_NAMESPACE
    mScheduleView->setLabelTextColor(2);
    QColor titleColor = "#FFFFFF";
    titleColor.setAlphaF(0.9);
    EXPECT_EQ(titleColor, mScheduleView->m_Title->palette().color(DPalette::WindowText));
}

//FontChange
TEST_F(ut_myscheduleview, FontChange)
{
    QEvent event(QEvent::FontChange);
    EXPECT_TRUE(QApplication::sendEvent(mScheduleView, &event));
}

//slotBtClick
TEST_F(ut_myscheduleview, slotBtClick_001)
{
    Stub stub;
    cscheduleDbusStub(stub);
    calendarDDialogExecStub(stub);
    mScheduleView->slotBtClick(0, "tt");
    calendarDDialogExecReturn = 0;
    EXPECT_EQ(mScheduleView->exec(), 0);
}

TEST_F(ut_myscheduleview, slotBtClick_002)
{
    Stub stub;
    calendarDDialogExecStub(stub);
    mScheduleView->slotBtClick(1, "tt");
    calendarDDialogExecReturn = 1;
    EXPECT_EQ(mScheduleView->exec(), 1);
}
