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
#include "doaapplytowidget.h"
#include "displaytext.h"
#include "doaapplytoitem.h"

#include <DFontSizeManager>
#include <DBackgroundGroup>

#include <QLabel>
#include <QVBoxLayout>

DOAApplyToWidget::DOAApplyToWidget(QWidget *parent)
    : QWidget(parent)

{
    initWidget();
}

void DOAApplyToWidget::clearApp()
{
    for (int i = 0; i < m_itemVector.size(); ++i) {
        m_mainLayout->removeWidget(m_itemVector.at(i));
        m_itemVector.at(i)->deleteLater();
    }
    m_itemVector.clear();
}

void DOAApplyToWidget::addApp(const DOAApplyToObject &app)
{
    DOAApplyToItem *item = new DOAApplyToItem();
    item->setApplyObject(app);
    m_mainLayout->addWidget(item);
    m_itemVector.append(item);
    connect(item, &DOAApplyToItem::signalChange, this, &DOAApplyToWidget::signApplyToItemChange);
}

void DOAApplyToWidget::initWidget()
{
    QLabel *applyLabel = new QLabel(DOA::AccountInfo::applyToStr);
    applyLabel->setAlignment(Qt::AlignLeft);
    DFontSizeManager::instance()->bind(applyLabel, DFontSizeManager::T5, QFont::Medium);

    m_mainLayout = new QVBoxLayout();
    m_mainLayout->setMargin(0);

    DBackgroundGroup *group = new DBackgroundGroup();
    group->setLayout(m_mainLayout);
    group->setItemSpacing(1);
    group->setItemMargins(QMargins(0, 0, 0, 0));
    group->setBackgroundRole(QPalette::Window);
    group->setUseWidgetBackground(false);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->addWidget(applyLabel);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(group);
    this->setLayout(mainLayout);
}
