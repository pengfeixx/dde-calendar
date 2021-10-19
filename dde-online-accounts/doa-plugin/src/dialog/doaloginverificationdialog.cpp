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
#include "doaloginverificationdialog.h"

#include <DFontSizeManager>

#include <QVBoxLayout>

DOALoginVerificationDialog::DOALoginVerificationDialog(QWidget *parent)
    : DDialog(parent)
{
    initWidget();
    m_spinner->start();
}

DOALoginVerificationDialog::~DOALoginVerificationDialog()
{
    m_spinner->stop();
}

//是否取消登录
bool DOALoginVerificationDialog::isCaneclLogin() const
{
    return m_caneclLogin;
}

//初始化界面
void DOALoginVerificationDialog::initWidget()
{
    setIcon(QIcon::fromTheme("preferences-system", QIcon::fromTheme("application-x-desktop")));
    QVBoxLayout *layout = new QVBoxLayout;
    //标题
    m_titleLbl = new DLabel(tr("Add a CalDAV Account"));
    m_titleLbl->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    DFontSizeManager::instance()->bind(m_titleLbl, DFontSizeManager::T6, QFont::Medium);
    QPalette titleLblPe;
    QColor titleLblColor(titleLblPe.color(DPalette::BrightText));
    titleLblColor.setAlphaF(0.9);
    titleLblPe.setColor(QPalette::WindowText, titleLblColor);
    m_titleLbl->setPalette(titleLblPe);

    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_titleLbl);
    layout->addStretch();

    m_spinner = new DSpinner();
    m_spinner->setFixedSize(48, 48);
    layout->addWidget(m_spinner, 0, Qt::AlignCenter);
    layout->addSpacing(32);
    DLabel *verificationLbl = new DLabel();
    verificationLbl->setText(tr("Verifying the account..."));
    verificationLbl->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    DFontSizeManager::instance()->bind(verificationLbl, DFontSizeManager::T8, QFont::Normal);
    QPalette verificationLblPe;
    QColor verificationLblColor(verificationLblPe.color(DPalette::BrightText));
    verificationLblColor.setAlphaF(0.7);
    verificationLblPe.setColor(QPalette::WindowText, verificationLblColor);
    verificationLbl->setPalette(verificationLblPe);
    layout->addWidget(verificationLbl);
    layout->addStretch();
    QWidget *widget = new QWidget();
    widget->setLayout(layout);
    addContent(widget);
    addButton(tr("Cancel", "button"));
    this->setFixedSize(420, 346);
}

//被动关闭窗口
void DOALoginVerificationDialog::slotClose()
{
    m_caneclLogin = false;
    this->close();
}
