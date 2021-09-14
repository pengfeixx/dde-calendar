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
#ifndef DOAPROTOCOLITEMDELEGATE_H
#define DOAPROTOCOLITEMDELEGATE_H

#include "consts.h"

#include <QStyledItemDelegate>
#include <QFont>

class DOAProtocolItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit DOAProtocolItemDelegate(QObject *parent = nullptr);

    //描绘画面显示
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    //处理鼠标事件
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;

    //返回item大小
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
signals:
    void signalSelectItem(ProtocolType type);

public slots:
};

#endif // DOAPROTOCOLITEMDELEGATE_H
