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
#include "ut_doaaccountlistmodel.h"
#include "doaaccountlistitemdelegate.h"
#include "doaaccountlistwidget.h"

#include <DListView>

#include <QVariant>

DGUI_USE_NAMESPACE

ut_doaaccountlistmodel::ut_doaaccountlistmodel()
{

}

void ut_doaaccountlistmodel::SetUp()
{
    doaAccountListModel = new DOAAccountListModel();
}

void ut_doaaccountlistmodel::TearDown()
{
    delete doaAccountListModel;
    doaAccountListModel = nullptr;
}

TEST_F(ut_doaaccountlistmodel, ut_doaaccountlistmodel_rowCount_001)
{
    QModelIndex index;
    EXPECT_EQ(doaAccountListModel->rowCount(index), 0);
}

TEST_F(ut_doaaccountlistmodel, ut_doaaccountlistmodel_data_001)
{
    QModelIndex index;
    EXPECT_EQ(doaAccountListModel->data(index, Qt::UserRole).toString(), "");
}

TEST_F(ut_doaaccountlistmodel, ut_doaaccountlistmodel_data_002)
{
    DOAAccountListItemDelegate doaAccountListItemDelegate;
    DListView listview;
    listview.setItemDelegate(&doaAccountListItemDelegate);
    listview.setModel(doaAccountListModel);

    AccountItemData itemData;
    itemData.accountId = "123456";
    AccountItemData itemData1;
    itemData1.accountId = "123457";
    doaAccountListModel->addAccount(itemData);
    doaAccountListModel->addAccount(itemData1);


    QModelIndex index;
    int count = doaAccountListModel->rowCount(index);
    //设置刚刚添加的为选中状态
    index = doaAccountListModel->index(count - 1);

    AccountItemData itemData2 = doaAccountListModel->data(index, Qt::UserRole).value<AccountItemData>();
    EXPECT_EQ(itemData2.accountId, "123457");
}


TEST_F(ut_doaaccountlistmodel, ut_doaaccountlistmodel_data_003)
{
    DOAAccountListItemDelegate doaAccountListItemDelegate;
    DListView listview;
    listview.setItemDelegate(&doaAccountListItemDelegate);
    listview.setModel(doaAccountListModel);

    AccountItemData itemData;
    itemData.accountId = "123456";
    AccountItemData itemData1;
    itemData1.accountId = "123457";
    doaAccountListModel->addAccount(itemData);
    doaAccountListModel->addAccount(itemData1);


    QModelIndex index;
    int count = doaAccountListModel->rowCount(index);
    //设置刚刚添加的为选中状态
    index = doaAccountListModel->index(count - 1);

    AccountItemData itemData2 = doaAccountListModel->data(index, Qt::DisplayRole).value<AccountItemData>();
    EXPECT_EQ(itemData2.accountId, "");
}

TEST_F(ut_doaaccountlistmodel, ut_doaaccountlistmodel_setData_001)
{
    QModelIndex index;
    AccountItemData itemData;
    EXPECT_EQ(doaAccountListModel->setData(index, QVariant::fromValue(itemData), Qt::UserRole), false);
}

TEST_F(ut_doaaccountlistmodel, ut_doaaccountlistmodel_setData_002)
{
    DOAAccountListItemDelegate doaAccountListItemDelegate;
    DListView listview;
    listview.setItemDelegate(&doaAccountListItemDelegate);
    listview.setModel(doaAccountListModel);

    AccountItemData itemData;
    itemData.accountId = "123456";
    AccountItemData itemData1;
    itemData1.accountId = "123457";
    doaAccountListModel->addAccount(itemData);
    doaAccountListModel->addAccount(itemData1);

    QModelIndex index;
    int count = doaAccountListModel->rowCount(index);
    //设置刚刚添加的为选中状态
    index = doaAccountListModel->index(count - 1);

    EXPECT_EQ(doaAccountListModel->setData(index, QVariant::fromValue(itemData1), Qt::UserRole), true);
}


TEST_F(ut_doaaccountlistmodel, ut_doaaccountlistmodel_setData_003)
{
    DOAAccountListItemDelegate doaAccountListItemDelegate;
    DListView listview;
    listview.setItemDelegate(&doaAccountListItemDelegate);
    listview.setModel(doaAccountListModel);

    AccountItemData itemData;
    itemData.accountId = "123456";
    AccountItemData itemData1;
    itemData1.accountId = "123457";
    doaAccountListModel->addAccount(itemData);
    doaAccountListModel->addAccount(itemData1);

    QModelIndex index;
    int count = doaAccountListModel->rowCount(index);
    //设置刚刚添加的为选中状态
    index = doaAccountListModel->index(count - 1);

    EXPECT_EQ(doaAccountListModel->setData(index, QVariant::fromValue(itemData1), Qt::DisplayRole), false);
}

