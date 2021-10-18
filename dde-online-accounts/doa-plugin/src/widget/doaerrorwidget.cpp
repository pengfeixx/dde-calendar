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
#include "doaerrorwidget.h"

#include <DFontSizeManager>
#include <DGuiApplicationHelper>

#include <QHBoxLayout>
#include <QEventLoop>
#include <QTimer>
#include <QPaintEvent>
#include <QPainter>
#include <QRegularExpression>
#include <QMouseEvent>
#include <QEvent>

bool widgetIsVisible = false; //窗口是否有效
const int errorIconWidth = 20; //错误标签宽度
const int errorspace = 8; //间隔

DOAErrorWidget::DOAErrorWidget(QWidget *parent)
    : QWidget(parent)
    , m_font(DFontSizeManager::instance()->get(DFontSizeManager::T8, QFont::Normal))
    , m_fontMeterics(m_font)
    , m_tryAgainStr(tr("try again"))
{
    m_spinner = new DSpinner();
    m_spinner->setFixedSize(20, 20);

    //错误信息
    m_errorMessageLabel = new QLabel();
    m_errorMessageLabel->setText(tr("Connecting to the account..."));
    m_errorMessageLabel->setFont(m_font);
    m_errorMessageLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);


    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addStretch();
    layout->addWidget(m_spinner);
    layout->addSpacing(8);
    layout->addWidget(m_errorMessageLabel);
    layout->addStretch();
    this->setLayout(layout);
    widgetIsVisible = true;
    //启用子窗口鼠标跟踪
    setMouseTracking(true);
}

DOAErrorWidget::~DOAErrorWidget()
{
    widgetIsVisible = false;
    m_spinner->stop();
    initData();
}

void DOAErrorWidget::setErrorMsg(const DOAAccount::AccountState accountState)
{
    //如果点击重试后，结果返回时间比较短
    if (m_tryAgainState.isClicked && m_tryAgainState.clickDateTime.msecsTo(QDateTime::currentDateTime()) < 200) {
        QEventLoop eventLoop;
        //优化用户体验设置600毫秒后退出
        QTimer::singleShot(600, &eventLoop, &QEventLoop::quit);
        //切换用户时退出
        connect(this, &DOAErrorWidget::sign_EventQuit, &eventLoop, &QEventLoop::quit);
        eventLoop.exec();
    }
    //如果窗口已被释放则退出
    if (!widgetIsVisible)
        return;
    m_spinner->stop();
    m_spinner->setVisible(false);
    m_errorMessageLabel->setVisible(false);
    m_tryAgainState.isClicked = false;
    //如果验证成功则隐藏
    if (DOAAccount::Account_Success == accountState) {
        setHidden(true);
        m_errorMsgState = MsgHide;
        return;
    }
    m_errorMsg.clear();
    //如果验证失败则显示
    setHidden(false);
    switch (accountState) {
    case DOAAccount::Account_AuthenticationFailed:
        //密码异常
        m_errorMsgState = MsgShow_NoTryAgain;
        m_errorMsg = tr("Cannot connect to the account, please check your password");
        break;
    case DOAAccount::Account_NetWorkException:
        //网络错误
        m_errorMsgState = MsgShow_TryAgain;
        m_errorMsg = tr("Network error, please check and");
        break;
    default:
        //服务器异常
        m_errorMsgState = MsgShow_TryAgain;
        m_errorMsg = tr("Server error, please");
        break;
    }
    showMsgByWidth();
}

//初始化数据
void DOAErrorWidget::initData()
{
    m_tryAgainState.isClicked = false;
    m_errorMsgState = MsgHide;
    m_errorMsg.clear();
    //通知退出事件循环
    emit sign_EventQuit();
}

