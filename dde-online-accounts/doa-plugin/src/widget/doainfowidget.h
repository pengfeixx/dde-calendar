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
#ifndef DOAINFOWIDGET_H
#define DOAINFOWIDGET_H

#include <DLineEdit>
#include <DPasswordEdit>

#include <QWidget>
#include <QLabel>

class DOAPasswordEdit;
DWIDGET_USE_NAMESPACE

/**
 * @brief The DOAInfoWidget class   帐户信息显示
 */
class DOAInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DOAInfoWidget(QWidget *parent = nullptr);

    /**
     * @brief setShowData       设置显示信息
     */
    void setShowData(const QString &userName, const QString &url, const QString &accountName, const QString &password);

private:
    /**
     * @brief initWidget  初始化帐户信息界面
     */
    void initWidget();
signals:
    void signalUpdateUserName(const QString &name);
    void signalUpdatePassword(const QString &passwrd);
public slots:
    /**
     * @brief slotUserNameFocusChanged      用户名编辑框焦点离开处理
     * @param onFocus
     */
    void slotUserNameFocusChanged(const bool onFocus);

    /**
     * @brief slotUserNameTextChanged       用户名编辑框编辑处理
     * @param text
     */
    void slotUserNameTextChanged(const QString &text);

private:
    DLineEdit *m_userName = nullptr;
    QLabel *m_serverAddressLbl = nullptr;
    QLabel *m_accountName = nullptr;
    DOAPasswordEdit *m_passwordEdit = nullptr;
    QString m_displayName = ""; //用户名
    QString m_password = ""; //密码
};

#endif // DOAINFOWIDGET_H
