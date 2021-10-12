/*
* Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
*
* Author:     chenhaifeng  <chenhaifeng@uniontech.com>
*
* Maintainer: chenhaifeng  <chenhaifeng@uniontech.com>
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
#include "doainformationwidget.h"
#include "doaaccountinfowidget.h"
#include "doaaccountprotocollistwidget.h"

DOAInformationWidget::DOAInformationWidget(QWidget *parent)
    : DStackedWidget(parent)
{
    initWidget();
}

void DOAInformationWidget::setModel(DOAAccountModel *model)
{
    if (m_accountModel != model) {
        if (m_accountModel) {
            disconnect(m_accountModel, &DOAAccountModel::signalChangeState, this, &DOAInformationWidget::slotShowStateChange);
        }
        m_accountModel = model;
        m_accountInfoWidget->setModel(m_accountModel);
        m_accountProWidget->setModel(m_accountModel);
        slotShowStateChange();
        connect(m_accountModel, &DOAAccountModel::signalChangeState, this, &DOAInformationWidget::slotShowStateChange);
    }
}

void DOAInformationWidget::initWidget()
{
    m_accountProWidget = new DOAAccountProtocolListWidget();
    this->addWidget(m_accountProWidget);
    m_accountInfoWidget = new DOAAccountInfoWidget();
    this->addWidget(m_accountInfoWidget);
}

void DOAInformationWidget::slotShowStateChange()
{
    if (m_accountModel) {
        DOAAccountModel::AccountWidgetState state = m_accountModel->state();
        //详情界面数据初始化
        m_accountInfoWidget->initData();
        if (state == DOAAccountModel::Account_Details) {
            setCurrentWidget(m_accountInfoWidget);
            //更新当前帐户信息
            m_accountInfoWidget->slotUpdateCurrentAccount();
        } else {
            setCurrentWidget(m_accountProWidget);
        }
    }
}
