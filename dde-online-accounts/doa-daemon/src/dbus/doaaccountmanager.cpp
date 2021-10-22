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
#include "doaaccountmanager.h"
#include "doaaccounts_adapter.h"
#include "doaaccountscalendar_adapter.h"
#include "dbus_consts.h"
#include "controller/doaqqprovider.h"
#include "utils.h"
#include "aesencryption.h"
#include "qjsonutils.h"

#include <QtDBus/QDBusConnection>
#include <QVariant>

DOAAccountManager::DOAAccountManager(QObject *parent)
    : QObject(parent)
    , m_netWorkDBus(new DOANetWorkDBus(this))
    , m_db(new AccountDB(this))
{
    this->setObjectName("DOAAccountManager");
    //数据库查询结果信号
    connect(m_db, &AccountDB::selectAccountResult, this, &DOAAccountManager::onSelectAccountResult);
    //网络状态变化信号
    connect(m_netWorkDBus, &DOANetWorkDBus::sign_NetWorkChange, this, &DOAAccountManager::netWorkStateNotify);

    //初始化数据库
    m_db->initDbAsync();
}

/**
 * @brief DOAAccountManager::netWorkStateNotify
 * @param config
 * 网卡状态变化处理
 */
void DOAAccountManager::netWorkStateNotify(const DOANetWorkDBus::NetWorkState networkState)
{
    //验证网络状态
    switch (networkState) {
    case DOANetWorkDBus::Active: { //网络连接成功
        qWarning() << "Active";
        emit this->sign_netWorkChange(true);
        break;
    }
    default:
        qWarning() << networkState;
        emit this->sign_netWorkChange(false);
        break;
    }
}

/**
 * @brief DOAAccountManager::initAccountPropertiesChange
 * @param accountAdapter
 * 初始化 各个帐户信号槽
 */
void DOAAccountManager::initAccountPropertiesChange(DOAAccountsadapter *accountAdapter)
{
    //帐户修改信号
    connect(accountAdapter, &DOAAccountsadapter::sign_changeProperty, this, &DOAAccountManager::onChangeProperty);
    //帐户删除信号
    connect(accountAdapter, &DOAAccountsadapter::sign_remove, this, &DOAAccountManager::onRemoveAccount);

    //检测帐户状态
    connect(this, &DOAAccountManager::sign_netWorkChange, accountAdapter, &DOAAccountsadapter::onNetWorkChange, Qt::QueuedConnection);
}

/**
 * @brief DOAAccountManager::creatAllAccountDbusFromDB
 * 从数据库中取出所有帐户信息
 */
void DOAAccountManager::creatAllAccountDbusFromDB()
{
    //读数据库查询数据
    m_db->queryAccountList();
}

/**
 * @brief DOAAccountManager::passwordPro
 * @param dbpassword 数据库密码
 * @return 传输密钥加密的密码
 * 从数据库中取出密码并解密再使用传输密钥加密
 */
QString DOAAccountManager::passwordPro(const QString &dbpassword)
{
    //使用数据库密钥解密密码
    QString descPasswordString;
    QString encPasswordString;

    bool result = AESEncryption::ecb_encrypt(dbpassword, descPasswordString, SKEY, false);

    if (!result) {
        qCritical() << "password desc fail";
        return "";
    }

    result = AESEncryption::ecb_encrypt(descPasswordString, encPasswordString, TKEY, true);

    if (!result) {
        qCritical() << "password enc fail";
        return "";
    }

    return encPasswordString;
}

/**
 * @brief DOAAccountManager::onSelectAccountResult
 * @param result
 * 数据库中取出帐户返回结果槽处理
 */
