// SPDX-FileCopyrightText: 2019 - 2026 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "cscheduledbusstub.h"
#include "stub.h"
#include <QtGlobal>

// CScheduleDBus 已被移除，提供空实现以满足链接
void cscheduleDbusStub(Stub &stub)
{
    Q_UNUSED(stub)
}
