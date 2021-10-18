#include "doanonetworklabel.h"

#include <DFontSizeManager>
#include <DPalette>
#include <DGuiApplicationHelper>

#include <QEvent>
#include <QPainter>
#include <QFont>

DWIDGET_USE_NAMESPACE
DGUI_USE_NAMESPACE

DOANoNetWorkLabel::DOANoNetWorkLabel(QWidget *parent)
    : QWidget(parent)
{
}

DOANoNetWorkLabel::~DOANoNetWorkLabel()
{
}

void DOANoNetWorkLabel::setText(const QString &str)
{
    m_text = str;
    update();
}

QString DOANoNetWorkLabel::getText() const
{
    return m_text;
}

void DOANoNetWorkLabel::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QFont font = DFontSizeManager::instance()->get(DFontSizeManager::T5, QFont::Bold);
    DPalette palette = this->palette();
    QColor color = DGuiApplicationHelper::instance()->applicationPalette().textTiele().color();
    color.setAlphaF(0.4);
    painter.setPen(color);
    painter.setFont(font);
    painter.drawText(rect(), Qt::AlignCenter, m_text);
}
