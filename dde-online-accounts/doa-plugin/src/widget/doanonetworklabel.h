#ifndef DOATITLELABEL_H
#define DOATITLELABEL_H

#include <QWidget>
/**
 * @brief The DOANoNetWorkLabel class       无网络标签
 */
class DOANoNetWorkLabel : public QWidget
{
    Q_OBJECT
public:
    explicit DOANoNetWorkLabel(QWidget *parent = nullptr);
    ~DOANoNetWorkLabel() override;
    void setText(const QString &str);
    QString getText() const;

protected:
    void paintEvent(QPaintEvent *e) override;
signals:

public slots:
private:
    QString m_text = "";
};

#endif // DOATITLELABEL_H
