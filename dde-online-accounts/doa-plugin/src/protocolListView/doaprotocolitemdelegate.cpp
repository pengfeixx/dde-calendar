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
#include "doaprotocolitemdelegate.h"
#include <DGuiApplicationHelper>
#include <DFontSizeManager>

#include <QPainter>
#include <QEvent>
#include <QSvgRenderer>

DGUI_USE_NAMESPACE
DWIDGET_USE_NAMESPACE
DOAProtocolItemDelegate::DOAProtocolItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void DOAProtocolItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.isValid()) {
        painter->setRenderHint(QPainter::Antialiasing); // 反锯齿;
        //获取当前item数据
        QVariant value = index.data(Qt::UserRole);
        AccountProtocol accountProtocol = value.value<AccountProtocol>();

        QStyleOptionViewItem viewOption(option); //用来在视图中画一个item

        QRectF rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        rect.setWidth(option.rect.width());
        rect.setHeight(option.rect.height());
        QBrush backgroudBrush;
        //获取背景色
        if (option.state.testFlag(QStyle::State_MouseOver)) {
            backgroudBrush = DGuiApplicationHelper::instance()->applicationPalette().brush(QPalette::Normal, QPalette::Midlight);
        } else {
            backgroudBrush = DGuiApplicationHelper::instance()->applicationPalette().itemBackground();
        }
        //画圆角矩形
        {
            const qreal radius = 8;
            painter->save();
            painter->setPen(Qt::NoPen);
            painter->setBrush(backgroudBrush);
            painter->drawRoundedRect(rect, radius, radius);
            painter->restore();
        }

        //画图标
        {
            const qreal icon_Width = 32;
            QRectF iconRect;
            iconRect.setX(rect.width() / 2 - 40 - icon_Width);
            iconRect.setY(rect.y() + (rect.height() - icon_Width) / 2);
            iconRect.setWidth(icon_Width);
            iconRect.setHeight(icon_Width);
            painter->save();
            painter->drawPixmap(QPointF(iconRect.x(), iconRect.y()), QIcon::fromTheme("doa_caldav").pixmap(iconRect.size().toSize()));
            painter->restore();
        }

        //绘制显示文字
        {
            QRectF textRect;
            textRect.setX(rect.width() / 2 - 20);
            textRect.setY(rect.y());
            textRect.setWidth(rect.width() / 2);
            textRect.setHeight(rect.height());
            painter->save();
            painter->setFont(DFontSizeManager::instance()->get(DFontSizeManager::T6, QFont::Medium));
            painter->setPen(DGuiApplicationHelper::instance()->applicationPalette().buttonText().color());
            painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, accountProtocol.protocolDisplayName);
            painter->restore();
        }
    }
}

bool DOAProtocolItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    //按钮点击事件
    if (event->type() == QEvent::MouseButtonPress) {
        QVariant value = model->data(index, Qt::UserRole);

        AccountProtocol accountProtocol = value.value<AccountProtocol>();
        emit signalSelectItem(accountProtocol.protocolType);
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

QSize DOAProtocolItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    QSize size = option.rect.size();
    //根据UI图设置固定高度56
    size.setHeight(56);
    return size;
}
