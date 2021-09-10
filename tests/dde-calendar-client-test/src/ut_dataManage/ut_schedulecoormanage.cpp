/*
* Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
*
* Author:     hejinghai <hejinghai@uniontech.com>
*
* Maintainer: hejinghai <hejinghai@uniontech.com>
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
#include "ut_schedulecoormanage.h"

#include <QDebug>

ut_schedulecoormanage::ut_schedulecoormanage()
{
}

void ut_schedulecoormanage::SetUp()
{
    cScheduleCoorManage = new CScheduleCoorManage();
}

void ut_schedulecoormanage::TearDown()
{
    delete cScheduleCoorManage;
    cScheduleCoorManage = nullptr;
}

//void CScheduleCoorManage::setRange(int w, int h, QDate begindate, QDate enddate, int rightmagin)
TEST_F(ut_schedulecoormanage, setRange)
{
    int w = 100;
    int h = 100;
    QDate begindate = QDate::currentDate();
    QDate enddate = begindate.addDays(7);
    int rightmagin = 1;
    cScheduleCoorManage->setRange(w, h, begindate, enddate, rightmagin);
    EXPECT_EQ(w, cScheduleCoorManage->m_width);
    EXPECT_EQ(h, cScheduleCoorManage->m_height);
    EXPECT_EQ(begindate, cScheduleCoorManage->m_begindate);
    EXPECT_EQ(enddate, cScheduleCoorManage->m_enddate);
    EXPECT_EQ(rightmagin, cScheduleCoorManage->m_rightmagin);
}

//void CScheduleCoorManage::setDateRange(QDate begindate, QDate enddate)
TEST_F(ut_schedulecoormanage, setDateRange)
{
    QDate begindate = QDate::currentDate();
    QDate enddate = begindate.addDays(7);
    cScheduleCoorManage->setDateRange(begindate, enddate);
    EXPECT_EQ(begindate, cScheduleCoorManage->m_begindate);
    EXPECT_EQ(enddate, cScheduleCoorManage->m_enddate);
}

/**
 * @brief ut_schedulecoormanage, getDrawRegion
 * (QDateTime begintime, QDateTime endtime)
 * (QDateTime begintime, QDateTime endtime, int index, int coount)
 * (QDate date, QDateTime begintime, QDateTime endtime, int index, int coount, int maxnum, int type)
 */
TEST_F(ut_schedulecoormanage, getDrawRegion)
{
    int w = 100;
    int h = 100;
    QDate begindate = QDate::currentDate();
    QDate enddate = begindate.addDays(7);
    int rightmagin = 1;
    cScheduleCoorManage->setRange(w, h, begindate, enddate, rightmagin);

    QDateTime bDate = QDateTime::currentDateTime();
    QDateTime eDate = bDate.addSecs(60 * 60);
    //第几个
    int index = 1;
    //一共多少个
    int totalNum = 3;
    //最多多少个
    int maxnum = 7;
    QRectF rect = cScheduleCoorManage->getDrawRegion(begindate, bDate, eDate, index, totalNum, maxnum);
    EXPECT_GT(rect.x(), 0);
    EXPECT_GT(rect.y(), 0);
    EXPECT_GT(rect.width(), 0);
    EXPECT_GT(rect.height(), 0);
}

//QRectF CScheduleCoorManage::getAllDayDrawRegion(QDate begin, QDate end)
TEST_F(ut_schedulecoormanage, getAllDayDrawRegion)
{
    int w = 100;
    int h = 100;
    QDate begindate = QDate::currentDate();
    QDate enddate = begindate.addDays(7);
    int rightmagin = 1;
    cScheduleCoorManage->setRange(w, h, begindate, enddate, rightmagin);

    QRectF rect = cScheduleCoorManage->getAllDayDrawRegion(begindate.addDays(1), begindate.addDays(2));
    EXPECT_EQ(rect.width(), w / 7 - 2);
}

//QDateTime CScheduleCoorManage::getDate(QPointF pos)
TEST_F(ut_schedulecoormanage, getDate)
{
    int w = 100;
    int h = 100;
    QDate begindate = QDate::currentDate();
    QDate enddate = begindate.addDays(7);
    int rightmagin = 1;
    cScheduleCoorManage->setRange(w, h, begindate, enddate, rightmagin);

    QPointF pos(0, 0);
    QDateTime dateTime = cScheduleCoorManage->getDate(pos);
    EXPECT_EQ(dateTime, QDateTime(begindate, QTime(0, 0, 0)));
}

//QDate CScheduleCoorManage::getsDate(QPointF pos)
TEST_F(ut_schedulecoormanage, getsDate)
{
    int w = 100;
    int h = 100;
    QDate begindate = QDate::currentDate();
    QDate enddate = begindate.addDays(7);
    int rightmagin = 1;
    cScheduleCoorManage->setRange(w, h, begindate, enddate, rightmagin);
    QPointF pos(0, 0);
    QDate date = cScheduleCoorManage->getsDate(pos);
    EXPECT_EQ(date, begindate);
}

//float CScheduleCoorManage::getHeight(const QTime &time)
TEST_F(ut_schedulecoormanage, getHeight)
{
    int w = 100;
    int h = 100;
    QDate begindate = QDate::currentDate();
    QDate enddate = begindate.addDays(7);
    int rightmagin = 1;
    cScheduleCoorManage->setRange(w, h, begindate, enddate, rightmagin);
    QTime currentTime = QTime::currentTime();
    float height = cScheduleCoorManage->getHeight(currentTime);
    EXPECT_GT(height, 0);
}
