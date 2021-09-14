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
#include "doaonlineaccount.h"
#include "displaytext.h"

#include <QDebug>
#include <QTranslator>

using namespace DCC_NAMESPACE;

DOAOnlineAccount::DOAOnlineAccount()
    : ModuleInterface()
    , m_accountModel(new DOAAccountModel)
    , m_translator(new QTranslator())
{
    //TODO 加载插件翻译文件
}

DOAOnlineAccount::~DOAOnlineAccount()
{
    delete m_accountModel;
    m_accountModel = nullptr;
}

QIcon DOAOnlineAccount::icon() const
{
    return QIcon::fromTheme("doa_onlineAccount");
}

void DOAOnlineAccount::preInitialize(bool sync, FrameProxyInterface::PushType pushType)
{
    Q_UNUSED(sync)
    Q_UNUSED(pushType)
}

void DOAOnlineAccount::initialize()
{
}

const QString DOAOnlineAccount::name() const
{
    return QStringLiteral("onlineaccount");
}

const QString DOAOnlineAccount::displayName() const
{
    return DOA::displayName;
}

void DOAOnlineAccount::active()
{
    createListWidget();
    createInformationWidget();
}

void DOAOnlineAccount::createListWidget()
{
    m_accountListWidget = new DOAAccountListWidget;
    m_accountListWidget->setModel(m_accountModel);
    m_accountListWidget->setVisible(false);
    m_frameProxy->pushWidget(this, m_accountListWidget);
    m_accountListWidget->setVisible(true);
}

void DOAOnlineAccount::createInformationWidget()
{
    m_informationWidget = new DOAInformationWidget;
    m_informationWidget->setModel(m_accountModel);
    m_informationWidget->setVisible(false);
    m_frameProxy->pushWidget(this, m_informationWidget);
    m_informationWidget->setVisible(true);
}

int DOAOnlineAccount::load(const QString &path)
{
    Q_UNUSED(path)
    createListWidget();
    createProtocolListWidget();
    qDebug() << Q_FUNC_INFO;
    return 0;
}

QStringList DOAOnlineAccount::availPage() const
{
    QStringList list;
    list << "account "
         << "create account";
    qDebug() << Q_FUNC_INFO;
    return list;
}

QString DOAOnlineAccount::translationPath() const
{
    //TODO 翻译文件路径
    return QStringLiteral("");
}

void DOAOnlineAccount::deactive()
{
}

void DOAOnlineAccount::contentPopped(QWidget *const w)
{
    Q_UNUSED(w)
}

void DOAOnlineAccount::reset()
{
}

QString DOAOnlineAccount::path() const
{
    return MAINWINDOW;
}

QString DOAOnlineAccount::follow() const
{
    return "cloudsync";
}
