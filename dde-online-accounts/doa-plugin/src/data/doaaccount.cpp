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
#include "doaaccount.h"
#include "dbus/doaaccountdbus.h"
#include "dbus/doaaccountpassword.h"
#include "aesencryption.h"

#include <QDebug>

DOAAccount::DOAAccount(QObject *parent)
    : QObject(parent)
    , m_Protocol(Protocol_CalDav)
{
}

//获取帐户名称
QString DOAAccount::getAccountName() const
{
    return m_accountName;
}

//设置帐户名称
void DOAAccount::setAccountName(const QString &value)
{
    m_accountName = value;
}

//获取帐户密码
QString DOAAccount::getAccountPassword() const
{
    return m_accountPassword;
}

//设置帐户密码
void DOAAccount::setAccountPassword(const QString &value)
{
    m_accountPassword = value;
}

//获取显示名称
QString DOAAccount::getUserName() const
{
    return m_displayName;
}

//设置帐户显示名称
void DOAAccount::setUserName(const QString &value)
{
    m_displayName = value;
}

//获取服务器地址
QString DOAAccount::getUrl() const
{
    return m_url;
}

//设置服务器地址
void DOAAccount::setUrl(const QString &value)
{
    m_url = value;
}

//获取相关资源路径
QString DOAAccount::getPath() const
{
    return m_path;
}

//设置相关资源路径
void DOAAccount::setPath(const QString &value)
{
    m_path = value;
}

//获取该帐户协议
DOAAccount::AccountProtocol DOAAccount::getProtocol() const
{
    return m_Protocol;
}

//设置帐户协议
void DOAAccount::setProtocol(const AccountProtocol &Protocol)
{
    m_Protocol = Protocol;
}

//添加应用于相关应用
void DOAAccount::addApplyObject(const DOAApplyToObject &applyObject)
{
    //如果列表中不包含该对象，则添加
    if (!m_applyObject.contains(applyObject)) {
        m_applyObject.append(applyObject);
    }
}

//获取应用于的所有应用
QVector<DOAApplyToObject> DOAAccount::getApplyObject() const
{
    return m_applyObject;
}

//获取帐户id
QString DOAAccount::getAccountID() const
{
    return m_accountID;
}

//设置帐户id
void DOAAccount::setAccountID(const QString &value)
{
    m_accountID = value;
}

//获取帐户状态
DOAAccount::AccountState DOAAccount::getAccountState() const
{
    return m_state;
}

//设置帐户状态
void DOAAccount::setAccountState(AccountState state)
{
    m_state = state;
}

//设置添加帐户时间
void DOAAccount::setAddAccountDateTime(const QDateTime &addDateTime)
{
    m_addDateTime = addDateTime;
}

//获取添加帐户时间
QDateTime DOAAccount::getAddAccountDateTime() const
{
    return m_addDateTime;
}

//设置帐户DBus路径
void DOAAccount::setAccountDBusPath(const QString &dbusPath)
{
    m_DBusPath = dbusPath;
    createDBus();
}

//设置帐户信息
void DOAAccount::setAccountInfo(const DOAAccountList::AccountInfo &info)
{
    //将从后端获取到的数据转换为帐户数据
    setAccountID(info.accountID);
    setAccountName(info.accountName);
    setUserName(info.displayName);
    setProtocol(getProtocolByindex(info.accountType));
    setAccountState(getStateByIndex(info.accountState));
    setAddAccountDateTime(info.accountAddTime);
    setUrl(info.serverIP);
    //该帐户存在应用于日历
    if (info.applyToCalendarState.isValid) {
        DOAApplyToObject applyToCalendar;
        applyToCalendar.setAppName("dde-calendar");
        applyToCalendar.setIsApply(!info.applyToCalendarState.disEnable);
        addApplyObject(applyToCalendar);
    }
    //该帐户存在应用于邮箱
    if (info.applyToEMailState.isValid) {
        DOAApplyToObject applyToCalendar;
        applyToCalendar.setAppName("deepin-mail");
        applyToCalendar.setIsApply(!info.applyToEMailState.disEnable);
        addApplyObject(applyToCalendar);
    }
    setAccountDBusPath(info.accountDBusPath);
    //根据获取到的帐户DBus路径创建对应的dbus接口
    createDBus();
    //如果密码DBus创建成功，获取对应密码
    if (m_passwordDBus) {
        m_passwordDBus->getPassword();
    }
}

void DOAAccount::updateUserName(const QString &userName)
{
    if (m_accountDBus) {
        if (!m_accountDBus->setUserName(userName)) {
            qWarning() << "set username error";
            //            setUserName(userName);
        }
    }
}

/**
 * @brief DOAAccount::updatePassword 更新密码
 * @param password
 */
void DOAAccount::updatePassword(const QString &password)
{
    if (m_passwordDBus) {
        QString ecbPassword;
        //加密密码
        AESEncryption::ecb_encrypt(password, ecbPassword, TKEY, true);
        //调用Dbus 更新密码
        m_passwordDBus->changePassword(ecbPassword);
        //设置本地帐户密码
        setAccountPassword(password);
        //更新密码 前端详情页
        emit signalPasswordChanged(getAccountID());
    }
}

