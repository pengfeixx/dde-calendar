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
#ifndef DACCOUNTDATABASE_H
#define DACCOUNTDATABASE_H

#include "ddatabase.h"
#include "daccount.h"
#include "dschedule.h"
#include "dscheduletype.h"

#include <QSharedPointer>

class DAccountDataBase : public DDataBase
{
    Q_OBJECT
public:
    typedef QSharedPointer<DAccountDataBase> Ptr;

    explicit DAccountDataBase(const DAccount::Ptr &account, QObject *parent = nullptr);
    //初始化数据库数据，会创建数据库文件和相关数据表
    void initDBData() override;
    ///////////////日程信息
    //创建日程
    QString createSchedule(const DSchedule::Ptr &schedule);
    bool updateSchedule(const DSchedule::Ptr &schedule);
    //根据日程id获取日程信息
    DSchedule::Ptr getScheduleByScheduleID(const QString &scheduleID);

    //根据日程类型ID获取日程id列表
    QStringList getScheduleIDListByTypeID(const QString &typeID);
    bool deleteScheduleByScheduleID(const QString &scheduleID, const int isDeleted = 0);
    bool deleteSchedulesByScheduleTypeID(const QString &typeID, const int isDeleted = 0);
    //根据关键字查询一定范围内的日程
    DSchedule::List querySchedulesByKey(const QString &key);
    //根据重复规则查询一定范围内的日程
    DSchedule::List querySchedulesByRRule(const QString &key, const ushort &rruleType);

    ///////////////类型信息
    /**
     * @brief createScheduleType        创建日程类型
     * @param typeInfo
     * @return
     */
    QString createScheduleType(const DScheduleType::Ptr &scheduleType);
    virtual DScheduleType::Ptr getScheduleTypeByID(const QString &typeID, const int isDeleted = 0);
    virtual DScheduleType::List getScheduleTypeList(const int isDeleted = 0);
    bool scheduleTypeByUsed(const QString &typeID, const int isDeleted = 0);
    bool deleteScheduleTypeByID(const QString &typeID, const int isDeleted = 0);
    bool updateScheduleType(const DScheduleType::Ptr &scheduleType);
    ///////////////帐户信息
    DAccount::Ptr getAccountInfo();
    void setAccountInfo(const DAccount::Ptr &account);

    ///////////////////类型颜色
    bool addTypeColor(const int typeColorNo, const QString &strColorHex, const int privilege);
    void deleteTypeColor();

protected:
    virtual void initScheduleType();
    //初始化系统类型
    virtual DScheduleType::List initSysType();

private:
    void createDB() override;
    //初始化日程数据库
    void initScheduleDB();
    void initTypeColor();
    void initAccountDB();

private:
    DAccount::Ptr m_account;
};

#endif // DACCOUNTDATABASE_H
