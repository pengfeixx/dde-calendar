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

ut_animationstackedwidget::ut_animationstackedwidget()
{

}

ut_animationstackedwidget::~ut_animationstackedwidget()
{

}

//void AnimationStackedWidget::setDuration(int duration)
TEST_F(ut_animationstackedwidget, setDuration)
{
    mAnimationStackedWidget->setDuration(400);
}

//void AnimationStackedWidget::animationFinished()
TEST_F(ut_animationstackedwidget, animationfinished)
{
    mAnimationStackedWidget->animationFinished();
}

//void AnimationStackedWidget::setCurrent(int index)
TEST_F(ut_animationstackedwidget, setCurrent)
{
    mAnimationStackedWidget->setCurrent(4);
}

//void AnimationStackedWidget::setPre()
TEST_F(ut_animationstackedwidget, setPre)
{
    mAnimationStackedWidget->setPre();
}

//void AnimationStackedWidget::setNext()
TEST_F(ut_animationstackedwidget, setNext)
{
    mAnimationStackedWidget->setNext();
}

//void AnimationStackedWidget::setCurrentWidget(int &index, int beginWidth)
TEST_F(ut_animationstackedwidget, setCurrentWidget)
{
    int index = 2;
    mAnimationStackedWidget->setCurrentWidget(index, 8);
}

//int AnimationStackedWidget::getBeginValue()
TEST_F(ut_animationstackedwidget, getBeginValue)
{
    mAnimationStackedWidget->getBeginValue();
}

//AnimationStackedWidget::MoveOrientation AnimationStackedWidget::getMoveOrientation(const int currIndex, const int nextIndex)
TEST_F(ut_animationstackedwidget, getMoveOrientation)
{
    mAnimationStackedWidget->getMoveOrientation(2, 4);
}

//double AnimationStackedWidget::offset() const
TEST_F(ut_animationstackedwidget, offset)
{
    mAnimationStackedWidget->offset();
}

//void AnimationStackedWidget::setOffset(double offset)
TEST_F(ut_animationstackedwidget, setOffset)
{
    mAnimationStackedWidget->setOffset(2.0);
}

TEST_F(ut_animationstackedwidget, animationtest)
{
    mAnimationStackedWidget->setCurrentIndex(0);
    mAnimationStackedWidget->setDuration(250);
    mAnimationStackedWidget->setCurrent(1);
    mAnimationStackedWidget->setFixedSize(500, 800);
    QPixmap pixmap(mAnimationStackedWidget->size());
    for (int i = 0; i <10; ++i) {
        mAnimationStackedWidget->setOffset(i);
        pixmap = mAnimationStackedWidget->grab();
    }

    mAnimationStackedWidget->setCurrentIndex(1);
    mAnimationStackedWidget->setCurrent(0);
    for (int i = 0; i <10; ++i) {
        mAnimationStackedWidget->setOffset(i);
        pixmap = mAnimationStackedWidget->grab();
    }
}
