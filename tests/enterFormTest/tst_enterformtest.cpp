#include <QtTest>
#include <QCoreApplication>
#include <QString>

#include "forms.h"
#include "session.h"
#include "requester.h"
#include "enterformwidget.h"
#include "ui_enterformwidget.h"

class tst_EnterFormTest : public QObject
{
    Q_OBJECT

public:
    tst_EnterFormTest() {}
    ~tst_EnterFormTest() {}

private slots:
    void initTestCase();
    void cleanupTestCase();

    void structureCreatedTest();

    void dataEntry_data();
    void dataEntry();

    void forgotPasswordButton();
private:
    EnterFormWidget* w;
};


void tst_EnterFormTest::initTestCase()
{
    w = new EnterFormWidget();
}

void tst_EnterFormTest::cleanupTestCase()
{
    delete w;
}

/*!
 * \brief Тестируем, создались ли все элементы на форме
 */
void tst_EnterFormTest::structureCreatedTest()
{
    QVERIFY2(w->ui->loginLineEdit, "loginLineEdit not created");
    QVERIFY2(w->ui->passwordLineEdit, "passwordLineEdit not created");

    QVERIFY2(w->ui->loginLabel, "loginLabel created");
    QCOMPARE(w->ui->loginLabel->text(), "Логин");

    QVERIFY2(w->ui->passwordLabel, "passwordLabel not created");
    QCOMPARE(w->ui->passwordLabel->text(), "Пароль");

    QVERIFY2(w->ui->forgotPasswordButton, "forgotPasswordButton not created");
    QCOMPARE(w->ui->forgotPasswordButton->text(), "Забыли пароль?");

    QVERIFY2(w->ui->loginButton, "loginButton edit not created");
    QCOMPARE(w->ui->loginButton->text(), "Войти");

    QVERIFY2(w->ui->errorTextBrowser, "errorTextBrowser edit not created");
}

void tst_EnterFormTest::dataEntry_data()
{
    QTest::addColumn<QString>("login");
    QTest::addColumn<QString>("password");
    QTest::addColumn<QJsonObject>("json");

    QTest::newRow("valid login") << "user" << "qwerty1234" << QJsonObject({{"login", "user"}, {"password", "qwerty1234"}});

    QSKIP("Add more tests");
}

/*!
 * \brief Тестирует поведение при вводе данных в поля
 */
void tst_EnterFormTest::dataEntry()
{
    QFETCH(QString, login);
    QFETCH(QString, password);
    QFETCH(QJsonObject, json);

    QTest::keyClicks(w->ui->loginLineEdit, login);
    QTest::keyClicks(w->ui->passwordLineEdit, password);
    QTest::mouseClick(w->ui->loginButton, Qt::LeftButton);

    QCOMPARE(login, w->ui->loginLineEdit->text());
    QCOMPARE(password, w->ui->passwordLineEdit->text());
    QCOMPARE(json.toVariantMap(), QJsonObject({{"login", login}, {"password", password}}).toVariantMap());
}

/*!
 * \brief Тестирует поведение при нажатии кнопки "Забыли пароль"
 */
void tst_EnterFormTest::forgotPasswordButton()
{
    QSignalSpy spy(w, SIGNAL(showRestorePasswordForm(Forms)));
    QTest::mouseClick(w->ui->forgotPasswordButton, Qt::LeftButton);

    QCOMPARE(spy.size(), 1);
    QList args = spy.takeFirst();
    QCOMPARE(args.at(0).toInt(), static_cast<int>(Forms::RESTORE_PASSWORD_FORM));
}

QTEST_MAIN(tst_EnterFormTest)

#include "tst_enterformtest.moc"
