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
#include "doadataconversion.h"

#include <QDebug>
#include <QTranslator>

DOAOnlineAccount::DOAOnlineAccount()
    : ModuleInterface()
    , m_accountModel(new DOAAccountModel)
    , m_translator(new QTranslator())
{
    // 加载插件翻译文件
    m_translator->load(QLocale::system(),
                       QStringLiteral("dde-online-accounts-plugin"),
                       QStringLiteral("_"),
                       QStringLiteral("/usr/share/dde-online-accounts-plugin/translations"));
    qApp->installTranslator(m_translator);
}

DOAOnlineAccount::~DOAOnlineAccount()
{
    if (m_translator) {
        qApp->removeTranslator(m_translator);
        m_translator->deleteLater();
    }

    if (m_accountModel) {
        delete m_accountModel;
        m_accountModel = nullptr;
    }
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
    return tr("Network Accounts");
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
    if (!m_accountListWidget) {
        active();
    }

    QEventLoop eventLoop;
    QTimer timer;
    timer.setInterval(2000);
    timer.setSingleShot(true);
    timer.start();
    connect(&timer, &QTimer::timeout, &eventLoop, &QEventLoop::quit);
    connect(m_accountModel, &DOAAccountModel::signalGetAccountListSuccess, &eventLoop, &QEventLoop::quit);
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);

    QStringList pages = path.split(",");

    if ("ADD" == pages[0]) {
        //如果为添加帐户信号
        if (m_accountModel->getAccountMap().size() > 0) {
            m_accountListWidget->slotGetAccountListSuccess();
            m_accountListWidget->slotClickeAddAccount();
        }
    } else if ("DEL" == pages[0]) {
        QString data = path.mid(path.indexOf(',') + 1);

        QList<QVariant> msg = accountListChangeParameterAnalysis(data);

        if (msg.size() == 0) {
            qWarning() << "delete page size 0";
            return 0;
        }

        //如果为删除帐户信号
        QString accountID = remvoeAccountJsonObjectToInfo(msg.at(2));

        if (!m_accountModel->getAccount(accountID)) {
            qWarning() << "delete account not existence";
            return 0;
        }

        QTimer::singleShot(20, this, [=] {
            m_accountListWidget->slotSelectItem(accountID);
            m_accountModel->signShowDeleteDialog();
        });
    }

    return 0;
}

QStringList DOAOnlineAccount::availPage() const
{
    QStringList list;
    list << "account "
         << "ADD"
         << "DEL";
    qDebug() << Q_FUNC_INFO;
    return list;
}

QString DOAOnlineAccount::translationPath() const
{
    //翻译文件路径
    return QStringLiteral(":/translations/dde-online-accounts-plugin_%1.ts");
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
