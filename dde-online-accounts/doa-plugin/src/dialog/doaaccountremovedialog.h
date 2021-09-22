#ifndef DOAACCOUNTREMOVEDIALOG_H
#define DOAACCOUNTREMOVEDIALOG_H

#include <DDialog>

DWIDGET_USE_NAMESPACE
class DOAAccountRemoveDialog : public DDialog
{
    Q_OBJECT
public:
    explicit DOAAccountRemoveDialog(QWidget *parent = nullptr);

private:
    /**
     * @brief initWidget        初始化界面
     */
    void initWidget();
signals:
    /**
     * @brief signalDeleteAccount   移除帐户
     */
    void signalDeleteAccount();
public slots:
    /**
     * @brief slotbuttonClicked     ddialog按钮点击
     * @param index                 按钮编号
     * @param text                  按钮显示文字
     */
    void slotbuttonClicked(int index, const QString &text);
};

#endif // DOAACCOUNTREMOVEDIALOG_H
