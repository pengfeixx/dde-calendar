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
#ifndef AESENCRYPTION_H
#define AESENCRYPTION_H

#include <QObject>

//传输数据加密密钥
#define TKEY "8ccaab0576dd5c9ff4ccaf8cbed55aad"
//数据库数据加密密钥
#define SKEY "7ffaab0576dad5c3fa4deaf1cb8d51ae"

class AESEncryption
{
public:
    AESEncryption();
    static QByteArray PKCS7Padding(const QByteArray &in, int alignSize);
    static QByteArray PKCS7UnPadding(const QByteArray &orgData);
    static bool ecb_encrypt(const QByteArray &orgData, QByteArray &destData, const QByteArray &key, bool enc);
};

#endif // AESENCRYPTION_H
