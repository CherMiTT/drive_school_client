#include "adminpanelformwidget.h"
#include "ui_adminpanelformwidget.h"
#include "addcardialog.h"

AdminPanelFormWidget::AdminPanelFormWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminPanelFormWidget)
{
    ui->setupUi(this);
    connect(Session::getRequester(), SIGNAL(showAllUsersArray(QJsonArray)), this, SLOT(on_receivedAllUsersArray(QJsonArray)));
    connect(Session::getRequester(), SIGNAL(showAdminsArray(QJsonArray)), this, SLOT(on_receivedAdminsArray(QJsonArray)));
    connect(Session::getRequester(), SIGNAL(showIstructorsArray(QJsonArray)), this, SLOT(on_receivedInstructorsArray(QJsonArray)));
    connect(Session::getRequester(), SIGNAL(showStudentsArray(QJsonArray)), this, SLOT(on_receivedStudentsArray(QJsonArray)));
    connect(Session::getRequester(), SIGNAL(showGroupsArray(QJsonArray)), this, SLOT(on_receivedGroupsArray(QJsonArray)));
    connect(Session::getRequester(), SIGNAL(showCarsArray(QJsonArray)), this, SLOT(on_receivedCarsArray(QJsonArray)));
    connect(Session::getRequester(), SIGNAL(showRoomsArray(QJsonArray)), this, SLOT(on_receivedRoomsArray(QJsonArray)));
    connect(Session::getRequester(), SIGNAL(getStudentGroup(QStringList)), this, SLOT(addStudent(QStringList)));

    on_pickUsersTabWidget_currentChanged(0);

    //TODO: сделать валидацию
}

AdminPanelFormWidget::~AdminPanelFormWidget()
{
    delete ui;
}

void AdminPanelFormWidget::on_addUserPushButton_clicked()
{
    //check all fields
    ui->statusLabel->setText("");
    if(ui->nameLineEdit->text().length() == 0)
    {
        ui->statusLabel->setText("Имя должно быть заполнено.");
        return;
    }
    if(ui->nameLineEdit->text().length() > 20)
    {
        ui->statusLabel->setText("Имя превышает 20 символов.");
        return;
    }
    if(ui->lastNameLineEdit->text().length() == 0)
    {
        ui->statusLabel->setText("Фамилия должна быть заполнена.");
        return;
    }
    if(ui->lastNameLineEdit->text().length() > 20)
    {
        ui->statusLabel->setText("Фамилия превышает 20 символов.");
        return;
    }
    if(ui->loginLineEdit->text().length() < 4 || ui->loginLineEdit->text().length() > 20)
    {
        ui->statusLabel->setText("Логин должен быть от 4 до 20 символов.");
        return;
    }
    if(ui->passwordLineEdit->text().length() < 4 || ui->passwordLineEdit->text().length() > 20)
    {
        ui->statusLabel->setText("Пароль должен быть от 4 до 20 символов.");
        return;
    }
    if(ui->phoneNumberLineEdit->text().length() < 8)
    {
        ui->statusLabel->setText("Номер телефона должен быть заполнен.");
        return;
    }
    if(ui->phoneNumberLineEdit->text().length() > 20)
    {
        ui->statusLabel->setText("Номер телефона слишком длинный.");
        return;
    }
    if(ui->emailLineEdit->text().length() < 4 || ui->emailLineEdit->text().length() > 20)
    {
        ui->statusLabel->setText("Email должен быть от 4 до 20 символов.");
        return;
    }
    if(ui->passLineEdit->text().length() < 4 || ui->passLineEdit->text().length() > 10)
    {
        ui->statusLabel->setText("Паспортные данные должны быть от 4 до 10 символов.");
        return;
    }

    Requester* requester = Session::getRequester();
    if(ui->roleComboBox->currentIndex() == 2) //Если студент
    {
        QJsonObject token {{"token", Session::getInstance()->getToken()}};
        requester->sendRequest("group-list", Requester::Type::POST, QJsonDocument(token).toJson());
        return;
    }

    if(ui->roleComboBox->currentIndex() == 1) //Если инструктор
    {
        bool notCanceled;
        int salary = QInputDialog::getInt(this, "Зарплата", "Зарплата", 10000, 1000, 100000, 1, &notCanceled);
        if (notCanceled)
        {
            Requester* requester = Session::getRequester();
            //form json and send request

            requester->sendRequest("add/user", Requester::Type::POST, getNewUserJson("", salary));
        }
        return;
    }

    //form json and send request
    requester->sendRequest("add/user", Requester::Type::POST, getNewUserJson());

}