TEST_F(ut_doaaccountlistmodel, ut_doaaccountlistmodel_addAccount_001)
{
    DOAAccountListItemDelegate doaAccountListItemDelegate;
    DListView listview;
    listview.setItemDelegate(&doaAccountListItemDelegate);
    listview.setModel(doaAccountListModel);

    AccountItemData itemData;
    itemData.accountId = "123456";
    AccountItemData itemData1;
    itemData1.accountId = "123457";
    doaAccountListModel->addAccount(itemData);
    doaAccountListModel->addAccount(itemData1);

    EXPECT_EQ(doaAccountListModel->m_accountList.count(), 2);
}

TEST_F(ut_doaaccountlistmodel, ut_doaaccountlistmodel_addAccount_002)
{
    DOAAccountListItemDelegate doaAccountListItemDelegate;
    DListView listview;
    listview.setItemDelegate(&doaAccountListItemDelegate);
    listview.setModel(doaAccountListModel);

    AccountItemData itemData;
    itemData.accountId = "123456";
    AccountItemData itemData1;
    itemData1.accountId = "123457";
    doaAccountListModel->addAccount(itemData);
    doaAccountListModel->addAccount(itemData1);
    AccountItemData itemData2;
    itemData2.accountId = "123457";
    doaAccountListModel->addAccount(itemData2);

    EXPECT_EQ(doaAccountListModel->m_accountList.count(), 2);
}

TEST_F(ut_doaaccountlistmodel, ut_doaaccountlistmodel_removeAccount_001)
{
    DOAAccountListItemDelegate doaAccountListItemDelegate;
    DListView listview;
    listview.setItemDelegate(&doaAccountListItemDelegate);
    listview.setModel(doaAccountListModel);

    AccountItemData itemData;
    itemData.accountId = "123456";
    AccountItemData itemData1;
    itemData1.accountId = "123457";
    doaAccountListModel->addAccount(itemData);
    doaAccountListModel->addAccount(itemData1);

    doaAccountListModel->removeAccount("123456");
    EXPECT_EQ(doaAccountListModel->m_accountList.count(), 1);
}

TEST_F(ut_doaaccountlistmodel, ut_doaaccountlistmodel_removeAccount_002)
{
    DOAAccountListItemDelegate doaAccountListItemDelegate;
    DListView listview;
    listview.setItemDelegate(&doaAccountListItemDelegate);
    listview.setModel(doaAccountListModel);

    AccountItemData itemData;
    itemData.accountId = "123456";
    AccountItemData itemData1;
    itemData1.accountId = "123457";
    doaAccountListModel->addAccount(itemData);
    doaAccountListModel->addAccount(itemData1);
    doaAccountListModel->removeAccount("1234568");

    EXPECT_EQ(doaAccountListModel->m_accountList.count(), 2);
}

TEST_F(ut_doaaccountlistmodel, ut_doaaccountlistmodel_changeAccount_001)
{
    DOAAccountListItemDelegate doaAccountListItemDelegate;
    DListView listview;
    listview.setItemDelegate(&doaAccountListItemDelegate);
    listview.setModel(doaAccountListModel);

    AccountItemData itemData;
    itemData.accountId = "123456";
    itemData.accountName = "123456";
    AccountItemData itemData1;
    itemData1.accountId = "123457";
    itemData1.accountName = "1234567";
    doaAccountListModel->addAccount(itemData);
    doaAccountListModel->addAccount(itemData1);

    AccountItemData itemData2;
    itemData2.accountId = "123457";
    itemData2.accountName = "1234568";

    doaAccountListModel->changeAccount(itemData2);
    EXPECT_EQ(doaAccountListModel->m_accountList.at(1).accountName, "1234568");
}

TEST_F(ut_doaaccountlistmodel, ut_doaaccountlistmodel_changeAccount_002)
{
    DOAAccountListItemDelegate doaAccountListItemDelegate;
    DListView listview;
    listview.setItemDelegate(&doaAccountListItemDelegate);
    listview.setModel(doaAccountListModel);

    AccountItemData itemData;
    itemData.accountId = "123456";
    itemData.accountName = "123456";
    AccountItemData itemData1;
    itemData1.accountId = "1234567";
    itemData1.accountName = "1234567";
    doaAccountListModel->addAccount(itemData);
    doaAccountListModel->addAccount(itemData1);

    AccountItemData itemData2;
    itemData2.accountId = "123458";
    itemData2.accountName = "1234568";

    doaAccountListModel->changeAccount(itemData2);

    EXPECT_EQ(doaAccountListModel->m_accountList.at(0).accountName, "123456");
    EXPECT_EQ(doaAccountListModel->m_accountList.at(1).accountName, "1234567");
}


TEST_F(ut_doaaccountlistmodel, ut_doaaccountlistmodel_clearAccount_001)
{
    DOAAccountListItemDelegate doaAccountListItemDelegate;
    DListView listview;
    listview.setItemDelegate(&doaAccountListItemDelegate);
    listview.setModel(doaAccountListModel);

    AccountItemData itemData;
    itemData.accountId = "123456";
    itemData.accountName = "123456";
    AccountItemData itemData1;
    itemData1.accountId = "1234567";
    itemData1.accountName = "1234567";
    doaAccountListModel->addAccount(itemData);
    doaAccountListModel->addAccount(itemData1);

    doaAccountListModel->clearAccount();

    EXPECT_EQ(doaAccountListModel->m_accountList.count(), 0);
}



