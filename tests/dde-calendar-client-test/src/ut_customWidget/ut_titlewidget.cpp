#include "ut_titlewidget.h"

#include <QTest>
#include <QResizeEvent>
#include <QKeyEvent>
#include <QFocusEvent>

ut_titleWidget::ut_titleWidget()
{

}

void ut_titleWidget::SetUp()
{
    m_titleWidget = new CTitleWidget();
}

void ut_titleWidget::TearDown()
{
    delete m_titleWidget;
    m_titleWidget = nullptr;
}

TEST_F(ut_titleWidget, resizeEvent_001)
{
    m_titleWidget->setFixedSize(600, 30);
    QResizeEvent resizeEvent(QSize(500, 30), QSize(600, 30));
    QApplication::sendEvent(m_titleWidget, &resizeEvent);
    EXPECT_EQ(m_titleWidget->m_searchEdit->width(), 240);
}

TEST_F(ut_titleWidget, resizeEvent_002)
{
    m_titleWidget->setFixedSize(1900, 30);
    QResizeEvent resizeEvent1(QSize(1920, 30), QSize(1900, 30));
    QApplication::sendEvent(m_titleWidget, &resizeEvent1);
    EXPECT_EQ(m_titleWidget->m_searchEdit->width(), 354);
}

TEST_F(ut_titleWidget, eventFilter_001)
{
    DButtonBoxButton *boxbtn = m_titleWidget->findChild<DButtonBoxButton *>();
    bool isFocus = false;
    QObject::connect(m_titleWidget, &CTitleWidget::signalSetButtonFocus, [&]() {
        isFocus = true;
    });
    ASSERT_TRUE(boxbtn);
    QKeyEvent keyevent(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);
    QApplication::sendEvent(boxbtn, &keyevent);
    EXPECT_TRUE(isFocus);

    DButtonBox *buttonBox = m_titleWidget->findChild<DButtonBox *>();
    if (buttonBox) {
        buttonBox->button(0)->setFocus();
        buttonBox->button(0)->setChecked(true);
        QFocusEvent focusEvent_in(QEvent::FocusIn, Qt::FocusReason::ActiveWindowFocusReason);
        QApplication::sendEvent(buttonBox, &focusEvent_in);
    }
}

TEST_F(ut_titleWidget, eventFilter_002)
{
    int isFocus = false;
    QObject::connect(m_titleWidget, &CTitleWidget::signalSearchFocusSwitch, [&]() {
        isFocus = true;
    });
    DSearchEdit *edit = m_titleWidget->findChild<DSearchEdit *>();
    ASSERT_TRUE(edit);
    QFocusEvent focusEvent_in(QEvent::FocusIn, Qt::FocusReason::TabFocusReason);
    QApplication::sendEvent(edit->lineEdit(), &focusEvent_in);
    QFocusEvent focusEvent_out(QEvent::FocusOut, Qt::FocusReason::TabFocusReason);
    QApplication::sendEvent(edit->lineEdit(), &focusEvent_out);
    EXPECT_TRUE(isFocus);
}
