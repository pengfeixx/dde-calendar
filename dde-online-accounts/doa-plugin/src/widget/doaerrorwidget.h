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

/**
 * @brief The DOAErrorWidget class      帐户详情错误显示模块
 *
 */
class DOAErrorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DOAErrorWidget(QWidget *parent = nullptr);

    ~DOAErrorWidget();

    /**
     * @brief DOAErrorWidget::setErrorMsg 设置错误信息
     * @param errorMsg
     */
    void setErrorMsg(const DOAAccount::AccountState);
private:
    struct TryAgainState {
        bool isClicked = false;
        QDateTime clickDateTime;
    };

signals:
    void sign_tryAgain();
public slots:
    void slot_tryAgain();

private:
    //错误信息label
    QLabel *m_errorMessageLabel = nullptr;
    //重试按钮
    DCommandLinkButton *m_tryAginLink = nullptr;

    DSpinner *m_spinner = nullptr;
    QLabel *m_iconLabel = nullptr;
    TryAgainState m_tryAgainState; //点击重试状态
};

#endif // DOAERRORWIDGET_H
