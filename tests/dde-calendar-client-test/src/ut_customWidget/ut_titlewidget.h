#ifndef TEST_TITLEWIDGET_H
#define TEST_TITLEWIDGET_H

#include "customWidget/ctitlewidget.h"
#include "gtest/gtest.h"

#include <QObject>

class ut_titleWidget : public testing::Test
{
public:
    ut_titleWidget();
    void SetUp() override;
    void TearDown() override;
public:
    CTitleWidget *m_titleWidget = nullptr;
};

#endif // TEST_TITLEWIDGET_H