void DOAAccountManager::onSelectAccountResult(const AccountResultList &result)
{
    for (int i = 0; i < result.count(); ++i) {
        DOAAccountsadapter *accountadapter = new DOAAccountsadapter(this);
        if (result[i].m_accountProviderType == "QQ") {
            //QQ帐户，创建QQ帐户对象
            DOAProvider *doaprovider = new DOAQQProvider();

            doaprovider->setAccountID(result[i].m_accountID);
            doaprovider->setUrl(result[i].m_accountURL);
            doaprovider->setProtocol((DOAProvider::ProtocolType)protocolTypemetaEnum.keyToValue(result[i].m_accountType.toLatin1().data()));
            doaprovider->setPath(result[i].m_accountDbusPath);
            doaprovider->setDisplayName(result[i].m_accountUserName);
            doaprovider->setAccountName(result[i].m_accountName);

            doaprovider->setSSL(result[i].m_isSSL);
            doaprovider->setCalendarDisabled(result[i].m_calendarDisabled);
            doaprovider->setAccountStat((DOAProvider::LoginState)(result[i].m_state.toInt()));

            doaprovider->setUri(result[i].m_accountURI);
            doaprovider->setProviderName((DOAProvider::AccountType)accountTypemetaEnum.keyToValue(result[i].m_accountProviderType.toLatin1().data()));
            //密码处理
            doaprovider->setAccountPassword(passwordPro(result[i].m_accountPassword));

            doaprovider->setCreateTime(result[i].m_accountCreateTime);

            accountadapter->setDoaProvider(doaprovider);

            m_doaProviderMap.insert(result[i].m_accountID, accountadapter);
        }

        //创建Dbus服务
        creatAccountDbus(accountadapter);

        //设置同步状态 使用现有值重新设置只为了触发定时检测
        QDBusInterface *iface = new QDBusInterface(kAccountsService, accountadapter->getDoaProvider()->getPath(), kAccountsServiceAccountIface,
                                                   QDBusConnection::sessionBus());
        iface->setProperty("CalendarDisabled", accountadapter->getDoaProvider()->getCalendarDisabled());
        iface->deleteLater();
    }

    //获取当前网络状态
    netWorkStateNotify(m_netWorkDBus->getNetWorkState());
}

/**
 * @brief DOAAccountManager::getAllAccount
 * @return
 * 获取帐户列表
 */
QString DOAAccountManager::getAllAccount()
{
    QJsonArray accountArray;
    QJsonObject accountList;
    QMap<QString, DOAAccountsadapter *>::iterator it;
    //从MAP中取出数据
    for (it = m_doaProviderMap.begin(); it != m_doaProviderMap.end(); ++it) {
        DOAAccountsadapter *doaAccountAdapter = it.value();
        //从缓存中取出数据 组JSON 返回给前端
        QJsonUtils::accountAddJsonArray(doaAccountAdapter->getDoaProvider(), accountArray);
    }

    QMap<QString, QVariant> accountListMap;
    accountListMap.insert("accountcnt", m_doaProviderMap.count());
    accountListMap.insert("accountlist", accountArray);
    accountListMap.insert("stat", 0);
    QString strJson = QJsonUtils::getJsonString(accountListMap);

    return strJson;
}

/**
 * @brief DOAAccountManager::creatAccountDbus
 * @param accountAdapter
 * 数据库操作成功，则创建当个帐户的dbus
 */
void DOAAccountManager::creatAccountDbus(DOAAccountsadapter *accountAdapter)
{
    //创建帐户dbus
    accountAdapter->setObjectName("accountAdapter");

    //创建当个帐户同步对象变化信号槽
    initAccountPropertiesChange(accountAdapter);

    QDBusConnection sessionBus = QDBusConnection::sessionBus();
    if (sessionBus.registerService(kAccountsService)) {
        //创建日历dbus
        if (!accountAdapter->getDoaProvider()->getCalendarDisabled()) {
            //日历可用
            DOAAccountsCalendardapter *accountcalendaradapter = new DOAAccountsCalendardapter(accountAdapter);
            accountcalendaradapter->setObjectName("accountcalendaradapter");
        }

        //QQ帐户创建获取密码dbus服务
        if (accountAdapter->getDoaProvider()->getProviderName() == DOAProvider::QQ) {
            DOAAccountsPassWordadapter *accountpasswordadapter = new DOAAccountsPassWordadapter(accountAdapter);
            accountpasswordadapter->setObjectName("accountpasswordadapter");
            connect(accountpasswordadapter, &DOAAccountsPassWordadapter::sign_changeProperty, this, &DOAAccountManager::onChangeProperty);
        }
        //导出所有对象
        sessionBus.registerObject(accountAdapter->getDoaProvider()->getPath(), accountAdapter, QDBusConnection::ExportAdaptors | QDBusConnection::ExportScriptableSlots | QDBusConnection::ExportAllProperties);
    }
}

/**
 * @brief DOAAccountManager::loginCancle
 * @param uuid 登录时传输的UUID
 * 用户取消
 */
