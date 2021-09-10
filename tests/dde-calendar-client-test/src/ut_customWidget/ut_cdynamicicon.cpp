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
#include "ut_cdynamicicon.h"

ut_cdynamicicon::ut_cdynamicicon()
{
}

void ut_cdynamicicon::SetUp()
{
    mDynamicicon = CDynamicIcon::getInstance();
}

void ut_cdynamicicon::TearDown()
{
    CDynamicIcon::releaseInstance();
    mDynamicicon = nullptr;
}

//void CDynamicIcon::setDate(const QDate &date)
TEST_F(ut_cdynamicicon, setDate)
{
    QDate currentDate = QDate::currentDate();
    mDynamicicon->setDate(currentDate);
    EXPECT_EQ(currentDate, mDynamicicon->m_Date);
}

//void CDynamicIcon::setTitlebar(DTitlebar *titlebar)
TEST_F(ut_cdynamicicon, setTitlebar)
{
    DTitlebar *titlebar = nullptr;
    mDynamicicon->setTitlebar(titlebar);
    EXPECT_EQ(titlebar, mDynamicicon->m_Titlebar);
}

TEST_F(ut_cdynamicicon, paintPixmap)
{
    QDate currentDate = QDate::currentDate();
    mDynamicicon->setDate(currentDate);
    QPixmap pixmap(QSize(20, 20));
    mDynamicicon->paintPixmap(&pixmap);
    EXPECT_EQ(pixmap.size(), QSize(20, 20));
}
