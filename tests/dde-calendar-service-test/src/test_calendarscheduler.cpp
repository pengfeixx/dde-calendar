// SPDX-FileCopyrightText: 2019 - 2026 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "test_calendarscheduler.h"

test_calendarscheduler::test_calendarscheduler()
{

}

// Test constructor/destructor
TEST_F(test_calendarscheduler, Constructor)
{
    // DAccountModule is created in SetUp and destroyed in TearDown
    ASSERT_NE(mCalendar, nullptr);
}

TEST_F(test_calendarscheduler, getAccountInfo)
{
    mCalendar->getAccountInfo();
}

TEST_F(test_calendarscheduler, getExpand)
{
    mCalendar->getExpand();
}

TEST_F(test_calendarscheduler, setExpand)
{
    mCalendar->setExpand(true);
    mCalendar->setExpand(false);
}

TEST_F(test_calendarscheduler, getAccountState)
{
    mCalendar->getAccountState();
}

TEST_F(test_calendarscheduler, setAccountState)
{
    mCalendar->setAccountState(0);
}

TEST_F(test_calendarscheduler, getSyncState)
{
    mCalendar->getSyncState();
}

TEST_F(test_calendarscheduler, getSyncFreq)
{
    mCalendar->getSyncFreq();
}

TEST_F(test_calendarscheduler, setSyncFreq)
{
    mCalendar->setSyncFreq("0");
}

TEST_F(test_calendarscheduler, getScheduleTypeList)
{
    mCalendar->getScheduleTypeList();
}

TEST_F(test_calendarscheduler, getSysColors)
{
    mCalendar->getSysColors();
}

TEST_F(test_calendarscheduler, updateRemindSchedules)
{
    mCalendar->updateRemindSchedules(true);
    mCalendar->updateRemindSchedules(false);
}

TEST_F(test_calendarscheduler, notifyMsgHanding_01)
{
    mCalendar->notifyMsgHanding("1", 1);
}

TEST_F(test_calendarscheduler, notifyMsgHanding_02)
{
    for (int i = 0; i < 25; i++) {
        mCalendar->notifyMsgHanding("1", i);
    }
}

TEST_F(test_calendarscheduler, remindJob)
{
    mCalendar->remindJob("1");
}
