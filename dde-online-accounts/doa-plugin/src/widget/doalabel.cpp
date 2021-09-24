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
#include "doalabel.h"

#include <QEvent>

DOALabel::DOALabel(QWidget *parent, Qt::WindowFlags f)
    : QLabel(parent, f)
    , m_text("")
{
}

DOALabel::DOALabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
    : QLabel(text, parent, f)
    , m_text(text)
{
    setTextByWidth();
}

void DOALabel::setShowText(const QString &text)
{
    m_text = text;
    setTextByWidth();
}

void DOALabel::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::FontChange) {
        //如果字体改变
        setTextByWidth();
    }
    QLabel::changeEvent(e);
}

void DOALabel::resizeEvent(QResizeEvent *event)
{
    setTextByWidth();
    QLabel::resizeEvent(event);
}

void DOALabel::setTextByWidth()
{
    QFont font = this->font();
    QFontMetrics metrics(font);
    QString showText = metrics.elidedText(m_text, Qt::ElideRight, this->width() - 2 * this->margin());
    setText(showText);
}
