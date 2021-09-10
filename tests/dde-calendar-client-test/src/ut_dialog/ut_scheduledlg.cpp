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
#include "ut_scheduledlg.h"

#include "../cscheduledbusstub.h"
#include "../dialog_stub.h"

#include <DPalette>

#include <QTest>

ut_scheduledlg::ut_scheduledlg()
{
}

void ut_scheduledlg::SetUp()
{
    mScheduleDlg = new CScheduleDlg(1);
}

void ut_scheduledlg::TearDown()
{
    delete mScheduleDlg;
    mScheduleDlg = nullptr;
}

QVector<ScheduleDataInfo> getScheduleDlgData()
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
//void CScheduleDlg::setData(const ScheduleDataInfo &info)
TEST_F(ut_scheduledlg, setData)
{
    mScheduleDlg->setData(getScheduleDlgData().first());
    EXPECT_EQ(mScheduleDlg->m_ScheduleDataInfo, getScheduleDlgData().first());
}

//void CScheduleDlg::setDate(const QDateTime &date)
TEST_F(ut_scheduledlg, setDate_001)
{
    QDateTime current(QDate::currentDate(), QTime(10, 10, 0));
    mScheduleDlg->setDate(current);
    QDateTime testTime(current.date(), QTime(10, 15, 0));
    EXPECT_EQ(testTime, mScheduleDlg->m_currentDate);
}

TEST_F(ut_scheduledlg, setDate_002)
{
    QDateTime current(QDate::currentDate(), QTime(10, 20, 0));
    mScheduleDlg->setDate(current);
    QDateTime testTime(current.date(), QTime(10, 30, 0));
    EXPECT_EQ(testTime, mScheduleDlg->m_currentDate);
}

TEST_F(ut_scheduledlg, setDate_003)
{
    QDateTime current(QDate::currentDate(), QTime(10, 35, 0));
    mScheduleDlg->setDate(current);
    QDateTime testTime(current.date(), QTime(10, 45, 0));
    EXPECT_EQ(testTime, mScheduleDlg->m_currentDate);
}

TEST_F(ut_scheduledlg, setDate_004)
{
    QDateTime current(QDate::currentDate(), QTime(10, 50, 0));
    mScheduleDlg->setDate(current);
    QDateTime testTime(current.date(), QTime(11, 0, 0));
    EXPECT_EQ(testTime, mScheduleDlg->m_currentDate);
}

//void CScheduleDlg::setAllDay(bool flag)
TEST_F(ut_scheduledlg, setAllDay)
{
    mScheduleDlg->setAllDay(true);
    EXPECT_TRUE(mScheduleDlg->m_allDayCheckbox->isChecked());
}

//bool CScheduleDlg::clickOkBtn()
TEST_F(ut_scheduledlg, clickOkBtn)
{
    Stub stub;
    cscheduleDbusStub(stub);
    mScheduleDlg->clickOkBtn();

    //begindatetime < enddatetime
    ScheduleDataInfo schedule;
    QDateTime currentDateTime = QDateTime::currentDateTime();
    schedule.setID(1);
    schedule.setBeginDateTime(currentDateTime);
    schedule.setEndDateTime(currentDateTime.addDays(-1));
    schedule.setTitleName("scheduleOne");
    schedule.setAllDay(true);
    schedule.setType(1);
    schedule.setRecurID(0);
    mScheduleDlg->setData(schedule);
    EXPECT_TRUE(mScheduleDlg->clickOkBtn());

    //
    mScheduleDlg->m_type = 1;
    schedule.setEndDateTime(currentDateTime.addDays(1));
    mScheduleDlg->setData(schedule);
    EXPECT_TRUE(mScheduleDlg->clickOkBtn());

    mScheduleDlg->m_rmindCombox->setCurrentIndex(3);
    EXPECT_TRUE(mScheduleDlg->clickOkBtn());

    mScheduleDlg->m_rmindCombox->setCurrentIndex(4);
    EXPECT_TRUE(mScheduleDlg->clickOkBtn());

    mScheduleDlg->m_rmindCombox->setCurrentIndex(5);
    EXPECT_TRUE(mScheduleDlg->clickOkBtn());

    schedule.setAllDay(false);
    mScheduleDlg->setData(schedule);
    EXPECT_TRUE(mScheduleDlg->clickOkBtn());

    mScheduleDlg->m_rmindCombox->setCurrentIndex(3);
    EXPECT_TRUE(mScheduleDlg->clickOkBtn());

    mScheduleDlg->m_rmindCombox->setCurrentIndex(4);
    EXPECT_TRUE(mScheduleDlg->clickOkBtn());

    mScheduleDlg->m_rmindCombox->setCurrentIndex(5);
    EXPECT_TRUE(mScheduleDlg->clickOkBtn());
    mScheduleDlg->m_endrepeatCombox->setCurrentIndex(2);
    EXPECT_TRUE(mScheduleDlg->clickOkBtn());

    mScheduleDlg->m_endrepeatCombox->setCurrentIndex(3);
    EXPECT_TRUE(mScheduleDlg->clickOkBtn());
}

