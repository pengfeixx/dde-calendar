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
#ifndef DOAADDACCOUNTDIALOG_H
#define DOAADDACCOUNTDIALOG_H

#include "consts.h"

#include <DDialog>

DWIDGET_BEGIN_NAMESPACE
class DLabel;
class DLineEdit;
class DPasswordEdit;
DWIDGET_END_NAMESPACE
class QComboBox;

DWIDGET_USE_NAMESPACE
/**
 * @brief The DOAAddAccountDialog class     添加帐户对话框
 */
class DOAAddAccountDialog : public DDialog
{
    Q_OBJECT
public:
    explicit DOAAddAccountDialog(QWidget *parent = nullptr);

private:
    /**
     * @brief initWidget    初始化显示界面
     */
    void initWidget();

    /**
     * @brief addItemWidget     添加设置项
     * @param displayName       显示名称
     * @param widget            对应的设置窗口
     * @return                  返回添加的窗口
     */
    QWidget *addItemWidget(const QString &displayName, QWidget *widget);

    /**
     * @brief setLoginEnableByInputs    根据输入信息设置登录按钮是否可以用
     * @return
     */
    void setLoginEnableByInputs();

    /**
     * @brief getInputInfoIsValid       获取所有输入信息是否有效
     * @return
     */
    bool getInputInfoIsValid();

    /**
     * @brief getAddAccountInfo     获取添加帐户信息
     */
    void getAddAccountInfo();

    /**
     * @brief matchEmail        判断邮箱帐号是否合法
     * @param mail              邮箱帐号
     * @return
     */
    bool matchEmail(const QString &mail);

    /**
     * @brief matchPhoneNumber      判断手机号码是否合法
     * @param phoneNumber           手机号码
     * @return
     */
    bool matchPhoneNumber(const QString &phoneNumber);
signals:

    /**
     * @brief signalAddAccountInfo      添加帐户信号
     * @param info                      帐户信息
     */
    void signalAddAccountInfo(const AddAccountInfo &info);

    /**
     * @brief signalCloseVerificationWidget     发送关闭登录验证界面信号
     */
    void signalCloseVerificationWidget();

    /**
     * @brief signalCaneclLogin         发送取消登录信号
     * @param infoUUID
     */
    void signalCaneclLogin(const QString &infoUUID);
public slots:

    /**
     * @brief slotLoginModelChanged     登录模式改变
     * @param index
     */
    void slotLoginModelChanged(int index);

    /**
     * @brief slotAccountFocusChanged   帐户输入框焦点改变事件
     * @param onFocus
     */
    void slotAccountFocusChanged(bool onFocus);

    /**
     * @brief slotbuttonClicked     ddialog按钮点击
     * @param index                 按钮编号
     * @param text                  按钮显示文字
     */
    void slotbuttonClicked(int index, const QString &text);

    /**
     * @brief slotAccountTextChanged        帐号输入框输入处理
     * @param text
     */
    void slotAccountTextChanged(const QString &text);

    /**
     * @brief slotPasswordTextChanged       密码输入框处理
     * @param text
     */
    void slotPasswordTextChanged(const QString &text);

    /**
     * @brief slotServerIPTextChanged       服务器输入框处理
     * @param text
     */
    void slotServerIPTextChanged(const QString &text);

    /**
     * @brief slotAddAccountResults     添加帐户返回结果处理
     * @param results                   返回结果
     */
    void slotAddAccountResults(int results);

private:
    Dtk::Widget::DLabel *m_titleLbl = nullptr;
    QComboBox *m_loginModel = nullptr; //登录方式
    Dtk::Widget::DLineEdit *m_accountName = nullptr; //帐户名称
    Dtk::Widget::DPasswordEdit *m_passwordEdit = nullptr; //帐户密码
    Dtk::Widget::DLineEdit *m_serverIP = nullptr; //帐户服务器地址
    QWidget *m_serverWidget = nullptr; //服务器地址对应的widget，根据登录方式设置隐藏
    Dtk::Widget::DLabel *m_loginError = nullptr; //登录错误
    bool m_accountIsOk = false; //登录信息是否输入正确
    bool m_passwordIsOk = false; //密码是否输入正确
    bool m_serverIPIsOk = false; //服务器地址是否输入正确
    AddAccountInfo m_addInfo; //需要新增的帐户信息
    bool m_loginSuccess = false; //是否登录成功
    QWidget *m_ContentWidget = nullptr;
};

#endif // DOAADDACCOUNTDIALOG_H
