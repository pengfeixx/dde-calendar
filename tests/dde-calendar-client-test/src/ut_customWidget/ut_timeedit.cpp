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
#include "ut_timeedit.h"

#include <QPixmap>
#include <QFocusEvent>
#include <QApplication>

ut_timeedit::ut_timeedit()
{
}

void ut_timeedit::SetUp()
{
    mTimeEdit = new CTimeEdit();
}

void ut_timeedit::TearDown()
{
    delete mTimeEdit;
    mTimeEdit = nullptr;
}

//void CTimeEdit::setTime(QTime time)
TEST_F(ut_timeedit, setTime)
{
    QTime current = QTime::currentTime();
    mTimeEdit->setTime(current);
    EXPECT_EQ(current, mTimeEdit->m_time);
    QString timeStr = current.toString(mTimeEdit->m_timeFormat);
    EXPECT_EQ(timeStr, mTimeEdit->m_timeEdit->getLineEdit()->text());
}

//QTime CTimeEdit::getTime()
TEST_F(ut_timeedit, getTime)
{
    QTime current = QTime::currentTime();
    mTimeEdit->setTime(current);
    mTimeEdit->getTime();
    EXPECT_EQ(current.hour(), mTimeEdit->m_time.hour());
    EXPECT_EQ(current.minute(), mTimeEdit->m_time.minute());
}

//setTimeFormat
TEST_F(ut_timeedit, setTimeFormat_001)
{
    mTimeEdit->setTimeFormat(0);
    EXPECT_EQ("h:mm", mTimeEdit->m_timeFormat);
}

TEST_F(ut_timeedit, setTimeFormat_002)
{
    mTimeEdit->setTimeFormat(1);
    EXPECT_EQ("hh:mm", mTimeEdit->m_timeFormat);
}

//slotFocusDraw
TEST_F(ut_timeedit, slotFocusDraw)
{
    mTimeEdit->slotFocusDraw(false);
    EXPECT_EQ(false, mTimeEdit->m_hasFocus);
}

//getPixmap
TEST_F(ut_timeedit, getPixmap)
{
    mTimeEdit->slotFocusDraw(true);
    mTimeEdit->setFixedSize(200, 50);
    QPixmap pixmap(mTimeEdit->size());
    mTimeEdit->render(&pixmap);
    EXPECT_EQ(pixmap.size(), mTimeEdit->size());
}

TEST_F(ut_timeedit, focusInEvent)
{
    mTimeEdit->setCurrentIndex(1);
    QFocusEvent focusEvent_in(QEvent::FocusIn, Qt::FocusReason::TabFocusReason);
    QApplication::sendEvent(mTimeEdit, &focusEvent_in);

    EXPECT_NE(mTimeEdit->lineEdit()->selectedText(), "");
}
