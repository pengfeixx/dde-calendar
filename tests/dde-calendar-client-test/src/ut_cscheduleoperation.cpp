/*
* Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
*
* Author:     chenhaifeng  <chenhaifeng@uniontech.com>
*
* Maintainer: chenhaifeng  <chenhaifeng@uniontech.com>
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
#include "ut_cscheduleoperation.h"

#include "cscheduledbus.h"
#include "dialog/dcalendarddialog.h"
#include "schedulectrldlg.h"
#include "dialog_stub.h"
#include "cscheduledbusstub.h"

#include <QSignalSpy>

ut_cscheduleoperation::ut_cscheduleoperation()
{
}

ut_cscheduleoperation::~ut_cscheduleoperation()
{
}



namespace ScheduleTestBtnNum {
static int button_num = 0;
}
int clickButton_stub(void *obj)
{
    Q_UNUSED(obj)
    return ScheduleTestBtnNum::button_num;
}

void ut_cscheduleoperation::SetUp()
{
    cscheduleDbusStub(stub);
}

void ut_cscheduleoperation::TearDown()
{
}

bool ut_changeRecurInfostub(const ScheduleDataInfo &newinfo, const ScheduleDataInfo &oldinfo)
{
    UpdateJob_titlename = oldinfo.getTitleName();
    return true;
}

TEST_F(ut_cscheduleoperation, createSchedule)
{
    ScheduleDataInfo info;
    bool ret = operation.createSchedule(info);
    ASSERT_TRUE(ret);
}

TEST_F(ut_cscheduleoperation, changeSchedule)
{
    calendarDDialogExecStub(stub);
    stub.set(ADDR(CScheduleCtrlDlg, clickButton), clickButton_stub);
    ScheduleDataInfo info;
    QDate current = QDate::currentDate();
    info.setBeginDateTime(QDateTime(current, QTime(0, 0, 0)));
    info.setEndDateTime(QDateTime(current, QTime(23, 59, 59)));
    info.setTitleName(tr("New Event"));
    info.setAllDay(true);
    info.setRemindData(RemindData(1, QTime(9, 0)));
    info.setID(0);
    info.setRecurID(0);

    ScheduleDataInfo newinfo = info;
    newinfo.setTitleName(tr("1"));

    newinfo.setAllDay(false);
    info.getRepetitionRule().setRuleId(RepetitionRule::RRule_NONE);
    ScheduleTestBtnNum::button_num = 0;
    operation.changeSchedule(newinfo, info);
    ASSERT_EQ(UpdateJob_titlename, "1");

    ScheduleTestBtnNum::button_num = 1;
    newinfo.setTitleName("2");
    operation.changeSchedule(newinfo, info);
    ASSERT_EQ(UpdateJob_titlename, "2");

    newinfo.setAllDay(true);
    newinfo.setTitleName("3");
    operation.changeSchedule(newinfo, info);
    ASSERT_EQ(UpdateJob_titlename, "3");

    QSignalSpy spy(&operation, SIGNAL(signalViewtransparentFrame(const int)));
    ScheduleTestBtnNum::button_num = 0;
    newinfo.getRepetitionRule().setRuleId(RepetitionRule::RRule_EVEDAY);
    bool ret = operation.changeSchedule(newinfo, info);
    ASSERT_EQ(spy.count(), 2);
    ASSERT_EQ(ret, false);

    ScheduleTestBtnNum::button_num = 1;
    newinfo.setTitleName(tr("4"));
    operation.changeSchedule(newinfo, info);
    ASSERT_EQ(UpdateJob_titlename, "4");
    ASSERT_EQ(spy.count(), 4);

    newinfo.setTitleName("5");
    info.getRepetitionRule().setRuleId(RepetitionRule::RRule_EVEDAY);
    stub.set(ADDR(CScheduleOperation, changeRecurInfo), ut_changeRecurInfostub);
    operation.changeSchedule(newinfo, info);
    ASSERT_EQ(UpdateJob_titlename, "5");
}

TEST_F(ut_cscheduleoperation, deleteSchedule)
{
    calendarDDialogExecStub(stub);
    stub.set(ADDR(CScheduleCtrlDlg, clickButton), clickButton_stub);
    ScheduleDataInfo info;
    QDate current = QDate::currentDate();
    info.setBeginDateTime(QDateTime(current, QTime(0, 0, 0)));
    info.setEndDateTime(QDateTime(current, QTime(23, 59, 59)));
    info.setTitleName(tr("New Event"));
    info.setAllDay(true);
    info.setRemindData(RemindData(1, QTime(9, 0)));
    info.setID(0);
    info.setRecurID(0);
    ScheduleTestBtnNum::button_num = 0;
    bool ret = operation.deleteSchedule(info);
    ASSERT_FALSE(ret);
    ScheduleTestBtnNum::button_num = 1;
    ret = operation.deleteSchedule(info);
    ASSERT_TRUE(ret);

    //删除重复日程
    info.getRepetitionRule().setRuleId(RepetitionRule::RRule_EVEDAY);
    ScheduleTestBtnNum::button_num = 0;
    ret = operation.deleteSchedule(info);
    ASSERT_FALSE(ret);
    ScheduleTestBtnNum::button_num = 1;
    ret = operation.deleteSchedule(info);
    ASSERT_TRUE(ret);
    ScheduleTestBtnNum::button_num = 2;
    ret = operation.deleteSchedule(info);
    ASSERT_TRUE(ret);

    info.setRecurID(2);
    ScheduleTestBtnNum::button_num = 0;
    ret = operation.deleteSchedule(info);
    ASSERT_FALSE(ret);
    ScheduleTestBtnNum::button_num = 1;
    ret = operation.deleteSchedule(info);
    ASSERT_TRUE(ret);
    ScheduleTestBtnNum::button_num = 2;
    operation.deleteSchedule(info);
    ASSERT_TRUE(ret);
}

TEST_F(ut_cscheduleoperation, queryScheduleStr)
{
    QDateTime currenttime = QDateTime::currentDateTime();
    QString str = operation.queryScheduleStr("", currenttime, currenttime);
    QString datestr = currenttime.toString("yyyy-MM-dd");
    ASSERT_TRUE(str.contains(datestr));
}

TEST_F(ut_cscheduleoperation, deleteOnlyInfo)
{
    ScheduleDataInfo info;
    info.setID(123);
    operation.deleteOnlyInfo(info);
    ASSERT_EQ(UpdateJob_titlename, "123");
}
