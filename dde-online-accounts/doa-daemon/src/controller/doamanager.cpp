/*
   * Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
   *
   * Author:     wujian <wujian@uniontech.com>
   *
   * Maintainer: wujian <wujian@uniontech.com>
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
#include "doamanager.h"
#include "utils.h"
#include "dbus/dbus_consts.h"

#include <QDBusMessage>
#include <QtDBus>
#include <QDBusConnection>

DOAManager::DOAManager(QObject *parent)
    : QObject(parent)
    , m_doaaccountManager(new DOAAccountManager(this))
{
    QDBusConnection sessionBus = QDBusConnection::sessionBus();

    //创建帐户管理dbus服务对象

    //注册服务和对象
    if (sessionBus.registerService(kAccountsService)) {
        sessionBus.registerObject(kAccountsServiceManagerPath, m_doaaccountManager, QDBusConnection::ExportScriptableSlots | QDBusConnection::ExportScriptableSignals | QDBusConnection::ExportAllProperties);
    }

    //从数据库中查询帐户信息生成dbus服务
    m_doaaccountManager->creatAllAccountDbusFromDB();
}
