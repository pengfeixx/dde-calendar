// SPDX-FileCopyrightText: 2019 - 2026 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "testscheduledata.h"

TestScheduleData::TestScheduleData()
{
}

DSchedule::List TestDataInfo::getScheduleItemDInfo()
{
    DSchedule::List scheduleDate;
    QDateTime currentDateTime = QDateTime::currentDateTime();

    DSchedule::Ptr schedule1 = DSchedule::Ptr(new DSchedule());
    schedule1->setUid("1");
    schedule1->setDtStart(currentDateTime);
    schedule1->setDtEnd(currentDateTime.addDays(1));
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
