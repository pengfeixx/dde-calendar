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
#include "ut_schedulectrldlg.h"

#include <DPalette>

#include <QEvent>
#include <QApplication>
#include <QAbstractButton>

ut_schedulectrldlg::ut_schedulectrldlg()
{
}

void ut_schedulectrldlg::SetUp()
{
    mScheduleCtrlDlg = new CScheduleCtrlDlg();
}

void ut_schedulectrldlg::TearDown()
{
    delete mScheduleCtrlDlg;
    mScheduleCtrlDlg = nullptr;
}

//void CScheduleCtrlDlg::setTheMe(const int type)
TEST_F(ut_schedulectrldlg, setTheMe_001)
{
    DGUI_USE_NAMESPACE
    mScheduleCtrlDlg->setTheMe(1);
    QColor color("#000000");
    color.setAlphaF(0.9);
    EXPECT_EQ(mScheduleCtrlDlg->m_firstLabel->palette().color(DPalette::WindowText), color);
    mScheduleCtrlDlg->setTheMe(2);
}

TEST_F(ut_schedulectrldlg, setTheMe_002)
{
    DGUI_USE_NAMESPACE
    mScheduleCtrlDlg->setTheMe(2);
    QColor color("#FFFFFF");
    color.setAlphaF(0.9);
    EXPECT_EQ(mScheduleCtrlDlg->m_firstLabel->palette().color(DPalette::WindowText), color);
}

//void CScheduleCtrlDlg::buttonJudge(int id)
TEST_F(ut_schedulectrldlg, buttonJudge)
{
    mScheduleCtrlDlg->buttonJudge(1);
    EXPECT_EQ(1, mScheduleCtrlDlg->m_id);
}

//QAbstractButton *CScheduleCtrlDlg::addPushButton(QString btName, bool type)
TEST_F(ut_schedulectrldlg, addPushButton_001)
{
    QString title("testschedule");
    bool type = false;
    mScheduleCtrlDlg->addPushButton(title, type);
    EXPECT_TRUE(mScheduleCtrlDlg->str_btName.contains(title));
}

TEST_F(ut_schedulectrldlg, addPushButton_002)
{
    QString title("testschedule");
    bool type = true;
    mScheduleCtrlDlg->addPushButton(title, type);
    EXPECT_TRUE(mScheduleCtrlDlg->str_btName.contains(title));
}

//QAbstractButton *CScheduleCtrlDlg::addsuggestButton(QString btName, bool type)
TEST_F(ut_schedulectrldlg, addsuggestButton_001)
{
    QString title("testschedule");
    bool type = false;
    mScheduleCtrlDlg->addsuggestButton(title, type);
    EXPECT_TRUE(mScheduleCtrlDlg->str_btName.contains(title));
}

TEST_F(ut_schedulectrldlg, addsuggestButton_002)
{
    QString title("testschedule");
    bool type = true;
    mScheduleCtrlDlg->addsuggestButton(title, type);
    EXPECT_TRUE(mScheduleCtrlDlg->str_btName.contains(title));
}

//QAbstractButton *CScheduleCtrlDlg::addWaringButton(QString btName, bool type)
TEST_F(ut_schedulectrldlg, addWaringButton_001)
{
    QString title("testschedule");
    bool type = true;
    mScheduleCtrlDlg->addWaringButton(title, type);
    EXPECT_TRUE(mScheduleCtrlDlg->str_btName.contains(title));
}

TEST_F(ut_schedulectrldlg, addWaringButton_002)
{
    QString title("testschedule");
    bool type = false;
    mScheduleCtrlDlg->addWaringButton(title, type);
    EXPECT_TRUE(mScheduleCtrlDlg->str_btName.contains(title));
}

//void CScheduleCtrlDlg::setText(QString str)
TEST_F(ut_schedulectrldlg, setText)
{
    QString title("testschedule");
    mScheduleCtrlDlg->setText(title);
    EXPECT_EQ(title, mScheduleCtrlDlg->m_firstLabel->text());
    EXPECT_EQ(title, mScheduleCtrlDlg->m_firstLabel->toolTip());
}

//void CScheduleCtrlDlg::setInformativeText(QString str)
TEST_F(ut_schedulectrldlg, setInfomativeText)
{
    QString title("testschedule");
    mScheduleCtrlDlg->setInformativeText(title);
    EXPECT_EQ(title, mScheduleCtrlDlg->m_seconLabel->text());
    EXPECT_EQ(title, mScheduleCtrlDlg->m_seconLabel->toolTip());
}

//int CScheduleCtrlDlg::clickButton()
TEST_F(ut_schedulectrldlg, clickButton_001)
{
    mScheduleCtrlDlg->addPushButton("test");
    mScheduleCtrlDlg->addPushButton("test");
    mScheduleCtrlDlg->addPushButton("test");
    mScheduleCtrlDlg->m_id = -1;
    EXPECT_EQ(3, mScheduleCtrlDlg->clickButton());
}

TEST_F(ut_schedulectrldlg, clickButton_002)
{
    mScheduleCtrlDlg->addPushButton("test");
    mScheduleCtrlDlg->addPushButton("test");
    mScheduleCtrlDlg->addPushButton("test");
    mScheduleCtrlDlg->m_id = 8;
    EXPECT_EQ(3, mScheduleCtrlDlg->clickButton());
}

TEST_F(ut_schedulectrldlg, clickButton_003)
{
    mScheduleCtrlDlg->addPushButton("test");
    mScheduleCtrlDlg->addPushButton("test");
    mScheduleCtrlDlg->addPushButton("test");
    mScheduleCtrlDlg->m_id = 1;
    EXPECT_EQ(1, mScheduleCtrlDlg->clickButton());
}

//changeEvent
TEST_F(ut_schedulectrldlg, changeEvent)
{
    QString title("testschedule");
    mScheduleCtrlDlg->addPushButton(title);
    mScheduleCtrlDlg->addPushButton(title);

    QEvent event(QEvent::FontChange);
    QApplication::sendEvent(mScheduleCtrlDlg, &event);
    EXPECT_EQ(title, mScheduleCtrlDlg->getButton(0)->text());
}
