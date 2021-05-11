/*!
* \file
* \brief Header file for welcome form
* \author CherMiTT
* \date	07.04.2021
* \version 1.0
*/

#include "welcomeformwidget.h"
#include "ui_welcomeformwidget.h"

WelcomeFormWidget::WelcomeFormWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WelcomeFormWidget)
{
    ui->setupUi(this);
    qDebug() << "Created WelcomeForm";
}

WelcomeFormWidget::~WelcomeFormWidget()
{
    delete ui;
}

void WelcomeFormWidget::on_enterPushButton_clicked()
{
    emit showLoginForm(Forms::ENTER_FORM);
}

void WelcomeFormWidget::on_registerPushButton_clicked()
{
    emit showRegisterForm(Forms::REGISTER_FORM);
}
