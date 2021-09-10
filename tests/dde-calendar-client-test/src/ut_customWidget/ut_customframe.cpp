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
#include "ut_customframe.h"

ut_customframe::ut_customframe()
{
}

void ut_customframe::SetUp()
{
    mCustomFrame = new CustomFrame();
}

void ut_customframe::TearDown()
{
    delete mCustomFrame;
    mCustomFrame = nullptr;
}

//void CustomFrame::setBColor(QColor normalC)
TEST_F(ut_customframe, setBcolor)
{
    QColor color(Qt::red);
    mCustomFrame->setBColor(color);
    EXPECT_TRUE(mCustomFrame->m_bflag);
    EXPECT_EQ(color, mCustomFrame->m_bnormalColor);
}

//void CustomFrame::setRoundState(bool lstate, bool tstate, bool rstate, bool bstate)
TEST_F(ut_customframe, setRoundState)
{
    bool lstate = true;
    bool tstate = true;
    bool retate = true;
    bool bstate = true;
    mCustomFrame->setRoundState(lstate, tstate, retate, bstate);
    EXPECT_EQ(lstate, mCustomFrame->m_lstate);
    EXPECT_EQ(tstate, mCustomFrame->m_tstate);
    EXPECT_EQ(retate, mCustomFrame->m_rstate);
    EXPECT_EQ(bstate, mCustomFrame->m_bstate);
}

//void CustomFrame::setTextStr(QFont font, QColor tc, QString strc, int flag)
TEST_F(ut_customframe, setTextStr)
{
    QFont font;
    QColor color(Qt::yellow);
    QString str("uttest");
    mCustomFrame->setTextStr(font, color, str, 1);
    EXPECT_EQ(font, mCustomFrame->m_font);
    EXPECT_EQ(color, mCustomFrame->m_tnormalColor);
    EXPECT_EQ(str, mCustomFrame->m_text);
    EXPECT_EQ(1, mCustomFrame->m_textflag);
}

//void CustomFrame::setTextStr(QString strc)
TEST_F(ut_customframe, setTextstr)
{
    QString str("uttest");
    mCustomFrame->setTextStr(str);
    EXPECT_EQ(str, mCustomFrame->m_text) << "custonText:" << mCustomFrame->m_text.toStdString();
}

//void CustomFrame::setTextColor(QColor tc)
TEST_F(ut_customframe, setTextColor)
{
    QColor color(Qt::yellow);
    mCustomFrame->setTextColor(color);
    EXPECT_EQ(color, mCustomFrame->m_tnormalColor);
}

//void CustomFrame::setTextFont(QFont font)
TEST_F(ut_customframe, setTextFont)
{
    QFont font;
    mCustomFrame->setTextFont(font);
    EXPECT_EQ(font, mCustomFrame->m_font);
}

//void CustomFrame::setTextAlign(int flag)
TEST_F(ut_customframe, setTextAlign)
{
    mCustomFrame->setTextAlign(2);
    EXPECT_EQ(2, mCustomFrame->m_textflag);
}

//void CustomFrame::setRadius(int radius)
TEST_F(ut_customframe, setRadius)
{
    mCustomFrame->setRadius(4);
    EXPECT_EQ(4, mCustomFrame->m_radius);
}

//void CustomFrame::setboreder(int framew)
TEST_F(ut_customframe, setboreder)
{
    mCustomFrame->setboreder(4);
    EXPECT_EQ(4, mCustomFrame->m_borderframew);
}

//void CustomFrame::setFixedSize(int w, int h)
TEST_F(ut_customframe, setFixedSize)
{
    mCustomFrame->setFixedSize(40, 44);
    EXPECT_TRUE(mCustomFrame->m_fixsizeflag);
    EXPECT_EQ(44, mCustomFrame->height());
    EXPECT_EQ(40, mCustomFrame->width());
}

