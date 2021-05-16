/*!
* \file
* \brief Code file for entering (loging in) form
* \author CherMiTT
* \date	07.04.2021
* \version 1.0
*/

#include "enterformwidget.h"
#include "ui_enterformwidget.h"
#include "requester.h"
#include "session.h"

EnterFormWidget::EnterFormWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnterFormWidget)
{
    ui->setupUi(this);

    qDebug() << "Created EnterForm";

}

EnterFormWidget::~EnterFormWidget()
{
    delete ui;
}

void EnterFormWidget::on_loginButton_clicked()
{
    qDebug() << "LogIn button clicked";

    ui->errorLabel->setText("");
    QString login = ui->loginLineEdit->text();
    QString pass = ui->passwordLineEdit->text();

    if(login.length() < 5 || pass.length() < 5)
    {
        qDebug() << "Too short login or password!";
        ui->errorLabel->setText("Логин и пароль не могут быть короче 5 символов");
        return;
    }

    //md5 hash
    pass = QString(QCryptographicHash::hash(pass.toUtf8(), QCryptographicHash::Md5).toHex());

    Session::updateSession(login, pass);
    Requester* requester = Session::getRequester();

    requester->sendRequest("login", Requester::Type::POST, Session::getAuthorizationJson());
    qDebug("Authorization request sent");
}

void EnterFormWidget::on_forgotPasswordButton_clicked()
{
    qDebug() << "Forgot password button clicked";
    emit showRestorePasswordForm(Forms::RESTORE_PASSWORD_FORM);
}

void EnterFormWidget::wrongLoginOrPassword()
{
    ui->errorLabel->setText("Неверный логин или пароль");
}

void EnterFormWidget::authorized()
{
    emit showMainMenuForm(Forms::MAIN_MENU_FORM);
}
