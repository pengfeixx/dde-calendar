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
#include "ut_doaprotocolmodel.h"
#include "doaprotocolitemdelegate.h"

#include <QListView>

ut_doaprotocolmodel::ut_doaprotocolmodel()
{

}

void ut_doaprotocolmodel::SetUp()
{
    doaProtocolModel = new DOAProtocolModel();
}

void ut_doaprotocolmodel::TearDown()
{
    delete doaProtocolModel;
    doaProtocolModel = nullptr;
}

TEST_F(ut_doaprotocolmodel, ut_doaprotocolmodel_rowCount_001)
{
    QModelIndex index;
    EXPECT_EQ(doaProtocolModel->rowCount(index), 1);
}

TEST_F(ut_doaprotocolmodel, ut_doaprotocolmodel_data_001)
{
    QModelIndex index;
    EXPECT_EQ(doaProtocolModel->data(index, Qt::UserRole).toString(), "");
}

TEST_F(ut_doaprotocolmodel, ut_doaprotocolmodel_data_002)
{
    DOAProtocolItemDelegate doaProtocolItemDelegate;
    QListView listview;
    listview.setItemDelegate(&doaProtocolItemDelegate);
    listview.setModel(doaProtocolModel);


    QModelIndex index;
    int count = doaProtocolModel->rowCount(index);
    //设置刚刚添加的为选中状态
    index = doaProtocolModel->index(count - 1);

    AccountProtocol itemData2 = doaProtocolModel->data(index, Qt::UserRole).value<AccountProtocol>();
    EXPECT_EQ(itemData2.protocolType, ProtocolType::Type_CalDAV);
}


TEST_F(ut_doaprotocolmodel, ut_doaprotocolmodel_data_003)
{
    DOAProtocolItemDelegate doaProtocolItemDelegate;
    QListView listview;
    listview.setItemDelegate(&doaProtocolItemDelegate);
    listview.setModel(doaProtocolModel);



    QModelIndex index;
    int count = doaProtocolModel->rowCount(index);
    //设置刚刚添加的为选中状态
    index = doaProtocolModel->index(count - 1);

    AccountProtocol itemData2 = doaProtocolModel->data(index, Qt::DisplayRole).value<AccountProtocol>();
    EXPECT_EQ(itemData2.protocolDisplayName,  "");
}

TEST_F(ut_doaprotocolmodel, ut_doaprotocolmodel_setData_001)
{
    QModelIndex index;
    AccountItemData itemData;
    EXPECT_EQ(doaProtocolModel->setData(index, QVariant::fromValue(itemData), Qt::UserRole), false);
}

TEST_F(ut_doaprotocolmodel, ut_doaprotocolmodel_setData_002)
{
    DOAProtocolItemDelegate doaProtocolItemDelegate;
    QListView listview;
    listview.setItemDelegate(&doaProtocolItemDelegate);
    listview.setModel(doaProtocolModel);

    QModelIndex index;
    int count = doaProtocolModel->rowCount(index);
    //设置刚刚添加的为选中状态
    index = doaProtocolModel->index(count - 1);

    AccountProtocol protocol;

    EXPECT_EQ(doaProtocolModel->setData(index, QVariant::fromValue(protocol), Qt::UserRole), true);
}


TEST_F(ut_doaprotocolmodel, ut_doaprotocolmodel_setData_003)
{
    DOAProtocolItemDelegate doaProtocolItemDelegate;
    QListView listview;
    listview.setItemDelegate(&doaProtocolItemDelegate);
    listview.setModel(doaProtocolModel);

    QModelIndex index;
    int count = doaProtocolModel->rowCount(index);
    //设置刚刚添加的为选中状态
    index = doaProtocolModel->index(count - 1);

    AccountProtocol protocol;

    EXPECT_EQ(doaProtocolModel->setData(index, QVariant::fromValue(protocol), Qt::DisplayRole), false);
}