void DOAErrorWidget::showMsgByWidth()
{
    int fontHeight = m_fontMeterics.height();
    m_errorMsgVector.clear();
    //需要显示的行数
    m_showRow = 0;
    //是否含有单词边界
    bool isContainsWordBoundaries = false;
    if (!m_errorMsg.isEmpty()) {
        //获取能够显示的宽度
        int errormsgShowWidth = this->width() - errorIconWidth - errorspace - 6;
        //如果显示不全则需要换行显示,目前错误信息最多显示2行
        //根据词边界分割字符
        QStringList strList = tokenize(m_errorMsg);
        if (strList.size() > 2) {
            m_errorMsgVector = getErrorMsgVector(strList, errormsgShowWidth);
            isContainsWordBoundaries = true;
        } else {
            //根据字符长度
            m_errorMsgVector = getErrorMsgVector(m_errorMsg, errormsgShowWidth);
            isContainsWordBoundaries = false;
        }
        m_showRow = m_errorMsgVector.size();
        //如果需要显示重试标签
        if (MsgShow_TryAgain == m_errorMsgState) {
            QString str = m_tryAgainStr;
            //如果存在单词边界则添加一个空格
            if (isContainsWordBoundaries) {
                str = " " + m_tryAgainStr;
            }
            //如果只有一行则需要考虑错误标签的宽度
            int offset = 0;
            if (m_errorMsgVector.size() == 1) {
                offset = errorIconWidth + errorspace + 6;
            }
            //如果最后一行添加重试后显示不全,需要添加一行
            if (m_errorMsgVector.last().len + m_fontMeterics.horizontalAdvance(str) > this->width() - offset) {
                m_showRow += 1;
            }
        }
    }

    fontHeight = qMax(fontHeight, 20);
    if (!m_errorMsgVector.isEmpty()) {
        setFixedHeight((fontHeight + 2) * m_showRow);
    } else {
        setFixedHeight(fontHeight + 2);
    }

    //如果不是验证状态
    if (MsgChecking != m_errorMsgState) {
        //更新绘制矩阵
        updateRect();
        //设置重试矩阵
        if (MsgShow_TryAgain == m_errorMsgState) {
            if (m_showRow != m_errorMsgVector.size()) {
                m_tryAgainRect.setX(m_iconRect.x());
                m_tryAgainRect.setY(m_errorMsgVector.last().rectF.bottom());
            } else {
                int offset = 0;
                if (isContainsWordBoundaries) {
                    offset = 4;
                }
                //如果根据单词分割则添加间距
                m_tryAgainRect.setX(m_errorMsgVector.last().rectF.right() + offset);
                m_tryAgainRect.setY(m_errorMsgVector.last().rectF.y());
            }
            m_tryAgainRect.setWidth(m_fontMeterics.horizontalAdvance(m_tryAgainStr));
            m_tryAgainRect.setHeight(m_errorMsgVector.last().rectF.height());
        }
        update();
    }
}

QStringList DOAErrorWidget::tokenize(const QString &str)
{
    QRegularExpression re("\\b");
    return str.split(re);
}

void DOAErrorWidget::updateRect()
{
    if (m_errorMsgVector.isEmpty())
        return;
    //矩阵高度
    qreal h = height() / m_showRow;
    qreal iconX = 0;
    qreal x = 0;
    for (int i = 0; i < m_errorMsgVector.size(); ++i) {
        if (0 == i) {
            //如果显示重试标签且只显示一行
            if (MsgShow_TryAgain == m_errorMsgState && m_errorMsgVector.size() == 1 && m_showRow == m_errorMsgVector.size()) {
                iconX = (width() - (errorIconWidth + errorspace + m_errorMsgVector.at(0).len + m_fontMeterics.horizontalAdvance(m_tryAgainStr))) / 2;
            } else {
                iconX = (width() - (errorIconWidth + errorspace + m_errorMsgVector.at(i).len)) / 2;
            }
            x = iconX + errorIconWidth + errorspace;
            //设置错误图标显示位置
            m_iconRect.setX(iconX);
            qreal iconh = (h - errorIconWidth) / 2;
            m_iconRect.setY(iconh);
            m_iconRect.setWidth(errorIconWidth);
            m_iconRect.setHeight(errorIconWidth);
        } else {
            x = iconX;
        }
        m_errorMsgVector[i].rectF.setX(x);
        m_errorMsgVector[i].rectF.setY(h * i);
        m_errorMsgVector[i].rectF.setWidth(m_errorMsgVector.at(i).len);
        m_errorMsgVector[i].rectF.setHeight(h);
    }
}

