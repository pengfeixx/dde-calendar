// SPDX-FileCopyrightText: 2019 - 2026 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef TEST_WEEKWINDOW_H
#define TEST_WEEKWINDOW_H

#include "gtest/gtest.h"
#include "widget/weekWidget/weekwindow.h"

#include <QObject>

class test_weekWindow : public QObject
    , public ::testing::Test
{
public:
    explicit test_weekWindow();
    void SetUp() override;
    void TearDown() override;

public:
    CWeekWindow *m_weekWindow {nullptr};
};

#endif // TEST_WEEKWINDOW_H
