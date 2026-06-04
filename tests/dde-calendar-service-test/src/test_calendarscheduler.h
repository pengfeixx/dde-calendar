// SPDX-FileCopyrightText: 2019 - 2026 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef TEST_CALENDARSCHEDULER_H
#define TEST_CALENDARSCHEDULER_H

#include "calendarDataManager/daccountmodule.h"
#include <QObject>
#include <gtest/gtest.h>

class test_calendarscheduler: public::testing::Test
{
public:
    test_calendarscheduler();

    virtual void SetUp()
    {
        mCalendar = new DAccountModule(DAccount::Ptr());
    }

    virtual void TearDown()
    {
        delete mCalendar;
        mCalendar = nullptr;
    }
protected:
    DAccountModule *mCalendar = nullptr;
};

#endif // TEST_CALENDARSCHEDULER_H
