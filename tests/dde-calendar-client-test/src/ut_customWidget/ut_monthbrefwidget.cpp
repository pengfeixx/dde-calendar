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
#include "ut_monthbrefwidget.h"

#include <QResizeEvent>
#include <QApplication>
#include <QMouseEvent>
#include <QTest>

ut_monthbrefwidget::ut_monthbrefwidget()
{

}

void ut_monthbrefwidget::SetUp()
{
    mMonthBrefWidget = new MonthBrefWidget();
    mMonthDayRect = new CMonthDayRect();
}

void ut_monthbrefwidget::TearDown()
{
    delete mMonthBrefWidget;
    mMonthBrefWidget = nullptr;
    delete mMonthDayRect;
    mMonthDayRect = nullptr;
}

QVector<QDate> getDateList()
{
    QDate currentdate = QDate::currentDate();
    QVector<QDate> dateList;
    for (int i = 0; i < 42; i++) {
        dateList.append(currentdate.addDays(i));
    }
    return dateList;
}

QVector<bool> getBoolList()
{
    QVector<bool> lineList;
    for (int i = 0; i < 42; i++) {
        if (i % 2 == 0)
            lineList.append(true);
        else
            lineList.append(false);
    }
    return lineList;
}

//void MonthBrefWidget::setDate(const int showMonth, const QVector<QDate> &showDate)
TEST_F(ut_monthbrefwidget, setDate)
{
    const int month = 4;
    mMonthBrefWidget->setDate(month, getDateList());
    EXPECT_EQ(month, mMonthBrefWidget->m_currentMonth);
    EXPECT_EQ(mMonthBrefWidget->m_DayItem.at(0)->getDate(), getDateList().at(0));
}

//void MonthBrefWidget::setTheMe(int type)
TEST_F(ut_monthbrefwidget, setTheMe)
{
    mMonthBrefWidget->setTheMe(1);
    mMonthBrefWidget->setTheMe(2);
}

//void MonthBrefWidget::setLintFlag(const QVector<bool> &lineFlag)
TEST_F(ut_monthbrefwidget, setLintFlag)
{
    mMonthBrefWidget->setLintFlag(getBoolList());
    EXPECT_EQ(mMonthBrefWidget->m_DayItem.at(0)->m_vlineflag, getBoolList().at(0));
}

//void MonthBrefWidget::setSearchScheduleFlag(const QVector<bool> &searchFlag)
TEST_F(ut_monthbrefwidget, setSearchScheduleFlag)
{
    mMonthBrefWidget->setSearchScheduleFlag(getBoolList());
    EXPECT_EQ(mMonthBrefWidget->m_DayItem.at(0)->m_searchScheduleFlag, getBoolList().at(0));
}

//void MonthBrefWidget::updateSize()
TEST_F(ut_monthbrefwidget, updateSize)
{
    mMonthBrefWidget->updateSize();
    qreal w = mMonthBrefWidget->width() / 7;
    qreal h = mMonthBrefWidget->height() / 6;
    EXPECT_GT(mMonthBrefWidget->m_DayItem.at(0)->m_rect.h, h - 0.00001);
    EXPECT_LT(mMonthBrefWidget->m_DayItem.at(0)->m_rect.h, h + 0.00001);
}

//int MonthBrefWidget::getMousePosItem(const QPointF &pos)
TEST_F(ut_monthbrefwidget, getMousePosItem)
{
    QPointF pointf(20, 20);
    mMonthBrefWidget->setFixedSize(210, 120);
    mMonthBrefWidget->updateSize();
    int res = mMonthBrefWidget->getMousePosItem(pointf);
    EXPECT_EQ(res, 0);
}

//void MonthBrefWidget::mousePress(const QPoint &point
TEST_F(ut_monthbrefwidget, mousePress)
{
    QPoint pointf(20, 20);
    mMonthBrefWidget->setFixedSize(210, 120);
    mMonthBrefWidget->updateSize();
    mMonthBrefWidget->mousePress(pointf);
    EXPECT_TRUE(mMonthBrefWidget->m_press);
    EXPECT_EQ(mMonthBrefWidget->m_pressIndex, 0);
}

//void CMonthDayRect::setTheMe(int type)
TEST_F(ut_monthbrefwidget, setTheme_001)
{
    mMonthDayRect->setTheMe(1);
    QColor hoveerColor("#000000");
    hoveerColor.setAlphaF(0.05);
    EXPECT_EQ(mMonthDayRect->m_currentColor.hoverColor, hoveerColor);
}

TEST_F(ut_monthbrefwidget, setTheme_002)
{
    mMonthDayRect->setTheMe(2);
    QColor hoveerColor("#FFFFFF");
    hoveerColor.setAlphaF(0.1);
    EXPECT_EQ(mMonthDayRect->m_currentColor.hoverColor, hoveerColor);
}

//void CMonthDayRect::setDate(const QDate &date)
TEST_F(ut_monthbrefwidget, setdate)
{
    QDate currentDate = QDate::currentDate();
    mMonthDayRect->setDate(currentDate);
    EXPECT_EQ(currentDate, mMonthDayRect->getDate());
}

