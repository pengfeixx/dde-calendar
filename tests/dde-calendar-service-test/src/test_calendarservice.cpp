// SPDX-FileCopyrightText: 2019 - 2026 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "test_calendarservice.h"

test_calendarservice::test_calendarservice()
{

}

// Test constructor/destructor
TEST_F(test_calendarservice, Constructor)
{
    ASSERT_NE(mService, nullptr);
}

TEST_F(test_calendarservice, getAccountList)
{
    mService->getAccountList();
}

TEST_F(test_calendarservice, getCalendarGeneralSettings)
{
    mService->getCalendarGeneralSettings();
}

TEST_F(test_calendarservice, setCalendarGeneralSettings)
{
    mService->setCalendarGeneralSettings("{}");
}

TEST_F(test_calendarservice, getfirstDayOfWeek)
{
    mService->getfirstDayOfWeek();
}

TEST_F(test_calendarservice, setFirstDayOfWeek)
{
    mService->setFirstDayOfWeek(0);
    mService->setFirstDayOfWeek(1);
}

TEST_F(test_calendarservice, getTimeFormatType)
{
    mService->getTimeFormatType();
}

TEST_F(test_calendarservice, setTimeFormatType)
{
    mService->setTimeFormatType(0);
    mService->setTimeFormatType(1);
}

TEST_F(test_calendarservice, remindJob_01)
{
    mService->remindJob("account1", "alarm1");
}

TEST_F(test_calendarservice, updateRemindSchedules_01)
{
    mService->updateRemindSchedules(true);
    mService->updateRemindSchedules(false);
}

TEST_F(test_calendarservice, notifyMsgHanding_01)
{
    mService->notifyMsgHanding("account1", "alarm1", 1);
}

TEST_F(test_calendarservice, isSupportUid)
{
    mService->isSupportUid();
}

TEST_F(test_calendarservice, calendarOpen)
{
    mService->calendarOpen(true);
    mService->calendarOpen(false);
}
