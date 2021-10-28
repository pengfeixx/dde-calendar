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
#include "ut_aesencryption.h"

#include <QtDebug>

ut_aesencryption::ut_aesencryption()
{

}

void ut_aesencryption::SetUp()
{
    aes = new AESEncryption();
}

void ut_aesencryption::TearDown()
{
    delete aes;
    aes = nullptr;
}

TEST_F(ut_aesencryption, ut_aesencryption_PKCS7Padding_001)
{
    QString data = "12345";
    QByteArray paddata = aes->PKCS7Padding(data.toUtf8(), 16);
    qWarning() << QString(paddata.toHex());
    EXPECT_EQ(QString(paddata.toHex()), "31323334350b0b0b0b0b0b0b0b0b0b0b");
}

TEST_F(ut_aesencryption, ut_aesencryption_PKCS7UnPadding_001)
{
    QString data = "31323334350b0b0b0b0b0b0b0b0b0b0b";
    QByteArray unpaddata = aes->PKCS7UnPadding(QByteArray::fromHex(data.toUtf8()));
    qWarning() << QString(unpaddata);
    EXPECT_EQ(QString(unpaddata), "12345");
}

TEST_F(ut_aesencryption, ut_aesencryption_ecb_encrypt_001)
{
    QString data = "12345678";
    QString data1 = "";
    QString key= "8ddaab0576dd5c9444ccaf8cbcc55aad";
    AESEncryption::ecb_encrypt(data, data1, key, true);
    qWarning() << data1;
    EXPECT_EQ(data1, "0b3b1a9110c75f56b422a9c962078425");
    AESEncryption::ecb_encrypt(data1, data, key, false);
    qWarning() << data;
    EXPECT_EQ(data, "12345678");
}


TEST_F(ut_aesencryption, ut_aesencryption_ecb_encrypt_003)
{
    QString data = "b78afe8bc08ab4fc48c23709998a1e6f";
    bool ret = AESEncryption::ecb_encrypt("b78afe8cf08ab4fc48c23709998a1e6f", data, "123456789012", false);
    EXPECT_EQ(ret, false);
}


