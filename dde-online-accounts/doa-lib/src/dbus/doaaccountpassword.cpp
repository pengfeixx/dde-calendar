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
#include "doaaccountpassword.h"

#include <QDBusReply>
#include <QDebug>

DOAAccountPassword::DOAAccountPassword(const QString &path, QObject *parent)
    : QDBusAbstractInterface(PASSWORD_DBUS_NAME, path, PASSWORD_DBUS_INTEERFACENAME, QDBusConnection::sessionBus(), parent)
{
    if (!this->isValid()) {
        qWarning() << "Error connecting remote object, service:" << this->service() << ",path:" << this->path() << ",interface" << this->interface();
    }
}

//获取密码
void DOAAccountPassword::getPassword()
{
    QList<QVariant> argumentList;
    //使用异步调用，防止前端界面卡顿
    bool isOk = callWithCallback(QStringLiteral("getPassword"), argumentList, this, SLOT(signalPassword(QString)), SLOT(slotDBusError(QDBusError)));
    if (!isOk) {
        qWarning() << "getPassword queueing failed";
    }
}

//修改密码
void DOAAccountPassword::changePassword(const QString &password)
{
    QList<QVariant> argumentList;
    argumentList << password;
    bool isOk = callWithCallback(QStringLiteral("ChangePassword"), argumentList, this, SLOT(signalChangePasswordResult(bool)), SLOT(slotDBusError(QDBusError)));
    if (!isOk) {
        qWarning() << "ChangePassword queueing failed";
    }
}

//服务对象错误信息处理
void DOAAccountPassword::slotDBusError(const QDBusError &error)
{
    qWarning() << Q_FUNC_INFO << error;
}
