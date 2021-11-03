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
#include "ut_doaerrorwidget.h"
#include "../../third-party_stub/stub.h"

#include <QSignalSpy>
#include <QMouseEvent>
#include <QDebug>
#include <QPaintEvent>

ut_doaerrorwidget::ut_doaerrorwidget()
{

}

void ut_doaerrorwidget::SetUp()
{
    doaErrorWidget = new DOAErrorWidget();
}

void ut_doaerrorwidget::TearDown()
{
    delete doaErrorWidget;
    doaErrorWidget = nullptr;
}

static QString resultMsg = "";
void ut_doaerrorwidget::stub_resutlMsg()
{
    resultMsg = "resultMsg";
}

TEST_F(ut_doaerrorwidget, ut_doaerrorwidget_setErrorMsg_001)
{
    doaErrorWidget->setErrorMsg(DOAAccount::AccountState::Account_ServerException);
    EXPECT_EQ(doaErrorWidget->m_errorMsgState, DOAErrorWidget::MsgShow_TryAgain);
}

TEST_F(ut_doaerrorwidget, ut_doaerrorwidget_setErrorMsg_002)
{
    doaErrorWidget->m_tryAgainState.isClicked = true;
    doaErrorWidget->setErrorMsg(DOAAccount::AccountState::Account_AuthenticationFailed);
    EXPECT_EQ(doaErrorWidget->m_errorMsgState, DOAErrorWidget::MsgShow_NoTryAgain);
}

TEST_F(ut_doaerrorwidget, ut_doaerrorwidget_setErrorMsg_003)
{
    doaErrorWidget->m_tryAgainState.isClicked = true;
    doaErrorWidget->setErrorMsg(DOAAccount::AccountState::Account_Success);
    EXPECT_EQ(doaErrorWidget->m_errorMsgState, DOAErrorWidget::MsgHide);
}

TEST_F(ut_doaerrorwidget, ut_doaerrorwidget_setErrorMsg_004)
{
    doaErrorWidget->m_tryAgainState.isClicked = true;
    doaErrorWidget->setErrorMsg(DOAAccount::AccountState::Account_NetWorkException);
    EXPECT_EQ(doaErrorWidget->m_errorMsgState, DOAErrorWidget::MsgShow_TryAgain);
}

TEST_F(ut_doaerrorwidget, ut_doaerrorwidget_initData_001)
{
    doaErrorWidget->m_tryAgainState.isClicked = true;
    QSignalSpy spy(doaErrorWidget, SIGNAL(sign_EventQuit()));
    doaErrorWidget->initData();
    EXPECT_EQ(doaErrorWidget->m_tryAgainState.isClicked, false);
    EXPECT_EQ(spy.count(), 1);
}

TEST_F(ut_doaerrorwidget, ut_doaerrorwidget_slot_tryAgain_001)
{
    QSignalSpy spy(doaErrorWidget, SIGNAL(sign_tryAgain()));
    doaErrorWidget->slot_tryAgain();
    EXPECT_EQ(doaErrorWidget->m_spinner->isPlaying(), true);
    EXPECT_EQ(spy.count(), 1);
}

TEST_F(ut_doaerrorwidget, ut_doaerrorwidget_leaveEvent_001)
{
    doaErrorWidget->m_tryAgainState.msState = DOAErrorWidget::MS_Press;
    QEvent *event;
    doaErrorWidget->leaveEvent(event);
    EXPECT_EQ(doaErrorWidget->m_tryAgainState.msState, DOAErrorWidget::MS_Leave);
}