void AdminPanelFormWidget::userAddResult(bool success)
{
    if(success)
        ui->statusLabel->setText("Пользователь добавлен");
    else
        ui->statusLabel->setText("Не удалось добавить пользователя");
}

QByteArray AdminPanelFormWidget::getNewUserJson(QString group, int salary)
{
    QString password = QString(QCryptographicHash::hash(ui->passwordLineEdit->text().toUtf8(), QCryptographicHash::Md5).toHex());
    int roleIndex =  ui->roleComboBox->currentIndex();
    QString role = "a";
    if(roleIndex == 1) role = "i";
    else if (roleIndex == 2) role = "s";

    QJsonObject obj;
    if(group != "") obj = QJsonObject{{"token", Session::getInstance()->getToken()}, {"name", ui->nameLineEdit->text()},
                     {"middle_name", ui->middleNameLineEdit->text()}, {"last_name", ui->lastNameLineEdit->text()},
                     {"login", ui->loginLineEdit->text()}, {"password", password},
                     {"phone_number", ui->phoneNumberLineEdit->text()}, {"email", ui->emailLineEdit->text()},
                     {"pass", ui->passLineEdit->text()}, {"role",  role}, {"group", group}};
    else if(salary != 0) obj = QJsonObject{{"token", Session::getInstance()->getToken()}, {"name", ui->nameLineEdit->text()},
                          {"middle_name", ui->middleNameLineEdit->text()}, {"last_name", ui->lastNameLineEdit->text()},
                          {"login", ui->loginLineEdit->text()}, {"password", password},
                          {"phone_number", ui->phoneNumberLineEdit->text()}, {"email", ui->emailLineEdit->text()},
                          {"pass", ui->passLineEdit->text()}, {"role",  role}, {"salary", salary}};
    else obj = QJsonObject{{"token", Session::getInstance()->getToken()}, {"name", ui->nameLineEdit->text()},
            {"middle_name", ui->middleNameLineEdit->text()}, {"last_name", ui->lastNameLineEdit->text()},
            {"login", ui->loginLineEdit->text()}, {"password", password},
            {"phone_number", ui->phoneNumberLineEdit->text()}, {"email", ui->emailLineEdit->text()},
            {"pass", ui->passLineEdit->text()}, {"role",  role}};

    qDebug() << obj;
    return QJsonDocument(obj).toJson();
}

void AdminPanelFormWidget::on_pickUsersTabWidget_currentChanged(int index)
{
    QJsonObject token {{"token", Session::getInstance()->getToken()}};
    Requester* requester = Session::getRequester();

    switch (index)
    {
    case 0:
    {
        qDebug() << "Displaying all users";
        requester->sendRequest("all-users", Requester::Type::POST, QJsonDocument(token).toJson());
        break;
    }
    case 1:
    {
        qDebug() << "Displaying students";
        requester->sendRequest("all-students", Requester::Type::POST, QJsonDocument(token).toJson());
        break;
    }
    case 2:
    {
        qDebug() << "Displaying instructors";
        requester->sendRequest("all-instructors", Requester::Type::POST, QJsonDocument(token).toJson());
        break;
    }
    case 3:
    {
        qDebug() << "Displaying admins";
        requester->sendRequest("all-admins", Requester::Type::POST, QJsonDocument(token).toJson());
        break;
    }
    case 4:
    {
        qDebug() << "Displaying groups";
        requester->sendRequest("all-groups", Requester::Type::POST, QJsonDocument(token).toJson());
        break;
    }
    case 5:
    {
        qDebug() << "Displaying cars";
        requester->sendRequest("all-cars", Requester::Type::POST, QJsonDocument(token).toJson());
        break;
    }
    case 6:
    {
        qDebug() << "Displaying rooms";
        requester->sendRequest("all-rooms", Requester::Type::POST, QJsonDocument(token).toJson());
        break;
    }

    }
}

