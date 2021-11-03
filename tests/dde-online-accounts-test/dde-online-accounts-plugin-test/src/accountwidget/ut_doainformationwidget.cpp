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
#include "ut_doainformationwidget.h"

ut_doainformationwidget::ut_doainformationwidget()
{

}

void ut_doainformationwidget::SetUp()
{
    doaInformationWidget = new DOAInformationWidget();
}

void ut_doainformationwidget::TearDown()
{
    delete doaInformationWidget;
    doaInformationWidget = nullptr;
}

TEST_F(ut_doainformationwidget, ut_doainformationwidget_setModel_001)
{
    DOAAccountModel modele;
    doaInformationWidget->setModel(&modele);
    EXPECT_EQ(doaInformationWidget->m_accountModel, &modele);
    DOAAccountModel modele1;
    doaInformationWidget->setModel(&modele1);
    EXPECT_EQ(doaInformationWidget->m_accountModel, &modele1);
}

TEST_F(ut_doainformationwidget, ut_doainformationwidget_initWidget_001)
{
    EXPECT_EQ(doaInformationWidget->count(), 2);
}

TEST_F(ut_doainformationwidget, ut_doainformationwidget_slotShowStateChange_001)
{
    DOAAccountModel modele;
    modele.setState(DOAAccountModel::Account_Details);
    doaInformationWidget->setModel(&modele);
    doaInformationWidget->slotShowStateChange();
    EXPECT_EQ(doaInformationWidget->currentWidget(), (QWidget*)doaInformationWidget->m_accountInfoWidget);
}

TEST_F(ut_doainformationwidget, ut_doainformationwidget_slotShowStateChange_002)
{
    DOAAccountModel modele;
    modele.setState(DOAAccountModel::Account_Init);
    doaInformationWidget->setModel(&modele);
    doaInformationWidget->slotShowStateChange();
    EXPECT_EQ(doaInformationWidget->currentWidget(), (QWidget*)doaInformationWidget->m_accountProWidget);
}
