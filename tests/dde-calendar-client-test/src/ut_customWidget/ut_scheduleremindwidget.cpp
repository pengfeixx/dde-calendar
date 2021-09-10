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
#include "ut_scheduleremindwidget.h"

ut_scheduleremindwidget::ut_scheduleremindwidget()
{
}

void ut_scheduleremindwidget::SetUp()
{
    mScheduleRemindWidget = new ScheduleRemindWidget();
    mCenterWidget = new CenterWidget();
}

void ut_scheduleremindwidget::TearDown()
{
    delete mScheduleRemindWidget;
    mScheduleRemindWidget =  nullptr;
    delete mCenterWidget;
    mCenterWidget = nullptr;
}

QVector<ScheduleDataInfo> getScheduleRemindData()
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
    schedule2.setAllDay(false);
    schedule2.setType(2);
    schedule2.setRecurID(0);

    QVector<ScheduleDataInfo> scheduleList{};
    scheduleList.append(schedule1);
    scheduleList.append(schedule2);
    return scheduleList;
}

//void SchecduleRemindWidget::setData(const ScheduleDataInfo &vScheduleInfo, const CSchedulesColor &gcolor)
TEST_F(ut_scheduleremindwidget, setData)
{
    CSchedulesColor gdcolor = CScheduleDataManage::getScheduleDataManage()->getScheduleColorByType(2);
    mScheduleRemindWidget->setData(getScheduleRemindData().first(), gdcolor);
    EXPECT_EQ(mScheduleRemindWidget->gdcolor.dotColor, gdcolor.dotColor);
    EXPECT_EQ(mScheduleRemindWidget->m_ScheduleInfo, getScheduleRemindData().first());
}

//void SchecduleRemindWidget::setDirection(DArrowRectangle::ArrowDirection value)
TEST_F(ut_scheduleremindwidget, setdirection)
{
    mScheduleRemindWidget->setDirection(DArrowRectangle::ArrowDirection::ArrowRight);
    EXPECT_EQ(mScheduleRemindWidget->arrowDirection(), DArrowRectangle::ArrowDirection::ArrowRight);
}

//void CenterWidget::setData(const ScheduleDataInfo &vScheduleInfo, const CSchedulesColor &gcolor)
TEST_F(ut_scheduleremindwidget, setDate)
{
    CSchedulesColor gdcolor = CScheduleDataManage::getScheduleDataManage()->getScheduleColorByType(2);
    mCenterWidget->setData(getScheduleRemindData().first(), gdcolor);
    EXPECT_EQ(mCenterWidget->gdcolor.dotColor, gdcolor.dotColor);
    EXPECT_EQ(mCenterWidget->m_ScheduleInfo, getScheduleRemindData().first());
}

//void CenterWidget::setTheMe(const int type)
TEST_F(ut_scheduleremindwidget, setTheMe_001)
{
    mCenterWidget->setTheMe(2);
    QColor timeColor("#C0C6D4");
    timeColor.setAlphaF(0.7);
    EXPECT_EQ(mCenterWidget->timeColor, timeColor);
}

TEST_F(ut_scheduleremindwidget, setTheMe_002)
{
    mCenterWidget->setTheMe(1);
    QColor timeColor("#414D68");
    timeColor.setAlphaF(0.7);
    EXPECT_EQ(mCenterWidget->timeColor, timeColor);
}

//getPixmap
TEST_F(ut_scheduleremindwidget, getPixmap)
{
    mCenterWidget->setFixedSize(800, 500);
    QPixmap pixmap(mCenterWidget->size());
    mCenterWidget->render(&pixmap);
    EXPECT_EQ(pixmap.size(), mCenterWidget->size());
}
