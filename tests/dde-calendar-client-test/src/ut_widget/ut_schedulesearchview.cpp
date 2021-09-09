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
#include "ut_schedulesearchview.h"
#include "../third-party_stub/stub.h"
#include "../calendar-basicstruct/src/utils.h"
#include "../third-party_stub/addr_pri.h"
#include "scheduleTask/cscheduledbus.h"
#include "scheduleTask/scheduletask.h"
#include "constants.h"
#include "../testscheduledata.h"

#include <QSignalSpy>

QVector<ScheduleDataInfo> getScheduleDInfo()
{
    QVector<ScheduleDataInfo> scheduleDate {};
    ScheduleDataInfo schedule1, schedule2, schedule3, schedule4, schedule5, scheduleFes;
    QDateTime currentDateTime = QDateTime::currentDateTime();

    schedule1.setID(1);
    schedule1.setBeginDateTime(currentDateTime);
    schedule1.setEndDateTime(currentDateTime.addSecs(60 * 60));
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

    schedule3.setID(3);
    schedule3.setBeginDateTime(currentDateTime.addDays(2));
    schedule3.setEndDateTime(currentDateTime.addDays(2).addSecs(60 * 60));
    schedule3.setTitleName("scheduleThree");
    schedule3.setAllDay(false);
    schedule3.setType(3);
    schedule3.setRecurID(0);

    schedule4.setID(4);
    schedule4.setBeginDateTime(currentDateTime.addDays(3));
    schedule4.setEndDateTime(currentDateTime.addDays(3).addSecs(60 * 60));
    schedule4.setTitleName("scheduleFour");
    schedule4.setAllDay(false);
    schedule4.setType(1);
    schedule4.setRecurID(0);

    schedule5.setID(5);
    schedule5.setBeginDateTime(currentDateTime.addDays(4));
    schedule5.setEndDateTime(currentDateTime.addDays(4).addSecs(60 * 60));
    schedule5.setTitleName("scheduleFive");
    schedule5.setAllDay(false);
    schedule5.setType(2);
    schedule5.setRecurID(0);

    scheduleFes.setID(6);
    scheduleFes.setBeginDateTime(currentDateTime.addDays(5));
    scheduleFes.setEndDateTime(currentDateTime.addDays(5).addSecs(60 * 60));
    scheduleFes.setTitleName("scheduleFestival");
    scheduleFes.setAllDay(true);
    scheduleFes.setType(4);
    scheduleFes.setRecurID(0);

    scheduleDate.append(schedule1);
    scheduleDate.append(schedule2);
    scheduleDate.append(schedule3);
    scheduleDate.append(schedule4);
    scheduleDate.append(schedule5);
    scheduleDate.append(scheduleFes);
    return scheduleDate;
}

QMap<QDate, QVector<ScheduleDataInfo>> getMapScheduleDInfo(int getDays)
{
    QDate currentDate = QDate::currentDate();
    QVector<ScheduleDataInfo> scheduleInfo {};
    QMap<QDate, QVector<ScheduleDataInfo>> scheduleDateInof {};
    switch (getDays) {
    case 0: {
        scheduleInfo.append(getScheduleDInfo().at(0));
        scheduleDateInof[currentDate] = scheduleInfo;
    } break;
    case 1: {
        scheduleInfo.append(getScheduleDInfo().at(1));
        scheduleDateInof[currentDate.addDays(1)] = scheduleInfo;
    } break;
    case 2: {
        scheduleInfo.append(getScheduleDInfo().at(2));
        scheduleDateInof[currentDate.addDays(2)] = scheduleInfo;
    } break;
    default: {
        scheduleInfo.append(getScheduleDInfo().at(3));
        scheduleDateInof[currentDate.addDays(3)] = scheduleInfo;
        scheduleInfo.append(getScheduleDInfo().at(4));
        scheduleDateInof[currentDate.addDays(4)] = scheduleInfo;
        scheduleInfo.append(getScheduleDInfo().at(5));
        scheduleDateInof[currentDate.addDays(5)] = scheduleInfo;
    } break;
    }
    return scheduleDateInof;
}

bool stub_QueryJobs(const QString &key, QDateTime starttime, QDateTime endtime, QMap<QDate, QVector<ScheduleDataInfo>> &out)
{
    Q_UNUSED(key);
    int days = static_cast<int>(starttime.daysTo(endtime));

    switch (days) {
    case 0: {
        out = getMapScheduleDInfo(0);
    } break;
    case 1: {
        out = getMapScheduleDInfo(1);
    } break;
    case 2: {
        out = getMapScheduleDInfo(2);
    } break;
    default: {
        out = getMapScheduleDInfo(days);
    } break;
    }
    return true;
}

ut_schedulesearchview::ut_schedulesearchview()
{
}

ut_schedulesearchview::~ut_schedulesearchview()
{
}

void ut_schedulesearchview::SetUp()
{
    mScheduleSearchView = new CScheduleSearchView();
    mScheduleSearchDateItem = new CScheduleSearchDateItem();
    mScheduleListWidget = new CScheduleListWidget();
    mScheduleSearchItem = new CScheduleSearchItem();
}

