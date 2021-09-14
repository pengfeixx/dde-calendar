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
#include "doaaccountinfowidget.h"
#include "displaytext.h"

#include <DWarningButton>
#include <DFontSizeManager>

#include <QLabel>
#include <QVBoxLayout>
#include <QScroller>
#include <QEvent>

DWIDGET_USE_NAMESPACE

DOAAccountInfoWidget::DOAAccountInfoWidget(QWidget *parent)
    : QWidget(parent)
    , m_content(new QWidget(this))
    , m_scrollArea(new QScrollArea(this))
    , m_accountInfo(new DOAInfoWidget(this))
    , m_accountProtocolLbl(new QLabel("doa_caldav", this))
    , m_applyToWidget(new DOAApplyToWidget(this))
    , m_errorWidget(new DOAErrorWidget)
    , m_accountModel(nullptr)
{
    initWidget();
}

void DOAAccountInfoWidget::setModel(DOAAccountModel *model)
{
    if (model) {
        m_accountModel = model;
    }
    slotUpdateCurrentAccount();

    connect(m_accountModel, &DOAAccountModel::signalSelectAccountChange, this, &DOAAccountInfoWidget::slotUpdateCurrentAccount);
}

void DOAAccountInfoWidget::slotUpdateCurrentAccount()
{
    //获取当前帐户信息
    m_Account = m_accountModel->getCurrentAccount();
    if (m_Account) {
        //设置帐户信息
        m_accountInfo->setShowData(m_Account->getDisplayName(), m_Account->getUrl(), m_Account->getAccountName());
        m_applyToWidget->clearApp();
        //设置应用于应用
        for (int i = 0; i < m_Account->getApplyObject().size(); ++i) {
            m_applyToWidget->addApp(m_Account->getApplyObject().at(i));
        }
    }
}

void DOAAccountInfoWidget::initWidget()
{
    //自动滚动区
    m_scrollArea = new QScrollArea;
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setFrameStyle(QFrame::NoFrame);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_scrollArea->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    m_scrollArea->setContentsMargins(0, 0, 0, 0);

    m_scrollArea->setWidget(m_content);

    //删除按钮
    DWarningButton *warningBtn = new DWarningButton(this);
    warningBtn->setText(DOA::AccountInfo::deleteAccount);

    DFontSizeManager::instance()->bind(m_accountProtocolLbl, DFontSizeManager::T3, QFont::Bold);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(warningBtn);
    layout->addWidget(m_errorWidget);
    layout->addSpacing(20);

    layout->addWidget(m_accountProtocolLbl);
    layout->addSpacing(20);
    layout->addWidget(m_accountInfo);
    layout->addSpacing(20);
    layout->addWidget(m_applyToWidget);
    layout->addStretch();
    m_content->setLayout(layout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->addWidget(m_scrollArea);
    mainLayout->setSpacing(0);
    this->setLayout(mainLayout);
}
