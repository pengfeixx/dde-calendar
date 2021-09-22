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
#include "accountdbmanager.h"

#include <QThread>

AccountDBManager::AccountDBManager(QObject *parent)
    : QObject(parent)
    , db_(nullptr)
    , db_thread_(nullptr)
{
    //初始化数据库
    initDbManager();
}

AccountDBManager::~AccountDBManager()
{
    delete db_;
    db_ = nullptr;
}

void AccountDBManager::initDbManager()
{
    //db_thread_ = new QThread(this);
    db_ = new AccountDB();
    //db_thread_->start();
    //db_->moveToThread(db_thread_);

    connect(this, &AccountDBManager::sign_selectAccountList, db_, &AccountDB::queryAccountList);
    connect(this, &AccountDBManager::sign_addAccount, db_, &AccountDB::addAccount);
    connect(this, SIGNAL(sign_updateProperty(const QString &, const QString &, QVariant)), db_, SLOT(updateProperty(const QString &, const QString &, QVariant)));
    connect(this, &AccountDBManager::sign_deleteAccount, db_, &AccountDB::deleteAccount);

    connect(db_, &AccountDB::selectAccountResult, this, &AccountDBManager::sign_selectAccountResult);
    connect(db_, &AccountDB::addAccountResult, this, &AccountDBManager::sign_addAccountResult);

    connect(db_thread_, &QThread::destroyed, db_, &QObject::deleteLater);

    //初始化创建数据库AccountDb::initDb
    emit db_->initDbAsync();
}
