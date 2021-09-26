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
#ifndef DOAONLINEACCOUNT_H
#define DOAONLINEACCOUNT_H

#include "interface/moduleinterface.h"
#include "accountwidget/doaaccountlistwidget.h"
#include "accountwidget/doainformationwidget.h"
#include "doaaccountmodel.h"

#include <QObject>

class QTranslator;
using namespace DCC_NAMESPACE;

/**
 * @brief The onlineaccount class   网络帐户插件
 */
class DOAOnlineAccount : public QObject
    , public ModuleInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID ModuleInterface_iid FILE "api.json")
    Q_INTERFACES(DCC_NAMESPACE::ModuleInterface)
public:
    DOAOnlineAccount();
    ~DOAOnlineAccount() override;
    QIcon icon() const override; //指定图标
    void preInitialize(bool sync = false, FrameProxyInterface::PushType pushType = FrameProxyInterface::PushType::Normal) override;
    void initialize() override;
    const QString name() const override; // 插件名字,例:return QStringLiteral("privacy"); 按照标准小写,此名字关系Gsetting配置
    const QString displayName() const override; // 可添加翻译文件,显示插件名称,例:return tr("Privacy");
    int load(const QString &path) override;
    QStringList availPage() const override;
    QString translationPath() const override;
    void deactive() override;
    void contentPopped(QWidget *const w) override;
    void reset() override;
    /**
     * @brief path
     * @return 插件级别及二级菜单插件所属模块
     */
    QString path() const override;

    /**
     * @brief follow
     * @return 插件插入位置，可以字符串或者数字
     */
    QString follow() const override;
signals:

public slots:
    void active() override; // 激活逻辑处理函数
private:
    /**
     * @brief createListWidget  创建帐户列表界面
     */
    void createListWidget();

    void createInformationWidget();

private:
    DOAAccountModel *m_accountModel = nullptr; //帐户数据管理
    QTranslator *m_translator = nullptr;
    DOAAccountListWidget *m_accountListWidget = nullptr;
    DOAInformationWidget *m_informationWidget = nullptr;
};

#endif // DOAONLINEACCOUNT_H
