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
#include "ut_doaaccountlistwidget.h"
#include "../../third-party_stub/stub.h"
#include "consts.h"

#include <QSignalSpy>

ut_doaaccountlistwidget::ut_doaaccountlistwidget()
{

}

void ut_doaaccountlistwidget::SetUp()
{
    doaAccountListWidget = new DOAAccountListWidget();
}

void ut_doaaccountlistwidget::TearDown()
{
    delete doaAccountListWidget;
    doaAccountListWidget = nullptr;
}

TEST_F(ut_doaaccountlistwidget, ut_doaaccountlistwidget_setModel_001)
{
    DOAAccountModel modele;
    doaAccountListWidget->setModel(&modele);
    EXPECT_EQ(doaAccountListWidget->m_model, &modele);
    DOAAccountModel modele1;
    doaAccountListWidget->setModel(&modele1);
    EXPECT_EQ(doaAccountListWidget->m_model, &modele1);
}

TEST_F(ut_doaaccountlistwidget, ut_doaaccountlistwidget_initWidget_001)
{
    EXPECT_EQ(doaAccountListWidget->m_addAccountBtn->size(), QSize(50,50));
}

TEST_F(ut_doaaccountlistwidget, ut_doaaccountlistwidget_slotSelectItem_001)
{
    DOAAccountModel modele;
    doaAccountListWidget->setModel(&modele);
    QSignalSpy spy(doaAccountListWidget->m_model, SIGNAL(signalChangeState()));
    doaAccountListWidget->slotSelectItem("12345");

    EXPECT_EQ(spy.count(), 1);
}

TEST_F(ut_doaaccountlistwidget, ut_doaaccountlistwidget_slotClickeAddAccount_001)
{
    QSignalSpy spy(doaAccountListWidget->m_model, SIGNAL(signalChangeState()));
    doaAccountListWidget->slotClickeAddAccount();

    EXPECT_EQ(spy.count(), 0);
}

TEST_F(ut_doaaccountlistwidget, ut_doaaccountlistwidget_slotClickeAddAccount_002)
{
    DOAAccountModel modele;
    doaAccountListWidget->setModel(&modele);
    QSignalSpy spy(doaAccountListWidget->m_model, SIGNAL(signalChangeState()));
    doaAccountListWidget->slotClickeAddAccount();

    EXPECT_EQ(spy.count(), 1);
}

TEST_F(ut_doaaccountlistwidget, ut_doaaccountlistwidget_slotGetAddAccount_001)
{
    DOAAccount info;
    info.setAccountID("12345");
    info.setUserName("uostest");
    doaAccountListWidget->slotGetAddAccount(&info);
    QModelIndex index;
    EXPECT_EQ(doaAccountListWidget->m_listModel->rowCount(index), 1);
}

TEST_F(ut_doaaccountlistwidget, ut_doaaccountlistwidget_slotGetDeleteAccount_001)
{
    DOAAccount info;
    info.setAccountID("12345");
    info.setUserName("uostest");
    doaAccountListWidget->slotGetAddAccount(&info);
    DOAAccount info1;
    info1.setAccountID("123451");
    info1.setUserName("uostest1");
    doaAccountListWidget->slotGetAddAccount(&info1);
    doaAccountListWidget->slotGetDeleteAccount("12345");
    EXPECT_EQ(doaAccountListWidget->m_listModel->m_accountList[doaAccountListWidget->m_listView->currentIndex().row()].accountId, "123451");
}

TEST_F(ut_doaaccountlistwidget, ut_doaaccountlistwidget_slotGetDeleteAccount_002)
{
    DOAAccount info;
    info.setAccountID("12345");
    info.setUserName("uostest");
    doaAccountListWidget->slotGetAddAccount(&info);
    QModelIndex index;
    doaAccountListWidget->slotGetDeleteAccount("12345");
    EXPECT_EQ(doaAccountListWidget->m_listModel->rowCount(index), 0);
}

TEST_F(ut_doaaccountlistwidget, ut_doaaccountlistwidget_slotGetDeleteAccount_003)
{
    DOAAccount info;
    info.setAccountID("12345");
    info.setUserName("uostest");
    doaAccountListWidget->slotGetAddAccount(&info);
    DOAAccount info1;
    info1.setAccountID("123451");
    info1.setUserName("uostest1");
    doaAccountListWidget->slotGetAddAccount(&info1);

    QModelIndex index;
    doaAccountListWidget->slotGetDeleteAccount("123451");
    qWarning() <<doaAccountListWidget->m_listModel->m_accountList[doaAccountListWidget->m_listView->currentIndex().row()].accountId <<doaAccountListWidget->m_listView->currentIndex().row();
    EXPECT_EQ(doaAccountListWidget->m_listModel->m_accountList[doaAccountListWidget->m_listView->currentIndex().row()].accountId, "12345");
}

