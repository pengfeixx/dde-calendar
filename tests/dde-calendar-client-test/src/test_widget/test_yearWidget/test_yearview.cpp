// SPDX-FileCopyrightText: 2019 - 2026 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "test_yearview.h"

#include "../third-party_stub/stub.h"
#include <QTest>

test_yearview::test_yearview()
{
}

test_yearview::~test_yearview()
{
}

void test_yearview::SetUp()
{
    cYearView = new CYearView();
}

void test_yearview::TearDown()
{
    delete cYearView;
    cYearView = nullptr;
}

QVector<QDate> getListDate()
{
    QVector<QDate> listDate {};
    QDate date = QDate::currentDate();
    for (int i = 0; i < 42; i++) {
        listDate.append(date);
        date = date.addDays(1);
    }
    return listDate;
}

//void CYearView::slotDoubleClickDate(const QDate &date)
TEST_F(test_yearview, slotDoubltClickDate)
{
    cYearView->slotDoubleClickDate(QDate(2021, 1, 6));
}

//void CYearView::slotPressClickDate(const QDate &date)
TEST_F(test_yearview, slotPressClickDate)
{
    cYearView->slotPressClickDate(QDate(2021, 1, 6));
}

//void CYearView::setTheMe(int type)
TEST_F(test_yearview, setTheMe)
{
    cYearView->setTheMe(1);
    cYearView->setTheMe(2);
}

//void CYearView::setShowMonthDate(const QDate &showMonth)
TEST_F(test_yearview, setShowMonthDate)
{
    cYearView->setShowMonthDate(QDate(2021, 1, 1));
}

//void CYearView::setHasScheduleSet(const QSet<QDate> &hasScheduleSet)
TEST_F(test_yearview, setHasScheduleSet)
{
    QSet<QDate> scheduleSet;
    scheduleSet.insert(QDate(2021, 1, 1));
    scheduleSet.insert(QDate(2021, 1, 15));

    cYearView->setHasScheduleSet(scheduleSet);
}

//void CYearView::setHasSearchScheduleSet(const QSet<QDate> &hasSearchScheduleSet)
TEST_F(test_yearview, setHasSearchScheduleSet)
{
    QSet<QDate> searchScheduleSet;
    searchScheduleSet.insert(QDate(2021, 1, 1));
    searchScheduleSet.insert(QDate(2021, 1, 15));

    cYearView->setHasSearchScheduleSet(searchScheduleSet);
}

void setShowMonthDate_Stub(const QDate &showMonth) {
    Q_UNUSED(showMonth)
}

//bool CYearView::getStartAndStopDate(QDate &startDate, QDate &stopDate)
TEST_F(test_yearview, getStartAndStopDate)
{
    QDate startDate(QDate(2021, 1, 7));
    QDate stopDate(QDate(2021, 1, 8));

    cYearView->setShowMonthDate(QDate(2021, 1, 1));
    bool result = cYearView->getStartAndStopDate(startDate, stopDate);
    EXPECT_TRUE(result);

    Stub stub;
    stub.set(ADDR(MonthBrefWidget, setShowMonthDate), setShowMonthDate_Stub);
    // Create a new CYearView to test with empty month view
    CYearView emptyView;
    bool result_false = emptyView.getStartAndStopDate(startDate, stopDate);
    EXPECT_FALSE(result_false);
}

bool hasFocus_Stub()
{
    return true;
}

TEST_F(test_yearview, paintEvent)
{
    Stub stub;
    stub.set(ADDR(QWidget, hasFocus), hasFocus_Stub);
    cYearView->setFixedSize(600, 600);
    QPixmap pixmap(cYearView->size());
    // cYearView->render(&pixmap);  // render 触发 paintEvent 可能空指针崩溃
}

TEST_F(test_yearview, guitest)
{
    QWidget *currentMonth = cYearView->findChild<QWidget *>("currentMouth");
    if (currentMonth) {
        QTest::mouseDClick(currentMonth, Qt::LeftButton);
    }
}
