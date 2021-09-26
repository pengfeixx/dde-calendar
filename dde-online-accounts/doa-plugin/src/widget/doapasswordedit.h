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
#ifndef DOAPASSWORDEDIT_H
#define DOAPASSWORDEDIT_H

#include <DPasswordEdit>
#include <DSuggestButton>

DWIDGET_USE_NAMESPACE
class DOAPasswordEdit : public DPasswordEdit
{
    Q_OBJECT
public:
    explicit DOAPasswordEdit(QWidget *parent = nullptr);
    void setPasswordButtonAutoHide(const bool isAutoHide);
    bool getPasswordButtonAutoHide() const;
    void setText(const QString &text);

private:
    void focusOutHandle();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
signals:
    /**
     * @brief signalePasswordChanged    密码改变信号，该信号只有在设置按钮自动隐藏时才有效
     */
    void signalePasswordChanged(const QString &password);
public slots:
    void slotTextChanged(const QString &str);

private:
    DSuggestButton *m_PasswordBtn = nullptr;
    bool m_PasswordBtnAutoHide = false;
    QString m_password = "";
};

#endif // DOAPASSWORDEDIT_H
