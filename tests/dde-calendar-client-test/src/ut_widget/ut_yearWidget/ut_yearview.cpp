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
#include "ut_yearview.h"

#include "../third-party_stub/stub.h"
#include <QTest>
#include <QSignalSpy>

ut_yearview::ut_yearview()
{
}

ut_yearview::~ut_yearview()
{
}

void ut_yearview::SetUp()
{
    cYearView = new CYearView();
}

void ut_yearview::TearDown()
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
TEST_F(ut_yearview, slotDoubltClickDate)
{
    QSignalSpy spy(cYearView, SIGNAL(signalMousePress(const QDate &, const int)));
    cYearView->slotDoubleClickDate(QDate(2021, 1, 6));
    ASSERT_EQ(spy.count(), 1);
}

//void CYearView::slotPressClickDate(const QDate &date)
TEST_F(ut_yearview, slotPressClickDate)
{
    QSignalSpy spy(cYearView, SIGNAL(signalMousePress(const QDate &, const int)));
    cYearView->slotPressClickDate(QDate(2021, 1, 6));
    ASSERT_EQ(spy.count(), 1);
}

//void CYearView::setTheMe(int type)
TEST_F(ut_yearview, setTheMe)
{
    cYearView->setTheMe(1);
    cYearView->setTheMe(2);
    ASSERT_EQ(QString::number(cYearView->m_bnormalColor.alphaF(), 'f', 2), "0.05");
}

//void CYearView::setShowDate(const QDate &showMonth, const QVector<QDate> &showDate)
TEST_F(ut_yearview, setShowDate)
{
    cYearView->setShowDate(getListDate().first(), getListDate());
    ASSERT_EQ(cYearView->m_showMonth, getListDate().first());
}

//void CYearView::setHasScheduleFlag(const QVector<bool> &hasScheduleFlag)
TEST_F(ut_yearview, setHasScheduleFlag)
{
    QVector<bool> listLintFlag {};
    listLintFlag.append(false);
    listLintFlag.append(true);

    cYearView->setHasScheduleFlag(listLintFlag);
    ASSERT_FALSE(cYearView->m_monthView->m_DayItem[1]->m_vlineflag);
}

//void CYearView::setHasSearchScheduleFlag(const QVector<bool> &hasSearchScheduleFlag)
TEST_F(ut_yearview, setHasSearchScheduleFlag)
{
    QVector<bool> listLintFlag {};
    listLintFlag.append(false);
    listLintFlag.append(true);

    cYearView->setHasSearchScheduleFlag(listLintFlag);
    ASSERT_FALSE(cYearView->m_monthView->m_DayItem[1]->m_searchScheduleFlag);
}

void setDate_Stub(const int showMonth, const QVector<QDate> &showDate) {
    Q_UNUSED(showMonth)
        Q_UNUSED(showDate)}

//bool CYearView::getStartAndStopDate(QDate &startDate, QDate &stopDate)
TEST_F(ut_yearview, getStartAndStopDate)
{
    QDate startDate(QDate(2021, 1, 7));
    QDate stopDate(QDate(2021, 1, 8));

    cYearView->setShowDate(getListDate().first(), getListDate());
    bool result = cYearView->getStartAndStopDate(startDate, stopDate);
    EXPECT_TRUE(result);

    QVector<QDate> listDate {};
    Stub stub;
    stub.set(ADDR(MonthBrefWidget, setDate), setDate_Stub);
    cYearView->setShowDate(getListDate().first(), listDate);
    bool result_false = cYearView->getStartAndStopDate(startDate, stopDate);
    EXPECT_FALSE(result_false);
}

bool hasFocus_Stub()
{
    return true;
}

TEST_F(ut_yearview, paintEvent)
{
    Stub stub;
    stub.set(ADDR(QWidget, hasFocus), hasFocus_Stub);
    cYearView->setFixedSize(600, 600);
    QPixmap pixmap(cYearView->size());
    cYearView->render(&pixmap);
    ASSERT_EQ(pixmap.size(), cYearView->size());
}

TEST_F(ut_yearview, guitest)
{
    QSignalSpy spy(cYearView, SIGNAL(signalMousePress(const QDate &, const int)));
    QWidget *currentMonth = cYearView->findChild<QWidget *>("currentMouth");
    if (currentMonth) {
        QTest::mouseDClick(currentMonth, Qt::LeftButton);
        ASSERT_EQ(spy.count(), 1);
    }
}
