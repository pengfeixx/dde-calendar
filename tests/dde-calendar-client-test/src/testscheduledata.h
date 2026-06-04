// SPDX-FileCopyrightText: 2019 - 2026 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef TESTSCHEDULEDATA_H
#define TESTSCHEDULEDATA_H

#include "dschedule.h"

class TestScheduleData
{
public:
    TestScheduleData();
};

namespace TestDataInfo {
DSchedule::List getScheduleItemDInfo();
}

#endif // TESTSCHEDULEDATA_H