void DOAAccountManager::loginCancle(const QString &uuid)
{
    QMutexLocker m_lock(&m_mutex); //单线程处理这个后续删除
    QMap<QString, DOAProvider *>::iterator it;
    //从登录队列中,取出数据删除
    for (it = m_doaProviderLoginingMap.begin(); it != m_doaProviderLoginingMap.end(); ++it) {
        if (it.key() == uuid) {
            DOAProvider *m_doaProvider = it.value();
            m_doaProvider->loginCancel();
            m_doaProviderLoginingMap.erase(it);
            break;
        }
    }
}

/**
 * @brief DOAAccountManager::addAccount
 * @param accountData 帐户信息JSON
 * @return
 * 增加帐户
 */
int DOAAccountManager::addAccount(const QString &accountData)
{
    qWarning() << QThread::currentThread();
    //创建当个帐户dbus对象
    DOAAccountsadapter *accountadapter = new DOAAccountsadapter(this);
    accountadapter->setDoaProvider(new DOAQQProvider);

    //解析dbus传入的参数
    if (!QJsonUtils::jsonString2DoaProvider(accountData, accountadapter->getDoaProvider())) {
        qCritical() << "login data error";
        return DOAProvider::DatatError;
    }

    //验证请求报文帐户ID是否为空
    if (accountadapter->getDoaProvider()->getAccountID().isEmpty()) {
        qCritical() << "request data error";
        accountadapter->getDoaProvider()->deleteLater();
        accountadapter->setDoaProvider(nullptr);
        return DOAProvider::DatatError;
    }

    //验证重复登录
    QMap<QString, DOAAccountsadapter *>::iterator itProviderMap;
    //从MAP中取出数据
    for (itProviderMap = m_doaProviderMap.begin(); itProviderMap != m_doaProviderMap.end(); ++itProviderMap) {
        //帐户名称和服务器地址一样判断为重复登录
        if (itProviderMap.value()->getDoaProvider()->getAccountName() == accountadapter->getDoaProvider()->getAccountName() && itProviderMap.value()->getDoaProvider()->getUrl() == accountadapter->getDoaProvider()->getUrl()) {
            qCritical() << "Repeat login";
            accountadapter->getDoaProvider()->deleteLater();
            accountadapter->setDoaProvider(nullptr);
            return DOAProvider::RepeatLogin;
        }
    }

    m_doaProviderLoginingMap.insert(accountadapter->getDoaProvider()->getAccountID(), accountadapter->getDoaProvider());

    //使用传输密钥密码处理
    QByteArray decPassword;
    QString dbuspassword = accountadapter->getDoaProvider()->getAccountPassword();

    //登录处理 使用明文登录验证
    DOAProvider::LoginState loginstate = accountadapter->getDoaProvider()->login();

    if (loginstate != DOAProvider::SUCCESS) {
        qCritical() << "login fiaile:" << loginStatemetaEnum.valueToKey(loginstate);
        QMutexLocker m_lock(&m_mutex);
        QMap<QString, DOAProvider *>::iterator it;
        //从登录队列中,取出数据删除
        for (it = m_doaProviderLoginingMap.begin(); it != m_doaProviderLoginingMap.end(); ++it) {
            if (it.key() == accountadapter->getDoaProvider()->getAccountID()) {
                accountadapter->getDoaProvider()->deleteLater();
                accountadapter->setDoaProvider(nullptr);
                m_doaProviderLoginingMap.erase(it);
                break;
            }
        }
        return loginstate;
    }

    //从登录队列中删除当前登录信息
    QMutexLocker m_lock(&m_mutex);
    QMap<QString, DOAProvider *>::iterator it;
    //从登录队列中,取出数据删除
    for (it = m_doaProviderLoginingMap.begin(); it != m_doaProviderLoginingMap.end(); ++it) {
        if (it.key() == accountadapter->getDoaProvider()->getAccountID()) {
            m_doaProviderLoginingMap.erase(it);
            break;
        }
    }

    //重置AccountID
    accountadapter->getDoaProvider()->setAccountID("");
    accountadapter->getDoaProvider()->setAccountStat(loginstate);

    //使用传输密钥解密密码
    QString accountPassword;

    bool result = AESEncryption::ecb_encrypt(dbuspassword, accountPassword, TKEY, false);

    if (!result) {
        qCritical() << "password desc fail";
        accountadapter->getDoaProvider()->deleteLater();
        accountadapter->setDoaProvider(nullptr);
        return DOAProvider::PassWordError;
    }

    //使用数据库密钥加密
    QString encPassWordString;
    result = AESEncryption::ecb_encrypt(accountPassword, encPassWordString, SKEY, true);

    if (!result) {
        qCritical() << "password enc fail";
        accountadapter->getDoaProvider()->deleteLater();
        accountadapter->setDoaProvider(nullptr);
        return DOAProvider::PassWordError;
    }

    //重置密码为输入密码
    accountadapter->getDoaProvider()->setAccountPassword(dbuspassword);

    //生成账户唯一ID号
    if (accountadapter->getDoaProvider()->getAccountID() == "") {
        QDateTime time = QDateTime::currentDateTime(); //获取当前时间
        uint timeT = time.toTime_t(); //将当前时间转为时间戳
        accountadapter->getDoaProvider()->setAccountID(QString("accounts_") + QString::number(timeT));
        m_doaProviderMap.insert(QString("accounts_") + QString::number(timeT), accountadapter);
        //生成dbus路径 服务名+/accounts/accounts__时间戳
        accountadapter->getDoaProvider()->setPath(kAccountsServicePath + QString("/accounts/") + QString("accounts_") + QString::number(timeT));
    }

    //生成带时区的创建时间
    QDateTime current_date_time = QDateTime::currentDateTime();
    QTime _offsetTime = QTime(0, 0).addSecs(current_date_time.timeZone().offsetFromUtc(current_date_time));
    QString current_date = QString("%1+%2").arg(current_date_time.toString("yyyy-MM-ddThh:mm:ss")).arg(_offsetTime.toString("hh:mm"));
    accountadapter->getDoaProvider()->setCreateTime(current_date);

    //数据库增加操作
    AccountInfo accountInfo;
    accountInfo.m_accountID = accountadapter->getDoaProvider()->getAccountID();
    accountInfo.m_accountURL = accountadapter->getDoaProvider()->getUrl();
    accountInfo.m_accountType = protocolTypemetaEnum.valueToKey(accountadapter->getDoaProvider()->getProtocol());
    accountInfo.m_accountDbusPath = accountadapter->getDoaProvider()->getPath();
    accountInfo.m_accountUserName = accountadapter->getDoaProvider()->getDisplayName();
    accountInfo.m_accountName = accountadapter->getDoaProvider()->getAccountName();
    accountInfo.m_isSSL = accountadapter->getDoaProvider()->getSSL();
    accountInfo.m_accountPassword = encPassWordString;
    accountInfo.m_calendarDisabled = accountadapter->getDoaProvider()->getCalendarDisabled();
    accountInfo.m_accountProviderType = accountTypemetaEnum.valueToKey(accountadapter->getDoaProvider()->getProviderName());
    accountInfo.m_accountURI = accountadapter->getDoaProvider()->getUri();
    accountInfo.m_accountCreateTime = accountadapter->getDoaProvider()->getCreateTime();

    //发送给数据库操作增加帐户
    bool ret = m_db->addAccount(accountInfo);
    if (!ret) {
        qWarning() << "db error";
        return DOAProvider::DBError;
    }

    creatAccountDbus(accountadapter);

    //设置同步状态 使用现有值重新设置只为了触发定时检测
    QDBusInterface *iface = new QDBusInterface(kAccountsService, accountadapter->getDoaProvider()->getPath(), kAccountsServiceAccountIface,
                                               QDBusConnection::sessionBus());
    iface->setProperty("CalendarDisabled", accountadapter->getDoaProvider()->getCalendarDisabled());
    iface->deleteLater();

    //生成JSON字符串
    QString strJson = QJsonUtils::doaProvider2String(accountadapter->getDoaProvider(), QJsonUtils::ADD);

    //密码验证成功发送帐户信息信号
    emit this->InterfaceAccountInfo(strJson);

    return 0;
}

