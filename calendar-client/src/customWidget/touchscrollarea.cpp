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
#include "touchscrollarea.h"

#include <QMouseEvent>
#include <QScrollBar>

touchScrollArea::touchScrollArea(QWidget *parent)
    : QScrollArea(parent)
{
}

void touchScrollArea::mousePressEvent(QMouseEvent *event)
{
    if (event->source() == Qt::MouseEventSynthesizedByQt) {
        m_begintPoint = event->pos();
        m_isTouchMove = true;
    }
    QScrollArea::mousePressEvent(event);
}

void touchScrollArea::mouseMoveEvent(QMouseEvent *event)
{
    //如果为触摸滑动状态则移动
    if (m_isTouchMove && event->source() == Qt::MouseEventSynthesizedByQt) {
        QPoint currentPos = event->pos();
        int offset_y = currentPos.y() - m_begintPoint.y();
        int value = this->verticalScrollBar()->value() - offset_y;
        m_begintPoint = currentPos;
        //控制设置值在正常范围内
        if (value < verticalScrollBar()->minimum()) {
            value = verticalScrollBar()->minimum();
        } else if (verticalScrollBar()->maximum() < value) {
            value = verticalScrollBar()->maximum();
        }
        //更新ScrollBar的当前值
        this->verticalScrollBar()->setValue(value);
    }
    QScrollArea::mouseMoveEvent(event);
}

void touchScrollArea::mouseReleaseEvent(QMouseEvent *event)
{
    m_isTouchMove = false;
    QScrollArea::mouseReleaseEvent(event);
}
