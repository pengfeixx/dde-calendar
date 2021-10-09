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
#include "doaloginverificationdialog.h"
#include "aesencryption.h"
#include "widget/doalabel.h"
#include "widget/doapasswordedit.h"

#include <DLineEdit>
#include <DLabel>
#include <DComboBox>
#include <DFontSizeManager>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QUuid>
#include <QNetworkConfiguration>

DOAAddAccountDialog::DOAAddAccountDialog(QWidget *parent)
    : DDialog(parent)
{
    initWidget();
}

void DOAAddAccountDialog::initWidget()
{
    setOnButtonClickedClose(false);
    //设置控制中心图标
    setIcon(QIcon::fromTheme("preferences-system", QIcon::fromTheme("application-x-desktop")));
    QVBoxLayout *layout = new QVBoxLayout;
    //标题
    m_titleLbl = new DLabel(tr("Add a CalDAV Account"));
    m_titleLbl->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    DFontSizeManager::instance()->bind(m_titleLbl, DFontSizeManager::T6, QFont::Medium);
    layout->setMargin(0);
    layout->setSpacing(10);
    layout->addWidget(m_titleLbl);
    //登录方式
    {
        m_loginModel = new DComboBox(this);
        m_loginModel->addItem(tr("Auto"));
        m_loginModel->addItem(tr("Manual"));
        m_loginModel->setCurrentIndex(0);
        layout->addWidget(addItemWidget(tr("Sign-in"), m_loginModel));
        connect(m_loginModel, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &DOAAddAccountDialog::slotLoginModelChanged);
    }
    //帐户名称
    {
        m_accountName = new DLineEdit();
        layout->addWidget(addItemWidget(tr("Account"), m_accountName));
        //提示信息
        m_accountName->setPlaceholderText(tr("Email/Phone number"));
        connect(m_accountName, &DLineEdit::focusChanged, this, &DOAAddAccountDialog::slotAccountFocusChanged);
        connect(m_accountName, &DLineEdit::textChanged, this, &DOAAddAccountDialog::slotAccountTextChanged);
    }
    //密码
    {
        m_passwordEdit = new DOAPasswordEdit();
        layout->addWidget(addItemWidget(tr("Password"), m_passwordEdit));
        m_passwordEdit->setPlaceholderText(tr("Required"));
        connect(m_passwordEdit, &DLineEdit::textChanged, this, &DOAAddAccountDialog::slotPasswordTextChanged);
    }
    //服务器地址
    {
        m_serverIP = new DLineEdit();
        //TODO:添加服务器地址限制

        m_serverWidget = addItemWidget(tr("Server IP"), m_serverIP);
        layout->addWidget(m_serverWidget);
        m_serverWidget->setVisible(false);
        m_serverIP->setPlaceholderText(tr("Required"));
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
        DFontSizeManager::instance()->bind(m_loginError, DFontSizeManager::T8, QFont::Normal);
    }

    m_ContentWidget = new QWidget();
    m_ContentWidget->setLayout(layout);
    addContent(m_ContentWidget);
    //添加按钮
    {
        addButton(tr("Cancel", "button"));
        addButton(tr("Sign In", "button"), false, ButtonType::ButtonRecommend);
        //登录按钮默认不可用
        getButton(1)->setEnabled(false);
    }
    this->setFixedSize(420, 346);

    connect(this, &DDialog::buttonClicked, this, &DOAAddAccountDialog::slotbuttonClicked);
}

