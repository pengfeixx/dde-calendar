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
#include "accountdb.h"
#include "utils.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QUuid>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>
#include <QDateTime>

const char kAccountinfoDropTable[] = "DROP TABLE IF EXISTS accountinfo";

//--------------- AccountInfo sql语句 -------------------
const char kAccountInfoTableSchema[] =
    "CREATE TABLE IF NOT EXISTS accountinfo "
    "(AccountID TEXT PRIMARY KEY,"
    "UserName TEXT,"
    "AccountName TEXT,"
    "AccountURL TEXT,"
    "AccountPassword TEXT,"
    "AccountPort INTEGER,"
    "AccountType TEXT,"
    "IsSSL INTEGER,"
    "State INTEGER,"
    "CreateTime TEXT,"
    "UpdateTime TEXT,"
    "AccountDbusPath TEXT,"
    "ProviderName TEXT,"
    "AccountURI TEXT)";

/**
 * @brief kAccountsyncobjectTableSchema
 * 创建同步对象表
 */
const char kAccountsyncobjectTableSchema[] =
    "CREATE TABLE IF NOT EXISTS accountsyncobject "
    "(id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "AccountID TEXT,"
    "SyncObjectType INTEGER,"
    "IsEnable TEXT)";

const char kAccountInfoIndexSchema[] =
    "CREATE UNIQUE INDEX IF NOT EXISTS AccountInfo_idx "
    "ON accountinfo (AccountName, AccountURL)";

const char kAccountsyncobjectIndexSchema[] =
    "CREATE INDEX IF NOT EXISTS Accountsyncobject_idx "
    "ON accountsyncobject (AccountID)";

const char kAccountInfoInsertEntry[] =
    "INSERT INTO accountinfo "
    "(AccountID, UserName, AccountName, AccountURL, AccountPassword, AccountPort, AccountType"
    ", IsSSL, State, CreateTime,AccountDbusPath,ProviderName, AccountURI) "
    "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?,?)";

const char kAccountsyncobjectInsertEntry[] =
    "INSERT INTO accountsyncobject "
    "(AccountID, SyncObjectType, IsEnable) "
    "VALUES (?, ?, ?)";

const char kAccountInfoSelectContent[] =
    "select AccountID, UserName, AccountName, AccountURL, AccountPassword, AccountPort, AccountType"
    ", IsSSL, State, AccountDbusPath,ProviderName, AccountURI,CreateTime from accountinfo"
    " order by CreateTime";

const char kAccountsyncobjectSelectContent[] =
    "select SyncObjectType, IsEnable from accountsyncobject where AccountID = ':AccountID'";

struct AccountDbPrivate {
    QSqlDatabase db;
};

AccountDB::AccountDB(QObject *parent)
    : QObject(parent)
    , p_(new AccountDbPrivate())
{
    qRegisterMetaType<AccountInfo>("AccountInfo");
    qRegisterMetaType<AccountResultList>("AccountResultList");
    initConnections();
}

AccountDB::~AccountDB()
{
    if (p_ != nullptr) {
        if (p_->db.isOpen()) {
            p_->db.close();
        }
        delete p_;
        p_ = nullptr;
    }
}

/**
 * @brief SearchDb::initConnections
 * 绑定信号槽
 */

void AccountDB::initConnections()
{
    connect(this, &AccountDB::initDbAsync, this, &AccountDB::initDb);
}

/**
 * @brief AccountDB::initDb
 * 初始化数据库创建数据库文件
 */
