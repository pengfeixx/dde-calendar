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
#include "ut_doapasswordedit.h"
#include "../../third-party_stub/stub.h"
#include <QSignalSpy>

ut_doapasswordedit::ut_doapasswordedit()
{

}

static QString resultMsg = "";
void ut_doapasswordedit::stub_resutlMsg()
{
    resultMsg = "resultMsg";
}

void ut_doapasswordedit::SetUp()
{
    doaPasswordEdit = new DOAPasswordEdit();
}

void ut_doapasswordedit::TearDown()
{
    delete doaPasswordEdit;
    doaPasswordEdit = nullptr;
}

TEST_F(ut_doapasswordedit, ut_doapasswordedit_setPasswordButtonAutoHide_001)
{
    doaPasswordEdit->setPasswordButtonAutoHide(false);
    EXPECT_EQ(doaPasswordEdit->m_PasswordBtnAutoHide, false);
}

TEST_F(ut_doapasswordedit, ut_doapasswordedit_getPasswordButtonAutoHide_001)
{
    doaPasswordEdit->setPasswordButtonAutoHide(true);
    EXPECT_EQ(doaPasswordEdit->getPasswordButtonAutoHide(), true);
}

TEST_F(ut_doapasswordedit, ut_doapasswordedit_setText_001)
{
    doaPasswordEdit->setText("12345");
    EXPECT_EQ(doaPasswordEdit->m_password, "12345");
    EXPECT_EQ(doaPasswordEdit->text(), "12345");
}

TEST_F(ut_doapasswordedit, ut_doapasswordedit_focusOutHandle_001)
{
    doaPasswordEdit->m_password = "12345";
    doaPasswordEdit->focusOutHandle();
    EXPECT_EQ(doaPasswordEdit->text(), "12345");
}

TEST_F(ut_doapasswordedit, ut_doapasswordedit_focusOutHandle_002)
{
    doaPasswordEdit->setText("123456");
    doaPasswordEdit->m_password = "12345";
    QSignalSpy spy(doaPasswordEdit, SIGNAL(signalePasswordChanged(const QString &)));
    doaPasswordEdit->focusOutHandle();

    EXPECT_EQ(doaPasswordEdit->m_password, "123456");
    EXPECT_EQ(spy.count(), 1);
}

TEST_F(ut_doapasswordedit, ut_doapasswordedit_eventFilter_001)
{
    QEvent event(QEvent::MouseButtonPress);
    EXPECT_EQ(doaPasswordEdit->eventFilter(nullptr, &event), false);
}

TEST_F(ut_doapasswordedit, ut_doapasswordedit_eventFilter_002)
{
    doaPasswordEdit->m_PasswordBtnAutoHide = true;
    QEvent event(QEvent::MouseButtonPress);
    EXPECT_EQ(doaPasswordEdit->eventFilter(doaPasswordEdit->m_PasswordBtn, &event), false);
}

TEST_F(ut_doapasswordedit, ut_doapasswordedit_eventFilter_003)
{
    doaPasswordEdit->m_PasswordBtnAutoHide = true;
    Stub st;
    st.set(ADDR(DOAPasswordEdit, focusOutHandle), ADDR(ut_doapasswordedit, stub_resutlMsg));
    resultMsg = "eventFilter";
    QEvent event(QEvent::FocusOut);
    doaPasswordEdit->eventFilter(doaPasswordEdit->m_PasswordBtn, &event);
    EXPECT_EQ(resultMsg, "resultMsg");
}

TEST_F(ut_doapasswordedit, ut_doapasswordedit_eventFilter_004)
{
    doaPasswordEdit->m_PasswordBtnAutoHide = true;
    Stub st;
    st.set(ADDR(DOAPasswordEdit, focusOutHandle), ADDR(ut_doapasswordedit, stub_resutlMsg));
    resultMsg = "eventFilter";
    QEvent event(QEvent::FocusOut);
    doaPasswordEdit->eventFilter(doaPasswordEdit->lineEdit(), &event);
    EXPECT_EQ(resultMsg, "resultMsg");
}

TEST_F(ut_doapasswordedit, ut_doapasswordedit_eventFilter_005)
{
    doaPasswordEdit->m_PasswordBtnAutoHide = true;
    Stub st;
    st.set(ADDR(DOAPasswordEdit, focusOutHandle), ADDR(ut_doapasswordedit, stub_resutlMsg));
    resultMsg = "eventFilter";
    QEvent event(QEvent::FocusOut);
    doaPasswordEdit->m_PasswordBtn->setFocus();
    doaPasswordEdit->eventFilter(doaPasswordEdit->lineEdit(), &event);
    EXPECT_EQ(resultMsg, "eventFilter");
}

TEST_F(ut_doapasswordedit, ut_doapasswordedit_eventFilter_006)
{
    doaPasswordEdit->m_PasswordBtnAutoHide = true;
    Stub st;
    st.set(ADDR(DOAPasswordEdit, focusOutHandle), ADDR(ut_doapasswordedit, stub_resutlMsg));
    resultMsg = "eventFilter";
    QEvent event(QEvent::FocusOut);
    doaPasswordEdit->lineEdit()->setFocus();
    doaPasswordEdit->eventFilter(doaPasswordEdit->m_PasswordBtn, &event);
    EXPECT_EQ(resultMsg, "eventFilter");
}

TEST_F(ut_doapasswordedit, ut_doapasswordedit_slotTextChanged_001)
{
    doaPasswordEdit->setEchoButtonIsVisible(false);
    doaPasswordEdit->slotTextChanged("");

    EXPECT_EQ(doaPasswordEdit->echoButtonIsVisible(), false);
}

TEST_F(ut_doapasswordedit, ut_doapasswordedit_slotTextChanged_002)
{
    doaPasswordEdit->setEchoButtonIsVisible(false);
    doaPasswordEdit->slotTextChanged("");

    EXPECT_EQ(doaPasswordEdit->echoButtonIsVisible(), false);
}

TEST_F(ut_doapasswordedit, ut_doapasswordedit_slotTextChanged_003)
{
    doaPasswordEdit->setEchoButtonIsVisible(true);
    doaPasswordEdit->slotTextChanged("1234");

    EXPECT_EQ(doaPasswordEdit->echoButtonIsVisible(), false);
}