//void CScheduleDlg::slotBtClick(int buttonIndex, QString buttonName)
TEST_F(ut_scheduledlg, slotBtClick_001)
{
    Stub stub;
    cscheduleDbusStub(stub);
    mScheduleDlg->slotBtClick(0, "ok");
    EXPECT_FALSE(mScheduleDlg->m_setAccept);
}

TEST_F(ut_scheduledlg, slotBtClick_002)
{
    Stub stub;
    cscheduleDbusStub(stub);
    mScheduleDlg->slotBtClick(1, "ok");
    EXPECT_TRUE(mScheduleDlg->m_setAccept);
}

TEST_F(ut_scheduledlg, slotBtClick_003)
{
    Stub stub;
    cscheduleDbusStub(stub);
    mScheduleDlg->slotBtClick(2, "ok");
    EXPECT_FALSE(mScheduleDlg->m_setAccept);
}

//void CScheduleDlg::slotTextChange()
TEST_F(ut_scheduledlg, slotTextChange)
{
    mScheduleDlg->slotTextChange();
    EXPECT_EQ(mScheduleDlg->m_textEdit->toPlainText(), "");
}

//void CScheduleDlg::slotendrepeatTextchange()
TEST_F(ut_scheduledlg, slotendrepeatTextchange_001)
{
    mScheduleDlg->m_endrepeattimes->setText("10");
    mScheduleDlg->slotendrepeatTextchange();
    EXPECT_TRUE(mScheduleDlg->getButton(1)->isEnabled());
}

TEST_F(ut_scheduledlg, slotendrepeatTextchange_002)
{
    mScheduleDlg->m_endrepeattimes->setText("");
    mScheduleDlg->slotendrepeatTextchange();
    EXPECT_FALSE(mScheduleDlg->getButton(1)->isEnabled());
}

//void CScheduleDlg::slotBDateEidtInfo(const QDate &date)
TEST_F(ut_scheduledlg, slotBDateEidtInfo)
{
    QDate current = QDate::currentDate();
    mScheduleDlg->slotBDateEidtInfo(current);
    EXPECT_EQ(current, mScheduleDlg->m_beginDateEdit->date());
    EXPECT_EQ(current, mScheduleDlg->m_endRepeatDate->minimumDate());
    EXPECT_EQ(current, mScheduleDlg->m_endDateEdit->minimumDate());
}

//void CScheduleDlg::slotallDayStateChanged(int state)
TEST_F(ut_scheduledlg, slotallDayStateCheanged_001)
{
    mScheduleDlg->slotallDayStateChanged(0);
    EXPECT_EQ(mScheduleDlg->m_rmindCombox->count(), 8);
}

TEST_F(ut_scheduledlg, slotallDayStateCheanged_002)
{
    mScheduleDlg->slotallDayStateChanged(1);
    EXPECT_EQ(mScheduleDlg->m_rmindCombox->count(), 5);
}

//void CScheduleDlg::slotbRpeatactivated(int index)
TEST_F(ut_scheduledlg, slotbRpearactivated_001)
{
    mScheduleDlg->slotbRpeatactivated(0);
    EXPECT_EQ(mScheduleDlg->size(), QSize(438, 470));
    EXPECT_FALSE(mScheduleDlg->m_endrepeatWidget->isVisible());
}

