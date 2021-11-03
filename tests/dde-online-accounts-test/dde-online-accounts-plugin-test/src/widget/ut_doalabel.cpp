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
#include "ut_doalabel.h"
#include "../../third-party_stub/stub.h"

#include <DFontSizeManager>

#include <QEvent>
#include <QResizeEvent>
#include <QDebug>

DWIDGET_USE_NAMESPACE

ut_doalabel::ut_doalabel()
{

}

static QString resultMsg = "";
void ut_doalabel::stub_resutlMsg()
{
    resultMsg = "resultMsg";
}

void ut_doalabel::SetUp()
{
    doaLabel = new DOALabel();
}

void ut_doalabel::TearDown()
{
    delete doaLabel;
    doaLabel = nullptr;
}

TEST_F(ut_doalabel, ut_doalabel_setShowText_001)
{
    doaLabel->setShowText("1234");
    EXPECT_EQ(doaLabel->m_text, "1234");
}

TEST_F(ut_doalabel, ut_doalabel_changeEvent_001)
{
    Stub st;
    st.set(ADDR(DOALabel, setTextByWidth), ADDR(ut_doalabel, stub_resutlMsg));
    QEvent e(QEvent::FontChange);
    resultMsg = "changeEvent";
    doaLabel->changeEvent(&e);
    EXPECT_EQ(resultMsg, "resultMsg");
}

TEST_F(ut_doalabel, ut_doalabel_resizeEvent_001)
{
    Stub st;
    st.set(ADDR(DOALabel, setTextByWidth), ADDR(ut_doalabel, stub_resutlMsg));
    QResizeEvent resizeevent(QSize(40, 60), QSize(40, 80));
    resultMsg = "resizeEvent";
    doaLabel->resizeEvent(&resizeevent);
    EXPECT_EQ(resultMsg, "resultMsg");
}

TEST_F(ut_doalabel, ut_doalabel_setTextByWidth_001)
{
    doaLabel->setFixedWidth(50);
    doaLabel->m_text = "123451234556";
    DFontSizeManager::instance()->bind(doaLabel, DFontSizeManager::T8, QFont::Normal);
    doaLabel->setTextByWidth();
    qWarning() << doaLabel->text();
    EXPECT_TRUE(doaLabel->text().contains("…"));
}
