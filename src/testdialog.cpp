#include "testdialog.h"
#include "ui_testdialog.h"
#include "session.h"
#include "requester.h"

TestDialog::TestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestDialog)
{
    ui->setupUi(this);

    connect(Session::getRequester(), SIGNAL(testInfo(QJsonObject)), this, SLOT(showTest(QJsonObject)));
}

TestDialog::~TestDialog()
{
    delete ui;
}

void TestDialog::on_buttonBox_accepted()
{

}

void TestDialog::showTest(QJsonObject o)
{
    qDebug() << o;
    QString text = o.value("text").toString();
    QString var1 = o.value("var1").toString();
    QString var2 = o.value("var2").toString();
    QString var3 = o.value("var3").toString();
    QString var4 = o.value("var4").toString();
    answer = o.value("answer").toString().toInt();
    QImage image;
    QByteArray im = o.value("image").toVariant().toByteArray();
    qDebug() << im;
    image.fromData(im, "jpg");
    ui->imageLabel->setPixmap(QPixmap::fromImage(image));
    ui->imageLabel->show();

    ui->text->setText(text);
    ui->var1->setText(var1);
    ui->var2->setText(var2);
    ui->var3->setText(var3);
    ui->var4->setText(var4);
}

void TestDialog::on_answerButton_clicked()
{
    bool result = false;
    switch (answer)
    {
    case 1:
    {
        if(ui->var1->isChecked()) result = true;
        break;
    }
    case 2:
    {
        if(ui->var2->isChecked()) result = true;
        break;
    }
    case 3:
    {
        if(ui->var3->isChecked()) result = true;
        break;
    }
    case 4:
    {
        if(ui->var4->isChecked()) result = true;
        break;
    }
    }
    if(result) ui->textBrowser->setText("Верно!");
    else ui->textBrowser->setText("Неверно!");
}