void ut_schedulesearchview::TearDown()
{
    delete mScheduleSearchView;
    mScheduleSearchView = nullptr;
    delete mScheduleSearchDateItem;
    mScheduleSearchDateItem = nullptr;
    delete mScheduleListWidget;
    mScheduleListWidget = nullptr;
    delete mScheduleSearchItem;
    mScheduleSearchItem = nullptr;
}

//void CScheduleSearchView::setTheMe(int type)
TEST_F(ut_schedulesearchview, setTheMe)
{
    int type = 1;
    mScheduleSearchView->setTheMe(type);
    ASSERT_EQ(mScheduleSearchView->m_lBackgroundcolor, Qt::white);

    type = 2;
    mScheduleSearchView->setTheMe(type);
    ASSERT_EQ(QString::number(mScheduleSearchView->m_bBackgroundcolor.alphaF(), 'f', 2), "0.05");
}

//void CScheduleSearchView::clearSearch()
TEST_F(ut_schedulesearchview, clearSearch)
{
    ScheduleDataInfo schedule1;
    schedule1.setID(1);
    schedule1.setBeginDateTime(QDateTime(QDate(2021, 1, 1), QTime(0, 0, 0)));
    schedule1.setEndDateTime(QDateTime(QDate(2021, 1, 2), QTime(23, 59, 59)));
    schedule1.setTitleName("schedule test one");
    schedule1.setAllDay(true);
    schedule1.setType(1);
    schedule1.setRecurID(0);
    mScheduleSearchView->createItemWidget(schedule1, QDate(2021, 1, 1), 1);

    mScheduleSearchView->clearSearch();
    ASSERT_EQ(mScheduleSearchView->m_gradientItemList->count(), 0);
}

//void CScheduleSearchView::setMaxWidth(const int w)
TEST_F(ut_schedulesearchview, setMacWidth)
{
    mScheduleSearchView->setMaxWidth(44);
    ASSERT_EQ(mScheduleSearchView->m_maxWidth, 44);
}

//void CScheduleSearchView::slotsetSearch()
TEST_F(ut_schedulesearchview, slotsetSearch)
{
    //    mScheduleSearchView->slotsetSearch("jie");
}

//void CScheduleSearchView::createItemWidget(ScheduleDataInfo info, QDate date, int rtype)
TEST_F(ut_schedulesearchview, createItemWidget)
{
    ScheduleDataInfo scheduleinof = getScheduleDInfo().first();
    mScheduleSearchView->createItemWidget(scheduleinof, QDate::currentDate(), 3);
    ASSERT_EQ(qobject_cast<CScheduleSearchItem *>(mScheduleSearchView->m_gradientItemList->itemWidget(mScheduleSearchView->m_gradientItemList->item(0)))->m_date, QDate::currentDate());
}

//QListWidgetItem *CScheduleSearchView::createItemWidget(QDate date)
TEST_F(ut_schedulesearchview, createItemWidgetDate)
{
    QListWidgetItem *itm = mScheduleSearchView->createItemWidget(QDate::currentDate());
    ASSERT_EQ(itm->sizeHint(), QSize(mScheduleSearchView->m_maxWidth - 25, 36));
}

//void CScheduleSearchView::slotSelectSchedule(const ScheduleDataInfo &scheduleInfo)
TEST_F(ut_schedulesearchview, slotSelectSchedule)
{
    QSignalSpy spy(mScheduleSearchView, SIGNAL(signalSelectSchedule(const ScheduleDataInfo &)));
    ScheduleDataInfo scheduleinof = getScheduleDInfo().first();
    mScheduleSearchView->slotSelectSchedule(scheduleinof);
    ASSERT_EQ(spy.count(), 1);
}
QString stub_str = "";
void stub_slotsetSearch(QString str)
{
    stub_str = "stub_slotsetSearch";
}

//void CScheduleSearchView::updateSearch()
TEST_F(ut_schedulesearchview, updateSearch)
{
    Stub st;
    st.set(ADDR(CScheduleSearchView, slotsetSearch), stub_slotsetSearch);
    mScheduleSearchView->updateSearch();
    ASSERT_TRUE(stub_str != "stub_slotsetSearch");
}

//void CScheduleSearchDateItem::setBackgroundColor(QColor color1)
TEST_F(ut_schedulesearchview, setBachgroundColor)
{
    QColor color1(240, 100, 100);
    mScheduleSearchDateItem->setBackgroundColor(color1);
    ASSERT_EQ(mScheduleSearchDateItem->m_Backgroundcolor, color1);
}

//void CScheduleSearchDateItem::setText(QColor tcolor, QFont font)
TEST_F(ut_schedulesearchview, setText)
{
    QColor color(240, 100, 100);
    QFont font;
    font.setWeight(QFont::Medium);
    font.setPixelSize(DDECalendar::FontSizeTwelve);
    mScheduleSearchDateItem->setText(color, font);
    ASSERT_EQ(mScheduleSearchDateItem->m_textcolor, color);
}

