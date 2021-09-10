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
#include "ut_todaybutton.h"

#include <DPalette>

#include <QTest>
#include <QFocusEvent>
#include <QEnterEvent>
//#include <QLeaveEvent>

ut_todaybutton::ut_todaybutton()
{

}

void ut_todaybutton::SetUp()
{
    mTodayButton = new CTodayButton();
}

void ut_todaybutton::TearDown()
{
    delete mTodayButton;
    mTodayButton = nullptr;
}

//void CTodayButton::setBColor(QColor normalC, QColor hoverC, QColor pressc, QColor normalC1, QColor hoverC1, QColor pressc1)
TEST_F(ut_todaybutton, setBColor)
{
    QColor normalC("#FFFFFF");
    QColor hoverC("#000000");
    QColor pressc("#000000");
    QColor normalC1("#FFFFFF");
    QColor hoverC1("#000000");
    QColor pressc1("#000000");
    mTodayButton->setBColor(normalC, hoverC, pressc, normalC1, hoverC1, pressc1);
    EXPECT_EQ(normalC, mTodayButton->m_bnormalColor);
    EXPECT_EQ(hoverC, mTodayButton->m_bhoverColor);
    EXPECT_EQ(pressc, mTodayButton->m_bPressColor);
    EXPECT_EQ(normalC1, mTodayButton->m_dbnormalColor);
    EXPECT_EQ(hoverC1, mTodayButton->m_dbhoverColor);
    EXPECT_EQ(pressc1, mTodayButton->m_dbPressColor);
}

//void CTodayButton::setTColor(QColor normalC, QColor hoverC, QColor pressc)
TEST_F(ut_todaybutton, setTColor)
{
    QColor normalC = Qt::red;
    QColor hoverC("#001A2E");
    QColor pressc("#0081FF");
    mTodayButton->setTColor(normalC, hoverC, pressc);
    EXPECT_EQ(normalC, mTodayButton->m_tnormalColor);
    EXPECT_EQ(hoverC, mTodayButton->m_thoverColor);
    EXPECT_EQ(pressc, mTodayButton->m_tPressColor);
}

//void CTodayButton::setshadowColor(QColor sc)
TEST_F(ut_todaybutton, setshadowColor)
{
    QColor shadowColr("#FFFFFF");
    mTodayButton->setshadowColor(shadowColr);
    EXPECT_EQ(shadowColr, mTodayButton->m_shadowColor);
}

//test mouse event
TEST_F(ut_todaybutton, mousePressEvent)
{
    QColor normalC = Qt::red;
    QColor hoverC("#001A2E");
    QColor pressc("#0081FF");
    mTodayButton->setTColor(normalC, hoverC, pressc);
    QColor normalC2("#FFFFFF");
    QColor hoverC2("#000000");
    QColor pressc2("#000000");
    QColor normalC1("#FFFFFF");
    QColor hoverC1("#000000");
    QColor pressc1("#000000");
    mTodayButton->setBColor(normalC2, hoverC2, pressc2, normalC1, hoverC1, pressc1);

    QTest::mousePress(mTodayButton, Qt::LeftButton);
    using namespace DTK_NAMESPACE::DGUI_NAMESPACE;
    DPalette pa = mTodayButton->palette();
    QColor pressColor = pa.color(DPalette::ButtonText);
    QColor DarkColor = pa.color(DPalette::Dark);
    QColor lightColor = pa.color(DPalette::Light);
    QColor shadowColor = pa.color(DPalette::Shadow);
    EXPECT_EQ(pressColor, pressc);
    EXPECT_EQ(DarkColor, pressc1);
    EXPECT_EQ(lightColor, pressc2);
    EXPECT_EQ(shadowColor, normalC2);
}
TEST_F(ut_todaybutton, mouseReleaseEvent)
{
    QColor normalC = Qt::red;
    QColor hoverC("#001A2E");
    QColor pressc("#0081FF");
    mTodayButton->setTColor(normalC, hoverC, pressc);
    QColor normalC2("#FFFFFF");
    QColor hoverC2("#000000");
    QColor pressc2("#000000");
    QColor normalC1("#FFFFFF");
    QColor hoverC1("#000000");
    QColor pressc1("#000000");
    mTodayButton->setBColor(normalC2, hoverC2, pressc2, normalC1, hoverC1, pressc1);

    QTest::mouseRelease(mTodayButton, Qt::LeftButton);

    using namespace DTK_NAMESPACE::DGUI_NAMESPACE;
    DPalette pa = mTodayButton->palette();
    QColor pressColor = pa.color(DPalette::ButtonText);
    QColor DarkColor = pa.color(DPalette::Dark);
    QColor lightColor = pa.color(DPalette::Light);
    QColor shadowColor = pa.color(DPalette::Shadow);
    EXPECT_EQ(pressColor, normalC);
    EXPECT_EQ(DarkColor, normalC1);
    EXPECT_EQ(lightColor, normalC2);
    EXPECT_EQ(shadowColor, normalC2);
}

