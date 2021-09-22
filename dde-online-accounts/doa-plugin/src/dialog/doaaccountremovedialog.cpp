#include "doaaccountremovedialog.h"
#include "displaytext.h"

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
    DLabel *title = new DLabel(DOA::RemoveAccountWidget::deleteAccount, this);
    title->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    DFontSizeManager::instance()->bind(title, DFontSizeManager::T6, QFont::Medium);
    //提醒内容
    DLabel *rompt = new DLabel(DOA::RemoveAccountWidget::deletePrompt, this);
    rompt->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    DFontSizeManager::instance()->bind(rompt, DFontSizeManager::T6, QFont::Normal);

    //设置控制中心图标
    setIcon(QIcon::fromTheme("preferences-system", QIcon::fromTheme("application-x-desktop")));
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(10);
    layout->addWidget(title);
    layout->addWidget(rompt);

    QWidget *widget = new QWidget();
    widget->setLayout(layout);
    addContent(widget);
    //添加按钮
    addButton(DOA::RemoveAccountWidget::cancel);
    //删除按钮
    addButton(DOA::RemoveAccountWidget::deletebtn, false, ButtonType::ButtonWarning);
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
