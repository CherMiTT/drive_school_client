#include "addtestdialog.h"
#include "ui_addtestdialog.h"
#include "session.h"
#include "requester.h"

AddTestDialog::AddTestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTestDialog)
{
    ui->setupUi(this);
}

AddTestDialog::~AddTestDialog()
{
    delete ui;
}

void AddTestDialog::on_imagePushButton_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, "Выбор изображения", "", "*.jpg");
    image.load(imagePath);
}

void AddTestDialog::on_buttonBox_accepted()
{
    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "JPG");
    buffer.close();

    QJsonObject obj;
    obj = QJsonObject{{"token", Session::getInstance()->getToken()}, {"text", ui->question->toPlainText()},
                     {"var1", ui->var1->text()}, {"var2", ui->var2->text()},
                     {"var3", ui->var3->text()}, {"var4", ui->var4->text()},
                     {"answer", ui->answer->currentIndex() + 1}, {"comment", ui->comment->toPlainText()},
                     {"image", QString::fromStdString(ba.toStdString())}};
    qDebug() << obj;
    Session::getRequester()->sendRequest("add/test", Requester::Type::POST, QJsonDocument(obj).toJson());
}
