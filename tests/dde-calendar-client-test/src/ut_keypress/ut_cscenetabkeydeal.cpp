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
#include "ut_cscenetabkeydeal.h"

#include "../third-party_stub/stub.h"
#include "view/graphicsItem/cscenebackgrounditem.h"
#include "keypressstub.h"


TEST(SceneTabHandle_test, ut_CSceneTabKeyDeal)
{
    KeyPressStub stub;
    CGraphicsScene *scene = new CGraphicsScene();
    CSceneTabKeyDeal tabDeal(scene);
    tabDeal.dealEvent();
    delete scene;
}

void ut_CSceneTabKeyDeal::SetUp()
{
    m_scene = new CGraphicsScene();
    m_sceneTabDeal = new CSceneTabKeyDeal();
}

void ut_CSceneTabKeyDeal::TearDown()
{
    delete m_scene;
    delete m_sceneTabDeal;
}

void setItemFocus_stub(void *obj, bool isFoucs) {
    Q_UNUSED(obj)
        Q_UNUSED(isFoucs)}

TEST_F(ut_CSceneTabKeyDeal, focusItemDeal_001)
{
    //    KeyPressStub stub;
    typedef void (*fptr)(CSceneBackgroundItem *, bool);
    fptr A_foo = (fptr)(&CSceneBackgroundItem::setItemFocus);
    Stub stub;
    stub.set(A_foo, setItemFocus_stub);
    CSceneBackgroundItem item(CSceneBackgroundItem::OnMonthView);
    bool deal = m_sceneTabDeal->focusItemDeal(&item, m_scene);
    EXPECT_FALSE(deal);
}
