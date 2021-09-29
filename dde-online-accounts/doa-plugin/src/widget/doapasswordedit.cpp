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
#include "doapasswordedit.h"

#include <QEvent>
#include <QRegExp>
#include <QRegExpValidator>

DOAPasswordEdit::DOAPasswordEdit(QWidget *parent)
    : DPasswordEdit(parent)
{
    //添加密码限制，只能输入字母，数字和特殊字符,限制中文和空白字符的输入
    QRegExp exp("^[^\u4e00-\u9fa5\\s]*$");
    QRegExpValidator *validator = new QRegExpValidator(exp, this);
    lineEdit()->setValidator(validator);
    connect(this, &DPasswordEdit::textChanged, this, &DOAPasswordEdit::slotTextChanged);
    //获取隐藏密码按钮
    m_PasswordBtn = this->findChild<DSuggestButton *>();
    if (m_PasswordBtn) {
        m_PasswordBtn->installEventFilter(this);
    }
    lineEdit()->installEventFilter(this);
}

void DOAPasswordEdit::setPasswordButtonAutoHide(const bool isAutoHide)
{
    m_PasswordBtnAutoHide = isAutoHide;
}

bool DOAPasswordEdit::getPasswordButtonAutoHide() const
{
    return m_PasswordBtnAutoHide;
}

void DOAPasswordEdit::setText(const QString &text)
{
    m_password = text;
    DPasswordEdit::setText(m_password);
}

void DOAPasswordEdit::focusOutHandle()
{
    //焦点离开后设置密码隐藏并设置按钮无效
    setEchoMode(QLineEdit::Password);
    setEchoButtonIsVisible(false);
    if (text().isEmpty())
        DPasswordEdit::setText(m_password);
    if (text() != m_password) {
        m_password = text();
        emit signalePasswordChanged(text());
    }
}

bool DOAPasswordEdit::eventFilter(QObject *watched, QEvent *event)
{
    //如果设置了自动隐藏
    if (m_PasswordBtnAutoHide) {
        if (event->type() == QEvent::FocusOut) {
            if (watched == lineEdit() && m_PasswordBtn != focusWidget()) {
                focusOutHandle();
            }
            if (watched == m_PasswordBtn && lineEdit() != focusWidget()) {
                focusOutHandle();
            }
        };
    }
    return DPasswordEdit::eventFilter(watched, event);
}

void DOAPasswordEdit::slotTextChanged(const QString &str)
{
    if (str.isEmpty() && !echoButtonIsVisible())
        setEchoButtonIsVisible(true);
}
