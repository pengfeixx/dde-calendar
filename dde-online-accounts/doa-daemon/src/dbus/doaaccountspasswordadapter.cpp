/*
* Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
*
* Author:     wangyou <wangyou@uniontech.com>
*
* Maintainer: wangyou <wangyou@uniontech.com>
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
#include "doaaccountspasswordadapter.h"
#include "utils.h"
#include "dbus_consts.h"
#include "aesencryption.h"
#include "doaaccounts_adapter.h"

#include <QDebug>

DOAAccountsPassWordadapter::DOAAccountsPassWordadapter(QObject *parent)
    : QDBusAbstractAdaptor(parent)
{
}

bool DOAAccountsPassWordadapter::ChangePassword(const QString &password)
{
    if (password.length() <= 0) {
        qCritical() << "password format error length 0";
        return false;
    }

    qobject_cast<DOAAccountsadapter *>(parent())->m_doaProvider->setAccountPassword(password);

    if (qobject_cast<DOAAccountsadapter *>(parent())->m_doaProvider->login() != DOAProvider::SUCCESS) {
        qCritical() << "password verification fail";
    }

    //使用传输密钥解出明文
    QString descPasswordString;
    if (!AESEncryption::ecb_encrypt(password, descPasswordString, TKEY, false)) {
        qCritical() << "password desc error";
        return false;
    }

    int descPasswordStringLen = descPasswordString.mid(0, 2).toInt();

    //验证密码长度是否正确
    if (descPasswordStringLen != descPasswordString.length() - 2) {
        qCritical() << "password format error";
        return false;
    }

    QString relPassword = descPasswordString.mid(2, descPasswordStringLen);

    //使用数据库密钥加密
    QString encPassWordString;
    if (!AESEncryption::ecb_encrypt(descPasswordString, encPassWordString, SKEY, true)) {
        qCritical() << "password desc error";
        return false;
    }

    qobject_cast<DOAAccountsadapter *>(parent())->m_doaProvider->setAccountPassword(encPassWordString);
    //保存数据库
    emit this->sign_changeProperty("Password", qobject_cast<DOAAccountsadapter *>(parent())->m_doaProvider);
    qobject_cast<DOAAccountsadapter *>(parent())->m_doaProvider->setAccountPassword(password);
    return true;
}

/**
 * @brief DOAAccountsPassWordadapter::getPassword
 * @return
 * 获取密码
 */
QString DOAAccountsPassWordadapter::getPassword()
{
    return qobject_cast<DOAAccountsadapter *>(parent())->m_doaProvider->getAccountPassword();
}