//QTEST_MAIN(testGUI_toDayButton)
TEST_F(ut_todaybutton, focusOutEvent)
{
    QColor normalC = Qt::red;
    QColor hoverC("#001A2E");
    QColor pressc("#0081FF");
    mTodayButton->setTColor(normalC, hoverC, pressc);
    QColor normalC2("#FFFFFF");
    QColor hoverC2("#000000");
    QColor pressc2("#000000");
    QColor normalC1("#FFFFFF");
    QColor hoverC1("#000000");
    QColor pressc1("#000000");
    mTodayButton->setBColor(normalC2, hoverC2, pressc2, normalC1, hoverC1, pressc1);

    mTodayButton->setFocus();
    QFocusEvent focusEvent_out(QEvent::FocusOut, Qt::FocusReason::TabFocusReason);
    QApplication::sendEvent(mTodayButton, &focusEvent_out);
    using namespace DTK_NAMESPACE::DGUI_NAMESPACE;
    DPalette pa = mTodayButton->palette();
    QColor pressColor = pa.color(DPalette::ButtonText);
    QColor DarkColor = pa.color(DPalette::Dark);
    QColor lightColor = pa.color(DPalette::Light);
    QColor shadowColor = pa.color(DPalette::Shadow);
    EXPECT_EQ(pressColor, normalC);
    EXPECT_EQ(DarkColor, normalC1);
    EXPECT_EQ(lightColor, normalC2);
    EXPECT_EQ(shadowColor, normalC2);
}

TEST_F(ut_todaybutton, enterEvent)
{
    QColor normalC = Qt::red;
    QColor hoverC("#001A2E");
    QColor pressc("#0081FF");
    mTodayButton->setTColor(normalC, hoverC, pressc);
    QColor normalC2("#FFFFFF");
    QColor hoverC2("#000000");
    QColor pressc2("#000000");
    QColor normalC1("#FFFFFF");
    QColor hoverC1("#000000");
    QColor pressc1("#000000");
    mTodayButton->setBColor(normalC2, hoverC2, pressc2, normalC1, hoverC1, pressc1);

    QEnterEvent enterEvent(QPointF(10, 2), QPointF(11, 3), QPointF(12, 4));
    QApplication::sendEvent(mTodayButton, &enterEvent);

    using namespace DTK_NAMESPACE::DGUI_NAMESPACE;
    DPalette pa = mTodayButton->palette();
    QColor pressColor = pa.color(DPalette::ButtonText);
    QColor DarkColor = pa.color(DPalette::Dark);
    QColor lightColor = pa.color(DPalette::Light);
    QColor shadowColor = pa.color(DPalette::Shadow);
    EXPECT_EQ(pressColor, hoverC);
    EXPECT_EQ(DarkColor, hoverC1);
    EXPECT_EQ(lightColor, hoverC2);
    EXPECT_EQ(shadowColor, normalC2);
}

TEST_F(ut_todaybutton, leaveEvent)
{
    QColor normalC = Qt::red;
    QColor hoverC("#001A2E");
    QColor pressc("#0081FF");
    mTodayButton->setTColor(normalC, hoverC, pressc);
    QColor normalC2("#FFFFFF");
    QColor hoverC2("#000000");
    QColor pressc2("#000000");
    QColor normalC1("#FFFFFF");
    QColor hoverC1("#000000");
    QColor pressc1("#000000");
    mTodayButton->setBColor(normalC2, hoverC2, pressc2, normalC1, hoverC1, pressc1);

    QEvent event(QEvent::Leave);
    QApplication::sendEvent(mTodayButton, &event);
    using namespace DTK_NAMESPACE::DGUI_NAMESPACE;
    DPalette pa = mTodayButton->palette();
    QColor pressColor = pa.color(DPalette::ButtonText);
    QColor DarkColor = pa.color(DPalette::Dark);
    QColor lightColor = pa.color(DPalette::Light);
    QColor shadowColor = pa.color(DPalette::Shadow);
    EXPECT_EQ(pressColor, normalC);
    EXPECT_EQ(DarkColor, normalC1);
    EXPECT_EQ(lightColor, normalC2);
    EXPECT_EQ(shadowColor, normalC2);
}

TEST_F(ut_todaybutton, keypressEvent)
{
    bool isClicked = false;
    QObject::connect(mTodayButton, &CTodayButton::clicked, [&] {
        isClicked = true;
    });
    QKeyEvent keyevent(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);
    QApplication::sendEvent(mTodayButton, &keyevent);
    EXPECT_TRUE(isClicked);
}
