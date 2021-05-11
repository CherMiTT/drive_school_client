#include <QtTest>
#include <QCoreApplication>
#include "welcomeformwidget.h"
#include "ui_welcomeformwidget.h"

class tst_WelcomeFormtest : public QObject
{
    Q_OBJECT

public:
    tst_WelcomeFormtest() {}
    ~tst_WelcomeFormtest() {}

private slots:
    void initTestCase();
    void cleanupTestCase();

    void structureCreatedTest();

    void enterButtonTest();
    void registerButtonTest();
private:
    WelcomeFormWidget* w;
};

void tst_WelcomeFormtest::initTestCase()
{
    w = new WelcomeFormWidget();
}

void tst_WelcomeFormtest::cleanupTestCase()
{
    delete w;
}

/*!
 * \brief Тестируем, создались ли все элементы на форме
 */
void tst_WelcomeFormtest::structureCreatedTest()
{
    QVERIFY2(w->ui->enterPushButton, "enterPushButton not created");
    QCOMPARE(w->ui->enterPushButton->text(), "Войти");

    QVERIFY2(w->ui->registerPushButton, "registerPushButton not created");
    QCOMPARE(w->ui->registerPushButton->text(), "Зарегистрироваться");

    QVERIFY2(w->ui->welcomeLabel, "welcomeLabel not createde");
}

void tst_WelcomeFormtest::enterButtonTest()
{
    QSignalSpy spy(w, SIGNAL(showLoginForm(Forms)));
    QTest::mouseClick(w->ui->enterPushButton, Qt::LeftButton);

    QCOMPARE(spy.size(), 1);
    QList args = spy.takeFirst();
    QCOMPARE(args.at(0).toInt(), static_cast<int>(Forms::ENTER_FORM));
}

void tst_WelcomeFormtest::registerButtonTest()
{
    QSignalSpy spy(w, SIGNAL(showRegisterForm(Forms)));
    QTest::mouseClick(w->ui->registerPushButton, Qt::LeftButton);

    QCOMPARE(spy.size(), 1);
    QList args = spy.takeFirst();
    QCOMPARE(args.at(0).toInt(), static_cast<int>(Forms::REGISTER_FORM));
}


QTEST_MAIN(tst_WelcomeFormtest)

#include "tst_welcomeformtest.moc"