TEST_F(ut_scheduledlg, slotbRpearactivated_002)
{
    mScheduleDlg->slotbRpeatactivated(1);
    EXPECT_EQ(mScheduleDlg->size(), QSize(438, 506));
    EXPECT_FALSE(mScheduleDlg->m_endrepeatWidget->isVisible());
}

//void CScheduleDlg::sloteRpeatactivated(int index)
TEST_F(ut_scheduledlg, sloteRpearactivated_001)
{
    mScheduleDlg->sloteRpeatactivated(0);
    EXPECT_TRUE(mScheduleDlg->getButton(1)->isEnabled());
    EXPECT_FALSE(mScheduleDlg->m_endrepeattimesWidget->isVisible());
    EXPECT_FALSE(mScheduleDlg->m_endRepeatDate->isVisible());
}

TEST_F(ut_scheduledlg, sloteRpearactivated_002)
{
    mScheduleDlg->sloteRpeatactivated(1);
    EXPECT_TRUE(mScheduleDlg->getButton(1)->isEnabled());
    EXPECT_FALSE(mScheduleDlg->m_endrepeattimesWidget->isVisible());
    EXPECT_FALSE(mScheduleDlg->m_endRepeatDate->isVisible());
}

TEST_F(ut_scheduledlg, sloteRpearactivated_003)
{
    mScheduleDlg->sloteRpeatactivated(2);
    EXPECT_TRUE(mScheduleDlg->getButton(1)->isEnabled());
    EXPECT_FALSE(mScheduleDlg->m_endrepeattimesWidget->isVisible());
    EXPECT_FALSE(mScheduleDlg->m_endRepeatDate->isVisible());
}

//void CScheduleDlg::setTheMe(const int type)
TEST_F(ut_scheduledlg, setTheMe_001)
{
    DGUI_USE_NAMESPACE
    mScheduleDlg->setTheMe(1);
    QColor color("#414D68");
    EXPECT_EQ(color, mScheduleDlg->m_textEdit->palette().color(DPalette::Text));
}

TEST_F(ut_scheduledlg, setTheMe_002)
{
    DGUI_USE_NAMESPACE
    mScheduleDlg->setTheMe(2);
    QColor color("#C0C6D4");
    EXPECT_EQ(color, mScheduleDlg->m_textEdit->palette().color(DPalette::Text));
}

//
TEST_F(ut_scheduledlg, exec)
{
    Stub stub;
    calendarDDialogExecStub(stub);
    calendarDDialogExecReturn = 0;
    EXPECT_EQ(mScheduleDlg->exec(), 0);
}

//updateDateTimeFormat
TEST_F(ut_scheduledlg, updateDateTimeFormat)
{
    mScheduleDlg->updateDateTimeFormat();
    EXPECT_EQ(mScheduleDlg->m_dateFormat, mScheduleDlg->m_beginDateEdit->displayFormat());
    EXPECT_EQ(mScheduleDlg->m_dateFormat, mScheduleDlg->m_endDateEdit->displayFormat());
    EXPECT_EQ(mScheduleDlg->m_dateFormat, mScheduleDlg->m_endRepeatDate->displayFormat());
}

//changeEvent
TEST_F(ut_scheduledlg, changeEvent)
{
    QEvent event(QEvent::FontChange);
    QApplication::sendEvent(mScheduleDlg, &event);
    QString typeStr = mScheduleDlg->m_typeLabel->text();
    QString str_contentlabel = mScheduleDlg->m_contentLabel->text();
    QString str_allDayLabel = mScheduleDlg->m_adllDayLabel->text();
    QString str_beginTimeLabel = mScheduleDlg->m_beginTimeLabel->text();
    QString str_endTimeLabel = mScheduleDlg->m_endTimeLabel->text();
    EXPECT_EQ(typeStr, mScheduleDlg->m_typeLabel->text());
    EXPECT_EQ(str_contentlabel, mScheduleDlg->m_contentLabel->text());
    EXPECT_EQ(str_allDayLabel, mScheduleDlg->m_adllDayLabel->text());
    EXPECT_EQ(str_beginTimeLabel, mScheduleDlg->m_beginTimeLabel->text());
    EXPECT_EQ(str_endTimeLabel, mScheduleDlg->m_endTimeLabel->text());
}
