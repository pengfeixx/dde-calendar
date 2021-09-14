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
#ifndef DOAACCOUNTLISTITEMDELEGATE_H
#define DOAACCOUNTLISTITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QFont>
#include <QFontMetrics>

class QSvgRenderer;
class DOAAccountListItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit DOAAccountListItemDelegate(QObject *parent = nullptr);

    //描绘画面显示
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    //处理鼠标事件
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;

    //返回item大小
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    /**
     * @brief getStringByWidth      根据字符宽度获取字符，若字符过多则显示。。。
     * @param str                   需要设置的字符
     * @param fm                    字符的字体属性
     * @param width                 最大宽度
     * @return                      返回处理后的字符
     */
    QString getStringByWidth(const QString &str, const QFontMetrics &fm, int width) const;

signals:
    void signalSelectItem(QString accountID);
public slots:
private:
    QSvgRenderer *m_typeSvg = nullptr;
    QFont m_userNameFont; //用户名字体
    QFont m_accountNameFont; //帐户字体
    QFontMetrics m_userNameMetrics;
    QFontMetrics m_accountNameMetrics;
};

#endif // DOAACCOUNTLISTITEMDELEGATE_H
