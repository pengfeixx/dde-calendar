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
#ifndef DOAERRORWIDGET_H
#define DOAERRORWIDGET_H

#include <data/doaaccount.h>

#include <DSpinner>
#include <DCommandLinkButton>

#include <QWidget>
#include <QLabel>

DWIDGET_USE_NAMESPACE

extern bool widgetIsVisible;

/**
 * @brief The DOAErrorWidget class      帐户详情错误显示模块
 *
 */
class DOAErrorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DOAErrorWidget(QWidget *parent = nullptr);
    ~DOAErrorWidget() override;
    /**
     * @brief DOAErrorWidget::setErrorMsg 设置错误信息
     * @param errorMsg
     */
    void setErrorMsg(const DOAAccount::AccountState);

    /**
     * @brief initData  初始化数据
     */
    void initData();

private:
    enum MouseState { MS_Press,
                      MS_Enter,
                      MS_Leave
    };
    struct TryAgainState {
        bool isClicked = false;
        QDateTime clickDateTime;
        MouseState msState = MS_Leave;
    };
    struct ErrorMsg {
        QString msg = "";
        int len = 0;
        QRectF rectF;
    };
    enum ShowState {
        MsgHide //隐藏
        ,
        MsgChecking //验证
        ,
        MsgShow_TryAgain //显示 重试
        ,
        MsgShow_NoTryAgain //显示 无重试
    };
    //根据宽度和字体大小显示错误信息
    void showMsgByWidth();
    /**
     * @brief tokenize          根据词边界拆分字符串
     * @param str
     * @return
     */
    QStringList tokenize(const QString &str);

    /**
     * @brief getErrorMsgVector     根据错误信息和限制宽度分割每行显示的内容
     * @param t                     根据词边界拆分后的字符集
     * @param limitLength           显示的宽度
     * @return                      每行显示的内容
     */
    template<typename T>
    QVector<ErrorMsg> getErrorMsgVector(const T &t, const int &limitLength);

    /**
     * @brief updateRect        更新错误信息需要显示的矩阵
     */
    void updateRect();
protected:
    void paintEvent(QPaintEvent *event) override;
    void changeEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;
signals:
    void sign_tryAgain();
    void sign_EventQuit();
public slots:
    void slot_tryAgain();
private:
    //错误信息label
    QLabel *m_errorMessageLabel = nullptr;
    DSpinner *m_spinner = nullptr;
    QString m_errorMsg {}; //为原始错误信息
    QVector<ErrorMsg> m_errorMsgVector {};
    TryAgainState m_tryAgainState; //点击重试状态
    ShowState m_errorMsgState = MsgHide;
    QRectF m_tryAgainRect;
    QFont m_font;
    QFontMetrics m_fontMeterics;
    QString m_tryAgainStr;
    QRectF m_iconRect;
    int m_showRow = 0;
};
#endif // DOAERRORWIDGET_H
