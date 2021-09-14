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
#include "doaprotocolmodel.h"
#include "displaytext.h"

DOAProtocolModel::DOAProtocolModel(QObject *parent)
    : QAbstractListModel(parent)
{
    AccountProtocol protocol;
    protocol.protocolType = ProtocolType::Type_CalDAV;
    protocol.protocolDisplayName = DOA::ProtocolWidget::calDavName;
    m_protocol.append(protocol);
}

int DOAProtocolModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_protocol.size();
}

QVariant DOAProtocolModel::data(const QModelIndex &index, int role) const
{
    QVariant ret;
    int row = index.row();

    if (row >= m_protocol.size() || (!index.isValid())) {
        return QVariant();
    }

    AccountProtocol protocol = m_protocol.at(row);
    if (role == Qt::UserRole)
        ret = QVariant::fromValue(protocol);
    return ret;
}

bool DOAProtocolModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool ret = false;
    int row = index.row();

    if (row >= m_protocol.size() || (!index.isValid())) {
        return false;
    }
    AccountProtocol protocol = m_protocol.at(row);

    if (role == Qt::UserRole) {
        AccountProtocol setData = value.value<AccountProtocol>();
        ret = true;
    }
    m_protocol.replace(row, protocol);
    return ret;
}
