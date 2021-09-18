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
#ifndef DOAACCOUNTMANAGER_H
#define DOAACCOUNTMANAGER_H

#include "doaprovider.h"
#include "controller/accountdbmanager.h"
#include "dbus/doa_notify_proxy.h"
#include "dbus/doaaccounts_adapter.h"
#include "dbus/doaaccountscalendar_adapter.h"
#include "db/account_result.h"
#include "dbus/doaaccountspasswordadapter.h"

#include <QObject>

#define DOAMANAGERINTFACE "com.dde.onlineaccount.manager"

class DOAAccountManager : public QObject
    , protected QDBusContext
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", DOAMANAGERINTFACE)
public:
    explicit DOAAccountManager(QObject *parent = nullptr);

    //从数据中取出帐户数据并创建dbus服务
    void creatAllAccountDbusFromDB();

public slots:
    void onRemoveAccount(DOAAccountsadapter *doaAccountAdapter);
    //查询帐户数据库结果
    void onSelectAccountResult(const AccountResultList &result);
    //增加帐户数据库操作结果
    void onAddResult(const QString &accountID, bool result);
    //帐户属性改变
    void onChangeProperty(const QString &propertyName, DOAProvider *doaProvider);

signals: //内部处理信号
    //增加帐户变化信号

    void sign_accountState(const QString &stateType, const QString &accountState);
    //增加帐户信号->>数据库管理类增加帐户信号->>数据库对象槽
    bool sign_addAccount(const AccountInfo &accountInfo);
    //检查帐户状态信号->>各个帐户检查状态槽
    void sign_checkAccountStat();

    //修改帐户属性信号->>数据库管理类修改帐户属性信号->>数据库对象槽
    void sign_updateProperty(const QString &accountID, const QString &property, QVariant value);
    //删除帐户属性信号->>数据库管理类删除帐户属性信号->>数据库对象槽
    void sign_deleteAccount(const QString &accountID);

public Q_SLOTS: // METHODS
    //dbus接口 增加帐户
    Q_SCRIPTABLE int addAccount(const QString &accountData);
    //dbus接口 获取所有帐户
    Q_SCRIPTABLE QString getAllAccount();
    //dbus接口 临时接口
    Q_SCRIPTABLE QString encPassword(const QString &password);
    //dbus接口 取消当前登录
    Q_SCRIPTABLE void loginCancle(const QString &uuid);
Q_SIGNALS: // SIGNALS dbus公共信号
    //属性变化通知信号
    Q_SCRIPTABLE void InterfaceAccountInfo(const QString &accountInfo);

    Q_SCRIPTABLE void InterfaceAccountStatus(const QString &stateType, const QString &accountState);

private:

    /**
     * @brief passwordPro
     * @param dbpassword
     * @return
     * 登录密码解密验证格式
     */
    QString passwordPro(const QString &dbpassword);

    //初始化帐户属性变化信号槽
    void initAccountPropertiesChange(DOAAccountsadapter *accountproxy);

    /**
     * @brief creatAccountDbus
     * @param accountAdapter
     * 创建各个帐户dbus服务
     */
    void creatAccountDbus(DOAAccountsadapter *accountAdapter);

    //通知类
    DoaNotifyProxy *m_doaNotifyProxy;
    //数据库对象
    AccountDBManager *m_accountDBManager;
    //各个帐户集合
    QMap<QString, DOAAccountsadapter *> m_doaProviderMap;
    //正在登录集合
    QMap<QString, DOAProvider *> m_doaProviderLoginingMap;

    QList<DOAProvider *> m_doaProviderList;

    //枚举类型key-value 转换
    QMetaEnum protocolTypemetaEnum = QMetaEnum::fromType<DOAProvider::ProtocolType>();
    QMetaEnum loginStatemetaEnum = QMetaEnum::fromType<DOAProvider::LoginState>();
    QMetaEnum accountTypemetaEnum = QMetaEnum::fromType<DOAProvider::AccountType>();
    QMetaEnum loginTypemetaEnum = QMetaEnum::fromType<DOAProvider::LoginType>();

    QMutex m_mutex;
};

#endif // DOAACCOUNTMANAGER_H
