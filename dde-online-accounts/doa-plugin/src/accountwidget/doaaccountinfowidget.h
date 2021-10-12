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
#ifndef ACCOUNTINFOWIDGET_H
#define ACCOUNTINFOWIDGET_H

#include "widget/doainfowidget.h"
#include "widget/doaapplytowidget.h"
#include "widget/doaerrorwidget.h"
#include "data/doaaccountmodel.h"
#include "data/doaaccount.h"

#include <QWidget>
#include <QLabel>
#include <QScrollArea>

/**
 * @brief The DOAAccountInfoWidget class        帐户详情窗口
 */
class DOAAccountInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DOAAccountInfoWidget(QWidget *parent = nullptr);
    void setModel(DOAAccountModel *model);

    void initData();
signals:

public slots:
    /**
     * @brief slotUpdateCurrentAccount      更新显示当前帐户信息
     */
    void slotUpdateCurrentAccount();

    /**
     * @brief slotDeleteCurrentAccount      移除当前帐户
     */
    void slotDeleteCurrentAccount();

    /**
     * @brief slotUpdateUserName        更新显示名称
     * @param userName                  显示名称
     */
    void slotUpdateUserName(const QString &userName);

    /**
     * @brief slotPropertyChanged 属性改变
     * @param accountID
     */
    void slotPropertyChanged(const QString &accountID);

    /**
     * @brief slotAccountStatusChanged      帐户状态发生改变
     * @param accountID                     帐户id
     */
    void slotAccountStatusChanged(const QString &accountID);

    /**
     * @brief slotUpdateApplyToItem 应用于改变
     * @param app
     */
    void slotUpdateApplyToItem(const DOAApplyToObject &app);

    /**
     * @brief slotShowErrorMsg 处理错误信息显示
     * @param accountID
     */
    void slotShowErrorMsg();

    /**
     * @brief slotUpdatePassword 处理密码改变
     * @param passowrd
     */
    void slotUpdatePassword(const QString &passowrd);

    /**
     * @brief DOAAccountInfoWidget::slotTryAgain
     * 重新检测帐户状态
     */
    void slotTryAgain();

private:
    /**
     * @brief initWidget    初始化界面
     */
    void initWidget();

    /**
     * @brief isCurrentShowAccount      是否为当前显示帐户
     * @param accountID                 帐户id
     * @return
     */
    bool isCurrentShowAccount(const QString &accountID);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QWidget *m_content;
    QScrollArea *m_scrollArea;
    DOAAccount *m_Account;
    DOAInfoWidget *m_accountInfo; //帐户信息窗口
    QLabel *m_accountProtocolLbl; //帐户协议
    DOAApplyToWidget *m_applyToWidget; //应用于窗口
    DOAErrorWidget *m_errorWidget; //错误信息
    DOAAccountModel *m_accountModel;
};

#endif // ACCOUNTINFOWIDGET_H
