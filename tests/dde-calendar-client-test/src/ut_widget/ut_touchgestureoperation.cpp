/*
* Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
*
* Author:     zhengxiaokang <zhengxiaokang@uniontech.com>
*
* Maintainer: zhengxiaokang <zhengxiaokang@uniontech.com>
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
#include "ut_touchgestureoperation.h"

ut_touchgestureoperation::ut_touchgestureoperation()
{
    mTouchGestureOperation = new touchGestureOperation();
}

ut_touchgestureoperation::~ut_touchgestureoperation()
{
    delete mTouchGestureOperation;
    mTouchGestureOperation = nullptr;
}

//void touchGestureOperation::setUpdate(bool b)
TEST_F(ut_touchgestureoperation, setUpdate)
{
    mTouchGestureOperation->setUpdate(true);
    ASSERT_TRUE(mTouchGestureOperation->m_update);
}

//bool touchGestureOperation::isUpdate() const
TEST_F(ut_touchgestureoperation, isUpdate)
{
    mTouchGestureOperation->setUpdate(false);
    bool res = mTouchGestureOperation->isUpdate();
    EXPECT_FALSE(res);
    mTouchGestureOperation->setUpdate(true);
    res = mTouchGestureOperation->isUpdate();
    EXPECT_TRUE(res);
}

//touchGestureOperation::TouchState touchGestureOperation::getTouchState() const
TEST_F(ut_touchgestureoperation, getTouchState)
{
    mTouchGestureOperation->m_touchState = touchGestureOperation::T_SINGLE_CLICK;
    mTouchGestureOperation->getTouchState();
    ASSERT_EQ(mTouchGestureOperation->m_touchState, touchGestureOperation::T_SINGLE_CLICK);
}

//touchGestureOperation::TouchMovingDirection touchGestureOperation::getMovingDir() const
TEST_F(ut_touchgestureoperation, getMovingDir)
{
    mTouchGestureOperation->m_movingDir = touchGestureOperation::T_LEFT;
    mTouchGestureOperation->getMovingDir();
    ASSERT_EQ(mTouchGestureOperation->m_movingDir, touchGestureOperation::T_LEFT);
}

//touchGestureOperation::TouchMovingDirection touchGestureOperation::getTouchMovingDir(QPointF &startPoint, QPointF &stopPoint, qreal &movingLine)
TEST_F(ut_touchgestureoperation, getTouchMovingDir)
{
    QPointF point1(10, 12);
    QPointF point2(30, 40);
    qreal num = 2;
    touchGestureOperation::TouchMovingDirection result = mTouchGestureOperation->getTouchMovingDir(point1, point2, num);
    ASSERT_EQ(result, touchGestureOperation::T_BOTTOM);
}

//void touchGestureOperation::calculateAzimuthAngle(QPointF &startPoint, QPointF &stopPoint)
TEST_F(ut_touchgestureoperation, calculateAzimuthAngle)
{
    QPointF point1(10, 12);
    QPointF point2(30, 40);
    mTouchGestureOperation->calculateAzimuthAngle(point1, point2);
    ASSERT_EQ(mTouchGestureOperation->m_movingDir, touchGestureOperation::T_BOTTOM);
}
