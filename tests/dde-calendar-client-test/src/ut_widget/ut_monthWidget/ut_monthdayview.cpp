/*
* Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
*
* Author:     zhengxiaokang <zhengxiaokang@uniontech.com>
*
* Maintainer: zhengxiaokang <zhengxiaokang@uniontech.com>
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
#include "ut_monthdayview.h"

#include <DPalette>
DGUI_USE_NAMESPACE
ut_monthdayview::ut_monthdayview()
{
}

void ut_monthdayview::SetUp()
{
    mMonthDayView = new CMonthDayView();
    mMonthWidget = new CMonthWidget();
    mMonthRect = new CMonthRect();
}

void ut_monthdayview::TearDown()
{
    delete mMonthDayView;
    mMonthDayView = nullptr;
    delete mMonthWidget;
    mMonthWidget = nullptr;
    delete mMonthRect;
    mMonthRect = nullptr;
}

//void CMonthDayView::setSelectDate(const QDate &date)
TEST_F(ut_monthdayview, setSelectdate)
{
    QDate selectDate = QDate::currentDate().addDays(5);
    mMonthDayView->setSelectDate(selectDate);
    EXPECT_EQ(selectDate, mMonthDayView->m_selectDate);
}

//void CMonthDayView::setTheMe(int type)
TEST_F(ut_monthdayview, setTheMe_001)
{
    int type = 1;
    QColor frameColor("#FFFFFF");
    mMonthDayView->setTheMe(type);
    EXPECT_EQ(frameColor, mMonthDayView->palette().color(DPalette::Background));
}

TEST_F(ut_monthdayview, setTheMe_002)
{
    int type = 2;
    QColor frameColor("#FFFFFF");
    frameColor.setAlphaF(0.05);

    mMonthDayView->setTheMe(type);
    EXPECT_EQ(frameColor, mMonthDayView->palette().color(DPalette::Background));
}

//void CMonthDayView::setSearchflag(bool flag)
TEST_F(ut_monthdayview, setSearchflag)
{
    bool flag = true;
    mMonthDayView->setSearchflag(flag);
    EXPECT_EQ(flag, mMonthDayView->m_searchFlag);
}

//void CMonthWidget::setDate(const QDate date[12])
TEST_F(ut_monthdayview, setDate)
{
    QDate m_days[12];
    QDate currentDate = QDate::currentDate();
    for (int i = 0; i < 12; i++) {
        m_days[i] = currentDate.addMonths(i);
    }
    mMonthWidget->setDate(m_days);
    for (int i = 0; i < 12; ++i) {
        EXPECT_EQ(mMonthWidget->m_MonthItem.at(i)->getDate(), m_days[i]);
    }
}

//void CMonthWidget::updateSize()
TEST_F(ut_monthdayview, updateSize)
{
    mMonthWidget->setFixedWidth(1200);
    qreal w = mMonthWidget->width() / mMonthWidget->m_MonthItem.size();
    mMonthWidget->updateSize();
    EXPECT_GT(w + 0.0001, mMonthWidget->m_MonthItem.at(0)->rect().width());
    EXPECT_LT(w - 0.0001, mMonthWidget->m_MonthItem.at(0)->rect().width());
}

//void CMonthRect::setDate(const QDate &date)
TEST_F(ut_monthdayview, setRectDate)
{
    QDate currentDate = QDate::currentDate();
    mMonthRect->setDate(currentDate);
    EXPECT_EQ(currentDate, mMonthRect->getDate());
}

//void CMonthRect::setRect(const QRectF &rect)
TEST_F(ut_monthdayview, setRect)
{
    QRectF rect(10, 50, 600, 20);
    mMonthRect->setRect(rect);
    EXPECT_EQ(rect, mMonthRect->rect());
}

//void CMonthRect::setDevicePixelRatio(const qreal pixel)
TEST_F(ut_monthdayview, setDevicePixelRatio)
{
    qreal pixel = 1.2;
    mMonthRect->setDevicePixelRatio(pixel);
    EXPECT_GT(pixel + 0.0001, mMonthRect->m_DevicePixelRatio);
    EXPECT_LT(pixel - 0.0001, mMonthRect->m_DevicePixelRatio);
}

//void CMonthRect::setTheMe(int type)
TEST_F(ut_monthdayview, setRTheMe_001)
{
    int type = 1;
    mMonthRect->setTheMe(type);
    QColor textColor = Qt::white;
    EXPECT_EQ(type, mMonthRect->m_themetype);
    EXPECT_EQ(textColor, mMonthRect->m_currentDayTextColor);
}

TEST_F(ut_monthdayview, setRTheMe_002)
{
    int type = 2;
    mMonthRect->setTheMe(type);
    QColor textColor("#C0C6D4");
    EXPECT_EQ(type, mMonthRect->m_themetype);
    EXPECT_EQ(textColor, mMonthRect->m_currentDayTextColor);
}
