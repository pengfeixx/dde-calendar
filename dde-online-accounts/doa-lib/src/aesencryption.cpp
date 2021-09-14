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

#define GCRY_CIPHER GCRY_CIPHER_AES128 // Pick the cipher here
#define GCRY_MODE GCRY_CIPHER_MODE_ECB // Pick the cipher mode here

AESEncryption::AESEncryption()
{
}

QByteArray AESEncryption::PKCS7Padding(const QByteArray &orgData, int alignSize)
{
    // 计算填充字节数
    int paddingSize = (orgData.size() % alignSize == 0) ? alignSize : (alignSize - orgData.size() % alignSize);

    // 进行填充
    QByteArray paddingData(orgData);
    paddingData.append(paddingSize, paddingSize);
    return paddingData;
}

QByteArray AESEncryption::PKCS7UnPadding(const QByteArray &orgData)
{
    char paddingSize = orgData.at(orgData.size() - 1);
    return orgData.left(orgData.size() - paddingSize);
}

bool AESEncryption::ecb_encrypt(const QByteArray &orgData, QByteArray &destData, const QByteArray &key, bool enc)
{
    // 检查密钥合法性(只能是16、24、32字节)
    Q_ASSERT(key.size() == 16 || key.size() == 24 || key.size() == 32);

    gcry_cipher_hd_t handle;

    gcry_control(GCRYCTL_DISABLE_SECMEM, 0);
    gcry_control(GCRYCTL_INITIALIZATION_FINISHED, 0);
    gcry_cipher_open(&handle, GCRY_CIPHER, GCRY_MODE, 0);

    size_t keyLength_ = gcry_cipher_get_algo_keylen(GCRY_CIPHER);
    gcry_cipher_setkey(handle, key, keyLength_);

    std::vector<char> outVector;
    size_t outLength = 0;
    std::string outstr;

    if (enc) {
        // 生成加密密钥
        QByteArray paddingArray = PKCS7Padding(orgData, 32);
        outLength = paddingArray.size() + 1;
        outVector.resize(outLength);

        gcry_cipher_encrypt(handle, outVector.data(), outLength, paddingArray, paddingArray.size());
        outstr.assign(outVector.begin(), outVector.end());
        destData = outstr.data();
    } else {
        outLength = orgData.size() + 1;
        outVector.resize(outLength);

        gcry_cipher_decrypt(handle, outVector.data(), outLength, orgData, orgData.size());

        outstr.assign(outVector.begin(), outVector.end());
        destData = outstr.data();
        if (destData.isEmpty()) {
        }
        // 解除PKCS7Padding填充
        destData = PKCS7UnPadding(destData);
    }

    gcry_cipher_close(handle);

    return true;
}
