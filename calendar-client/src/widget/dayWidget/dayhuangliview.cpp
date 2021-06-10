/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     kirigaya <kirigaya@mkacg.com>
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
#include "dayhuangliview.h"
#include "scheduledlg.h"

#include <DHiDPIHelper>

#include <QAction>
#include <QListWidget>
#include <QLabel>
#include <QPainter>
#include <QHBoxLayout>
#include <QStylePainter>
#include <QRect>
CDayHuangLiLabel::CDayHuangLiLabel(QWidget *parent)
    : DLabel(parent)
{
    setMargin(0);
}

void CDayHuangLiLabel::setbackgroundColor(QColor backgroundColor)
{
    m_backgroundColor = backgroundColor;
}

void CDayHuangLiLabel::setTextInfo(QColor tcolor, QFont font)
{
    m_textcolor = tcolor;
    m_font = font;
}

void CDayHuangLiLabel::setHuangLiText(QStringList vhuangli, int type)
{
    m_vHuangli = vhuangli;
    m_type = type;
    m_showStr = vhuangli.join("   ");
    QString str = vhuangli.join(".");
    setToolTip(str);
    QFontMetrics metrics(m_font);
    m_textWidth = metrics.width(m_showStr);
    update();
}
void CDayHuangLiLabel::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    int labelwidth = width();
    int labelheight = height();

    QPainter painter(this);
    QRect fillRect = QRect(0, 0, labelwidth, labelheight);
    painter.setRenderHints(QPainter::HighQualityAntialiasing);
    painter.setBrush(QBrush(m_backgroundColor));
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(fillRect, 12, 12);
    QPixmap pixmap;
    if (m_type == 0)
        pixmap = DHiDPIHelper::loadNxPixmap(":/resources/icon/dde-yi.svg");
    else {
        pixmap = DHiDPIHelper::loadNxPixmap(":/resources/icon/dde-ji.svg");
    }
    pixmap.setDevicePixelRatio(devicePixelRatioF());
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.drawPixmap(QRect(m_leftMagin, m_topMagin + 1, 22, 22), pixmap);
    painter.restore();

    painter.setFont(m_font);
    painter.setPen(m_textcolor);

    const int text_X = m_leftMagin + 34;
    const int text_Width = this->width() - text_X - 20;

    if (m_textWidth > text_Width) {
        QStringList showList = getShowString(m_vHuangli, text_Width);
        //高度上下边距20
        qreal text_Height = (this->height() - 40) / showList.size();
        for (int i = 0; i < showList.size(); ++i) {
            painter.drawText(QRectF(text_X, text_Height * i + 20, text_Width, text_Height), Qt::AlignLeft | Qt::AlignVCenter, showList.at(i));
        }
    } else {
        painter.drawText(QRect(text_X, 10, text_Width, this->height() - 20), Qt::AlignLeft | Qt::AlignVCenter, m_showStr);
    }
}

void CDayHuangLiLabel::resizeEvent(QResizeEvent *event)
{
    m_leftMagin = static_cast<int>(0.0424 * width() + 0.5);
    m_topMagin = (height() - 20) / 2;
    DLabel::resizeEvent(event);
}

/**
 * @brief CDayHuangLiLabel::getShowString       根据获取的黄历信息和显示宽度获取每行显示的字符
 * @param vhuangli                              黄历信息
 * @param maxWidth                              最大显示宽度
 * @return
 */
QStringList CDayHuangLiLabel::getShowString(const QStringList &vhuangli, const int maxWidth)
{
    QString showst = "";
    QStringList showString {};
    QFontMetrics metrics(m_font);
    for (int i = 0; i < vhuangli.size(); ++i) {
        if (metrics.width(showst) + metrics.width(vhuangli.at(i)) < maxWidth) {
            showst += vhuangli.at(i) + "   ";
        } else {
            showString.append(showst);
            showst = vhuangli.at(i) + "   ";
        }
    }
    showString.append(showst);
    return showString;
}
