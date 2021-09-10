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
#include "ut_calldaykeyrightdeal.h"

#include "../third-party_stub/stub.h"
#include "view/graphicsItem/cweekdaybackgrounditem.h"
#include "keypressstub.h"

void ut_CAllDayKeyRightDeal::SetUp()
{
    m_scene = new CGraphicsScene();
    m_rightDeal = new CAllDayKeyRightDeal(m_scene);
}

void ut_CAllDayKeyRightDeal::TearDown()
{
    delete m_scene;
    delete m_rightDeal;
}

TEST_F(ut_CAllDayKeyRightDeal, focusItemDeal)
{
    KeyPressStub stub;
    CWeekDayBackgroundItem backgroundItem;
    EXPECT_TRUE(m_rightDeal->focusItemDeal(&backgroundItem, m_scene));
}
