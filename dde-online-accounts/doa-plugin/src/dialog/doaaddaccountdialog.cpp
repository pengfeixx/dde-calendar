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
#include "doaaddaccountdialog.h"
#include "displaytext.h"
#include "doaloginverificationdialog.h"
#include "aesencryption.h"

#include <DPasswordEdit>
#include <DLineEdit>
#include <DLabel>
#include <DComboBox>
#include <DFontSizeManager>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QAbstractButton>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QUuid>

DOAAddAccountDialog::DOAAddAccountDialog(QWidget *parent)
    : DDialog(parent)
{
    initWidget();
}

void DOAAddAccountDialog::initWidget()
{
    setOnButtonClickedClose(false);
    setIcon(QIcon::fromTheme("preferences-system", QIcon::fromTheme("application-x-desktop")));
    QVBoxLayout *layout = new QVBoxLayout;
    //标题
    m_titleLbl = new DLabel(DOA::LoginWidget::addCalDav);
    m_titleLbl->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    DFontSizeManager::instance()->bind(m_titleLbl, DFontSizeManager::T6, QFont::Medium);
    layout->setMargin(0);
    layout->setSpacing(10);
    layout->addWidget(m_titleLbl);
    //登录方式
    {
        m_loginModel = new QComboBox(this);
        m_loginModel->addItem(DOA::LoginWidget::loginAuto);
        m_loginModel->addItem(DOA::LoginWidget::LoginManual);
        m_loginModel->setCurrentIndex(0);
        layout->addWidget(addItemWidget(DOA::LoginWidget::loginModel, m_loginModel));
        connect(m_loginModel, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &DOAAddAccountDialog::slotLoginModelChanged);
    }
    //帐户名称
    {
        m_accountName = new DLineEdit();
        layout->addWidget(addItemWidget(DOA::LoginWidget::accountName, m_accountName));
        //提示信息
        m_accountName->setPlaceholderText(DOA::LoginWidget::accountPlaceholder);
        connect(m_accountName, &DLineEdit::focusChanged, this, &DOAAddAccountDialog::slotAccountFocusChanged);
        connect(m_accountName, &DLineEdit::textChanged, this, &DOAAddAccountDialog::slotAccountTextChanged);
    }
    //密码
    {
        m_passwordEdit = new DPasswordEdit();
        layout->addWidget(addItemWidget(DOA::LoginWidget::accountPassword, m_passwordEdit));
        m_passwordEdit->setPlaceholderText(DOA::LoginWidget::accountPasswordPlaceholder);
        connect(m_passwordEdit, &DLineEdit::focusChanged, this, &DOAAddAccountDialog::slotPasswordFocusChanged);
        connect(m_passwordEdit, &DLineEdit::textChanged, this, &DOAAddAccountDialog::slotPasswordTextChanged);
    }
    //服务器地址
    {
        m_serverIP = new DLineEdit();
        m_serverWidget = addItemWidget(DOA::LoginWidget::serverIp, m_serverIP);
        layout->addWidget(m_serverWidget);
        m_serverWidget->setVisible(false);
        m_serverIP->setPlaceholderText(DOA::LoginWidget::serveripPlaceholder);
        connect(m_serverIP, &DLineEdit::focusChanged, this, &DOAAddAccountDialog::slotServerIPFocusChanged);
        connect(m_serverIP, &DLineEdit::textChanged, this, &DOAAddAccountDialog::slotPasswordTextChanged);
    }
    layout->addStretch();
    //错误信息
    {
        m_loginError = new DLabel();
        layout->addWidget(m_loginError);
        m_loginError->setFixedHeight(20);
        m_loginError->setForegroundRole(DPalette::TextWarning);
        m_loginError->setAlignment(Qt::AlignCenter);
        DFontSizeManager::instance()->bind(m_titleLbl, DFontSizeManager::T8, QFont::Normal);
    }

    QWidget *widget = new QWidget();
    widget->setLayout(layout);
    addContent(widget);
    //添加按钮
    {
        addButton(DOA::LoginWidget::CancelBtn);
        addButton(DOA::LoginWidget::signInBtn, false, ButtonType::ButtonRecommend);
        //登录按钮默认不可用
        getButton(1)->setEnabled(false);
    }
    this->setFixedSize(420, 346);

    connect(this, &DDialog::buttonClicked, this, &DOAAddAccountDialog::slotbuttonClicked);
}

QWidget *DOAAddAccountDialog::addItemWidget(const QString &displayName, QWidget *widget)
{
    QLabel *label = new QLabel(displayName, this);
    label->setToolTip(displayName);
    label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    label->setFixedWidth(70);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->addWidget(label);
    layout->addWidget(widget);
    QWidget *itemWidget = new QWidget();
    itemWidget->setLayout(layout);
    itemWidget->setFixedHeight(36);
    return itemWidget;
}

//根据输入信息设置登录按钮是否可以用
void DOAAddAccountDialog::setLoginEnableByInputs()
{
    bool enable = m_accountName->lineEdit()->text().isEmpty() || m_passwordEdit->lineEdit()->text().isEmpty();
    if (m_loginModel->currentIndex() == 1) {
        //手动模式
        enable = enable || m_serverIP->lineEdit()->text().isEmpty();
    }
    getButton(1)->setEnabled(!enable);
}

//获取所有输入信息是否有效
bool DOAAddAccountDialog::getInputInfoIsValid()
{
    bool isOk = m_accountIsOk && m_passwordIsOk;
    if (m_loginModel->currentIndex() == 1) {
        //手动模式
        isOk = isOk && m_serverIPIsOk;
    }
    return isOk;
}