void AdminPanelFormWidget::on_receivedAllUsersArray(QJsonArray arr)
{
    ui->allUsersTableWidget->setRowCount(arr.count());

    for(int i = 0; i < arr.count(); i++)
    {
        QJsonObject o = arr[i].toObject();
        ui->allUsersTableWidget->setItem(i, 0, new QTableWidgetItem(o.value("login").toString()));
        ui->allUsersTableWidget->setItem(i, 1, new QTableWidgetItem(o.value("first_name").toString()));
        ui->allUsersTableWidget->setItem(i, 2, new QTableWidgetItem(o.value("last_name").toString()));
        ui->allUsersTableWidget->setItem(i, 3, new QTableWidgetItem(o.value("middle_name").toString()));
        ui->allUsersTableWidget->setItem(i, 4, new QTableWidgetItem(o.value("phone_number").toString()));
        ui->allUsersTableWidget->setItem(i, 5, new QTableWidgetItem(o.value("email").toString()));
        ui->allUsersTableWidget->setItem(i, 6, new QTableWidgetItem(o.value("pass_number").toString()));
        ui->allUsersTableWidget->setItem(i, 7, new QTableWidgetItem(o.value("registration_date").toString()));
        ui->allUsersTableWidget->setItem(i, 8, new QTableWidgetItem(o.value("role").toString()));
    }
}

void AdminPanelFormWidget::on_receivedAdminsArray(QJsonArray arr)
{
    ui->allAdminsTableWidget->setRowCount(arr.count());

    for(int i = 0; i < arr.count(); i++)
    {
        QJsonObject o = arr[i].toObject();
        ui->allAdminsTableWidget->setItem(i, 0, new QTableWidgetItem(o.value("login").toString()));
        ui->allAdminsTableWidget->setItem(i, 1, new QTableWidgetItem(o.value("first_name").toString()));
        ui->allAdminsTableWidget->setItem(i, 2, new QTableWidgetItem(o.value("last_name").toString()));
        ui->allAdminsTableWidget->setItem(i, 3, new QTableWidgetItem(o.value("middle_name").toString()));
        ui->allAdminsTableWidget->setItem(i, 4, new QTableWidgetItem(o.value("phone_number").toString()));
        ui->allAdminsTableWidget->setItem(i, 5, new QTableWidgetItem(o.value("email").toString()));
    }
}

void AdminPanelFormWidget::on_receivedInstructorsArray(QJsonArray arr)
{
    ui->allInstructorsTableWidget->setRowCount(arr.count());

    for(int i = 0; i < arr.count(); i++)
    {
        QJsonObject o = arr[i].toObject();
        ui->allInstructorsTableWidget->setItem(i, 0, new QTableWidgetItem(o.value("login").toString()));
        ui->allInstructorsTableWidget->setItem(i, 1, new QTableWidgetItem(o.value("first_name").toString()));
        ui->allInstructorsTableWidget->setItem(i, 2, new QTableWidgetItem(o.value("last_name").toString()));
        ui->allInstructorsTableWidget->setItem(i, 3, new QTableWidgetItem(o.value("middle_name").toString()));
        ui->allInstructorsTableWidget->setItem(i, 4, new QTableWidgetItem(o.value("phone_number").toString()));
        ui->allInstructorsTableWidget->setItem(i, 5, new QTableWidgetItem(o.value("email").toString()));
        ui->allInstructorsTableWidget->setItem(i, 7, new QTableWidgetItem(o.value("hired_date").toString()));
        ui->allInstructorsTableWidget->setItem(i, 8, new QTableWidgetItem(o.value("salary").toString()));
    }
}

void AdminPanelFormWidget::on_receivedStudentsArray(QJsonArray arr)
{
    ui->allStudentsTableWidget->setRowCount(arr.count());

    for(int i = 0; i < arr.count(); i++)
    {
        QJsonObject o = arr[i].toObject();
        ui->allStudentsTableWidget->setItem(i, 0, new QTableWidgetItem(o.value("login").toString()));
        ui->allStudentsTableWidget->setItem(i, 1, new QTableWidgetItem(o.value("first_name").toString()));
        ui->allStudentsTableWidget->setItem(i, 2, new QTableWidgetItem(o.value("last_name").toString()));
        ui->allStudentsTableWidget->setItem(i, 3, new QTableWidgetItem(o.value("middle_name").toString()));
        ui->allStudentsTableWidget->setItem(i, 4, new QTableWidgetItem(o.value("phone_number").toString()));
        ui->allStudentsTableWidget->setItem(i, 5, new QTableWidgetItem(o.value("email").toString()));
        ui->allStudentsTableWidget->setItem(i, 6, new QTableWidgetItem(o.value("group").toString()));
    }
}

