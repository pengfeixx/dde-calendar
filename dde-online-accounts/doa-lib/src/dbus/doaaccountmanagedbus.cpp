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
    if (!this->isValid()) {
        qWarning() << "Error connecting remote object, service:" << this->service() << ",path:" << this->path() << ",interface" << this->interface();
    }
    //关联后端dbus触发信号
    if (!QDBusConnection::sessionBus().connect(this->service(), this->path(), this->interface(), "", this, SLOT(propertyChanged(QDBusMessage)))) {
        qWarning() << "the connection was fail!";
    };
}

//添加帐户
void DOAAccountManageDBus::addAccount(const AddAccountInfo &info)
{
    QList<QVariant> argumentList;
    argumentList << QVariant::fromValue(addAccountInfoToJson(info));
    //使用异步调用，防止前端界面卡顿
    bool isOk = callWithCallback(QStringLiteral("addAccount"), argumentList, this, SLOT(signalAddAccountResults(int)), SLOT(slotDBusError(QDBusError)));
    if (!isOk) {
        qWarning() << "addAccount queueing failed";
    }
}

//获取帐户信息
void DOAAccountManageDBus::getAccountList()
{
    DOAAccountList::AccountInfoList accountInfoList;
    QList<QVariant> argumentList;

    bool isOk = callWithCallback(QStringLiteral("getAllAccount"), argumentList, this, SLOT(slotGetAccountList(QString)), SLOT(slotDBusError(QDBusError)));
    if (!isOk) {
        qWarning() << "getAllAccount queueing failed";
    }
}

//取消登录
void DOAAccountManageDBus::loginCancle(const QString &uuid)
{
    QList<QVariant> argumentList;
    argumentList << uuid;
    bool isOk = callWithCallback(QStringLiteral("loginCancle"), argumentList, this, SLOT(signalLoginCancle()), SLOT(slotDBusError(QDBusError)));
    if (!isOk) {
        qWarning() << "loginCancle queueing failed";
    }
}

//帐户列表信息改变处理
void DOAAccountManageDBus::accountListChangeHandle(const QString &infoStr)
{
    //    qDebug() << Q_FUNC_INFO << infoStr; iterfaceoper
    QList<QVariant> msg = accountListChangeParameterAnalysis(infoStr);
    if (msg.size() == 3) {
        //如错处理错误则退出
        if (msg.at(1).toInt() != 0) {
            qWarning() << msg.at(0).toString() << ",state:" << msg.at(1).toInt();
            return;
        }
        if ("ADD" == msg.at(0).toString()) {
            //如果为添加帐户信号
            DOAAccountList::AccountInfo info = accountJsonObjectToInfo(msg.at(2));
            emit signalAddAccountInfo(info);
            return;
        }
        if ("DEL" == msg.at(0).toString()) {
            //如果为删除帐户信号
            QString accountID = remvoeAccountJsonObjectToInfo(msg.at(2));
            emit signalDeleteAccount(accountID);
            return;
        }
    }
}

//帐户当前状态处理
void DOAAccountManageDBus::accountStateHandle(const QString &state)
{
    qDebug() << Q_FUNC_INFO << state;
}

//监听服务对象信号
void DOAAccountManageDBus::propertyChanged(const QDBusMessage &msg)
{
    if (msg.type() == QDBusMessage::SignalMessage && msg.path() == this->path() && msg.interface() == this->interface()) {
        if (msg.member() == "InterfaceAccountInfo") {
            //如果是帐户信息改变信号
            if (msg.arguments().size() > 0) {
                accountListChangeHandle(msg.arguments().first().toString());
            }
            return;
        }
    }
}

//服务对象错误信息处理
void DOAAccountManageDBus::slotDBusError(const QDBusError &error)
{
    qWarning() << Q_FUNC_INFO << error;
}

//处理获取到的所有帐户信息
void DOAAccountManageDBus::slotGetAccountList(const QString &infoList)
{
    //去序列化
    DOAAccountList::AccountInfoList info = accountListJsonToAccountInfoList(infoList);
    emit signalGetAccountList(info);
}
