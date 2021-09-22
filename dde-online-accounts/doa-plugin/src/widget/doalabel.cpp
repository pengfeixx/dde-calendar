#include "doalabel.h"

#include <QEvent>

DOALabel::DOALabel(QWidget *parent, Qt::WindowFlags f)
    : QLabel(parent, f)
    , m_text("")
{
}

DOALabel::DOALabel(const QString &text, QWidget *parent, Qt::WindowFlags f)
    : QLabel(text, parent, f)
    , m_text(text)
{
    setTextByWidth();
}

void DOALabel::setShowText(const QString &text)
{
    m_text = text;
    setTextByWidth();
}

void DOALabel::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::FontChange) {
        //如果字体改变
        setTextByWidth();
    }
    QLabel::changeEvent(e);
}

void DOALabel::resizeEvent(QResizeEvent *event)
{
    setTextByWidth();
    QLabel::resizeEvent(event);
}

void DOALabel::setTextByWidth()
{
    QFont font = this->font();
    QFontMetrics metrics(font);
    QString showText = metrics.elidedText(m_text, Qt::ElideRight, this->width() - 2 * this->margin());
    setText(showText);
}
