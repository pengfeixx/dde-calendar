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
#include "ut_ccustomtimeedit.h"

#include "../third-party_stub/stub.h"

#include <QTest>
#include <QFocusEvent>
#include <QLineEdit>

void ut_CCustomTimeEdit::SetUp()
{
    m_timeEdit = new CCustomTimeEdit();
}

void ut_CCustomTimeEdit::TearDown()
{
    delete m_timeEdit;
    m_timeEdit = nullptr;
}

bool isSetCursor = false;
void setCursorPosition_Stub(int)
{
    isSetCursor = true;
}
//mouseEventTest
TEST_F(ut_CCustomTimeEdit, mouseEventTest)
{
    QWidget *widget = new QWidget();
    m_timeEdit->setParent(widget);
    Stub stub;
    stub.set(ADDR(QLineEdit, setCursorPosition), setCursorPosition_Stub);
    QTest::mousePress(m_timeEdit, Qt::LeftButton);
    EXPECT_TRUE(isSetCursor);
    m_timeEdit->setParent(nullptr);
    delete  widget;
}

TEST_F(ut_CCustomTimeEdit, focusInEvent)
{
    QFocusEvent focusEvent_in(QEvent::FocusIn, Qt::FocusReason::ActiveWindowFocusReason);
    QApplication::sendEvent(m_timeEdit, &focusEvent_in);
    QObject::connect(m_timeEdit, &CCustomTimeEdit::signalUpdateFocus, [=](bool isFocus) {
        EXPECT_TRUE(isFocus);
    });
}

TEST_F(ut_CCustomTimeEdit, focusOutEvent)
{
    QFocusEvent focusEvent_out(QEvent::FocusOut, Qt::FocusReason::TabFocusReason);
    QApplication::sendEvent(m_timeEdit, &focusEvent_out);
    QObject::connect(m_timeEdit, &CCustomTimeEdit::signalUpdateFocus, [=](bool isFocus) {
        EXPECT_FALSE(isFocus);
    });
}

TEST_F(ut_CCustomTimeEdit, keyPressEvent)
{
    QWidget *widget = new QWidget();
    m_timeEdit->setParent(widget);
    QKeyEvent keyevent(QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);
    QApplication::sendEvent(m_timeEdit, &keyevent);
    EXPECT_EQ(m_timeEdit->lineEdit()->cursorPosition(), 0) << "position:" << m_timeEdit->lineEdit()->cursorPosition();
    m_timeEdit->setParent(nullptr);
    delete  widget;
}