void AdminPanelFormWidget::on_receivedGroupsArray(QJsonArray arr)
{
    ui->allGroupsTableWidget->setRowCount(arr.count());

    for(int i = 0; i < arr.count(); i++)
    {
        QJsonObject o = arr[i].toObject();
        ui->allGroupsTableWidget->setItem(i, 0, new QTableWidgetItem(o.value("id").toString()));
        ui->allGroupsTableWidget->setItem(i, 1, new QTableWidgetItem(o.value("group").toString()));
    }
}

void AdminPanelFormWidget::on_receivedCarsArray(QJsonArray arr)
{
    ui->allCarsTableWidget->setRowCount(arr.count());

    for(int i = 0; i < arr.count(); i++)
    {
        QJsonObject o = arr[i].toObject();
        ui->allCarsTableWidget->setItem(i, 0, new QTableWidgetItem(o.value("plate").toString()));
        ui->allCarsTableWidget->setItem(i, 1, new QTableWidgetItem(o.value("model").toString()));
        ui->allCarsTableWidget->setItem(i, 2, new QTableWidgetItem(o.value("status").toString()));
    }
}

void AdminPanelFormWidget::on_receivedRoomsArray(QJsonArray arr)
{
    ui->allRoomsTableWidget->setRowCount(arr.count());

    for(int i = 0; i < arr.count(); i++)
    {
        QJsonObject o = arr[i].toObject();
        ui->allRoomsTableWidget->setItem(i, 0, new QTableWidgetItem(o.value("number").toString()));
    }
}

void AdminPanelFormWidget::addStudent(QStringList groups)
{
    bool notCanceled;
    QString group = QInputDialog::getItem(this, "Выбор группы", "Выберите группу",
                                        groups, 0, false, &notCanceled);
    if (notCanceled)
    {
        Requester* requester = Session::getRequester();
        //form json and send request
        qDebug() << group;
        requester->sendRequest("add/user", Requester::Type::POST, getNewUserJson(group));
    }
}

void AdminPanelFormWidget::on_addCarPushButton_clicked()
{
    AddCarDialog dialog(this);
    dialog.exec();
}

void AdminPanelFormWidget::on_addRoomPushButton_clicked()
{
    bool notCanceled;
    int room = QInputDialog::getInt(this, "Номер аудитории", "Номер аудитории", 1, 1, 1000, 1, &notCanceled);
    if (notCanceled)
    {
        Requester* requester = Session::getRequester();
        //form json and send request
        qDebug() << room;
        QJsonObject obj;
        obj = QJsonObject{{"token", Session::getInstance()->getToken()}, {"room", room}};

        requester->sendRequest("add/room", Requester::Type::POST, QJsonDocument(obj).toJson());
    }
}

void AdminPanelFormWidget::on_addGroupPushButton_clicked()
{
    bool notCanceled;
    QString name = QInputDialog::getText(this, "Название группы", "Название группы", QLineEdit::Normal, "", &notCanceled);
    if (notCanceled)
    {
        Requester* requester = Session::getRequester();
        //form json and send request
        qDebug() << name;
        QJsonObject obj;
        obj = QJsonObject{{"token", Session::getInstance()->getToken()}, {"name", name}};

        requester->sendRequest("add/group", Requester::Type::POST, QJsonDocument(obj).toJson());
    }
}

void AdminPanelFormWidget::on_addStudentPushButton_clicked()
{
    ui->mainTabWidget->setCurrentIndex(1);
}

void AdminPanelFormWidget::on_addUserFromViewPushButton_clicked()
{
    ui->mainTabWidget->setCurrentIndex(1);
}

void AdminPanelFormWidget::on_addInstructorPushButton_clicked()
{
    ui->mainTabWidget->setCurrentIndex(1);
}

void AdminPanelFormWidget::on_pushButton_clicked()
{
    ui->mainTabWidget->setCurrentIndex(1);
}