//获取添加帐户信息
void DOAAddAccountDialog::getAddAccountInfo()
{
    m_addInfo.type = m_loginModel->currentIndex() + 1;
    m_addInfo.accountName = m_accountName->text();
    QString orgarray;
    //加密
    AESEncryption::ecb_encrypt(m_passwordEdit->text().toLatin1(), orgarray, QByteArray::fromHex(TKEY), true);

    m_addInfo.accountPassword = orgarray;

    if (m_loginModel->currentIndex() == 0) {
        //自动模式
        m_addInfo.serverIP = "";
    } else {
        //手动模式
        m_addInfo.serverIP = m_serverIP->text();
    }
    m_addInfo.UUID = QUuid::createUuid().toString();
}

//判断邮箱帐号是否合法
bool DOAAddAccountDialog::matchEmail(const QString &mail)
{
    //Email地址
    QRegularExpression reg("^[A-Za-z0-9]+([_\\.][A-Za-z0-9]+)*@([A-Za-z0-9\\-]+\\.)+[A-Za-z]{2,6}$");
    QRegularExpressionMatch match = reg.match(mail);
    return match.hasMatch();
}

//判断手机号码是否合法
bool DOAAddAccountDialog::matchPhoneNumber(const QString &phoneNumber)
{
    //手机号码
    QRegularExpression reg("^(13[0-9]|14[01456879]|15[0-35-9]|16[2567]|17[0-8]|18[0-9]|19[0-35-9])\\d{8}$");
    QRegularExpressionMatch match = reg.match(phoneNumber);
    return match.hasMatch();
}

//登录模式切换
void DOAAddAccountDialog::slotLoginModelChanged(int index)
{
    //如果为手动
    if (index == 1) {
        m_serverWidget->setVisible(true);
    } else {
        m_serverWidget->setVisible(false);
    }
    setLoginEnableByInputs();
}

//帐户输入框焦点改变事件
void DOAAddAccountDialog::slotAccountFocusChanged(bool onFocus)
{
    m_accountIsOk = false;
    //如果帐户输入框失去焦点
    if (!onFocus) {
        m_loginError->setText("");
        //如果输入内容不为空
        if (!m_accountName->lineEdit()->text().isEmpty()) {
            QString accountName = m_accountName->lineEdit()->text();

            //先判断是否为合格的手机号
            if (matchPhoneNumber(accountName)) {
                m_accountName->setAlert(true);
                //提示目前只支持QQ帐号
                m_loginError->setText(DOA::LoginWidget::supportQQ);
                m_accountName->showAlertMessage(DOA::LoginWidget::supportQQ);
            } else if (matchEmail(accountName)) {
                //合格的邮箱帐号,判断是否为QQ帐号
                QRegularExpression reg("@qq.com$", QRegularExpression::CaseInsensitiveOption);
                QRegularExpressionMatch match = reg.match(accountName);
                if (match.hasMatch()) {
                    m_accountName->setAlert(false);
                    m_accountIsOk = true;
                } else {
                    //提示目前只支持QQ
                    m_accountName->showAlertMessage(DOA::LoginWidget::supportQQ);
                    m_loginError->setText(DOA::LoginWidget::supportQQ);
                }
            } else {
                m_accountName->setAlert(true);
                //提示邮箱不合法
                m_accountName->showAlertMessage(DOA::LoginWidget::illegalEmail);
                m_loginError->setText(DOA::LoginWidget::illegalEmail);
            }
        }
    }
}

//密码输入框焦点改变事件
void DOAAddAccountDialog::slotPasswordFocusChanged(bool onFocus)
{
    if (!onFocus) {
        if (!m_passwordEdit->text().isEmpty()) {
            //密码不为空

            m_passwordEdit->setAlert(false);
            m_passwordIsOk = true;
        }
    }
}

//服务器输入框焦点改变事件
void DOAAddAccountDialog::slotServerIPFocusChanged(bool onFocus)
{
    if (!onFocus) {
        if (!m_passwordEdit->text().isEmpty()) {
            //不为空
            m_serverIP->setAlert(false);
        }
    }
}

//按钮处理事件
void DOAAddAccountDialog::slotbuttonClicked(int index, const QString &text)
{
    Q_UNUSED(text)
    //如果为登录按钮
    if (index == 1) {
        //获取窗口中的帐户信息
        getAddAccountInfo();
        //发送添加帐户信息
        emit signalAddAccountInfo(m_addInfo);
        //弹出验证窗口
        DOALoginVerificationDialog dialog(this);
        connect(this, &DOAAddAccountDialog::signalCloseVerificationWidget, &dialog, &DOALoginVerificationDialog::slotClose);
        dialog.exec();
        //如果是主动取消，则发送取消登录信号
        if (dialog.isCaneclLogin()) {
            emit signalCaneclLogin(m_addInfo.UUID);
        }
    }
}

//帐号输入框输入处理
void DOAAddAccountDialog::slotAccountTextChanged(const QString &text)
{
    Q_UNUSED(text)
    if (m_accountName->isAlert())
        m_accountName->setAlert(false);
    setLoginEnableByInputs();
}

//密码输入框处理
void DOAAddAccountDialog::slotPasswordTextChanged(const QString &text)
{
    Q_UNUSED(text)
    if (m_passwordEdit->isAlert())
        m_passwordEdit->setAlert(false);
    setLoginEnableByInputs();
}

//服务器输入框处理
void DOAAddAccountDialog::slotServerIPTextChanged(const QString &text)
{
    Q_UNUSED(text)
    if (m_serverIP->isAlert())
        m_serverIP->setAlert(true);
    setLoginEnableByInputs();
}

void DOAAddAccountDialog::slotLoginState(int state)
{
    //关闭登录验证对话框
    emit signalCloseVerificationWidget();
    //根据返回状态决定是关闭登录对话框还是提示错误信息
    switch (state) {
    case 1:

        break;
    default:
        break;
    }
}
