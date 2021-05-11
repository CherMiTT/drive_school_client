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

    QString login = ui->loginLineEdit->text();
    QString pass = ui->passwordLineEdit->text();

    if(login.length() <= 5 || pass.length() < 8)
    {
        qDebug() << "Too short login or password!";
        return;
    }

    Session::updateSession(login, pass);
    const Requester* requester = Session::getRequester();

    requester->sendRequest("login", Requester::Type::POST, Session::getAuthorizationJson());
    qDebug("Request sent");
}

void EnterFormWidget::on_forgotPasswordButton_clicked()
{
    qDebug() << "Forgot password button clicked";
    emit showRestorePasswordForm(Forms::RESTORE_PASSWORD_FORM);
}
