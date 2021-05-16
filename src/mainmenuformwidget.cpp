#include "mainmenuformwidget.h"
#include "ui_mainmenuformwidget.h"
#include "requester.h"
#include "session.h"

MainMenuFormWidget::MainMenuFormWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenuFormWidget)
{
    ui->setupUi(this);

    QJsonObject token {{"token", Session::getInstance()->getToken()}};

    Requester* requester = Session::getRequester();
    requester->sendRequest("profile-info", Requester::Type::POST, QJsonDocument(token).toJson());
    qDebug("Profile info request sent");
}

MainMenuFormWidget::~MainMenuFormWidget()
{
    delete ui;
}
