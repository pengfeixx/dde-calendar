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
#include "ut_dayhuangliview.h"

ut_dayhuangliview::ut_dayhuangliview()
{
}

void ut_dayhuangliview::SetUp()
{
    mDayHuangLiLabel = new CDayHuangLiLabel();
}

void ut_dayhuangliview::TearDown()
{
    delete mDayHuangLiLabel;
    mDayHuangLiLabel = nullptr;
}

//void CDayHuangLiLabel::setbackgroundColor(QColor backgroundColor)
TEST_F(ut_dayhuangliview, setbackgroundColor)
{
    QColor setColor(50, 60, 87);
    mDayHuangLiLabel->setbackgroundColor(setColor);
    EXPECT_EQ(setColor, mDayHuangLiLabel->m_backgroundColor);
}

//void CDayHuangLiLabel::setTextInfo(QColor tcolor, QFont font)
TEST_F(ut_dayhuangliview, setTextInfo)
{
    QColor setColor(10, 60, 47);
    QFont font;
    font.setWeight(10);
    mDayHuangLiLabel->setTextInfo(setColor, font);
    EXPECT_EQ(setColor, mDayHuangLiLabel->m_textcolor);
    EXPECT_EQ(font, mDayHuangLiLabel->m_font);
}

//void CDayHuangLiLabel::setHuangLiText(QStringList vhuangli, int type)
TEST_F(ut_dayhuangliview, setHuangLiText_001)
{
    QStringList strlist {"嫁娶", "入土"};
    QString testList("嫁娶.入土");
    int type = 1;
    mDayHuangLiLabel->setHuangLiText(strlist, 1);
    EXPECT_EQ(mDayHuangLiLabel->toolTip(), testList);
    EXPECT_EQ(type, mDayHuangLiLabel->m_type);
}

TEST_F(ut_dayhuangliview, setHuangLiText_002)
{
    QStringList strlist {};
    int type = 1;
    mDayHuangLiLabel->setHuangLiText(strlist, 1);
    EXPECT_EQ(mDayHuangLiLabel->toolTip(), QString());
    EXPECT_EQ(type, mDayHuangLiLabel->m_type);
}

TEST_F(ut_dayhuangliview, getPixmap)
{
    mDayHuangLiLabel->setbackgroundColor(QColor(100, 100, 255));
    mDayHuangLiLabel->setFixedSize(200, 50);
    QPixmap pixmap(mDayHuangLiLabel->size());
    mDayHuangLiLabel->render(&pixmap);
    EXPECT_EQ(pixmap.size(), mDayHuangLiLabel->size());
}
