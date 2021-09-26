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
#include "doaaccountdbus.h"

#include <QDBusPendingReply>
#include <QDBusReply>
#include <QtDebug>
#include <QDBusInterface>

DOAAccountDBus::DOAAccountDBus(const QString &path, QObject *parent)
    : QDBusAbstractInterface(ACCOUNT_DBUS_NAME, path, ACCOUNT_DBUS_INTEERFACENAME, QDBusConnection::sessionBus(), parent)
{
    if (!this->isValid()) {
        qWarning() << "Error connecting remote object, service:" << this->service() << ",path:" << this->path() << ",interface" << this->interface();
    }
    //关联后端dbus属性
    if (!QDBusConnection::sessionBus().connect(this->service(), this->path(), "org.freedesktop.DBus.Properties", "PropertiesChanged", "sa{sv}as", this, SLOT(propertiesChanged(QDBusMessage)))) {
        qWarning() << "the connection was fail!";
    };
}

//删除帐户
bool DOAAccountDBus::remove()
{
    QList<QVariant> argumentList;
    QDBusPendingCall pCall = asyncCallWithArgumentList(QStringLiteral("Remove"), argumentList);
    pCall.waitForFinished();
    QDBusMessage reply = pCall.reply();
    if (reply.type() != QDBusMessage::ReplyMessage) {
        qWarning() << "Remove error :" << reply;
        return false;
    }
    QDBusReply<bool> result = reply;
    return result.value();
}

//检测帐户状态
void DOAAccountDBus::checkAccountState()
{
    QList<QVariant> argumentList;
    QDBusPendingCall pCall = asyncCallWithArgumentList(QStringLiteral("CheckAccountState"), argumentList);
}

//获取是否应用于日历
bool DOAAccountDBus::getCalendarDisabled()
{
    return getPropertyByName("CalendarDisabled").toBool();
}

//设置是否应用于日历
bool DOAAccountDBus::setCalendarDisabled(bool disabled)
{
    return setPropertyByName("CalendarDisabled", disabled);
}

//获取用户名
QString DOAAccountDBus::getUserName()
{
    return getPropertyByName("UserName").toString();
}

//设置用户名
bool DOAAccountDBus::setUserName(const QString &userName)
{
    return setPropertyByName("UserName", userName);
}

//获取帐户id
QString DOAAccountDBus::getAccountID()
{
    return getPropertyByName("Id").toString();
}

//获取帐户服务提供商,比如QQ等
int DOAAccountDBus::getProviderName()
{
    return getPropertyByName("ProviderName").toInt();
}

//获取帐户类型,比如CalDav等
int DOAAccountDBus::getProviderType()
{
    return getPropertyByName("ProviderType").toInt();
}

//根据属性名称获取对应属性值
QVariant DOAAccountDBus::getPropertyByName(const char *porpertyName)
{
    QDBusInterface dbusinterface(this->service(), this->path(), this->interface(), QDBusConnection::sessionBus(), this);
    return dbusinterface.property(porpertyName);
}

//根据属性名称设置属性值
bool DOAAccountDBus::setPropertyByName(const char *porpertyName, const QVariant &value)
{
    QDBusInterface dbusinterface(this->service(), this->path(), this->interface(), QDBusConnection::sessionBus(), this);
    return dbusinterface.setProperty(porpertyName, value);
}

//监听相关属性
void DOAAccountDBus::propertiesChanged(const QDBusMessage &msg)
{
    QList<QVariant> arguments = msg.arguments();
    // 参数固定长度
    if (3 != arguments.count())
        return;
    QString interfaceName = msg.arguments().at(0).toString();
    if (interfaceName != this->interface())
        return;
    QVariantMap changedProps = qdbus_cast<QVariantMap>(arguments.at(1).value<QDBusArgument>());
    QStringList keys = changedProps.keys();
    foreach (const QString &prop, keys) {
        if (prop == "CalendarDisabled") {
            bool disabled = changedProps[prop].toBool();
            emit signalCalendarDisabled(disabled);
        } else if (prop == "UserName") {
            QString userName = changedProps[prop].toString();
            emit signalUserNameChanged(userName);
        } else if (prop == "Status") {
            emit signalStatusChanged(changedProps[prop].toInt());
        }
    }
}
