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
#include "ut_weekwindow.h"

#include "../third-party_stub/stub.h"
#include "customWidget/scheduleview.h"
#include "customWidget/todaybutton.h"

ut_weekWindow::ut_weekWindow()
{
}

void ut_weekWindow::SetUp()
{
    m_weekWindow = new CWeekWindow(nullptr);
}

void ut_weekWindow::TearDown()
{
    delete m_weekWindow;
    m_weekWindow = nullptr;
}

TEST_F(ut_weekWindow, setTheMe)
{
    m_weekWindow->setTheMe(0);
    QColor sbColor("#002A57");
    sbColor.setAlphaF(0.05);
    ASSERT_EQ(m_weekWindow->m_today->m_shadowColor, sbColor);
    m_weekWindow->setTheMe(1);
    ASSERT_EQ(m_weekWindow->m_today->m_shadowColor, sbColor);
    QColor sbColor1("#000000");
    sbColor1.setAlphaF(0.05);
    m_weekWindow->setTheMe(2);
    ASSERT_EQ(m_weekWindow->m_today->m_shadowColor, sbColor1);
}

TEST_F(ut_weekWindow, updateHeight)
{
    m_weekWindow->updateHeight();
}

TEST_F(ut_weekWindow, setTime)
{
    QTime time(13, 51, 24);
    //定位非全天显示位置
    m_weekWindow->setTime(time);
    ASSERT_EQ(QString::number(m_weekWindow->m_scheduleView->m_graphicsView->m_sceneHeightScale, 'f', 2), "0.58");
}

TEST_F(ut_weekWindow, setYearData)
{
    QString str = QCoreApplication::translate("today", "Today", "Today");
    m_weekWindow->setYearData();
    ASSERT_EQ(m_weekWindow->m_today->text(), str);
}

QString wekwindow_str = "";
namespace WeekDeleteItem {
void slotDeleteitem_Stub(void *obj)
{
    Q_UNUSED(obj)
    wekwindow_str = "slotDeleteitem_Stub";
}
} // namespace WeekDeleteItem

TEST_F(ut_weekWindow, deleteselectSchedule)
{
    Stub stub;
    stub.set(ADDR(CScheduleView, slotDeleteitem), WeekDeleteItem::slotDeleteitem_Stub);
    m_weekWindow->deleteselectSchedule();
    ASSERT_EQ(wekwindow_str, "slotDeleteitem_Stub");
}

bool IsDragging_Stub(void *obj)
{
    Q_UNUSED(obj)
    return false;
}

TEST_F(ut_weekWindow, slotIsDragging)
{
    Stub stub;
    stub.set(ADDR(CScheduleView, IsDragging), IsDragging_Stub);
    bool isDragging;
    m_weekWindow->slotIsDragging(isDragging);
    ASSERT_EQ(isDragging, false);
}
