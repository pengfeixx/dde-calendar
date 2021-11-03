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
#include "ut_doaaccountlistitemdelegate.h"
#include "../../third-party_stub/stub.h"
#include "doaaccountlistmodel.h"


#include <DGuiApplicationHelper>

#include <QPainter>
#include <QEvent>
#include <QSignalSpy>
#include <QString>
#include <QtDebug>

DGUI_USE_NAMESPACE

bool ut_doaaccountlistitemdelegate::stub_resultTrue()
{
    return true;
}

void ut_doaaccountlistitemdelegate::SetUp()
{
    doaAccountListItemDelegate = new DOAAccountListItemDelegate(&doaAccountListWidget);
}

void ut_doaaccountlistitemdelegate::TearDown()
{
    delete doaAccountListItemDelegate;
    doaAccountListItemDelegate = nullptr;
}

TEST_F(ut_doaaccountlistitemdelegate, ut_doaaccountlistitemdelegate_paint_001)
{
    Stub s;
    s.set(ADDR(QModelIndex, isValid), ADDR(ut_doaaccountlistitemdelegate, stub_resultTrue));
    QPainter painter;
    QStyleOptionViewItem option;
    QModelIndex index;
    option.state = QStyle::State_MouseOver;
    doaAccountListItemDelegate->paint(&painter, option, index);
    QPixmap pix = doaAccountListWidget.grab(QRect(QPoint(0, 0), QSize(0, 0)));
}

TEST_F(ut_doaaccountlistitemdelegate, ut_doaaccountlistitemdelegate_paint_002)
{
    Stub s;
    s.set(ADDR(QModelIndex, isValid), ADDR(ut_doaaccountlistitemdelegate, stub_resultTrue));
    QPainter painter;
    QStyleOptionViewItem option;
    QModelIndex index;
    option.state = QStyle::State_MouseOver|QStyle::State_Selected;
    doaAccountListItemDelegate->paint(&painter, option, index);
    QPixmap pix = doaAccountListWidget.grab(QRect(QPoint(0, 0), QSize(0, 0)));
}

TEST_F(ut_doaaccountlistitemdelegate, ut_doaaccountlistitemdelegate_editorEvent_001)
{
    DListView listview;
    DOAAccountListModel m_listModel;
    listview.setItemDelegate(doaAccountListItemDelegate);
    listview.setModel(&m_listModel);

    QEvent event(QEvent::MouseButtonPress);

    QStyleOptionViewItem option;
    QModelIndex index;
    QSignalSpy spy(doaAccountListItemDelegate, SIGNAL(signalSelectItem(QString)));
    doaAccountListItemDelegate->editorEvent(&event, &m_listModel, option, index);
    EXPECT_EQ(spy.count(), 1);
}

TEST_F(ut_doaaccountlistitemdelegate, ut_doaaccountlistitemdelegate_editorEvent_002)
{
    DListView listview;
    DOAAccountListModel m_listModel;
    listview.setItemDelegate(doaAccountListItemDelegate);
    listview.setModel(&m_listModel);

    QEvent event(QEvent::MouseMove);

    QStyleOptionViewItem option;
    QModelIndex index;
    QSignalSpy spy(doaAccountListItemDelegate, SIGNAL(signalSelectItem(QString)));
    EXPECT_EQ(doaAccountListItemDelegate->editorEvent(&event, &m_listModel, option, index), true);
    EXPECT_EQ(spy.count(), 0);
}

TEST_F(ut_doaaccountlistitemdelegate, ut_doaaccountlistitemdelegate_sizeHint_001)
{
    QStyleOptionViewItem option;
    QModelIndex index;
    QFont font;
    font.setFamily("DejaVu Sans");
    qWarning() << font.family();
    //设置文字大小为50像素
    font.setPixelSize(50);
    //设置文字为粗体
    font.setBold(true);             //封装的setWeight函数
    //设置文字为斜体
    font.setItalic(true);           //封装的setStyle函数
    //设置文字大小
    font.setPointSize(20);
    //设置文字倾斜
    font.setStyle(QFont::StyleItalic);
    //设置文字粗细//enum Weight 存在5个值
    font.setWeight(QFont::Light);
    //设置文字上划线
    font.setOverline(true);
    //设置文字下划线
    font.setUnderline(true);
    //设置文字中划线
    font.setStrikeOut(true);

    //设置字间距%
    font.setLetterSpacing(QFont::PercentageSpacing,300);          //300%,100为默认
    //设置字间距像素值
    font.setLetterSpacing(QFont::AbsoluteSpacing,20);             //设置字间距为100像素
    //设置首个字母大写（跟参数有关，也可以设置全部大写AllUppercase）
    font.setCapitalization(QFont::Capitalize);

    QFontMetrics fmetr(font);
    doaAccountListItemDelegate->m_userNameMetrics = fmetr;
    doaAccountListItemDelegate->m_accountNameMetrics = fmetr;
    qWarning() << doaAccountListItemDelegate->sizeHint(option, index);
    EXPECT_EQ(doaAccountListItemDelegate->sizeHint(option, index), QSize(0, 84));
}

TEST_F(ut_doaaccountlistitemdelegate, ut_doaaccountlistitemdelegate_getStringByWidth_001)
{
    QString str = doaAccountListItemDelegate->getStringByWidth("1234567890@qq.com",
                                                               doaAccountListItemDelegate->m_accountNameMetrics, 50);
    qWarning() << str;
    EXPECT_TRUE(str.contains("…"));

}



