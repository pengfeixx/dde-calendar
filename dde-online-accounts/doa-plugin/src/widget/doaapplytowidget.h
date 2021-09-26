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
#ifndef DOAAPPLYTOWIDGET_H
#define DOAAPPLYTOWIDGET_H

#include "doaapplytoobject.h"

#include <QWidget>

class DOAApplyToItem;
class QVBoxLayout;
/**
 * @brief The DOAApplyToWidget class    应用于窗口
 */
class DOAApplyToWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DOAApplyToWidget(QWidget *parent = nullptr);

    /**
     * @brief clearApp      清空应用与显示
     */
    void clearApp();

    /**
     * @brief addApp       添加应用于相关应用
     * @param app
     */
    void addApp(const DOAApplyToObject &app);
signals:
    /**
     * @brief signApplyToItemChange       应用于改变信号
     * @param app
     */
    void signApplyToItemChange(const DOAApplyToObject &app);
public slots:

private:
    /**
     * @brief initWidget      界面初始化
     */
    void initWidget();

private:
    QVector<DOAApplyToItem *> m_itemVector = {};
    QVBoxLayout *m_mainLayout = nullptr;
};

#endif // DOAAPPLYTOWIDGET_H
