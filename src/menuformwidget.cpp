#include "menuformwidget.h"
#include "ui_menuformwidget.h"
#include "session.h"
#include "requester.h"
#include "testdialog.h"

MenuFormWidget::MenuFormWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuFormWidget)
{
    ui->setupUi(this);

    connect(Session::getRequester(), SIGNAL(showStudentSchedule(QJsonArray)), this, SLOT(on_receivedLessonsArray(QJsonArray)));
    connect(Session::getRequester(), SIGNAL(showStudentGroup(QJsonObject)), this, SLOT(on_receivedGroupArray(QJsonObject)));
    connect(Session::getRequester(), SIGNAL(showTestIds(QStringList)), this, SLOT(on_receivedTestIds(QStringList)));

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
        Session::getRequester()->sendRequest("student/group", Requester::Type::POST, QJsonDocument(obj).toJson());

        obj = QJsonObject{{"token", Session::getInstance()->getToken()}};
        Session::getRequester()->sendRequest("student/schedule", Requester::Type::POST, QJsonDocument(obj).toJson());
        return;
    }
    if(index == 1)
    {
        QJsonObject obj;
        obj = QJsonObject{{"token", Session::getInstance()->getToken()}};
        Session::getRequester()->sendRequest("student/test-ids", Requester::Type::POST, QJsonDocument(obj).toJson());
        return;
    }
}

void MenuFormWidget::on_receivedLessonsArray(QJsonArray arr)
{
    ui->scheduleTableWidget->setRowCount(arr.count());

    for(int i = 0; i < arr.count(); i++)
    {
        QJsonObject o = arr[i].toObject();
        ui->scheduleTableWidget->setItem(i, 0, new QTableWidgetItem(o.value("time").toString()));
        ui->scheduleTableWidget->setItem(i, 1, new QTableWidgetItem(o.value("room").toString()));
        ui->scheduleTableWidget->setItem(i, 2, new QTableWidgetItem(o.value("instructor").toString()));
        ui->scheduleTableWidget->setItem(i, 3, new QTableWidgetItem(o.value("type").toString()));
    }
}

void MenuFormWidget::on_receivedGroupArray(QJsonObject o)
{
    QString group = o.value("group").toString();
    ui->groupLabel->setText("Расписание группы " + group);
}

void MenuFormWidget::on_receivedTestIds(QStringList list)
{
    ui->testIdComboBox->addItems(list);
}

void MenuFormWidget::on_watchTest_clicked()
{
    QJsonObject obj;
    obj = QJsonObject{{"token", Session::getInstance()->getToken()}, {"id", ui->testIdComboBox->currentText().toInt()}};
    Session::getRequester()->sendRequest("student/test", Requester::Type::POST, QJsonDocument(obj).toJson());

    TestDialog dialog(this);
    dialog.exec();
}
