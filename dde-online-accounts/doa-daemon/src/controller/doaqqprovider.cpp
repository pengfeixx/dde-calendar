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
#include "doaqqprovider.h"
#include "aesencryption.h"

#include <QDebug>
#include <QTimer>
#include <QBuffer>
#include <QEventLoop>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSslConfiguration>
#include <QRegularExpression>

DOAQQProvider::DOAQQProvider(QObject *parent)
    : DOAProvider(parent)
    , m_manager(new QNetworkAccessManager(this))
{
    setUrl("https://dav.qq.com");
    setProviderName(QQ);
    m_timer.setInterval(20000);
    m_timer.setSingleShot(true);
}

DOAQQProvider::~DOAQQProvider()
{
    qWarning() << "~DOAQQProvider";
}

/**
 * @brief DOAQQProvider::login
 * @return LoginState 登录状态枚举
 * 登录验证密码
 */
DOAProvider::LoginState DOAQQProvider::login()
{
    //验证密码或者帐户名是否为空
    if (getAccountName() == "") {
        qCritical() << "Account name is empty";
        return AccountNameEmpty;
    } else if (getAccountPassword() == "") {
        qCritical() << "Password is empty";
        return PassWordEmpty;
    }

    //取帐户后缀
    QRegularExpression reg("@qq.com$", QRegularExpression::CaseInsensitiveOption);
    QRegularExpressionMatch match = reg.match(getAccountName());
    if (!match.hasMatch()) {
        qCritical() << "Account format error";
        return AccountNameError;
    }

    DOAProvider::LoginState ret;

    //服务器URI为空
    if (getUri() == "") {
        //查询服务器URI
        ret = getCalendarUri();
        if (ret != DOAProvider::SUCCESS) {
            qCritical() << "Failed to get URL";
            return ret;
        }
    }

    //验证用户名密码发送到QQ
    ret = getPropname();

    if (ret != DOAProvider::SUCCESS) {
        qWarning() << "login fail" << ret;
        return ret;
    }

    return SUCCESS;
}

/**
 * @brief DOAQQProvider::getCalendarUri
 * @return LoginState 枚举
 * 获取日历uri
 */
DOAProvider::LoginState DOAQQProvider::getCalendarUri()
{
    QBuffer *buffer = new QBuffer();
    buffer->open(QIODevice::ReadWrite);
    //检索所有属性名称
    QString requestString =
        " <?xml version=\"1.0\" encoding=\"utf-8\" ?>\r\n"
        " <propfind xmlns=\"DAV:\">\r\n"
        " <prop>\r\n"
        " <current-user-principal/>\r\n"
        " <principal-URL/>\r\n"
        " <resourcetype/>\r\n"
        " </A:prop>\r\n"
        " </propfind>\r\n";
    qint64 buffersize = buffer->write(requestString.toUtf8());
    buffer->seek(0);
    buffer->size();

    QByteArray contentlength;
    contentlength.append(QString::number(buffersize));

    QString url = getUrl() + "/.well-known/caldav";
    //设置请求头
    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader("User-Agent", "deepin-calendar");
    request.setRawHeader("Depth", "1");
    request.setRawHeader("Prefer", "return-minimal");
    request.setRawHeader("Content-Type", "text/xml; charset=utf-8");
    request.setRawHeader("Content-Length", contentlength);

    //设置SSL访问
    if (getSSL()) {
        QSslConfiguration conf = request.sslConfiguration();
        conf.setPeerVerifyMode(QSslSocket::VerifyNone);
        request.setSslConfiguration(conf);
    }

    m_reply = m_manager->sendCustomRequest(request, QByteArray("PROPFIND"), buffer);

    QEventLoop eventLoop;
    connect(&m_timer, &QTimer::timeout, &eventLoop, &QEventLoop::quit);
    connect(m_reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    m_timer.start();
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);

    if (m_timer.isActive()) {
        m_timer.stop();
        QByteArray replyData = m_reply->readAll();
        int statusCode = m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        QVariant redirectAttr = m_reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

        if (m_reply->error() != QNetworkReply::NoError
            || 301 != statusCode //状态码300 Multiple Choices，既不是错误也不算重定向，应该是qt bug
            || redirectAttr.isNull()) {
            QString errString = m_reply->error() ? m_reply->errorString() : QString("This is not allowed when Redirection occurred(%1)").arg(statusCode);
            qCritical() << errString;
            replyData.clear();
            m_reply->deleteLater();
            m_reply = nullptr;
            delete buffer;
            return ServerError;
        } else {
            setUri(getUrl() + redirectAttr.toString());
        }
    } else {
        delete buffer;
        return timeouthandle();
    }
    m_reply->deleteLater();
    m_reply = nullptr;
    delete buffer;
    return SUCCESS;
}

