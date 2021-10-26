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
