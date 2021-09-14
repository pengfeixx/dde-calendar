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
#ifndef DOAACCOUNTMODEL_H
#define DOAACCOUNTMODEL_H

#include "doaaccount.h"
#include "dbus/doaaccountmanagedbus.h"

#include <QObject>
#include <QMap>

/**
 * @brief The accountModel class   网络帐户数据管理
 */
class DOAAccountModel : public QObject
{
    Q_OBJECT
public:
    //帐户界面显示状态
    enum AccountWidgetState {
        Account_Init, //初始状态(帐户列表为空)
        Account_Create, //添加帐户状态(帐户列表有信息)
        Account_Details //显示帐户信息状态
    };

public:
    explicit DOAAccountModel(QObject *parent = nullptr);

    /**
     * @brief state 获取帐户界面的状态
     * @return      返回帐户界面的状态
     */
    AccountWidgetState state() const;

    /**
     * @brief setState  设置帐户界面的状态
     * @param state     帐户界面的状态
     */
    void setState(const AccountWidgetState &state);

    /**
     * @brief getAccount    获取帐户信息
     * @param accountID     帐户的ID
     * @return              返回帐户信息
     */
    DOAAccount *getAccount(QString accountID);

    /**
     * @brief getAccountMap    获取所有帐户信息
     * @return                  返回所有帐户信息
     */
    QMap<QString, DOAAccount *> getAccountMap();

    /**
     * @brief setCurrentAccountByID     根据帐户id设置当前帐户显示信息
     * @param accountID                 帐户id
     * @return                          返回是否设置成功
     */
    bool setCurrentAccountByID(QString accountID);

    /**
     * @brief getCurrentAccount     获取当前帐户信息
     * @return
     */
    DOAAccount *getCurrentAccount();

signals:
    /**
     * @brief signalChangeState       当前窗口显示状态改变
     * @param state
     */
    void signalChangeState();

    /**
     * @brief accountStateChange        帐户状态改变
     * @param accountID                 帐户id
     * @param isError                   帐户是否正常
     */
    void signalAccountStateChange(const QString accountID, const bool isError);

    /**
     * @brief signalSelectAccountChange       修改选中日程
     */
    void signalSelectAccountChange();
public slots:
    /**
     * @brief addAccount    添加帐户
     * @param info
     */
    qint32 slotAddAccount(const AddAccountInfo &info);

    /**
     * brief slotCancleLogin    取消登录
     * @param uuid
     */
    void slotCancleLogin(const QString &uuid);

private:
    QMap<QString, DOAAccount *> m_accounts = {}; //帐户列表
    AccountWidgetState m_state = Account_Init; //当前状态
    DOAAccount *m_currentAccount = nullptr; //当前显示帐户
    DOAAccountManageDBus *m_accountDBus = nullptr; //帐户dbus
};

#endif // DOAACCOUNTMODEL_H
