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
#include "ut_utils.h"
#include "utils.h"
#include <QProcess>
#include <QDir>


TEST_F(ut_utils, ut_utils_mkMutiDir_001)
{
    QString strbasepath = "/tmp";
    QString strpath = strbasepath.append("/dirtest/12/13");
    QString rmstrpath = strbasepath.append("/dirtest");
    QProcess pro;
    QString command = "rm -rf "+rmstrpath;
    pro.start(command);
    pro.waitForFinished();

    QString rmpath = Utils::mkMutiDir(rmstrpath);
    QDir mkdir(rmstrpath);
    EXPECT_TRUE(mkdir.exists());
    EXPECT_EQ(rmpath, rmstrpath);

    rmpath = Utils::mkMutiDir(strpath);
    EXPECT_EQ(rmpath, strpath);
}
