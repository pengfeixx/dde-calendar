/*
   * Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
   *
   * Author:     chenhaifeng <chenhaifeng@uniontech.com>
   *
   * Maintainer: chenhaifeng <chenhaifeng@uniontech.com>
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
#include "ut_animationstackedwidget.h"

void ut_animationstackedwidget::SetUp()
{
    mAnimationStackedWidget = new AnimationStackedWidget();
    widget1 = new QWidget(mAnimationStackedWidget);
    widget2 = new QWidget(mAnimationStackedWidget);
    mAnimationStackedWidget->addWidget(widget1);
    mAnimationStackedWidget->addWidget(widget2);
}

void ut_animationstackedwidget::TearDown()
{
    delete mAnimationStackedWidget;
    mAnimationStackedWidget = nullptr;
}

//void AnimationStackedWidget::setDuration(int duration)
TEST_F(ut_animationstackedwidget, setDuration)
{
    mAnimationStackedWidget->setDuration(400);
    EXPECT_EQ(400, mAnimationStackedWidget->m_Duration);
}

//void AnimationStackedWidget::animationFinished()
TEST_F(ut_animationstackedwidget, animationfinished)
{
    mAnimationStackedWidget->animationFinished();
    EXPECT_FALSE(mAnimationStackedWidget->m_IsAnimation);
}

//void AnimationStackedWidget::setCurrent(int index)
TEST_F(ut_animationstackedwidget, setCurrent)
{
    mAnimationStackedWidget->setCurrent(4);
    EXPECT_TRUE(mAnimationStackedWidget->m_IsAnimation);
}

//void AnimationStackedWidget::setPre()
TEST_F(ut_animationstackedwidget, setPre)
{
    int currentIndex = mAnimationStackedWidget->currentIndex();
    mAnimationStackedWidget->setPre();
    EXPECT_TRUE(mAnimationStackedWidget->m_IsAnimation);
}

//void AnimationStackedWidget::setNext()
TEST_F(ut_animationstackedwidget, setNext)
{
    int currentIndex = mAnimationStackedWidget->currentIndex();
    mAnimationStackedWidget->setNext();
    EXPECT_TRUE(mAnimationStackedWidget->m_IsAnimation);
}

//void AnimationStackedWidget::setCurrentWidget(int &index, int beginWidth)
TEST_F(ut_animationstackedwidget, setCurrentWidget)
{
    int index = 2;
    mAnimationStackedWidget->setCurrentWidget(index, 8);
    EXPECT_TRUE(mAnimationStackedWidget->m_IsAnimation);
}

//int AnimationStackedWidget::getBeginValue()
TEST_F(ut_animationstackedwidget, getBeginValue_001)
{
    QRect widgetRect = mAnimationStackedWidget->rect();
    EXPECT_EQ(widgetRect.width(), mAnimationStackedWidget->getBeginValue());
}

TEST_F(ut_animationstackedwidget, getBeginValue_002)
{
    QRect widgetRect = mAnimationStackedWidget->rect();
    mAnimationStackedWidget->m_animationOri = AnimationStackedWidget::TB;
    EXPECT_EQ(widgetRect.height(), mAnimationStackedWidget->getBeginValue());
}

//AnimationStackedWidget::MoveOrientation AnimationStackedWidget::getMoveOrientation(const int currIndex, const int nextIndex)
TEST_F(ut_animationstackedwidget, getMoveOrientation_001)
{
    EXPECT_EQ(AnimationStackedWidget::RightToLeft, mAnimationStackedWidget->getMoveOrientation(2, 4));
}

TEST_F(ut_animationstackedwidget, getMoveOrientation_002)
{
    EXPECT_EQ(AnimationStackedWidget::LeftToRight, mAnimationStackedWidget->getMoveOrientation(3, 2));
}

TEST_F(ut_animationstackedwidget, getMoveOrientation_003)
{
    mAnimationStackedWidget->m_animationOri = AnimationStackedWidget::TB;
    EXPECT_EQ(AnimationStackedWidget::TopToBottom, mAnimationStackedWidget->getMoveOrientation(3, 2));
}

TEST_F(ut_animationstackedwidget, getMoveOrientation_004)
{
    mAnimationStackedWidget->m_animationOri = AnimationStackedWidget::TB;
    EXPECT_EQ(AnimationStackedWidget::BottomToTop, mAnimationStackedWidget->getMoveOrientation(2, 3));
}

TEST_F(ut_animationstackedwidget, getMoveOrientation_005)
{
    mAnimationStackedWidget->m_animationOri = AnimationStackedWidget::TB;
    EXPECT_EQ(AnimationStackedWidget::LeftToRight, mAnimationStackedWidget->getMoveOrientation(2, 2));
}

//double AnimationStackedWidget::offset() const
TEST_F(ut_animationstackedwidget, offset)
{
    mAnimationStackedWidget->setOffset(10);
    EXPECT_GT(mAnimationStackedWidget->offset(), 10 - 0.00001);
    EXPECT_LT(mAnimationStackedWidget->offset(), 10 + 0.00001);
}

//void AnimationStackedWidget::setOffset(double offset)
TEST_F(ut_animationstackedwidget, setOffset)
{
    mAnimationStackedWidget->setOffset(2.0);
    EXPECT_GT(mAnimationStackedWidget->offset(), 2 - 0.00001);
    EXPECT_LT(mAnimationStackedWidget->offset(), 2 + 0.00001);
}

TEST_F(ut_animationstackedwidget, animationtest)
{
    mAnimationStackedWidget->setCurrentIndex(0);
    mAnimationStackedWidget->setDuration(250);
    mAnimationStackedWidget->setCurrent(1);
    mAnimationStackedWidget->setFixedSize(500, 800);
    QPixmap pixmap(mAnimationStackedWidget->size());
    for (int i = 0; i < 10; ++i) {
        mAnimationStackedWidget->setOffset(i);
        pixmap = mAnimationStackedWidget->grab();
    }
    EXPECT_EQ(pixmap.size(), mAnimationStackedWidget->size());
    mAnimationStackedWidget->setCurrentIndex(1);
    mAnimationStackedWidget->setCurrent(0);
    for (int i = 0; i < 10; ++i) {
        mAnimationStackedWidget->setOffset(i);
        pixmap = mAnimationStackedWidget->grab();
    }
    EXPECT_EQ(pixmap.size(), mAnimationStackedWidget->size());
}
