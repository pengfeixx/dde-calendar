// SPDX-FileCopyrightText: 2019 - 2026 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "test_schedulerdatabase.h"

test_schedulerdatabase::test_schedulerdatabase()
{

}

// Test constructor/destructor
TEST_F(test_schedulerdatabase, Constructor)
{
    ASSERT_NE(mBase, nullptr);
}

TEST_F(test_schedulerdatabase, getScheduleTypeList)
{
    schedulerdatabase_next = false;
    mBase->getScheduleTypeList();
}

TEST_F(test_schedulerdatabase, getValidRemindJob)
{
    schedulerdatabase_next = false;
    mBase->getValidRemindJob();
}

TEST_F(test_schedulerdatabase, getRemindSchedule)
{
    schedulerdatabase_next = false;
    mBase->getRemindSchedule();
}

TEST_F(test_schedulerdatabase, getScheduleIDListByTypeID)
{
    schedulerdatabase_next = false;
    mBase->getScheduleIDListByTypeID("0");
}

TEST_F(test_schedulerdatabase, deleteSchedulesByScheduleTypeID)
{
    schedulerdatabase_next = false;
    mBase->deleteSchedulesByScheduleTypeID("0");
}

TEST_F(test_schedulerdatabase, scheduleTypeByUsed)
{
    schedulerdatabase_next = false;
    mBase->scheduleTypeByUsed("0");
}

TEST_F(test_schedulerdatabase, deleteScheduleTypeByID)
{
    schedulerdatabase_next = false;
    mBase->deleteScheduleTypeByID("0");
}

TEST_F(test_schedulerdatabase, getFestivalTypeID)
{
    schedulerdatabase_next = false;
    mBase->getFestivalTypeID();
}

TEST_F(test_schedulerdatabase, setDBPath_01)
{
    schedulerdatabase_next = false;
    mBase->setDBPath("123");
    EXPECT_EQ(mBase->getDBPath(), "123");
}
