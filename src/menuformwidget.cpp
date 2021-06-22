#include "menuformwidget.h"
#include "ui_menuformwidget.h"
#include "session.h"
#include "requester.h"

MenuFormWidget::MenuFormWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuFormWidget)
{
    ui->setupUi(this);
    on_tabWidget_currentChanged(0);
}

MenuFormWidget::~MenuFormWidget()
{
    delete ui;
}

void MenuFormWidget::on_tabWidget_currentChanged(int index)
{
    if(index == 0)
    {
        QJsonObject obj;
        obj = QJsonObject{{"token", Session::getInstance()->getToken()}};
        Session::getRequester()->sendRequest("student/schedule", Requester::Type::POST, QJsonDocument(obj).toJson());
        return;
    }
    if(index == 1)
    {
        return;
    }
}
