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
#include "ut_monthwindow.h"

#include "../third-party_stub/stub.h"
#include "monthWidget/monthview.h"

#include <QApplication>

ut_monthWindow::ut_monthWindow()
{
}

void ut_monthWindow::SetUp()
{
    m_monthWindow = new CMonthWindow(nullptr);
}

void ut_monthWindow::TearDown()
{
    delete m_monthWindow;
    m_monthWindow = nullptr;
}

TEST_F(ut_monthWindow, setTheMe_001)
{
    int type = 0;
    m_monthWindow->setTheMe(type);
    QColor gridColor("#F8F8F8");
    EXPECT_EQ(gridColor, m_monthWindow->m_gridWidget->palette().color(DPalette::Background));
}

TEST_F(ut_monthWindow, setTheMe_002)
{
    int type = 2;
    m_monthWindow->setTheMe(type);
    QColor gridColor("#252525");
    EXPECT_EQ(gridColor, m_monthWindow->m_gridWidget->palette().color(DPalette::Background));
}

namespace MonthWindow {
bool isDelete = false;
void deleteselectschedule_Stub(void *obj)
{
    Q_UNUSED(obj)
    isDelete = true;
}
} // namespace MonthWindow

TEST_F(ut_monthWindow, deleteselectSchedule)
{
    Stub stub;
    stub.set(ADDR(CMonthView, deleteSelectSchedule), MonthWindow::deleteselectschedule_Stub);
    m_monthWindow->deleteselectSchedule();
    EXPECT_TRUE(MonthWindow::isDelete);
}

TEST_F(ut_monthWindow, previousMonth)
{
    QDate currentDate = QDate::currentDate();
    m_monthWindow->setSelectDate(currentDate);
    m_monthWindow->previousMonth();
    ASSERT_EQ(m_monthWindow->getSelectDate(), currentDate.addMonths(1));
}

TEST_F(ut_monthWindow, nextMonth)
{
    QDate currentDate = QDate::currentDate();
    m_monthWindow->setSelectDate(currentDate);
    m_monthWindow->nextMonth();
    ASSERT_EQ(m_monthWindow->getSelectDate(), currentDate.addMonths(-1));
}

TEST_F(ut_monthWindow, slotViewSelectDate)
{
    bool isSwitch = false;
    QObject::connect(m_monthWindow, &CMonthWindow::signalSwitchView, [&]() {
        isSwitch = true;
    });
    QDate currentDate = QDate::currentDate();
    m_monthWindow->slotViewSelectDate(currentDate);
    EXPECT_TRUE(isSwitch);
}

TEST_F(ut_monthWindow, resizeEvent_001)
{
    m_monthWindow->setFixedSize(500, 300);
    QResizeEvent resizeEvent1(QSize(0, 30), QSize(1900, 30));
    m_monthWindow->m_searchFlag = false;
    QApplication::sendEvent(m_monthWindow, &resizeEvent1);
    EXPECT_EQ(m_monthWindow->m_tMainLayout->contentsMargins().right(), 10);
}

TEST_F(ut_monthWindow, resizeEvent_002)
{
    m_monthWindow->setFixedSize(500, 300);
    QResizeEvent resizeEvent1(QSize(0, 30), QSize(1900, 30));
    m_monthWindow->m_searchFlag = true;
    QApplication::sendEvent(m_monthWindow, &resizeEvent1);
    EXPECT_EQ(m_monthWindow->m_tMainLayout->contentsMargins().right(), 0);
}

TEST_F(ut_monthWindow, slottoday)
{
    QDate seletDate = QDate::currentDate().addDays(3);
    m_monthWindow->setSelectDate(seletDate);
    EXPECT_EQ(m_monthWindow->getSelectDate(), seletDate);
    m_monthWindow->slottoday();
    EXPECT_EQ(m_monthWindow->getSelectDate(), QDate::currentDate());
}
