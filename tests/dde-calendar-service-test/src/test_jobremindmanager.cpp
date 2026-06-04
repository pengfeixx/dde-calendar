// SPDX-FileCopyrightText: 2019 - 2026 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "test_jobremindmanager.h"
#include "../third-party_stub/stub.h"
#include "service_stub.h"

#include <QDBusAbstractInterface>
#include <QDebug>

void stub_callWithArgumentList(QDBus::CallMode mode,
                               const QString &method,
                               const QList<QVariant> &args)
{
    Q_UNUSED(mode);
    Q_UNUSED(method);
    Q_UNUSED(args);
}

test_jobremindmanager::test_jobremindmanager()
{
    Stub stub;
    stub.set(ADDR(QDBusAbstractInterface, callWithArgumentList), stub_callWithArgumentList);
    jobRemindManager = new DAlarmManager();
}

test_jobremindmanager::~test_jobremindmanager()
{
    delete jobRemindManager;
}

// Test constructor/destructor
TEST_F(test_jobremindmanager, Constructor)
{
    ASSERT_NE(jobRemindManager, nullptr);
}

// void DAlarmManager::updateRemind(const DRemindData::List &remindList)
TEST_F(test_jobremindmanager, updateRemind)
{
    Stub stub;
    qDBusAbstractInterface_callWithArgumentList_stub(stub);
    DRemindData::List remindList;
    jobRemindManager->updateRemind(remindList);
}

// void DAlarmManager::notifyJobsChanged(const DRemindData::List &remindList)
TEST_F(test_jobremindmanager, notifyJobsChanged)
{
    Stub stub;
    qDBusAbstractInterface_callWithArgumentList_stub(stub);
    DRemindData::List remindList;
    jobRemindManager->notifyJobsChanged(remindList);
}

// void DAlarmManager::notifyMsgHanding(const DRemindData::Ptr &remindData, const int operationNum)
TEST_F(test_jobremindmanager, notifyMsgHanding)
{
    Stub stub;
    qDBusAbstractInterface_callWithArgumentList_stub(stub);
    DRemindData::Ptr remindData = DRemindData::Ptr::create();
    for (int i = 0; i < 25; i++) {
        jobRemindManager->notifyMsgHanding(remindData, i);
    }
}

// void DAlarmManager::remindLater(const DRemindData::Ptr &remindData, const int operationNum)
TEST_F(test_jobremindmanager, remindLater)
{
    Stub stub;
    qDBusAbstractInterface_callWithArgumentList_stub(stub);
    DRemindData::Ptr remindData = DRemindData::Ptr::create();
    jobRemindManager->remindLater(remindData, 1);
}

// DBusNotify *DAlarmManager::getdbusnotify()
TEST_F(test_jobremindmanager, getdbusnotify)
{
    jobRemindManager->getdbusnotify();
}
