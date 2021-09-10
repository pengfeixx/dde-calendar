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
#include "ut_ckeyrightdeal.h"

#include "../third-party_stub/stub.h"
#include "view/graphicsItem/cscenebackgrounditem.h"
#include "keypressstub.h"

void ut_CKeyRightDeal::SetUp()
{
    m_rightDeal = new CKeyRightDeal();
    m_scene = new CGraphicsScene();
}

void ut_CKeyRightDeal::TearDown()
{
    delete m_rightDeal;
    delete m_scene;
}

TEST_F(ut_CKeyRightDeal, focusItemDeal)
{
    CSceneBackgroundItem item(CSceneBackgroundItem::OnDayView);
    bool deal = m_rightDeal->focusItemDeal(&item, m_scene);
    EXPECT_TRUE(deal);
}
