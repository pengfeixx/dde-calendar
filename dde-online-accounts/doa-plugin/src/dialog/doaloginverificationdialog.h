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
#ifndef DOALOGINVERIFICATIONDIALOG_H
#define DOALOGINVERIFICATIONDIALOG_H

#include <DDialog>
#include <DLabel>
#include <DSpinner>

DWIDGET_USE_NAMESPACE
/**
 * @brief The DOALoginVerificationDialog class      登录验证对话框
 */
class DOALoginVerificationDialog : public DDialog
{
    Q_OBJECT
public:
    explicit DOALoginVerificationDialog(QWidget *parent = nullptr);
    ~DOALoginVerificationDialog() override;
    /**
     * @brief isCaneclLogin     是否取消登录
     * @return
     */
    bool isCaneclLogin() const;

private:
    /**
     * @brief initWidget        初始化界面
     */
    void initWidget();
signals:

public slots:
    /**
     * @brief slotClose         关闭窗口
     */
    void slotClose();

private:
    DLabel *m_titleLbl = nullptr;
    DSpinner *m_spinner = nullptr;
    bool m_caneclLogin = true; //是否取消登录，默认为取消登录，只有在被动关闭窗口时才不是取消登录
};

#endif // DOALOGINVERIFICATIONDIALOG_H
