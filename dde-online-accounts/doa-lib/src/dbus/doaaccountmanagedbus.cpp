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
#include "doaaccountmanagedbus.h"

#include "doadataconversion.h"

#include <QDBusReply>
#include <QDebug>

DOAAccountManageDBus::DOAAccountManageDBus(QObject *parent)
    : QDBusAbstractInterface(DBUS_NAME, DBUS_PATH, DBUS_INTEERFACENAME, QDBusConnection::sessionBus(), parent)
{
    //关联后端dbus触发信号
    if (!QDBusConnection::sessionBus().connect(this->service(), this->path(), this->interface(), "", this, SLOT(propertyChanged(QDBusMessage)))) {
        qWarning() << "the connection was fail!";
    };
}

qint32 DOAAccountManageDBus::addAccount(const AddAccountInfo &info)
{
    QList<QVariant> argumentList;
    argumentList << QVariant::fromValue(addAccountInfoToJson(info));
    QDBusPendingCall pCall = asyncCallWithArgumentList(QStringLiteral("addAccount"), argumentList);
    pCall.waitForFinished();
    QDBusMessage reply = pCall.reply();
    if (reply.type() != QDBusMessage::ReplyMessage) {
        qWarning() << "addAccount error :" << reply;
        return -1;
    }
    QDBusReply<qint32> id = reply;
    return id.value();
}

//获取帐户信息
DOAAccountList::AccountInfoList DOAAccountManageDBus::getAccountList()
{
    DOAAccountList::AccountInfoList accountInfoList;
    QList<QVariant> argumentList;
    QDBusPendingCall pCall = asyncCallWithArgumentList(QStringLiteral("getAllAccount"), argumentList);
    pCall.waitForFinished();
    QDBusMessage reply = pCall.reply();
    if (reply.type() != QDBusMessage::ReplyMessage) {
        qWarning() << "getAllAccount error :" << reply;
        return accountInfoList;
    }
    QDBusReply<QString> listStr = reply;
    qDebug() << listStr;
    return accountListJsonToAccountInfoList(listStr);
}

void DOAAccountManageDBus::loginCancle(const QString &uuid)
{
    QList<QVariant> argumentList;
    argumentList << uuid;
    QDBusPendingCall pCall = asyncCallWithArgumentList(QStringLiteral("loginCancle"), argumentList);
    pCall.waitForFinished();
    QDBusMessage reply = pCall.reply();
    if (reply.type() != QDBusMessage::ReplyMessage) {
        qWarning() << "loginCancle error :" << reply;
    }
}

void DOAAccountManageDBus::propertyChanged(const QDBusMessage &msg)
{
    if (msg.type() == QDBusMessage::SignalMessage && msg.path() == this->path() && msg.interface() == this->interface()) {
        //TODO: 帐户管理信号监听
        qDebug() << msg.member() << msg.arguments();
    }
}