void DOAErrorWidget::paintEvent(QPaintEvent *event)
{
    if (MsgChecking == m_errorMsgState) {
        QWidget::paintEvent(event);
        return;
    }
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    {
        painter.setPen(Qt::NoPen);
        painter.drawPixmap(QPointF(m_iconRect.x(), m_iconRect.y()), QIcon::fromTheme("doa_error").pixmap(QSize(20, 20)));
    }
    {
        //绘制错误消息
        QColor color = DGuiApplicationHelper::instance()->applicationPalette().textTips().color();
        painter.setFont(m_font);
        painter.setPen(color);
        for (int i = 0; i < m_errorMsgVector.size(); ++i) {
            painter.drawText(m_errorMsgVector.at(i).rectF, Qt::AlignCenter, m_errorMsgVector.at(i).msg);
        }
    }
    if (MsgShow_TryAgain == m_errorMsgState) {
        //绘制重试
        QColor textColor = DGuiApplicationHelper::instance()->applicationPalette().highlight().color();
        if (MS_Enter == m_tryAgainState.msState) {
            textColor = textColor.lighter(130);
        }
        painter.setPen(textColor);
        painter.drawText(m_tryAgainRect, Qt::AlignCenter, m_tryAgainStr);
    }
}

void DOAErrorWidget::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::FontChange) {
        //根据字体宽度调整高度
        showMsgByWidth();
    }
}

void DOAErrorWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    //根据窗口的宽度调整高度
    showMsgByWidth();
}

void DOAErrorWidget::mousePressEvent(QMouseEvent *event)
{
    if (MsgShow_TryAgain == m_errorMsgState && m_tryAgainRect.contains(event->pos())) {
        m_tryAgainState.msState = MS_Press;
    } else {
        QWidget::mousePressEvent(event);
    }
    update();
}

void DOAErrorWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (MsgShow_TryAgain == m_errorMsgState && m_tryAgainRect.contains(event->pos())) {
        m_tryAgainState.msState = MS_Enter;
        //触发重试
        slot_tryAgain();
    } else {
        QWidget::mouseReleaseEvent(event);
        m_tryAgainState.msState = MS_Leave;
    }
    update();
}

void DOAErrorWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (MsgShow_TryAgain == m_errorMsgState && m_tryAgainRect.contains(event->pos())) {
        m_tryAgainState.msState = MS_Enter;
    } else {
        m_tryAgainState.msState = MS_Leave;
        QWidget::mouseMoveEvent(event);
    }
    update();
}

void DOAErrorWidget::leaveEvent(QEvent *event)
{
    m_tryAgainState.msState = MS_Leave;
    QWidget::leaveEvent(event);
    update();
}

void DOAErrorWidget::slot_tryAgain()
{
    m_errorMsgState = MsgChecking;
    m_errorMsg.clear();
    m_errorMsgVector.clear();
    m_spinner->setVisible(true);
    m_spinner->start();
    m_errorMessageLabel->setVisible(true);
    showMsgByWidth();
    //获取点击时间
    m_tryAgainState.isClicked = true;
    m_tryAgainState.clickDateTime = QDateTime::currentDateTime();
    emit this->sign_tryAgain();
}

template<typename T>
QVector<DOAErrorWidget::ErrorMsg> DOAErrorWidget::getErrorMsgVector(const T &t, const int &limitLength)
{
    QString str("");
    QVector<ErrorMsg> msgVector {};
    for (int i = 0; i < t.size(); ++i) {
        //第一行需要显示错误标签,除去第一行其他行需要加上错误标签的宽度
        int len = msgVector.size() > 0 ? limitLength + errorIconWidth + errorspace : limitLength;
        //如果超过显示长度则换行
        if ((m_fontMeterics.width(str) + m_fontMeterics.width(t.at(i))) > len) {
            ErrorMsg msg;
            msg.msg = str;
            msg.len = m_fontMeterics.width(str);
            msgVector.append(msg);
            str = "";
        }
        str += t.at(i);
        //如果是最后一个
        if (t.size() - 1 == i) {
            ErrorMsg msg;
            msg.msg = str;
            msg.len = m_fontMeterics.width(str);
            msgVector.append(msg);
        }
    }
    return msgVector;
}