//QDate CMonthDayRect::getDate() const
TEST_F(ut_monthbrefwidget, getdate)
{
    QDate currentDate = QDate::currentDate();
    mMonthDayRect->setDate(currentDate);
    EXPECT_EQ(currentDate, mMonthDayRect->getDate());
}

//void CMonthDayRect::setCellEvent(const CMonthDayRect::CellEventType &type)
TEST_F(ut_monthbrefwidget, setCellEvent)
{
    mMonthDayRect->setCellEvent(CMonthDayRect::CellEventType::Cellhover);
    EXPECT_EQ(mMonthDayRect->m_cellEventType, CMonthDayRect::CellEventType::Cellhover);
}

//void CMonthDayRect::setIsCurrentMonth(const bool isCurrMonth)
TEST_F(ut_monthbrefwidget, setIsCurrentMonth)
{
    mMonthDayRect->setIsCurrentMonth(true);
    EXPECT_TRUE(mMonthDayRect->m_isCurrentMonth);
}

//QRectF CMonthDayRect::rect() const
TEST_F(ut_monthbrefwidget, rect)
{
    mMonthDayRect->setRect(QRect(10, 10, 8, 8));
    EXPECT_EQ(QRect(10, 10, 8, 8), mMonthDayRect->rect());
}

//void CMonthDayRect::setRect(const QRectF &rect)
TEST_F(ut_monthbrefwidget, setRect_001)
{
    mMonthDayRect->setRect(QRect(10, 10, 8, 8));
    EXPECT_EQ(QRect(10, 10, 8, 8), mMonthDayRect->rect());
}

//void CMonthDayRect::setRect(qreal x, qreal y, qreal w, qreal h)
TEST_F(ut_monthbrefwidget, setRect_002)
{
    QRectF rect(9, 9, 9, 9);
    mMonthDayRect->setRect(rect);
    EXPECT_EQ(rect, mMonthDayRect->rect());
}

//void CMonthDayRect::setLineFlag(const bool flag)
TEST_F(ut_monthbrefwidget, setLineFlag)
{
    mMonthDayRect->setLineFlag(true);
    EXPECT_TRUE(mMonthDayRect->m_vlineflag);
}

//void CMonthDayRect::setSearchScheduleFlag(const bool flag)
TEST_F(ut_monthbrefwidget, setSearchScheduleflag)
{
    mMonthDayRect->setSearchScheduleFlag(true);
    EXPECT_TRUE(mMonthDayRect->m_searchScheduleFlag);
}

//void CMonthDayRect::setDevicePixelRatio(const qreal pixel)
TEST_F(ut_monthbrefwidget, setDevicePixelRatio)
{
    mMonthDayRect->setDevicePixelRatio(2);
    EXPECT_EQ(2, mMonthDayRect->m_DevicePixelRatio);
}

//void CMonthDayRect::setCurrentRect(CMonthDayRect *currrect)
TEST_F(ut_monthbrefwidget, setCurrentrect)
{
    mMonthDayRect->setCurrentRect(mMonthDayRect);
    EXPECT_EQ(mMonthDayRect->m_CurrentRect, mMonthDayRect);
}

//void CMonthDayRect::setSystemActiveColor(const QColor &activeColor)
TEST_F(ut_monthbrefwidget, setSystemActiveColor)
{
    QColor color(Qt::red);
    mMonthDayRect->setSystemActiveColor(color);
    EXPECT_EQ(color, mMonthDayRect->m_highColor);
}

//getPixmap
TEST_F(ut_monthbrefwidget, getPixmap)
{
    mMonthBrefWidget->setFixedSize(800, 500);
    mMonthBrefWidget->setDate(QDate::currentDate().month(), getDateList());
    QPixmap pixmap(mMonthBrefWidget->size());
    mMonthBrefWidget->render(&pixmap);
    EXPECT_EQ(pixmap.size(), mMonthBrefWidget->size());
}

TEST_F(ut_monthbrefwidget, resizeEvent)
{
    mMonthBrefWidget->setFixedSize(QSize(600, 500));
    QResizeEvent resizeEvent(QSize(600, 501), QSize(600, 500));
    QApplication::sendEvent(mMonthBrefWidget, &resizeEvent);
    EXPECT_EQ(QSize(600, 500), mMonthBrefWidget->size());
}

TEST_F(ut_monthbrefwidget, mouseEvent)
{
    mMonthBrefWidget->setFixedSize(QSize(600, 500));
    mMonthBrefWidget->setDate(QDate::currentDate().month(), getDateList());
    QTest::mouseDClick(mMonthBrefWidget, Qt::MouseButton::LeftButton);
    QTest::mouseRelease(mMonthBrefWidget, Qt::MouseButton::LeftButton);
    EXPECT_EQ(mMonthBrefWidget->m_touchState, 0);
    EXPECT_EQ(mMonthBrefWidget->m_touchBeginPoint, QPoint());
}

//mouseDoubleClickEvent
TEST_F(ut_monthbrefwidget, mouseDoubleClickEvent)
{
    mMonthBrefWidget->setFixedSize(QSize(600, 500));
    mMonthBrefWidget->setDate(QDate::currentDate().month(), getDateList());
    QTest::mouseDClick(mMonthBrefWidget, Qt::MouseButton::LeftButton);
    EXPECT_FALSE(mMonthBrefWidget->m_press);
}
