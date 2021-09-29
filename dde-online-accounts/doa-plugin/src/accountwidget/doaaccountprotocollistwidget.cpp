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
#include "doaaccountprotocollistwidget.h"
#include "doaprotocolmodel.h"
#include "doaprotocolitemdelegate.h"
#include "dialog/doaaddaccountdialog.h"

#include <DFontSizeManager>
#include <DListView>

#include <QLabel>
#include <QVBoxLayout>
#include <QNetworkConfigurationManager>
#include <QNetworkConfiguration>

DWIDGET_USE_NAMESPACE
DOAAccountProtocolListWidget::DOAAccountProtocolListWidget(QWidget *parent)
    : QWidget(parent)
{
    QLabel *addAccountLbl = new QLabel(tr("Add an Account"), this);
    DFontSizeManager::instance()->bind(addAccountLbl, DFontSizeManager::T5, QFont::Bold);

    QLabel *selectProtocolLbl = new QLabel(tr("Choose an account type"), this);
    DFontSizeManager::instance()->bind(selectProtocolLbl, DFontSizeManager::T6, QFont::Medium);

    DListView *mListView = new DListView();

    mListView->setAccessibleName("protocolListView");
    mListView->setFrameShape(QFrame::NoFrame);
    mListView->setViewportMargins(QMargins(0, 5, 0, 0));
    mListView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mListView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mListView->setEditTriggers(QListView::NoEditTriggers);
    mListView->setDragEnabled(false);
    mListView->setIconSize(QSize(30, 30));
    mListView->setLayoutDirection(Qt::LeftToRight);
    DOAProtocolItemDelegate *itemDelegate = new DOAProtocolItemDelegate;
    mListView->setItemDelegate(itemDelegate);
    mListView->setModel(new DOAProtocolModel);
    mListView->setSpacing(5);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addSpacing(10);
    layout->addWidget(addAccountLbl, 0, Qt::AlignCenter);
    layout->addSpacing(6);
    layout->addWidget(selectProtocolLbl, 0, Qt::AlignCenter);
    layout->addSpacing(10);
    layout->addWidget(mListView);
    this->setLayout(layout);

    connect(itemDelegate, &DOAProtocolItemDelegate::signalSelectItem, this, &DOAAccountProtocolListWidget::slotAccountItemClicked);

    m_network = new QNetworkConfigurationManager(this);
    slotConfigurationChanged(m_network->defaultConfiguration());
}

void DOAAccountProtocolListWidget::setModel(DOAAccountModel *model)
{
    if (model != m_dataModel) {
        m_dataModel = model;
    }
}

void DOAAccountProtocolListWidget::slotAccountItemClicked(ProtocolType type)
{
    //根据类型弹出对应登录框
    if (type == ProtocolType::Type_CalDAV) {
        DOAAddAccountDialog addAccountDialog(this);
        connect(&addAccountDialog, &DOAAddAccountDialog::signalAddAccountInfo, this, &DOAAccountProtocolListWidget::slotAddAccount);
        connect(&addAccountDialog, &DOAAddAccountDialog::signalCaneclLogin, m_dataModel, &DOAAccountModel::slotCancleLogin);
        connect(m_dataModel, &DOAAccountModel::signalAddAccountResults, &addAccountDialog, &DOAAddAccountDialog::slotAddAccountResults);

        connect(m_network, &QNetworkConfigurationManager::configurationChanged, &addAccountDialog, &DOAAddAccountDialog::slotConfigurationChanged);
        addAccountDialog.slotConfigurationChanged(m_networkConfiguration);
        addAccountDialog.exec();
    }
}

void DOAAccountProtocolListWidget::slotAddAccount(const AddAccountInfo &info)
{
    if (m_dataModel) {
        m_dataModel->slotAddAccount(info);
    }
}

void DOAAccountProtocolListWidget::slotConfigurationChanged(const QNetworkConfiguration &config)
{
    m_networkConfiguration = config;
}
