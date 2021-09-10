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
#include "ut_cweekdayscenetabkeydeal.h"

#include "../third-party_stub/stub.h"
#include "view/graphicsItem/cweekdaybackgrounditem.h"
#include "keypressstub.h"

void ut_CWeekDaySceneTabKeyDeal::SetUp()
{
    m_scene = new CGraphicsScene();
    m_weekTabDeal = new CWeekDaySceneTabKeyDeal();
}

void ut_CWeekDaySceneTabKeyDeal::TearDown()
{
    delete m_scene;
    delete m_weekTabDeal;
}

TEST_F(ut_CWeekDaySceneTabKeyDeal, focusItemDeal_001)
{
    CWeekDayBackgroundItem item;
    bool deal = m_weekTabDeal->focusItemDeal(&item, m_scene);
    EXPECT_TRUE(deal);
}

TEST_F(ut_CWeekDaySceneTabKeyDeal, focusItemDeal_002)
{
    bool deal = m_weekTabDeal->focusItemDeal(nullptr, m_scene);
    EXPECT_FALSE(deal);
}
