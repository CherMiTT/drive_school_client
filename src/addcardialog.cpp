#include "addcardialog.h"
#include "ui_addcardialog.h"
#include "requester.h"
#include "session.h"

AddCarDialog::AddCarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCarDialog)
{
    ui->setupUi(this);
}

AddCarDialog::~AddCarDialog()
{
    delete ui;
}

void AddCarDialog::on_buttonBox_accepted()
{
    qDebug() << "Car dialog ok clicked";
    QJsonObject obj;
    obj = QJsonObject{{"token", Session::getInstance()->getToken()}, {"model", ui->modelLineEdit->text()},
                     {"plate", ui->plateLineEdit->text()}, {"price", ui->priceLineEdit->text()},
                     {"date", ui->boughtDateDateEdit->text()}, {"status", ui->statusComboBox->currentIndex()}};
    qDebug() << obj;

    Session::getRequester()->sendRequest("add/car", Requester::Type::POST, QJsonDocument(obj).toJson());
}