/**
 * @brief DOAAccountManager::removeAccount
 * @param doaAccountAdapter
 * 删除帐户的信号槽
 */
void DOAAccountManager::onRemoveAccount(DOAAccountsadapter *doaAccountAdapter)
{
    //删除当前帐户所有信号连接
    doaAccountAdapter->disconnect();
    //当前帐户槽连接
    disconnect(this, &DOAAccountManager::sign_netWorkChange, doaAccountAdapter, &DOAAccountsadapter::onNetWorkChange);

    QDBusConnection sessionBus = QDBusConnection::sessionBus();
    if (sessionBus.registerService(kAccountsService)) {
        //删除当前帐户dbus路径
        sessionBus.unregisterObject(doaAccountAdapter->getDoaProvider()->getPath(), QDBusConnection::UnregisterNode);
    }

    //删除数据库数据
    m_db->deleteAccount(doaAccountAdapter->getDoaProvider()->getAccountID());

    //从缓存中删除数据
    QMap<QString, DOAAccountsadapter *>::iterator it;
    for (it = m_doaProviderMap.begin(); it != m_doaProviderMap.end(); ++it) {
        if (it.key() == doaAccountAdapter->getDoaProvider()->getAccountID()) {
            m_doaProviderMap.erase(it);
            break;
        }
    }
    //发送删除信号通知给前端
    QString strJson = QJsonUtils::doaProvider2String(doaAccountAdapter->getDoaProvider(), QJsonUtils::DEL);

    emit this->InterfaceAccountInfo(strJson);

    //删除帐户
    doaAccountAdapter->getDoaProvider()->deleteLater();
    doaAccountAdapter->setDoaProvider(nullptr);
    doaAccountAdapter->deleteLater();

}