void AccountDB::initDb()
{
    //获取本地配置文件目录
    QString dbdir = Utils::mkMutiDir(QStandardPaths::writableLocation(QStandardPaths::HomeLocation).append("/.local/share/deepin/dde-online-accounts"));
    qDebug() << dbdir;
    QDir dir(dbdir);
    if (!dir.exists()) {
        qCritical() << __FUNCTION__ << "db path not exist!" << dbdir;
    }
    QString databasePath = dbdir.append("/accounts.db");

    //创建数据库
    p_->db = QSqlDatabase::addDatabase("QSQLITE", QUuid::createUuid().toString(QUuid::WithoutBraces));
    p_->db.setDatabaseName(databasePath);
    if (!p_->db.open()) {
        qCritical() << "Failed to open search db:" << databasePath << p_->db.lastError().text()
                    << p_->db.lastError().nativeErrorCode() << p_->db.lastError().type()
                    << p_->db.lastError().databaseText() << p_->db.lastError().driverText()
                    << p_->db.lastError().isValid();
    }

    //创建表
    initAccountTable();
}

/**
 * @brief AccountDB::initAccountTable
 * 数据库初始化操作
 */
void AccountDB::initAccountTable()
{
    QSqlQuery query(p_->db);

    qWarning() << kAccountInfoTableSchema;
    qWarning() << kAccountsyncobjectTableSchema;
    qWarning() << kAccountInfoIndexSchema;
    qWarning() << kAccountsyncobjectIndexSchema;

    //创建相关表
    if (!query.exec(kAccountInfoTableSchema)) {
        qCritical() << "Failed to initialize AccountInfo table:" << query.lastError().text();
        return;
    }

    //创建同步对象
    if (!query.exec(kAccountsyncobjectTableSchema)) {
        qCritical() << "Failed to create Accountsyncobject table" << query.lastError().text();
        return;
    }

    //创建帐户索引
    if (!query.exec(kAccountInfoIndexSchema)) {
        qCritical() << "Failed to create kAccountInfoIndexSchema index for search table" << query.lastError().text();
        return;
    }

    //创建帐户同步索引
    if (!query.exec(kAccountsyncobjectIndexSchema)) {
        qCritical() << "Failed to create kAccountsyncobjectIndexSchema index for search table" << query.lastError().text();
        return;
    }
}

/**
 * @brief AccountDB::queryAccountList
 * 查询账户列表
 */
void AccountDB::queryAccountList()
{
    QSqlQuery query(p_->db);

    AccountResultList accountResult;
    bool calendarDisable = false;
    qWarning() << "=======>" << kAccountInfoSelectContent;

    if (query.exec(kAccountInfoSelectContent)) {
        while (query.next()) {
            qDebug() << "queryAccountList===> " << query.value(0).toString();
            QSqlQuery syncquery(p_->db);
            const QString sql =
                QString(kAccountsyncobjectSelectContent).replace(":AccountID", query.value(0).toString());
            if (syncquery.exec(sql)) {
                while (syncquery.next()) {
                    if (syncquery.value(0).toString() == "1") {
                        //日历是否禁用 数据库 0：可用 其他：禁用
                        calendarDisable = syncquery.value(1).toInt() == 0 ? false : true;
                    }
                }
            }
            accountResult.append(AccountInfo {
                query.value(0).toString(),
                query.value(1).toString(),
                query.value(2).toString(),
                query.value(3).toString(),
                query.value(4).toString(),
                query.value(5).toString(),
                query.value(6).toString(),
                query.value(7).toInt() == 0 ? false : true,
                query.value(8).toString(),
                query.value(9).toString(),
                query.value(10).toString(),
                calendarDisable,
                query.value(11).toString(),
                query.value(12).toString(),
            });
        }
    } else {
        qCritical() << "Failed to selectAccountList:" << query.lastError().text();
    }
    qDebug() << "result size:" << accountResult.size();
    emit this->selectAccountResult(accountResult);
}

/**
 * @brief AccountDB::deleteAccount
 * @param accountID 帐户ID
 * 删除帐户
 */