//void CScheduleSearchDateItem::setDate(QDate date)
TEST_F(ut_schedulesearchview, setDate)
{
    mScheduleSearchDateItem->setDate(QDate::currentDate());
    ASSERT_EQ(mScheduleSearchDateItem->m_date, QDate::currentDate());
}

//void CScheduleSearchItem::setBackgroundColor(QColor color1)
TEST_F(ut_schedulesearchview, setBackGroundColor)
{
    QColor color(240, 100, 100);
    mScheduleSearchItem->setBackgroundColor(color);
    ASSERT_EQ(mScheduleSearchItem->m_Backgroundcolor, color);
}

//void CScheduleSearchItem::setSplitLineColor(QColor color1)
TEST_F(ut_schedulesearchview, setSplitLineColor)
{
    QColor color(240, 100, 100);
    mScheduleSearchItem->setSplitLineColor(color);
    ASSERT_EQ(mScheduleSearchItem->m_splitlinecolor, color);
}

//void CScheduleSearchItem::setText(QColor tcolor, QFont font)
TEST_F(ut_schedulesearchview, setItemText)
{
    QColor color(240, 100, 100);
    QFont font;
    font.setWeight(QFont::Medium);
    font.setPixelSize(DDECalendar::FontSizeTwelve);
    mScheduleSearchItem->setText(color, font);
    ASSERT_EQ(mScheduleSearchItem->m_tTextColor, color);
}

//void CScheduleSearchItem::setTimeC(QColor tcolor, QFont font)
TEST_F(ut_schedulesearchview, setTimeC)
{
    QColor color(240, 100, 100);
    QFont font;
    font.setWeight(QFont::Medium);
    font.setPixelSize(DDECalendar::FontSizeTwelve);
    mScheduleSearchItem->setTimeC(color, font);
    ASSERT_EQ(mScheduleSearchItem->m_timecolor, color);
}

//void CScheduleSearchItem::setData(ScheduleDataInfo vScheduleInfo, QDate date)
TEST_F(ut_schedulesearchview, setItemDate)
{
    ScheduleDataInfo scheduleinfo = getScheduleDInfo().first();
    mScheduleSearchItem->setData(scheduleinfo, QDate::currentDate());
    ASSERT_EQ(mScheduleSearchItem->m_date, QDate::currentDate());
}

//void CScheduleSearchItem::setRoundtype(int rtype)
TEST_F(ut_schedulesearchview, setRoundtype)
{
    mScheduleSearchItem->setRoundtype(3);
    mScheduleSearchItem->setRoundtype(2);
    ASSERT_EQ(mScheduleSearchItem->m_roundtype, 2);
}

//void CScheduleSearchItem::setTheMe(int type)
TEST_F(ut_schedulesearchview, setItemTheMe)
{
    mScheduleSearchItem->setTheMe(1);
    mScheduleSearchItem->setTheMe(2);
    ASSERT_EQ(mScheduleSearchItem->m_presscolor.timeColor.alphaF(), 1);
}

//void CScheduleSearchItem::slotEdit()
TEST_F(ut_schedulesearchview, slotEdit)
{
    //    ScheduleDataInfo scheduleinfo = getScheduleDInfo().first();
    //    mScheduleSearchItem->setData(scheduleinfo, QDate::currentDate());
    //    mScheduleSearchItem->slotEdit();
}

//void CScheduleSearchItem::slotDelete()
TEST_F(ut_schedulesearchview, slotDelete)
{
    //    ScheduleDataInfo scheduleinfo = getScheduleDInfo().first();
    //    mScheduleSearchItem->setData(scheduleinfo, QDate::currentDate());
    //    mScheduleSearchItem->slotDelete();
}

//const ScheduleDataInfo &getData() const
TEST_F(ut_schedulesearchview, getDate)
{
    ScheduleDataInfo sp = mScheduleSearchItem->getData();
    ASSERT_EQ(sp.m_ScheduleType, 1);
}

QMap<QDate, QVector<ScheduleDataInfo>> stub_getSearchScheduleInfo(void *obj, const QString &key, const QDateTime &startTime, const QDateTime &endTime)
{
    Q_UNUSED(obj)
    Q_UNUSED(key)
    Q_UNUSED(startTime)
    Q_UNUSED(endTime)
    QMap<QDate, QVector<ScheduleDataInfo>> searchScheduleInfo {};
    searchScheduleInfo[QDate::currentDate()] = TestDataInfo::getScheduleItemDInfo();
    return searchScheduleInfo;
}

//
TEST_F(ut_schedulesearchview, getPixmap)
{
    Stub stub;

    stub.set((QMap<QDate, QVector<ScheduleDataInfo>>(CScheduleTask::*)(const QString &, const QDateTime &, const QDateTime &))ADDR(CScheduleTask, getSearchScheduleInfo), stub_getSearchScheduleInfo);

    mScheduleSearchView->slotsetSearch("xjrc");
    mScheduleSearchView->setFixedSize(300, 800);
    QPixmap pixmap(mScheduleListWidget->size());
    pixmap = mScheduleSearchView->grab();
    ASSERT_EQ(pixmap.size(), mScheduleSearchView->size());
}
