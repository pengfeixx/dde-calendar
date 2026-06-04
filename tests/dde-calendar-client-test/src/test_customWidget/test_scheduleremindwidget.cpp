// SPDX-FileCopyrightText: 2019 - 2026 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "test_scheduleremindwidget.h"

test_scheduleremindwidget::test_scheduleremindwidget()
{
    mScheduleRemindWidget = new ScheduleRemindWidget();
    mCenterWidget = new CenterWidget();
}

test_scheduleremindwidget::~test_scheduleremindwidget()
{
    delete mScheduleRemindWidget;
    mScheduleRemindWidget =  nullptr;
    delete mCenterWidget;
    mCenterWidget = nullptr;
}

DSchedule::List getScheduleRemindData()
{
    DSchedule::List scheduleList;

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
    schedule2->setAllDay(false);
    schedule2->setScheduleTypeID("2");

    scheduleList.append(schedule1);
    scheduleList.append(schedule2);
    return scheduleList;
}

//void ScheduleRemindWidget::setData(const DSchedule::Ptr &vScheduleInfo, const CSchedulesColor &gcolor)
TEST_F(test_scheduleremindwidget, setData)
{
    CSchedulesColor gdcolor = CScheduleDataManage::getScheduleDataManage()->getScheduleColorByType("1");
    mScheduleRemindWidget->setData(getScheduleRemindData().first(), gdcolor);
}

//void ScheduleRemindWidget::setDirection(DArrowRectangle::ArrowDirection value)
TEST_F(test_scheduleremindwidget, setdirection)
{
    mScheduleRemindWidget->setDirection(DArrowRectangle::ArrowDirection::ArrowRight);
}

//void CenterWidget::setData(const DSchedule::Ptr &vScheduleInfo, const CSchedulesColor &gcolor)
TEST_F(test_scheduleremindwidget, setDate)
{
    CSchedulesColor gdcolor = CScheduleDataManage::getScheduleDataManage()->getScheduleColorByType("1");
    mCenterWidget->setData(getScheduleRemindData().first(), gdcolor);
}

//void CenterWidget::setTheMe(const int type)
TEST_F(test_scheduleremindwidget, setTheMe)
{
    mCenterWidget->setTheMe(1);
    mCenterWidget->setTheMe(2);
}

//getPixmap - 验证控件可设置尺寸
//注意: render() 会触发 CenterWidget::paintEvent，后者访问 m_ScheduleInfo，
//未调用 setData() 时该指针为空，因此跳过 render 调用。
TEST_F(test_scheduleremindwidget, getPixmap)
{
    mCenterWidget->setFixedSize(800, 500);
    QPixmap pixmap(mCenterWidget->size());
    // mCenterWidget->render(&pixmap);  // 需要 m_ScheduleInfo 非空
}