void AccountDB::deleteAccount(const QString &accountID)
{
    QString sql;
    sql = QString("delete from accountinfo where accountid = '%1'").arg(accountID);

    QSqlQuery query(p_->db);
    if (!query.exec(sql)) {
        qCritical() << "Failed to insert search entry:" << query.lastError().text();
    }
    //删除同步对象
    sql = QString("delete from accountsyncobject where accountid = '%1'").arg(accountID);
    if (!query.exec(sql)) {
        qCritical() << "Failed to insert search entry:" << query.lastError().text();
    }
}

/**
 * @brief AccountDB::updateProperty
 * @param accountID 账户ID
 * @param property 字段名
 * @param value 字段值
 */
void AccountDB::updateProperty(const QString &accountID, const QString &property, QVariant value)
{
    QString sql;
    if (property == "CalendarDisable") {
        sql = QString("update accountsyncobject set IsEnable = '%1' where accountid = '%2' and SyncObjectType = '1'").arg(value.toBool() ? "1" : "0").arg(accountID);
    } else if (property == "UserName") {
        sql = QString("update accountinfo set UserName = '%1' where accountid = '%2'").arg(value.toString()).arg(accountID);
    } else if (property == "Status") {
        sql = QString("update accountinfo set State = '%1' where accountid = '%2'").arg(value.toString()).arg(accountID);
    } else if (property == "Password") {
        sql = QString("update accountinfo set AccountPassword = '%1' where accountid = '%2'").arg(value.toString()).arg(accountID);
    }

    QSqlQuery query(p_->db);
    if (!query.exec(sql)) {
        qCritical() << "Failed to insert search entry:" << query.lastError().text();
    }
}

/**
 * @brief AccountDB::addAccount
 * @param accountInfo
 * @return
 */
bool AccountDB::addAccount(const AccountInfo &accountInfo)
{
    QSqlQuery query(p_->db);

    if (!p_->db.transaction()) {
        qWarning() << "Failed to start db transaction!";
        emit this->addAccountResult(accountInfo.m_accountID, false);
        return false;
    }

    bool ok = query.prepare(kAccountInfoInsertEntry);
    if (!ok) {
        qCritical() << "kAccountInfoInsertEntry error:" << query.lastError().text();
        emit this->addAccountResult(accountInfo.m_accountID, ok);
        return false;
    }
    query.bindValue(0, accountInfo.m_accountID);
    query.bindValue(1, accountInfo.m_accountUserName);
    query.bindValue(2, accountInfo.m_accountName);
    query.bindValue(3, accountInfo.m_accountURL);
    query.bindValue(4, accountInfo.m_accountPassword);
    query.bindValue(5, accountInfo.m_accountPort);
    query.bindValue(6, accountInfo.m_accountType);
    query.bindValue(7, accountInfo.m_isSSL == true ? 0 : 1);
    query.bindValue(8, "0");
    query.bindValue(9, accountInfo.m_accountCreateTime);
    query.bindValue(10, accountInfo.m_accountDbusPath);
    query.bindValue(11, accountInfo.m_accountProviderType);
    query.bindValue(12, accountInfo.m_accountURI);

    ok = query.exec();

    if (!ok) {
        p_->db.rollback();
        qCritical() << "Failed to insert search entry:" << query.lastError().text();
        emit this->addAccountResult(accountInfo.m_accountID, ok);
        return false;
    }

    QSqlQuery syncquery(p_->db);
    syncquery.prepare(kAccountsyncobjectInsertEntry);
    syncquery.bindValue(0, accountInfo.m_accountID);
    syncquery.bindValue(1, "1");
    syncquery.bindValue(2, accountInfo.m_calendarDisabled ? 1 : 0);

    ok = syncquery.exec();

    if (!ok) {
        p_->db.rollback();
        qCritical() << "Failed to insert search entry:" << query.lastError().text();
        emit this->addAccountResult(accountInfo.m_accountID, ok);
        return false;
    } else {
        p_->db.commit();
    }
    emit this->addAccountResult(accountInfo.m_accountID, ok);
    return true;
}