TEST_F(ut_doaaccountlistwidget, ut_doaaccountlistwidget_slotGetDeleteAccount_004)
{
    DOAAccount info;
    info.setAccountID("12345");
    info.setUserName("uostest");
    doaAccountListWidget->slotGetAddAccount(&info);
    DOAAccount info1;
    info1.setAccountID("123451");
    info1.setUserName("uostest1");
    doaAccountListWidget->slotGetAddAccount(&info1);
    DOAAccount info2;
    info2.setAccountID("123452");
    info2.setUserName("uostest2");
    doaAccountListWidget->slotGetAddAccount(&info2);
    QModelIndex index  = doaAccountListWidget->m_listModel->index(1);
    doaAccountListWidget->m_listView->setCurrentIndex(index);
    doaAccountListWidget->slotGetDeleteAccount("123451");
    qWarning() << doaAccountListWidget->m_listView->currentIndex().row();
    EXPECT_EQ(doaAccountListWidget->m_listModel->m_accountList[doaAccountListWidget->m_listView->currentIndex().row()].accountId, "123452");
}

TEST_F(ut_doaaccountlistwidget, ut_doaaccountlistwidget_slotShowStateChanged_001)
{
    DOAAccountModel modele;
    doaAccountListWidget->setModel(&modele);
    modele.setState(DOAAccountModel::Account_Create);
    doaAccountListWidget->slotShowStateChanged();
    EXPECT_EQ(doaAccountListWidget->m_stackedWidget->currentIndex(), 1);
}

TEST_F(ut_doaaccountlistwidget, ut_doaaccountlistwidget_slotShowStateChanged_002)
{
    DOAAccountModel modele;
    doaAccountListWidget->setModel(&modele);
    modele.setState(DOAAccountModel::Account_Init);
    doaAccountListWidget->slotShowStateChanged();
    EXPECT_EQ(doaAccountListWidget->m_stackedWidget->currentIndex(), 0);
}

TEST_F(ut_doaaccountlistwidget, ut_doaaccountlistwidget_slotAccountItemDataChanged_001)
{
    DOAAccountModel modele;
    doaAccountListWidget->setModel(&modele);
    DOAAccount *info = new DOAAccount(doaAccountListWidget);
    info->setAccountID("12345");
    info->setUserName("uostest");
    doaAccountListWidget->m_model->m_accounts.insert("12345" , info);
    doaAccountListWidget->slotGetAddAccount(info);
    DOAAccount *info1= new DOAAccount(doaAccountListWidget);;
    info1->setAccountID("123451");
    info1->setUserName("uostest1");
    doaAccountListWidget->m_model->m_accounts["123451"] = info1;
    doaAccountListWidget->slotGetAddAccount(info1);
    DOAAccount *info2= new DOAAccount(doaAccountListWidget);;
    info2->setAccountID("123452");
    info2->setUserName("uostesttest");
    doaAccountListWidget->m_model->m_accounts["123452"] = info2;
    doaAccountListWidget->slotGetAddAccount(info2);
    EXPECT_EQ(doaAccountListWidget->m_listModel->m_accountList[1].accountDisplayName, "uostest1");
    DOAAccount *account = doaAccountListWidget->m_model->getAccount("123451");
    account->setUserName("12345678");
    doaAccountListWidget->slotAccountItemDataChanged("123451");
    qWarning() << doaAccountListWidget->m_listModel->m_accountList[1].accountDisplayName;
    EXPECT_EQ(doaAccountListWidget->m_listModel->m_accountList[1].accountDisplayName, "12345678");
}

TEST_F(ut_doaaccountlistwidget, ut_doaaccountlistwidget_slotGetAccountListSuccess_001)
{
    DOAAccountModel modele;
    doaAccountListWidget->setModel(&modele);
    doaAccountListWidget->slotGetAccountListSuccess();
    EXPECT_EQ(doaAccountListWidget->m_stackedWidget->currentIndex(), 0);
}

TEST_F(ut_doaaccountlistwidget, ut_doaaccountlistwidget_slotGetAccountListSuccess_002)
{
    DOAAccountModel modele;
    doaAccountListWidget->setModel(&modele);
    doaAccountListWidget->slotGetAccountListSuccess();
    DOAAccount *info = new DOAAccount(doaAccountListWidget);
    info->setAccountID("12345");
    info->setUserName("uostest");
    doaAccountListWidget->m_model->m_accounts.insert("12345" , info);
    doaAccountListWidget->slotGetAddAccount(info);
    doaAccountListWidget->slotGetAccountListSuccess();
    EXPECT_EQ(doaAccountListWidget->m_stackedWidget->currentIndex(), 1);
}

TEST_F(ut_doaaccountlistwidget, ut_doaaccountlistwidget_getAccountList_001)
{
    DOAAccountModel modele;
    doaAccountListWidget->setModel(&modele);
    doaAccountListWidget->slotGetAccountListSuccess();
    DOAAccount *info = new DOAAccount(doaAccountListWidget);
    info->setAccountID("12345");
    info->setUserName("uostest");
    doaAccountListWidget->m_model->m_accounts.insert("12345" , info);
    doaAccountListWidget->getAccountList();
    EXPECT_EQ(doaAccountListWidget->m_listModel->m_accountList.count(), 1);
}

TEST_F(ut_doaaccountlistwidget, ut_doaaccountlistwidget_getItemData_001)
{
    AccountItemData accitemData;
    DOAAccount info;
    info.setAccountID("12345");
    info.setUserName("uostest");
    accitemData = doaAccountListWidget->getItemData(&info);

    EXPECT_EQ(accitemData.accountId, "12345");
    EXPECT_EQ(accitemData.accountDisplayName, "uostest");
}



