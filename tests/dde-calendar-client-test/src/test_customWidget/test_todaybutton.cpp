// SPDX-FileCopyrightText: 2019 - 2026 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "test_todaybutton.h"

#include <QTest>
#include <QFocusEvent>
#include <QEnterEvent>
//#include <QLeaveEvent>

test_todaybutton::test_todaybutton()
{

}

void test_todaybutton::SetUp()
{
    mTodayButton = new CTodayButton();
}

void test_todaybutton::TearDown()
{
    delete mTodayButton;
    mTodayButton = nullptr;
}

// These methods were removed from CTodayButton in the current version
// TEST_F(test_todaybutton, setBColor) { ... }
// TEST_F(test_todaybutton, setTColor) { ... }
// TEST_F(test_todaybutton, setshadowColor) { ... }

//test mouse event
TEST_F(test_todaybutton, mouseEventTest)
{
    QTest::mousePress(mTodayButton, Qt::LeftButton);
    QTest::mouseRelease(mTodayButton, Qt::LeftButton);

    QWidget *testWidget = new QWidget();
    CTodayButton *toDayButton = new CTodayButton(testWidget);
    toDayButton->setGeometry(10, 10, 20, 20);
    testWidget->setFixedSize(50, 50);
    toDayButton->setFocus(Qt::TabFocusReason);
    QTest::mouseMove(testWidget, QPoint(2, 2));
    QTest::mouseMove(testWidget, QPoint(15, 15));
    QTest::mouseMove(testWidget, QPoint(45, 45));
    QTest::keyClick(testWidget, Qt::Key_Tab);
    QTest::keyClick(testWidget->focusWidget(), Qt::Key_Tab);
    QTest::keyClick(testWidget->focusWidget(), Qt::Key_Tab);
    delete testWidget;
}

//test key event
TEST_F(test_todaybutton, keyEventTest)
{
    QTest::keyClick(mTodayButton, Qt::Key_Enter);
    QTest::keyClick(mTodayButton, Qt::Key_Tab);
}

//QTEST_MAIN(testGUI_toDayButton)
TEST_F(test_todaybutton,focusOutEvent)
{
    mTodayButton->setFocus();
    QFocusEvent focusEvent_out( QEvent::FocusOut,Qt::FocusReason::TabFocusReason);
    QApplication::sendEvent(mTodayButton,&focusEvent_out);
}

TEST_F(test_todaybutton,enterEvent)
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    QEnterEvent enterEvent(QPointF(10,2), QPointF(11,3), QPointF(10,2));
#else
    QEnterEvent enterEvent(QPointF(10,2), QPointF(11,3), QPointF(12,4));
#endif
    QApplication::sendEvent(mTodayButton,&enterEvent);
    QEvent event(QEvent::Leave);
    QApplication::sendEvent(mTodayButton,&event);
}

TEST_F(test_todaybutton,keypressEvent)
{
    QKeyEvent keyevent(QEvent::KeyPress,Qt::Key_Return,Qt::NoModifier);
    QApplication::sendEvent(mTodayButton,&keyevent);
}
