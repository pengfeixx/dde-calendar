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
#include "ut_doaaccountprotocollistwidget.h"
#include "../../third-party_stub/stub.h"

#include <DDialog>

DWIDGET_USE_NAMESPACE

ut_doaaccountprotocollistwidget::ut_doaaccountprotocollistwidget()
{

}

static int m_execresutl = 0;

int ut_doaaccountprotocollistwidget::DDialog_Exec_stub()
{
    m_execresutl = 1;
    return m_execresutl;
}

void ut_doaaccountprotocollistwidget::stub_slotAddAccount(const AddAccountInfo &info)
{
    m_execresutl = 2;
}

void ut_doaaccountprotocollistwidget::SetUp()
{
    doaAccountProtocolListWidget = new DOAAccountProtocolListWidget();
}

void ut_doaaccountprotocollistwidget::TearDown()
{
    delete doaAccountProtocolListWidget;
    doaAccountProtocolListWidget = nullptr;
}

TEST_F(ut_doaaccountprotocollistwidget, ut_doaaccountprotocollistwidget_setModel_001)
{
    DOAAccountModel modele;
    doaAccountProtocolListWidget->setModel(&modele);
    EXPECT_EQ(doaAccountProtocolListWidget->m_dataModel, &modele);
    DOAAccountModel modele1;
    doaAccountProtocolListWidget->setModel(&modele1);
    EXPECT_EQ(doaAccountProtocolListWidget->m_dataModel, &modele1);
}

TEST_F(ut_doaaccountprotocollistwidget, ut_doaaccountprotocollistwidget_slotAccountItemClicked_001)
{
    Stub st;
    typedef int (*ut_QDialog_exec_ptr)();
    ut_QDialog_exec_ptr dptr = (ut_QDialog_exec_ptr)(&DDialog::exec);
    st.set(dptr, ADDR(ut_doaaccountprotocollistwidget, DDialog_Exec_stub));

    m_execresutl = 2;
    doaAccountProtocolListWidget->slotAccountItemClicked(ProtocolType::Type_CalDAV);
    EXPECT_EQ(m_execresutl, 1);
}

TEST_F(ut_doaaccountprotocollistwidget, ut_doaaccountprotocollistwidget_slotAddAccount_001)
{
    Stub st;
    st.set(ADDR(DOAAccountModel, slotAddAccount), ADDR(ut_doaaccountprotocollistwidget, stub_slotAddAccount));

    AddAccountInfo info;
    m_execresutl = 0;
    doaAccountProtocolListWidget->slotAddAccount(info);
    EXPECT_EQ(m_execresutl, 0);
}

TEST_F(ut_doaaccountprotocollistwidget, ut_doaaccountprotocollistwidget_slotAddAccount_002)
{
    Stub st;
    st.set(ADDR(DOAAccountModel, slotAddAccount), ADDR(ut_doaaccountprotocollistwidget, stub_slotAddAccount));

    DOAAccountModel modele;
    doaAccountProtocolListWidget->setModel(&modele);

    AddAccountInfo info;
    m_execresutl = 0;
    doaAccountProtocolListWidget->slotAddAccount(info);
    EXPECT_EQ(m_execresutl, 2);
}

TEST_F(ut_doaaccountprotocollistwidget, ut_doaaccountprotocollistwidget_slotConfigurationChanged_001)
{
    doaAccountProtocolListWidget->slotConfigurationChanged(DOANetWorkDBus::NetWorkState::Disconnect);
    EXPECT_EQ(doaAccountProtocolListWidget->m_networkConfiguration, DOANetWorkDBus::NetWorkState::Disconnect);
}
