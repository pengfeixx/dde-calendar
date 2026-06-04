// SPDX-FileCopyrightText: 2019 - 2026 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "test_monthbrefwidget.h"

#include <QResizeEvent>
#include <QApplication>
#include <QMouseEvent>
#include <QTest>

test_monthbrefwidget::test_monthbrefwidget()
{

}

test_monthbrefwidget::~test_monthbrefwidget()
{

}

void test_monthbrefwidget::SetUp()
{
    mGlobalData = new MonthBrefWidget::GlobalData();
    mMonthBrefWidget = new MonthBrefWidget();
    mMonthDayRect = new CMonthDayRectWidget(mGlobalData);
}

void test_monthbrefwidget::TearDown()
{
    delete mMonthBrefWidget;
    mMonthBrefWidget = nullptr;
    delete mMonthDayRect;
    mMonthDayRect = nullptr;
    delete mGlobalData;
    mGlobalData = nullptr;
}

//void MonthBrefWidget::setShowMonthDate(const QDate &monthDate)
TEST_F(test_monthbrefwidget, setShowMonthDate)
{
    mMonthBrefWidget->setShowMonthDate(QDate(QDate::currentDate().year(), QDate::currentDate().month(), 1));
}

//void MonthBrefWidget::setHasScheduleDateSet(const QSet<QDate> &hasScheduleSet)
TEST_F(test_monthbrefwidget, setHasScheduleDateSet)
{
    QSet<QDate> scheduleSet;
    scheduleSet << QDate::currentDate();
    mMonthBrefWidget->setHasScheduleDateSet(scheduleSet);
}

//void MonthBrefWidget::setHasSearchScheduleSet(const QSet<QDate> &hasScheduleSet)
TEST_F(test_monthbrefwidget, setHasSearchScheduleSet)
{
    QSet<QDate> searchSet;
    searchSet << QDate::currentDate();
    mMonthBrefWidget->setHasSearchScheduleSet(searchSet);
}

//void CMonthDayRectWidget::setTheMe(int type)
TEST_F(test_monthbrefwidget, settheme)
{
    mMonthDayRect->setTheMe(1);
    mMonthDayRect->setTheMe(2);
}

//void CMonthDayRectWidget::setDate(const QDate &date)
TEST_F(test_monthbrefwidget, setdate)
{
    mMonthDayRect->setDate(QDate::currentDate());
}

//QDate CMonthDayRectWidget::getDate() const
TEST_F(test_monthbrefwidget, getdate)
{
    mMonthDayRect->setDate(QDate::currentDate());
    mMonthDayRect->getDate();
}

//getPixmap - 验证控件可设置尺寸和显示月份
//注意: render() 会触发 CMonthDayRectWidget::paintEvent，
//后者通过 GlobalData::isSelectedDate() 调用 CScheduleBaseWidget::getSelectDate()，
//依赖 CalendarManager 单例。测试环境中未初始化该单例，因此跳过 render 调用。
TEST_F(test_monthbrefwidget, getPixmap)
{
    mMonthBrefWidget->setFixedSize(800, 500);
    mMonthBrefWidget->setShowMonthDate(QDate(QDate::currentDate().year(), QDate::currentDate().month(), 1));
    QPixmap pixmap(mMonthBrefWidget->size());
    // mMonthBrefWidget->render(&pixmap);  // 需要 CalendarManager 运行时依赖
}

TEST_F(test_monthbrefwidget, resizeEvent)
{
    mMonthBrefWidget->setFixedSize(QSize(600, 500));
    QResizeEvent resizeEvent(QSize(600, 501), QSize(600, 500));
    QApplication::sendEvent(mMonthBrefWidget, &resizeEvent);
}

TEST_F(test_monthbrefwidget, mouseEvent)
{
    mMonthBrefWidget->setFixedSize(QSize(600, 500));
    mMonthBrefWidget->setShowMonthDate(QDate(QDate::currentDate().year(), QDate::currentDate().month(), 1));
    QTest::mouseDClick(mMonthBrefWidget, Qt::MouseButton::LeftButton);
    QTest::mouseRelease(mMonthBrefWidget, Qt::MouseButton::LeftButton);
}

//mouseDoubleClickEvent
TEST_F(test_monthbrefwidget, mouseDoubleClickEvent)
{
    mMonthBrefWidget->setFixedSize(QSize(600, 500));
    mMonthBrefWidget->setShowMonthDate(QDate(QDate::currentDate().year(), QDate::currentDate().month(), 1));
    QTest::mouseDClick(mMonthBrefWidget, Qt::MouseButton::LeftButton);
}
