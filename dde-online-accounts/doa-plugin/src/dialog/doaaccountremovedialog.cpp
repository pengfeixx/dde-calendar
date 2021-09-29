#include "doaaccountremovedialog.h"

#include <DLabel>
#include <DFontSizeManager>

#include <QVBoxLayout>

DOAAccountRemoveDialog::DOAAccountRemoveDialog(QWidget *parent)
    : DDialog(parent)
{
    initWidget();
}

//初始化界面
void DOAAccountRemoveDialog::initWidget()
{
    //标题
    DLabel *title = new DLabel(tr("Are you sure you want to delete this account?"), this);
    title->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    DFontSizeManager::instance()->bind(title, DFontSizeManager::T6, QFont::Medium);
    //提醒内容
    DLabel *rompt = new DLabel(tr("You will lose all data associated with the account on this device"), this);
    rompt->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    DFontSizeManager::instance()->bind(rompt, DFontSizeManager::T6, QFont::Normal);

    //设置控制中心图标
    setIcon(QIcon::fromTheme("doa_warning"));
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(10);
    layout->addWidget(title);
    layout->addWidget(rompt);

    QWidget *widget = new QWidget();
    widget->setLayout(layout);
    addContent(widget);
    //添加按钮
    addButton(tr("Cancel", "button"));
    //删除按钮
    addButton(tr("Delete", "button"), false, ButtonType::ButtonWarning);
    connect(this, &DDialog::buttonClicked, this, &DOAAccountRemoveDialog::slotbuttonClicked);
}

//ddialog按钮点击处理
void DOAAccountRemoveDialog::slotbuttonClicked(int index, const QString &text)
{
    Q_UNUSED(text)
    //如果为删除按钮
    if (index == 1) {
        emit signalDeleteAccount();
    }
}