/**
 * @brief DOAQQProvider::getPropname
 * @return LoginState 登录状态枚举
 * 验证用户密码
 */
DOAProvider::LoginState DOAQQProvider::getPropname()
{
    //des password
    QString relPassword = "";

    //使用TKEY解密
    if (!AESEncryption::ecb_encrypt(getAccountPassword(), relPassword, TKEY, false)) {
        qCritical() << "password decrypt error";
        return PassWordError;
    }

    QBuffer *buffer = new QBuffer();
    buffer->open(QIODevice::ReadWrite);
    //检索所有属性名称
    QString requestString =
        " <?xml version=\"1.0\" encoding=\"utf-8\" ?>\r\n"
        " <propfind xmlns=\"DAV:\">\r\n"
        " <prop>\r\n"
        " <current-user-principal/>\r\n"
        " <principal-URL/>\r\n"
        " <resourcetype/>\r\n"
        " </A:prop>\r\n"
        " </propfind>\r\n";
    qint64 buffersize = buffer->write(requestString.toUtf8());
    buffer->seek(0);
    buffer->size();

    QByteArray contentlength;
    contentlength.append(QString::number(buffersize));

    //设置认证字段
    QString authorization = "Basic ";
    authorization.append(QString(getAccountName() + ":" + relPassword).toLocal8Bit().toBase64());

    //设置请求头
    QNetworkRequest request;
    request.setUrl(getUri());
    request.setRawHeader("Authorization", authorization.toUtf8());
    request.setRawHeader("Depth", "1");
    request.setRawHeader("Prefer", "return-minimal");
    request.setRawHeader("Content-Type", "text/xml; charset=utf-8");
    request.setRawHeader("Content-Length", contentlength);

    //设置ssl认证方式
    if (getSSL()) {
        QSslConfiguration conf = request.sslConfiguration();
        conf.setPeerVerifyMode(QSslSocket::VerifyNone);
        request.setSslConfiguration(conf);
    }

    if (m_timer.isActive()) { //已经启动检测
        qWarning() << "checking...";
        return Checking;
    } else {
        m_timer.start();
    }

    //发送请求
    m_reply = m_manager->sendCustomRequest(request, QByteArray("PROPFIND"), buffer);

    QEventLoop eventLoop;

    connect(&m_timer, &QTimer::timeout, &eventLoop, &QEventLoop::quit);
    connect(m_reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);

    if (m_timer.isActive()) {
        m_timer.stop();
        //网络请求返回
        QByteArray replyData = m_reply->readAll();
        int statusCode = m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

        qWarning() << statusCode << getAccountID();
        if (m_reply->error() != QNetworkReply::NoError
            || (207 != statusCode && 200 != statusCode)) {
            QString errString = m_reply->error() ? m_reply->errorString() : QString("errorno(%1)").arg(statusCode);
            qWarning() << errString;
            replyData.clear();
            m_reply->deleteLater();
            m_reply = nullptr;
            delete buffer;
            if (401 == statusCode) {
                return PassWordError;
            }
            return ServerError;
        }
    } else {
        delete buffer;
        return timeouthandle();
    }
    m_reply->deleteLater();
    m_reply = nullptr;
    delete buffer;
    return SUCCESS;
}

/**
 * @brief DOAQQProvider::loginCancel
 * 取消登录
 */
void DOAQQProvider::loginCancel()
{
    isUserCancle = true;
    m_timer.stop();
    if (m_reply) {
        m_reply->abort();
    }
}

//定时器超时处理
DOAProvider::LoginState DOAQQProvider::timeouthandle()
{
    m_reply->deleteLater();
    m_reply = nullptr;

    if (isUserCancle) {
        qCritical() << "UserCancel" << getAccountID();
        isUserCancle = false;
        return UserCancel;
    }
    qCritical() << "network timeout" << getAccountID();
    return TIMEOUT;
}
