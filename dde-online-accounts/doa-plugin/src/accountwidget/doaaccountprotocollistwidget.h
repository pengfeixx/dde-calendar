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
#ifndef DOAACCOUNTPROTOCOLLISTWIDGET_H
#define DOAACCOUNTPROTOCOLLISTWIDGET_H

#include "consts.h"
#include "data/doaaccountmodel.h"

#include <QListView>

/**
 * @brief The accountProtocolListWidget class   帐户协议选择列表窗口
 */
class DOAAccountProtocolListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DOAAccountProtocolListWidget(QWidget *parent = nullptr);
    void setModel(DOAAccountModel *model);
signals:
    void signalLoginState(int state);
public slots:
    /**
     * @brief slotAccountItemClicked
     * @param type
     */
    void slotAccountItemClicked(ProtocolType type);

    /**
     * @brief slotAddAccount        添加帐户信息
     * @param info
     */
    void slotAddAccount(const AddAccountInfo &info);

private:
    QListView *m_protocolList;
    DOAAccountModel *m_dataModel = nullptr;
};

#endif // DOAACCOUNTPROTOCOLLISTWIDGET_H