TEST_F(ut_doaerrorwidget, ut_doaerrorwidget_mouseMoveEvent_001)
{
    doaErrorWidget->m_tryAgainState.msState = DOAErrorWidget::MS_Enter;
    QPoint pos(403,34);
    QMouseEvent event0(QEvent::MouseButtonPress, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    doaErrorWidget->mouseMoveEvent(&event0);
    EXPECT_EQ(doaErrorWidget->m_tryAgainState.msState, DOAErrorWidget::MS_Leave);
}

TEST_F(ut_doaerrorwidget, ut_doaerrorwidget_mouseMoveEvent_002)
{
    doaErrorWidget->m_errorMsgState = DOAErrorWidget::MsgShow_TryAgain;
    doaErrorWidget->m_tryAgainRect.setX(400);
    doaErrorWidget->m_tryAgainRect.setY(30);
    doaErrorWidget->m_tryAgainRect.setWidth(30);
    doaErrorWidget->m_tryAgainRect.setHeight(40);
    doaErrorWidget->m_tryAgainState.msState = DOAErrorWidget::MS_Leave;
    QPoint pos(403,34);
    QMouseEvent event0(QEvent::MouseButtonPress, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    doaErrorWidget->mouseMoveEvent(&event0);
    EXPECT_EQ(doaErrorWidget->m_tryAgainState.msState, DOAErrorWidget::MS_Enter);
}

TEST_F(ut_doaerrorwidget, ut_doaerrorwidget_mouseReleaseEvent_001)
{
    doaErrorWidget->m_tryAgainState.msState = DOAErrorWidget::MS_Enter;
    QPoint pos(403,34);
    QMouseEvent event0(QEvent::MouseButtonPress, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    doaErrorWidget->mouseReleaseEvent(&event0);
    EXPECT_EQ(doaErrorWidget->m_tryAgainState.msState, DOAErrorWidget::MS_Leave);
}

TEST_F(ut_doaerrorwidget, ut_doaerrorwidget_mouseReleaseEvent_002)
{
    doaErrorWidget->m_errorMsgState = DOAErrorWidget::MsgShow_TryAgain;
    doaErrorWidget->m_tryAgainRect.setX(400);
    doaErrorWidget->m_tryAgainRect.setY(30);
    doaErrorWidget->m_tryAgainRect.setWidth(30);
    doaErrorWidget->m_tryAgainRect.setHeight(40);
    doaErrorWidget->m_tryAgainState.msState = DOAErrorWidget::MS_Leave;
    QPoint pos(403,34);
    QMouseEvent event0(QEvent::MouseButtonPress, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    doaErrorWidget->mouseReleaseEvent(&event0);
    EXPECT_EQ(doaErrorWidget->m_tryAgainState.msState, DOAErrorWidget::MS_Enter);
}

TEST_F(ut_doaerrorwidget, ut_doaerrorwidget_mousePressEvent_001)
{
    doaErrorWidget->m_tryAgainState.msState = DOAErrorWidget::MS_Enter;
    QPoint pos(403,34);
    QMouseEvent event0(QEvent::MouseButtonPress, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    doaErrorWidget->mousePressEvent(&event0);
    EXPECT_EQ(doaErrorWidget->m_tryAgainState.msState, DOAErrorWidget::MS_Enter);
}

TEST_F(ut_doaerrorwidget, ut_doaerrorwidget_mousePressEvent_002)
{
    doaErrorWidget->m_errorMsgState = DOAErrorWidget::MsgShow_TryAgain;
    doaErrorWidget->m_tryAgainRect.setX(400);
    doaErrorWidget->m_tryAgainRect.setY(30);
    doaErrorWidget->m_tryAgainRect.setWidth(30);
    doaErrorWidget->m_tryAgainRect.setHeight(40);
    doaErrorWidget->m_tryAgainState.msState = DOAErrorWidget::MS_Leave;
    QPoint pos(403,34);
    QMouseEvent event0(QEvent::MouseButtonPress, pos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    doaErrorWidget->mousePressEvent(&event0);
    EXPECT_EQ(doaErrorWidget->m_tryAgainState.msState, DOAErrorWidget::MS_Press);
}

TEST_F(ut_doaerrorwidget, ut_doaerrorwidget_resizeEvent_001)
{
    Stub st;
    st.set(ADDR(DOAErrorWidget, showMsgByWidth), ADDR(ut_doaerrorwidget, stub_resutlMsg));
    QResizeEvent *e;
    resultMsg = "resizeEvent";
    doaErrorWidget->resizeEvent(e);
    EXPECT_EQ(resultMsg, "resultMsg");
}

TEST_F(ut_doaerrorwidget, ut_doaerrorwidget_changeEvent_001)
{
    Stub st;
    st.set(ADDR(DOAErrorWidget, showMsgByWidth), ADDR(ut_doaerrorwidget, stub_resutlMsg));
    QEvent e(QEvent::FontChange);
    resultMsg = "changeEvent";
    doaErrorWidget->changeEvent(&e);
    EXPECT_EQ(resultMsg, "resultMsg");
}

TEST_F(ut_doaerrorwidget, ut_doaerrorwidget_changeEvent_002)
{
    Stub st;
    st.set(ADDR(DOAErrorWidget, showMsgByWidth), ADDR(ut_doaerrorwidget, stub_resutlMsg));
    QEvent e(QEvent::MouseButtonPress);
    resultMsg = "changeEvent";
    doaErrorWidget->changeEvent(&e);
    EXPECT_EQ(resultMsg, "changeEvent");
}

TEST_F(ut_doaerrorwidget, ut_doaerrorwidget_tokenize_001)
{
    QString str = "Network error, please check and";
    QStringList strlist = doaErrorWidget->tokenize(str);
    qWarning() << strlist;
    EXPECT_EQ(strlist.count(), 11);
}

TEST_F(ut_doaerrorwidget, ut_doaerrorwidget_paintEvent_001)
{
    QPixmap pixmap(doaErrorWidget->size());
    doaErrorWidget->render(&pixmap);
}

TEST_F(ut_doaerrorwidget, ut_doaerrorwidget_updateRect_001)
{
    doaErrorWidget->updateRect();
    EXPECT_EQ(doaErrorWidget->m_errorMsgVector.count(), 0);
}

TEST_F(ut_doaerrorwidget, ut_doaerrorwidget_updateRect_002)
{
    struct ErrorMsg {
        QString msg = "";
        int len = 0;
        QRectF rectF;
    };
    DOAErrorWidget::ErrorMsg errmsg;
    errmsg.msg = "Network error";
    errmsg.len = errmsg.msg.length();
    errmsg.rectF = QRectF(0, 0, 12, 12);
    doaErrorWidget->setFixedSize(60, 20);
    doaErrorWidget->m_errorMsgVector.append(errmsg);
    doaErrorWidget->m_showRow = 2;
    doaErrorWidget->updateRect();
    EXPECT_EQ(doaErrorWidget->m_errorMsgVector.at(0).rectF, QRectF(37, 0, 13, 10));
}

TEST_F(ut_doaerrorwidget, ut_doaerrorwidget_showMsgByWidth_001)
{
    doaErrorWidget->setFixedWidth(100);
    doaErrorWidget->m_errorMsg = "Network error, please check and";
    doaErrorWidget->showMsgByWidth();
    EXPECT_GT(doaErrorWidget->m_showRow, 1);
}

TEST_F(ut_doaerrorwidget, ut_doaerrorwidget_showMsgByWidth_002)
{
    doaErrorWidget->m_errorMsgState =  DOAErrorWidget::MsgShow_TryAgain;
    doaErrorWidget->setFixedWidth(100);
    doaErrorWidget->m_errorMsg = "Network error, please check and";
    doaErrorWidget->showMsgByWidth();
    EXPECT_GT(doaErrorWidget->m_showRow, 2);
}
