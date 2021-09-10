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
#include "ut_ckeydowndeal.h"

#include "../third-party_stub/stub.h"
#include "view/graphicsItem/cscenebackgrounditem.h"
#include "keypressstub.h"

TEST(DownHandle_test, ut_CKeyDownDeal)
{
    KeyPressStub stub;
    CGraphicsScene *scene = new CGraphicsScene();
    CKeyDownDeal downDeal(scene);
    downDeal.dealEvent();
    delete scene;
}

void ut_CKeyDownDeal::SetUp()
{
    m_DownDeal = new CKeyDownDeal();
    m_scene = new CGraphicsScene();
}

void ut_CKeyDownDeal::TearDown()
{
    delete m_DownDeal;
    delete m_scene;
}

TEST_F(ut_CKeyDownDeal, focusItemDeal)
{
    KeyPressStub stub;
    CSceneBackgroundItem item(CSceneBackgroundItem::OnWeekView);
    bool deal = m_DownDeal->focusItemDeal(&item, m_scene);
    EXPECT_TRUE(deal);
}
