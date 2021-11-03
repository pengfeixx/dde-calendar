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
#include "ut_doaaddaccountdialog.h"
#include "doapasswordedit.h"
#include "../../third-party_stub/stub.h"

#include <DLineEdit>
#include <DDialog>
#include <DLabel>

#include <QPushButton>
#include <QComboBox>
#include <QDebug>
#include <QSignalSpy>

DWIDGET_USE_NAMESPACE

ut_doaaddaccountdialog::ut_doaaddaccountdialog()
{

}

static int m_execresutl = 0;

int ut_doaaddaccountdialog::DDialog_Exec_stub()
{
    m_execresutl = 1;
    return m_execresutl;
}

void ut_doaaddaccountdialog::SetUp()
{
    doaAddAccountDialog = new DOAAddAccountDialog();
}

void ut_doaaddaccountdialog::TearDown()
{
    delete doaAddAccountDialog;
    doaAddAccountDialog = nullptr;
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_initWidget_001)
{
    EXPECT_EQ(doaAddAccountDialog->size(), QSize(420, 346));
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_addItemWidget_001)
{
    QWidget widgetid;
    QWidget *widgetitem = doaAddAccountDialog->addItemWidget("12345", &widgetid);

    EXPECT_EQ(widgetitem->height(), 36);
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_setLoginEnableByInputs_001)
{
    doaAddAccountDialog->setLoginEnableByInputs();
    EXPECT_EQ(qobject_cast<QPushButton*>(doaAddAccountDialog->getButton(1))->isEnabled(), false);
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_setLoginEnableByInputs_002)
{
    doaAddAccountDialog->m_accountName->lineEdit()->setText("123");
    doaAddAccountDialog->m_passwordEdit->lineEdit()->setText("123");
    doaAddAccountDialog->setLoginEnableByInputs();
    EXPECT_EQ(qobject_cast<QPushButton*>(doaAddAccountDialog->getButton(1))->isEnabled(), true);
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_setLoginEnableByInputs_003)
{
    doaAddAccountDialog->m_accountName->lineEdit()->setText("123");
    doaAddAccountDialog->m_passwordEdit->lineEdit()->setText("123");
    doaAddAccountDialog->m_serverIP->lineEdit()->setText("12345");
    doaAddAccountDialog->m_loginModel->setCurrentIndex(1);
    doaAddAccountDialog->setLoginEnableByInputs();
    EXPECT_EQ(qobject_cast<QPushButton*>(doaAddAccountDialog->getButton(1))->isEnabled(), true);
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_setLoginEnableByInputs_004)
{
    doaAddAccountDialog->m_accountName->lineEdit()->setText("123");
    doaAddAccountDialog->m_passwordEdit->lineEdit()->setText("123");
    doaAddAccountDialog->m_loginModel->setCurrentIndex(1);
    doaAddAccountDialog->setLoginEnableByInputs();
    EXPECT_EQ(qobject_cast<QPushButton*>(doaAddAccountDialog->getButton(1))->isEnabled(), false);
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_getAddAccountInfo_001)
{
    doaAddAccountDialog->getAddAccountInfo();
    EXPECT_EQ(doaAddAccountDialog->m_addInfo.loginModel, 1);
    EXPECT_EQ(doaAddAccountDialog->m_addInfo.accountName, "");
    EXPECT_EQ(doaAddAccountDialog->m_addInfo.serverIP, "");
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_getAddAccountInfo_002)
{
    doaAddAccountDialog->m_loginModel->setCurrentIndex(1);
    doaAddAccountDialog->m_serverIP->lineEdit()->setText("12345");
    doaAddAccountDialog->getAddAccountInfo();
    EXPECT_EQ(doaAddAccountDialog->m_addInfo.loginModel, 2);
    EXPECT_EQ(doaAddAccountDialog->m_addInfo.accountName, "");
    EXPECT_EQ(doaAddAccountDialog->m_addInfo.serverIP, "12345");
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_matchEmail_001)
{
    EXPECT_EQ(doaAddAccountDialog->matchEmail("1234@qq.com"), true);
    EXPECT_EQ(doaAddAccountDialog->matchEmail("1234@qq"), false);
    EXPECT_EQ(doaAddAccountDialog->matchEmail("@qq.com"), false);
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_matchPhoneNumber_001)
{
    EXPECT_EQ(doaAddAccountDialog->matchPhoneNumber("1234@qq.com"), false);
    EXPECT_EQ(doaAddAccountDialog->matchPhoneNumber("1234111qq"), false);
    EXPECT_EQ(doaAddAccountDialog->matchPhoneNumber("13"), false);
    EXPECT_EQ(doaAddAccountDialog->matchPhoneNumber("142"), false);
    EXPECT_EQ(doaAddAccountDialog->matchPhoneNumber("14231234567"), false);
    EXPECT_EQ(doaAddAccountDialog->matchPhoneNumber("14531234567"), true);
    EXPECT_EQ(doaAddAccountDialog->matchPhoneNumber("15431234567"), false);
    EXPECT_EQ(doaAddAccountDialog->matchPhoneNumber("15631234567"), true);
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_slotLoginModelChanged_001)
{
    doaAddAccountDialog->slotLoginModelChanged(1);
    qWarning() << doaAddAccountDialog->m_serverWidget->isVisible();
    EXPECT_EQ(doaAddAccountDialog->m_serverWidget->isHidden(), false);
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_slotLoginModelChanged_002)
{
    doaAddAccountDialog->slotLoginModelChanged(0);
    EXPECT_EQ(doaAddAccountDialog->m_serverWidget->isVisible(), false);
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_slotAccountFocusChanged_001)
{
    doaAddAccountDialog->m_accountIsOk = true;
    doaAddAccountDialog->m_accountName->lineEdit()->setText("123456");
    doaAddAccountDialog->slotAccountFocusChanged(true);

    EXPECT_EQ(doaAddAccountDialog->m_accountName->isAlert(), false);
    EXPECT_EQ(doaAddAccountDialog->m_accountIsOk, false);
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_slotAccountFocusChanged_002)
{
    doaAddAccountDialog->m_accountIsOk = true;
    doaAddAccountDialog->m_accountName->lineEdit()->setText("123456");
    doaAddAccountDialog->slotAccountFocusChanged(false);

    EXPECT_EQ(doaAddAccountDialog->m_accountName->isAlert(), true);
    EXPECT_EQ(doaAddAccountDialog->m_accountIsOk, false);

    doaAddAccountDialog->m_accountName->lineEdit()->setText("15912345678");
    doaAddAccountDialog->slotAccountFocusChanged(false);

    EXPECT_EQ(doaAddAccountDialog->m_accountName->isAlert(), true);
    EXPECT_EQ(doaAddAccountDialog->m_accountIsOk, false);
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_slotAccountFocusChanged_003)
{
    doaAddAccountDialog->m_accountIsOk = true;
    doaAddAccountDialog->m_accountName->lineEdit()->setText("123456@164.com");
    doaAddAccountDialog->slotAccountFocusChanged(false);

    EXPECT_EQ(doaAddAccountDialog->m_accountName->isAlert(), true) << "123456@164.com";
    EXPECT_EQ(doaAddAccountDialog->m_accountIsOk, false);

    doaAddAccountDialog->m_accountName->lineEdit()->setText("123456@qq.com");
    doaAddAccountDialog->slotAccountFocusChanged(false);

    EXPECT_EQ(doaAddAccountDialog->m_accountName->isAlert(), false)  << "123456@qq.com";
    EXPECT_EQ(doaAddAccountDialog->m_accountIsOk, true);
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_slotbuttonClicked_001)
{
    doaAddAccountDialog->m_accountIsOk = false;
    doaAddAccountDialog->m_networkIsOk = false;
    QSignalSpy spy(doaAddAccountDialog,SIGNAL(signalAddAccountInfo(const AddAccountInfo &)));
    doaAddAccountDialog->slotbuttonClicked(1, "1234");
    EXPECT_EQ(spy.count(), 0);
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_slotbuttonClicked_002)
{
    doaAddAccountDialog->m_accountIsOk = true;
    doaAddAccountDialog->m_networkIsOk = true;
    QSignalSpy spy(doaAddAccountDialog,SIGNAL(signalAddAccountInfo(const AddAccountInfo &)));
    Stub st;
    typedef int (*ut_QDialog_exec_ptr)();
    ut_QDialog_exec_ptr dptr = (ut_QDialog_exec_ptr)(&DDialog::exec);
    st.set(dptr, ADDR(ut_doaaddaccountdialog, DDialog_Exec_stub));
    doaAddAccountDialog->slotbuttonClicked(1, "1234");
    EXPECT_EQ(spy.count(), 1);
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_slotAccountTextChanged_001)
{
    doaAddAccountDialog->m_accountName->setAlert(false);
    doaAddAccountDialog->slotAccountTextChanged("12345");
    EXPECT_EQ(doaAddAccountDialog->m_accountName->isAlert(), false);
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_slotAccountTextChanged_002)
{
    doaAddAccountDialog->m_accountName->setAlert(true);
    doaAddAccountDialog->slotAccountTextChanged("12345");
    EXPECT_EQ(doaAddAccountDialog->m_accountName->isAlert(), false);
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_slotServerIPTextChanged_001)
{
    doaAddAccountDialog->m_serverIP->setAlert(false);
    doaAddAccountDialog->slotServerIPTextChanged("12345");
    EXPECT_EQ(doaAddAccountDialog->m_serverIP->isAlert(), false);
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_slotServerIPTextChanged_002)
{
    doaAddAccountDialog->m_serverIP->setAlert(true);
    doaAddAccountDialog->slotServerIPTextChanged("12345");
    EXPECT_EQ(doaAddAccountDialog->m_serverIP->isAlert(), true);
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_slotPasswordTextChanged_001)
{
    doaAddAccountDialog->m_passwordEdit->setAlert(false);
    doaAddAccountDialog->slotPasswordTextChanged("12345");
    EXPECT_EQ(doaAddAccountDialog->m_passwordEdit->isAlert(), false);
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_slotPasswordTextChanged_002)
{
    doaAddAccountDialog->m_passwordEdit->setAlert(true);
    doaAddAccountDialog->slotPasswordTextChanged("12345");
    EXPECT_EQ(doaAddAccountDialog->m_passwordEdit->isAlert(), false);
}


TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_slotAddAccountResults_001)
{
    doaAddAccountDialog->slotAddAccountResults(1);
    EXPECT_EQ(doaAddAccountDialog->m_loginError->text(), "Server error, please try again");
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_slotAddAccountResults_002)
{
    doaAddAccountDialog->slotAddAccountResults(2);
    EXPECT_EQ(doaAddAccountDialog->m_loginError->text(), "");
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_slotAddAccountResults_003)
{
    doaAddAccountDialog->slotAddAccountResults(3);
    EXPECT_EQ(doaAddAccountDialog->m_loginError->text(), "Server error, please try again");
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_slotAddAccountResults_004)
{
    doaAddAccountDialog->slotAddAccountResults(4);
    EXPECT_EQ(doaAddAccountDialog->m_loginError->text(), "Cannot verify the account and password");
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_slotAddAccountResults_005)
{
    doaAddAccountDialog->slotAddAccountResults(10);
    EXPECT_EQ(doaAddAccountDialog->m_loginError->text(), "Account added already");
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_slotAddAccountResults_006)
{
    doaAddAccountDialog->slotAddAccountResults(7);
    EXPECT_EQ(doaAddAccountDialog->m_loginError->text(), "Server error, please try again");
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_slotConfigurationChanged_001)
{
    doaAddAccountDialog->m_loginError->setText("1234");
    doaAddAccountDialog->slotConfigurationChanged(DOANetWorkDBus::NetWorkState::Connecting);
    EXPECT_EQ(doaAddAccountDialog->m_loginError->text(), "1234");
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_slotConfigurationChanged_002)
{
    doaAddAccountDialog->m_loginError->setText("Network error, please check and try again");
    doaAddAccountDialog->slotConfigurationChanged(DOANetWorkDBus::NetWorkState::Connecting);
    EXPECT_EQ(doaAddAccountDialog->m_loginError->text(), "");
}

TEST_F(ut_doaaddaccountdialog, ut_doaaddaccountdialog_slotConfigurationChanged_003)
{
    doaAddAccountDialog->slotConfigurationChanged(DOANetWorkDBus::NetWorkState::Disconnect);
    EXPECT_EQ(doaAddAccountDialog->m_loginError->text(), "Network error, please check and try again");
}