//更新应用于
void DOAAccount::updateApplyTo(const DOAApplyToObject &app)
{
    if (m_accountDBus) {
        if (app.appName() == "dde-calendar") {
            //调用Dbus更新后端
            if (!m_accountDBus->setCalendarDisabled(!app.isApply())) {
                qWarning() << "set dde-calendar error";
            }

            slotCalendarDisabled(!app.isApply());
        }
    }
}

//创建与帐户关联的DBus
void DOAAccount::createDBus()
{
    m_accountDBus = new DOAAccountDBus(m_DBusPath, this);
    if (m_accountDBus->isValid()) {
        connect(m_accountDBus, &DOAAccountDBus::signalUserNameChanged, this, &DOAAccount::slotUserNameChanged);
        connect(m_accountDBus, &DOAAccountDBus::signalCalendarDisabled, this, &DOAAccount::slotCalendarDisabled);
        connect(m_accountDBus, &DOAAccountDBus::signalStatusChanged, this, &DOAAccount::slotAccountStatus);
    } else {
        qWarning() << "m_accountDBus DBus create error";
        delete m_accountDBus;
        m_accountDBus = nullptr;
    }

    m_passwordDBus = new DOAAccountPassword(m_DBusPath, this);
    if (m_passwordDBus->isValid()) {
        connect(m_passwordDBus, &DOAAccountPassword::signalPassword, this, &DOAAccount::slotGetPassword);
    } else {
        qWarning() << "m_passwordDBus DBus create error";
        delete m_passwordDBus;
        m_passwordDBus = nullptr;
    }
}

//根据协议编号获取对应的协议
DOAAccount::AccountProtocol DOAAccount::getProtocolByindex(const int index)
{
    return static_cast<DOAAccount::AccountProtocol>(index);
}

//根据帐户状态编号获取对应的状态
DOAAccount::AccountState DOAAccount::getStateByIndex(const int index)
{
    AccountState state;
    switch (index) {
    case 0:
        state = Account_Success;
        break;
    case 1:
        state = Account_TimeOut;
        break;
    case 4:
        state = Account_AuthenticationFailed;
        break;
    default:
        state = Account_ServerException;
        qDebug() << this->getAccountID() << "state:" << index;
        break;
    }
    return state;
}

//用户名改变
void DOAAccount::slotUserNameChanged(const QString &userName)
{
    if (getUserName() != userName) {
        setUserName(userName);
        emit signalUserNameChanged(getAccountID());
    }
}

//是否应用于日历属性改变
void DOAAccount::slotCalendarDisabled(bool disabled)
{
    for (int i = 0; i < m_applyObject.size(); ++i) {
        if (m_applyObject.at(i).appName() == "dde-calendar") {
            m_applyObject[i].setIsApply(!disabled);
            break;
        }
    }
}

//是否帐户状态属性改变
void DOAAccount::slotAccountStatus(int accountStatus)
{
    //转换帐户状态
    int accountState;
    switch (accountStatus) {
    case 0:
        accountState = DOAAccount::Account_Success;
        break;
    case 1:
        accountState = DOAAccount::Account_TimeOut;
        break;
    case 3:
    case 9:
    case 11:
        accountState = DOAAccount::Account_ServerException;
        break;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
        accountState = DOAAccount::Account_AuthenticationFailed;
        break;
    default:
        accountState = DOAAccount::Account_ServerException;
        break;
    }

    if (getAccountState() != accountState) {
        setAccountState((DOAAccount::AccountState)accountState);
        emit signalUserNameChanged(getAccountID()); //更新状态列表
        emit signalAccountStatusChanged(getAccountID()); //更新状态详情
        //状态正常则重新获取密码
        if (m_passwordDBus) {
            m_passwordDBus->getPassword();
        }
    }
}

//处理加密后的密码
void DOAAccount::slotGetPassword(const QString &password)
{
    QString ecbPassword;
    AESEncryption::ecb_encrypt(password, ecbPassword, TKEY, false);
    if (getAccountPassword() != ecbPassword) {
        setAccountPassword(ecbPassword);
        emit signalPasswordChanged(getAccountID());
    }
}

//移除该帐户
void DOAAccount::slotRemove()
{
    if (m_accountDBus) {
        m_accountDBus->remove();
    }
}

void DOAAccount::slotCheckState()
{
    if (m_accountDBus) {
        m_accountDBus->checkAccountState();
    }
}

QDebug operator<<(QDebug debug, const DOAAccount &account)
{
    debug << "accountID:" << account.getAccountID()
          << ",accountName:" << account.getAccountName()
          << ",displayName:" << account.getUserName()
          << ",url:" << account.getUrl();
    return debug;
}

QDebug operator<<(QDebug debug, const DOAAccount *account)
{
    debug << "accountID:" << account->getAccountID()
          << ",accountName:" << account->getAccountName()
          << ",displayName:" << account->getUserName()
          << ",url:" << account->getUrl();
    return debug;
}
