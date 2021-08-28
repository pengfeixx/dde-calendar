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
#include "ut_graphicsscene.h"

#include <QDate>
#include <QFocusEvent>
#include <QApplication>
#include <QGraphicsRectItem>
#include "view/graphicsItem/cfocusitem.h"

ut_graphicsscene::ut_graphicsscene()
{
}

void ut_graphicsscene::SetUp()
{
    m_Scene = new CGraphicsScene();
}

void ut_graphicsscene::TearDown()
{
    delete m_Scene;
    m_Scene = nullptr;
}

TEST_F(ut_graphicsscene, getCurrentFocusItem)
{
    QGraphicsItem *item = m_Scene->getCurrentFocusItem();
    Q_UNUSED(item)
}

//setPrePage
TEST_F(ut_graphicsscene, setPrePage)
{
    m_Scene->setPrePage(QDate::currentDate(), false);
}

//focusInDeal
TEST_F(ut_graphicsscene, focusInDeal)
{
    m_Scene->setIsShowCurrentItem(true);
    QFocusEvent event(QEvent::FocusIn, Qt::TabFocusReason);
    QApplication::sendEvent(m_Scene, &event);
}

TEST_F(ut_graphicsscene, focusInDeal1)
{
    CFocusItem *item = new CFocusItem();
    m_Scene->setCurrentFocusItem(item);
    m_Scene->addItem(item);
    QFocusEvent event(QEvent::FocusIn, Qt::ActiveWindowFocusReason);
    QApplication::sendEvent(m_Scene, &event);
    m_Scene->clear();
}

//focusOutDeal
TEST_F(ut_graphicsscene, focusOutDeal)
{
    QFocusEvent event(QEvent::FocusOut, Qt::TabFocusReason);
    m_Scene->setActiveSwitching(true);
    QApplication::sendEvent(m_Scene, &event);
}

//focusOutDeal
TEST_F(ut_graphicsscene, focusOutDeal1)
{
    QFocusEvent event(QEvent::FocusOut, Qt::TabFocusReason);
    m_Scene->setActiveSwitching(false);
    QApplication::sendEvent(m_Scene, &event);
}

//setIsContextMenu
TEST_F(ut_graphicsscene, setIsContextMenu)
{
    m_Scene->setIsShowCurrentItem(false);
}

//currentItemInit
TEST_F(ut_graphicsscene, currentItemInit)
{
    CFocusItem *item = new CFocusItem();
    m_Scene->setCurrentFocusItem(item);
    m_Scene->addItem(item);
    m_Scene->currentItemInit();
    m_Scene->clear();
}

//getActiveSwitching
TEST_F(ut_graphicsscene, getActiveSwitching)
{
    m_Scene->getActiveSwitching();
}
