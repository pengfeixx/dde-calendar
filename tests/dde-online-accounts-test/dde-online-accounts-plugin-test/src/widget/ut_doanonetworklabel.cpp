/*
* Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
*
* Author:     wangyou <wangyou@uniontech.com>
*
* Maintainer: wangyou <wangyou@uniontech.com>
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
#include "ut_doanonetworklabel.h"

ut_doanonetworklabel::ut_doanonetworklabel()
{

}

void ut_doanonetworklabel::SetUp()
{
    doaNoNetWorkLabel = new DOANoNetWorkLabel();
}

void ut_doanonetworklabel::TearDown()
{
    delete doaNoNetWorkLabel;
    doaNoNetWorkLabel = nullptr;
}

TEST_F(ut_doanonetworklabel, ut_doanonetworklabel_setText_001)
{
    doaNoNetWorkLabel->setText("12345");
    EXPECT_EQ(doaNoNetWorkLabel->m_text, "12345");
}

TEST_F(ut_doanonetworklabel, ut_doanonetworklabel_getText_001)
{
    doaNoNetWorkLabel->setText("12345");
    EXPECT_EQ(doaNoNetWorkLabel->getText(), "12345");
}

TEST_F(ut_doanonetworklabel, ut_doanonetworklabel_paintEvent_001)
{
    doaNoNetWorkLabel->paintEvent(nullptr);
}
