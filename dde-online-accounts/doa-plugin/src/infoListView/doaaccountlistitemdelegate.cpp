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
#include "doaaccountlistitemdelegate.h"
#include "consts.h"

#include <DFontSizeManager>
#include <DGuiApplicationHelper>
#include <DApplicationHelper>

#include <QMouseEvent>
#include <QPainter>
#include <QSvgRenderer>

DGUI_USE_NAMESPACE
DWIDGET_USE_NAMESPACE
DOAAccountListItemDelegate::DOAAccountListItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
    , m_typeSvg(new QSvgRenderer(this))
    , m_userNameFont(DFontSizeManager::instance()->get(DFontSizeManager::T7, QFont::Medium))
    , m_accountNameFont(DFontSizeManager::instance()->get(DFontSizeManager::T8, QFont::Normal))
    , m_userNameMetrics(m_userNameFont)
    , m_accountNameMetrics(m_accountNameFont)
{
}

void DOAAccountListItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.isValid()) {
        painter->setRenderHint(QPainter::Antialiasing); // 反锯齿;
        //获取当前item数据
        QVariant value = index.data(Qt::UserRole);
        AccountItemData accountData = value.value<AccountItemData>();

        QStyleOptionViewItem viewOption(option); //用来在视图中画一个item

        QRectF rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        rect.setWidth(option.rect.width());
        rect.setHeight(option.rect.height());

        QBrush backgroudBrush;
        QColor textColor;
        textColor = DGuiApplicationHelper::instance()->applicationPalette().buttonText().color();
        //获取背景色
        if (option.state.testFlag(QStyle::State_Selected)) {
            textColor = DGuiApplicationHelper::instance()->applicationPalette().highlightedText().color();
            //选中状态
            backgroudBrush = DGuiApplicationHelper::instance()->applicationPalette().highlight();
            //选中状态下鼠标悬浮
            if (option.state.testFlag(QStyle::State_MouseOver)) {
                backgroudBrush.setColor(backgroudBrush.color().lighter(120));
            }
        } else if (option.state.testFlag(QStyle::State_MouseOver)) {
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
        //帐户类型图标宽度
        const qreal typeIcon_Width = 32;
        //帐户类型图标高度
        const qreal typeIcon_Height = 32;
        const qreal typeIcon_X = (rect.height() - typeIcon_Height) / 2;
        //绘制帐户类型图标
        {
            //垂直居中
            qreal y = rect.y() + typeIcon_X;
            //类型图标位置
            QRectF typeIconRect;
            typeIconRect.setX(typeIcon_X);
            typeIconRect.setY(y);
            typeIconRect.setWidth(typeIcon_Width);
            typeIconRect.setHeight(typeIcon_Height);

            painter->save();
            painter->drawPixmap(QPointF(typeIconRect.x(), typeIconRect.y()), QIcon::fromTheme(accountData.accountTypeFileName).pixmap(typeIconRect.size().toSize()));
            painter->restore();
        }

        const qreal errorIcon_Width = 20;
        const qreal errorIcon_Height = 20;

        qreal accountNameX = typeIcon_Width + typeIcon_X + 10;
        qreal accountNameWidth = rect.width() - accountNameX - 10;
        if (accountData.accountState) {
            accountNameWidth -= errorIcon_Width;
        }
        //绘制帐户用户名
        {
            QRectF userNameRect;
            userNameRect.setX(accountNameX);
            userNameRect.setY(rect.y() + 8);
            userNameRect.setWidth(accountNameWidth);
            userNameRect.setHeight(m_userNameMetrics.height());
            painter->save();
            painter->setFont(m_userNameFont);
            painter->setPen(textColor);
            //若显示文字过多则多余的显示。。。
            painter->drawText(userNameRect, Qt::AlignLeft, getStringByWidth(accountData.accountDisplayName, m_accountNameMetrics, static_cast<int>(accountNameWidth)));
            painter->restore();
        }
        //绘制帐户名称
        {
            QRectF accountNameRect;
            accountNameRect.setX(accountNameX);
            accountNameRect.setY(rect.y() + 8 + m_userNameMetrics.height());
            accountNameRect.setWidth(accountNameWidth);
            accountNameRect.setHeight(m_accountNameMetrics.height());
            painter->save();
            painter->setFont(m_accountNameFont);
            painter->setPen(textColor);
            //若显示文字过多则多余的显示。。。
            painter->drawText(accountNameRect, Qt::AlignLeft, getStringByWidth(accountData.accountName, m_accountNameMetrics, static_cast<int>(accountNameWidth)));
            painter->restore();
        }
        //如果状态异常则绘制异常图标
        if (accountData.accountState) {
            QRectF errorRect;
            errorRect.setX(rect.x() + rect.width() - 10 - errorIcon_Width);
            errorRect.setY(rect.y() + (rect.height() - errorIcon_Height) / 2);
            errorRect.setWidth(errorIcon_Width);
            errorRect.setHeight(errorIcon_Height);

            painter->save();
            painter->drawPixmap(QPointF(errorRect.x(), errorRect.y()), QIcon::fromTheme("doa_error").pixmap(errorRect.size().toSize()));
            painter->restore();
        }
    }
}

bool DOAAccountListItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    //按钮点击事件
    if (event->type() == QEvent::MouseButtonPress) {
        QVariant value = model->data(index, Qt::UserRole);

        AccountItemData accountData = value.value<AccountItemData>();
        emit signalSelectItem(accountData.accountId);
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

QSize DOAAccountListItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size = option.rect.size();

    QVariant value = index.data(Qt::UserRole);
    AccountItemData accountData = value.value<AccountItemData>();

    //根据当前字体设置item高度
    int itemHeight = 8 + m_userNameMetrics.height() + m_accountNameMetrics.height() + 10;

    itemHeight = qMax(52, itemHeight);
    size.setHeight(itemHeight);
    return size;
}

//根据字符宽度获取字符，若字符过多则显示。。。
QString DOAAccountListItemDelegate::getStringByWidth(const QString &str, const QFontMetrics &fm, int width) const
{
    return fm.elidedText(str, Qt::ElideRight, width);
}