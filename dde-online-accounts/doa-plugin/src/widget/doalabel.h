#ifndef DOALABEL_H
#define DOALABEL_H

#include <QLabel>

class DOALabel : public QLabel
{
    Q_OBJECT
public:
    explicit DOALabel(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    explicit DOALabel(const QString &text, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    void setShowText(const QString &text);

protected:
    void changeEvent(QEvent *e) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    /**
     * @brief setTextByWidth        根据宽度设置显示字符
     */
    void setTextByWidth();
signals:

public slots:
private:
    QString m_text;
};

#endif // DOALABEL_H
