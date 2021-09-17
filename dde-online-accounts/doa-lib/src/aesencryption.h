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

#include <QString>
#include <QByteArray>

//传输密钥 用于接口间密码加密
#define TKEY "8ccaab0576dd5c9ff4ccaf8cbed55aad"
//数据库密钥 用于数据库存储密钥加密
#define SKEY "7ffaab0576dad5c3fa4deaf1cb8d51ae"

#define GCRY_CIPHER GCRY_CIPHER_AES128 // Pick the cipher here
#define GCRY_MODE GCRY_CIPHER_MODE_ECB // Pick the cipher mode here

class AESEncryption
{
public:
    /**
     * @brief AESEncryption::ecb_encrypt
     * @param orgData 源数据
     * @param destData 目标数据
     * @param key  加解密钥
     * @param enc  加解密标志 true:加密，false:解密
     * @return
     * AES 加解密数据
     */
    static bool ecb_encrypt(const QString &orgData, QString &destData, const QString &key, bool enc);

private:
    //填充数据
    static QByteArray PKCS7Padding(const QByteArray &in, int alignSize);
    //解除填充数据
    static QByteArray PKCS7UnPadding(const QByteArray &orgData);
};

#endif // AESENCRYPTION_H
