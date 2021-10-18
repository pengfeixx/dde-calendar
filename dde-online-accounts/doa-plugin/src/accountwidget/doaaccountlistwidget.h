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
#ifndef DOAACCOUNTLISTWIDGET_H
#define DOAACCOUNTLISTWIDGET_H

#include "data/doaaccountmodel.h"
#include "doaaccountlistmodel.h"
#include "doaaccountlistitemdelegate.h"

#include <DFloatingButton>
#include <DListView>
#include <DStackedWidget>

#include <QWidget>
#include <QStandardItemModel>

class DOANoNetWorkLabel;

DWIDGET_USE_NAMESPACE

/**
 * @brief The accountListWidget class   帐户列表窗口
 */
class DOAAccountListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DOAAccountListWidget(QWidget *parent = nullptr);
    ~DOAAccountListWidget() override;
    void setModel(DOAAccountModel *model);

private:
    void initWidget();
signals:

public slots:
    /**
     * @brief slotSelectItem    接收item点击选择的account
     * @param accountID
     */
    void slotSelectItem(QString accountID);

    /**
     * @brief slotClickeAddAccount    点击添加帐户事件
     */
    void slotClickeAddAccount();

    /**
     * @brief slotGetAddAccount         添加获取到添加的帐户信息
     * @param info
     */
    void slotGetAddAccount(const DOAAccount *info);

    /**
     * @brief slotGetDeleteAccount      移除获取到需要移除的帐户ID
     * @param accountID
     */
    void slotGetDeleteAccount(const QString &accountID);

    /**
     * @brief slotShowStateChanged           页面显示状态
     */
    void slotShowStateChanged();

    /**
     * @brief slotAccountItemDataChanged       帐户项数据发生改变
     * @param accountID
     */
    void slotAccountItemDataChanged(const QString &accountID);

    /**
     * @brief slotGetAccountListSuccess     所有用户信息获取成功处理
     */
    void slotGetAccountListSuccess();

private:
    /**
     * @brief getAccountList        获取帐户列表信息
     */
    void getAccountList();

    AccountItemData getItemData(const DOAAccount *account);

private:
    DOAAccountModel *m_model;
    DFloatingButton *m_addAccountBtn; //添加用户按钮
    DListView *m_listView; //帐户信息列表
    DOANoNetWorkLabel *m_promptLbl; //无帐户信息提示
    DOAAccountListModel *m_listModel;
    DOAAccountListItemDelegate *m_listDelegate;
    DStackedWidget *m_stackedWidget;
};

#endif // DOAACCOUNTLISTWIDGET_H
