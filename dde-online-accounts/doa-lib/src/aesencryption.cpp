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
#include "aesencryption.h"

#include <gcrypt.h>

#include <QDebug>

/**
 * @brief AESEncryption::PKCS7Padding
 * @param orgData 源数据
 * @param alignSize 填充长度
 * @return 填充后数据
 */
QByteArray AESEncryption::PKCS7Padding(const QByteArray &orgData, int alignSize)
{
    // 计算填充字节数
    int paddingSize = (orgData.size() % alignSize == 0) ? alignSize : (alignSize - orgData.size() % alignSize);

    // 进行填充
    QByteArray paddingData(orgData);
    paddingData.append(paddingSize, paddingSize);
    return paddingData;
}

/**
 * @brief AESEncryption::PKCS7UnPadding
 * @param orgData 填充后数据
 * @return 解除后填充数据
 */
QByteArray AESEncryption::PKCS7UnPadding(const QByteArray &orgData)
{
    char paddingSize = orgData.at(orgData.size() - 1);
    return orgData.left(orgData.size() - paddingSize);
}

/**
 * @brief AESEncryption::ecb_encrypt
 * @param orgData 源数据
 * @param destData 目标数据
 * @param key  加解密钥
 * @param enc  加解密标志 true:加密，false:解密
 * @return
 * AES 加解密数据
 */
bool AESEncryption::ecb_encrypt(const QString &instr, QString &outstr, const QString &keystr, bool enc)
{
    QByteArray orgData;
    QByteArray key = QByteArray::fromHex(keystr.toUtf8());

    gcry_cipher_hd_t handle;

    gcry_control(GCRYCTL_DISABLE_SECMEM, 0);
    gcry_control(GCRYCTL_INITIALIZATION_FINISHED, 0);
    gcry_cipher_open(&handle, GCRY_CIPHER, GCRY_MODE, 0);

    //设置AES加解密参数
    size_t keyLength_ = gcry_cipher_get_algo_keylen(GCRY_CIPHER);
    gcry_cipher_setkey(handle, key, keyLength_);

    size_t outLength = 0;
    QByteArray destData;
    if (enc) {
        QString relPasswordtmp = QString("%1%2").arg(instr.length()).arg(instr);
        orgData = relPasswordtmp.toUtf8();
        //源数据补位32位
        QByteArray paddingArray = PKCS7Padding(orgData, 32);
        //计算补位数据长度
        outLength = paddingArray.size();
        //设置大小
        destData.resize(outLength);

        //加密数据
        gcry_cipher_encrypt(handle, destData.data(), outLength, paddingArray, paddingArray.size());

        if (destData.size() <= 0) {
            qCritical() << "encrypt error";
            gcry_cipher_close(handle);
            return false;
        }
        outstr = destData.toHex();
    } else {
        orgData = QByteArray::fromHex(instr.toUtf8());
        //计算源数据大小
        outLength = orgData.size();
        //设置大小
        destData.resize(outLength);

        //解密数据
        gcry_cipher_decrypt(handle, destData.data(), outLength, orgData, orgData.size());

        if (destData.size() <= 0) {
            qCritical() << "decrypt error";
            gcry_cipher_close(handle);
            return false;
        }
        //解除PKCS7Padding填充
        destData = PKCS7UnPadding(destData);

        QString relPasswordStr = destData;

        //取出密码长度
        int descPasswordStringLen = relPasswordStr.mid(0, 2).toInt();

        //验证密码长度是否正确
        if (descPasswordStringLen != relPasswordStr.length() - 2) {
            qCritical() << "password format error";
            gcry_cipher_close(handle);
            return false;
        }

        //根据密码前两位取出密码
        outstr = relPasswordStr.mid(2, relPasswordStr.mid(0, 2).toInt());
    }

    gcry_cipher_close(handle);

    return true;
}
