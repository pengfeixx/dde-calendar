/*
* Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
*
* Author:     wangyou <wangyou@uniontech.com>
*
* Maintainer: wangyou <wangyou@uniontech.com>
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
#ifndef DOAQQPROVIDER_H
#define DOAQQPROVIDER_H

#include "doaprovider.h"

#include <QNetworkAccessManager>
#include <QObject>
#include <QTimer>

class DOAQQProvider : public DOAProvider
{
public:
    explicit DOAQQProvider(QObject *parent = nullptr);

    ~DOAQQProvider() override;

protected:
    LoginState login() override;
    void loginCancel() override;

private:
    /**
     * @brief timeouthandle     定时器超时处理
     */
    LoginState timeouthandle();

private:
    //使用获取属性接口验证密码是否正确
    LoginState getPropname();
    //根据URL查询出日历同步URL
    LoginState getCalendarUri();

    QNetworkAccessManager *m_manager = nullptr;
    QNetworkReply *m_reply = nullptr;

    bool isUserCancle = false;
    //同步返回 网络超时定时器
    QTimer m_timer;
};

#endif // DOAQQPROVIDER_H