QWidget *DOAAddAccountDialog::addItemWidget(const QString &displayName, QWidget *widget)
{
    DOALabel *label = new DOALabel(displayName, this);
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

//获取添加帐户信息
void DOAAddAccountDialog::getAddAccountInfo()
{
    m_addInfo.loginModel = m_loginModel->currentIndex()+1;

    m_addInfo.accountName = m_accountName->text();
    QString orgarray;
    //加密
    AESEncryption::ecb_encrypt(m_passwordEdit->text(), orgarray, TKEY, true);

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
        //如果输入内容不为空
        if (!m_accountName->lineEdit()->text().isEmpty()) {
            QString accountName = m_accountName->lineEdit()->text();

            //先判断是否为合格的手机号
            if (matchPhoneNumber(accountName)) {
                //TODO 由于目前只支持QQ，故提示目前只支持QQ帐号
                m_accountName->setAlert(true);
                m_accountName->showAlertMessage(tr("Now only QQ account is supported"), m_ContentWidget);
            } else if (matchEmail(accountName)) {
                //合格的邮箱帐号,判断是否为QQ帐号
                QRegularExpression reg("@qq.com$", QRegularExpression::CaseInsensitiveOption);
                QRegularExpressionMatch match = reg.match(accountName);
                if (match.hasMatch()) {
                    m_accountName->setAlert(false);
                    m_accountName->hideAlertMessage();
                    m_accountIsOk = true;
                } else {
                    //提示目前只支持QQ
                    m_accountName->setAlert(true);
                    m_accountName->showAlertMessage(tr("Now only QQ account is supported"), m_ContentWidget);
                }
            } else {
                m_accountName->setAlert(true);
                //提示邮箱不合法
                m_accountName->showAlertMessage(tr("Illegal email address"), m_ContentWidget);
            }
        }
    }
}

//按钮处理事件
void DOAAddAccountDialog::slotbuttonClicked(int index, const QString &text)
{
    Q_UNUSED(text)
    //如果为登录按钮
    if (index == 1) {
        //如果帐户输入不合法或网络不正常则退出
        if (!(m_accountIsOk && m_networkIsOk))
            return;
        //获取窗口中的帐户信息
        getAddAccountInfo();
        //发送添加帐户信息
        emit signalAddAccountInfo(m_addInfo);
        //TODO 添加对后端没有反馈信号的超时处理

        //弹出验证窗口
        DOALoginVerificationDialog dialog(this);
        connect(this, &DOAAddAccountDialog::signalCloseVerificationWidget, &dialog, &DOALoginVerificationDialog::slotClose);
        dialog.exec();
        //如果是主动取消，则发送取消登录信号
        if (dialog.isCaneclLogin()) {
            emit signalCaneclLogin(m_addInfo.UUID);
        }
    } else {
        //取消按钮
        close();
    }
}

//帐号输入框输入处理
void DOAAddAccountDialog::slotAccountTextChanged(const QString &text)
{
    Q_UNUSED(text)
    if (m_accountName->isAlert()) {
        m_accountName->setAlert(false);
        m_accountName->hideAlertMessage();
    }
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

//添加帐户返回结果处理
void DOAAddAccountDialog::slotAddAccountResults(int results)
{
    //关闭登录验证对话框
    emit signalCloseVerificationWidget();
    //根据返回状态决定是关闭登录对话框还是提示错误信息
    switch (results) {
    case 0: {
        // 成功, 成功后关闭登录框
        close();
    } break;
    case 1: {
        //登录超时，登录超时显示服务器异常文案
        qWarning() << "time out";
        m_loginError->setText(tr("Server error, please try again"));
    } break;
    case 2: {
        //用户取消
        m_loginError->setText("");
    } break;
    case 3: {
        //服务器异常
        m_loginError->setText(tr("Server error, please try again"));
    } break;
    case 4: {
        //认证失败
        m_loginError->setText(tr("Cannot verify the account and password"));
    } break;
    case 10: {
        //重复登录
        m_loginError->setText(tr("Account added already"));
    } break;
    default: {
        qWarning() << "Other status :" << results;
        //TODO 其他的状态按服务器异常状态错误显示，待后续状态补充后再更新
        m_loginError->setText(tr("Server error, please try again"));
    } break;
    }
}

//网络状态处理槽
void DOAAddAccountDialog::slotConfigurationChanged(const QNetworkConfiguration &config)
{
    if (!config.state().testFlag(QNetworkConfiguration::StateFlag::Active)) {
        //没有连接网络
        m_loginError->setText(tr("Network error, please check and try again"));
        m_networkIsOk = false;
    } else {
        //如果当前提示为网络错误则去除网络错误提示
        if (m_loginError->text() == tr("Network error, please check and try again")) {
            m_loginError->setText("");
            m_networkIsOk = true;
        }
    }
}