/**
 * @brief DOAAccountManager::onChangeProperty
 * @param propertyName
 * @param doaProvider
 */
void DOAAccountManager::onChangeProperty(const QString &propertyName, DOAProvider *doaProvider)
{
    //更新数据库
    QVariant value;
    if (propertyName == "CalendarDisable") {
        //修改数据库CalendarDisable值
        value = QVariant::fromValue(doaProvider->getCalendarDisabled());
        m_db->updateProperty(doaProvider->getAccountID(), propertyName, value);
    } else if (propertyName == "UserName") {
        //修改数据库用户名
        value = QVariant::fromValue(doaProvider->getDisplayName());
        m_db->updateProperty(doaProvider->getAccountID(), propertyName, value);
    } else if (propertyName == "Status") {
        //修改数据库状态
        int state = doaProvider->getAccountStat();
        value = QVariant::fromValue(state);
        m_db->updateProperty(doaProvider->getAccountID(), propertyName, value);
    } else if (propertyName == "Password") {
        //修改数据库密码
        value = QVariant::fromValue(doaProvider->getAccountPassword());
        m_db->updateProperty(doaProvider->getAccountID(), propertyName, value);
    }
}

/**
 * @brief DOAAccountManager::onAddResult
 * @param accountID
 * @param result
 * 数据库增加成功
 */
void DOAAccountManager::onAddResult(const QString &accountID, bool result)
{
    DOAAccountsadapter *accountadapter = m_doaProviderMap[accountID];
    if (result) {
        creatAccountDbus(accountadapter);

        //组增加帐户Map
        QMap<QString, QVariant> addAccountMap;
        addAccountMap.insert("accountname", accountadapter->getDoaProvider()->getAccountName());
        addAccountMap.insert("stat", 0);
        addAccountMap.insert("accountid", accountadapter->getDoaProvider()->getAccountID());
        addAccountMap.insert("accountdbuspath", accountadapter->getDoaProvider()->getPath());
        addAccountMap.insert("accounttype", accountadapter->getDoaProvider()->getProtocol());
        addAccountMap.insert("accountflag", accountadapter->getDoaProvider()->getProviderName());
        addAccountMap.insert("username", accountadapter->getDoaProvider()->getDisplayName());
        addAccountMap.insert("accountstat", accountadapter->getDoaProvider()->getAccountStat());
        addAccountMap.insert("calendardisable", accountadapter->getDoaProvider()->getCalendarDisabled());
        addAccountMap.insert("accounturi", accountadapter->getDoaProvider()->getUri());
        addAccountMap.insert("iterfaceoper", "ADD");

        QString strJson = QJsonUtils::getJsonString(addAccountMap);

        //密码验证成功发送帐户信息信号
        emit this->InterfaceAccountInfo(strJson);
    } else {
        //失败发送帐户信息信号
        QMap<QString, QVariant> addAccountMap;
        addAccountMap.insert("accountname", accountadapter->getDoaProvider()->getAccountName());
        addAccountMap.insert("stat", "F001");
        addAccountMap.insert("msg", "数据库错误");
        addAccountMap.insert("iterfaceoper", "ADD");

        QString strJson = QJsonUtils::getJsonString(addAccountMap);

        emit this->InterfaceAccountInfo(strJson);
    }
}
