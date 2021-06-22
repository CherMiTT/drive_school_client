#include "addlessondialog.h"
#include "ui_addlessondialog.h"
#include "session.h"
#include "requester.h"

AddLessonDialog::AddLessonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLessonDialog)
{
    ui->setupUi(this);

    Requester* requester = Session::getRequester();

    connect(requester, SIGNAL(getLessonGroup(QStringList)), this, SLOT(showGroups(QStringList)));
    connect(requester, SIGNAL(getLessonInstructor(QStringList)), this, SLOT(showInstructors(QStringList)));
    connect(requester, SIGNAL(getLessonRoom(QStringList)), this, SLOT(showRooms(QStringList)));

    QJsonObject token {{"token", Session::getInstance()->getToken()}};
    requester->sendRequest("lesson-group-list", Requester::Type::POST, QJsonDocument(token).toJson());
    requester->sendRequest("lesson-instr-list", Requester::Type::POST, QJsonDocument(token).toJson());
    requester->sendRequest("lesson-rooms-list", Requester::Type::POST, QJsonDocument(token).toJson());
}

AddLessonDialog::~AddLessonDialog()
{
    delete ui;
}

void AddLessonDialog::on_buttonBox_accepted()
{
    Requester* requester = Session::getRequester();
    QJsonObject obj {{"token", Session::getInstance()->getToken()},
                     {"group", ui->groupComboBox->currentText()},
                     {"instructor", ui->instructorComboBox->currentText()},
                     {"room", ui->roomComboBox->currentText()},
                     {"time", ui->dateTimeEdit->dateTime().toString("yyyy MM dd hh mm ss")},
                     {"type", ui->lessonTypeComboBox->currentIndex()}};
    requester->sendRequest("add/lesson", Requester::Type::POST, QJsonDocument(obj).toJson());
}

void AddLessonDialog::showGroups(QStringList list)
{
    ui->groupComboBox->addItems(list);
}

void AddLessonDialog::showInstructors(QStringList list)
{
    ui->instructorComboBox->addItems(list);
}

void AddLessonDialog::showRooms(QStringList list)
{
    ui->roomComboBox->addItems(list);
}
