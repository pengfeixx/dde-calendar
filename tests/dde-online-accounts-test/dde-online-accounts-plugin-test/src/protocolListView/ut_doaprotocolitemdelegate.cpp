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
#include "ut_doaprotocolitemdelegate.h"
#include "../../third-party_stub/stub.h"

#include <DListView>

#include <QPainter>
#include <QEvent>
#include <QSignalSpy>

DGUI_USE_NAMESPACE

ut_doaprotocolitemdelegate::ut_doaprotocolitemdelegate()
{

}

void ut_doaprotocolitemdelegate::SetUp()
{
    doaProtocolItemDelegate = new DOAProtocolItemDelegate(&doaAccountProtocolListWidget);
}

void ut_doaprotocolitemdelegate::TearDown()
{
    delete doaProtocolItemDelegate;
    doaProtocolItemDelegate = nullptr;
}

bool ut_doaprotocolitemdelegate::stub_resultTrue()
{
    return true;
}

TEST_F(ut_doaprotocolitemdelegate, ut_doaprotocolitemdelegate_paint_001)
{
    Stub s;
    s.set(ADDR(QModelIndex, isValid), ADDR(ut_doaprotocolitemdelegate, stub_resultTrue));

    QListView listview;
    DOAProtocolModel m_listModel;
    listview.setItemDelegate(doaProtocolItemDelegate);
    listview.setModel(&m_listModel);
    QPainter painter;
    QStyleOptionViewItem option;
    QModelIndex index;
    option.state = QStyle::State_MouseOver;
    doaProtocolItemDelegate->paint(&painter, option, index);
    QPixmap pix = doaAccountProtocolListWidget.grab(QRect(QPoint(0, 0), QSize(0, 0)));
}

TEST_F(ut_doaprotocolitemdelegate, ut_doaprotocolitemdelegate_editorEvent_001)
{
    QListView listview;
    DOAProtocolModel m_listModel;
    listview.setItemDelegate(doaProtocolItemDelegate);
    listview.setModel(&m_listModel);

    QEvent event(QEvent::MouseButtonPress);

    QStyleOptionViewItem option;
    QModelIndex index;
    QSignalSpy spy(doaProtocolItemDelegate, SIGNAL(signalSelectItem(ProtocolType)));
    doaProtocolItemDelegate->editorEvent(&event, &m_listModel, option, index);
    EXPECT_EQ(spy.count(), 1);
}

TEST_F(ut_doaprotocolitemdelegate, ut_doaprotocolitemdelegate_editorEvent_002)
{
    QListView listview;
    DOAProtocolModel m_listModel;
    listview.setItemDelegate(doaProtocolItemDelegate);
    listview.setModel(&m_listModel);

    QEvent event(QEvent::MouseMove);

    QStyleOptionViewItem option;
    QModelIndex index;
    QSignalSpy spy(doaProtocolItemDelegate, SIGNAL(signalSelectItem(ProtocolType)));
    EXPECT_EQ(doaProtocolItemDelegate->editorEvent(&event, &m_listModel, option, index), false);
    EXPECT_EQ(spy.count(), 0);
}

TEST_F(ut_doaprotocolitemdelegate, ut_doaprotocolitemdelegate_sizeHint_001)
{
    QStyleOptionViewItem option;
    QModelIndex index;
    qWarning() << doaProtocolItemDelegate->sizeHint(option, index);
    EXPECT_EQ(doaProtocolItemDelegate->sizeHint(option, index), QSize(0, 56));
}
