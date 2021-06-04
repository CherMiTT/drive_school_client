#include "adminpanelformwidget.h"
#include "ui_adminpanelformwidget.h"

AdminPanelFormWidget::AdminPanelFormWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminPanelFormWidget)
{
    ui->setupUi(this);

    //TODO: сделать валидацию

    /*QRegularExpression nameRegEx("[A-Z, a-z, а-я, А-Я]{0, 20}");
    QRegularExpression phoneRegEx("((\+7|7|8)+([0-9]){10})");
    QRegularExpression emailRegEx("(?:[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*|\"(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21\x23-\x5b\x5d-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])*\")@(?:(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\[(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?|[a-z0-9-]*[a-z0-9]:(?:[\x01-\x08\x0b\x0c\x0e-\x1f\x21-\x5a\x53-\x7f]|\\[\x01-\x09\x0b\x0c\x0e-\x7f])+)\])");
    QRegularExpression passwordRegEx("(?=.*[0-9])(?=.*[a-z])(?=.*[A-Z])(?=.*[@#$%^&+=])(?=\S+$).{8,}$");
    QRegularExpression loginRegEx("(?=.*[A-Za-z0-9]$)[A-Za-z][A-Za-z\d.-]{0,19}");

    QValidator *nameValidator = new QRegularExpressionValidator(nameRegEx);
    QValidator *emailValidator = new QRegularExpressionValidator(emailRegEx);
    QValidator *phoneValidator = new QRegularExpressionValidator(phoneRegEx);
    QValidator *passwordValidator = new QRegularExpressionValidator(passwordRegEx);
    QValidator *loginValidator = new QRegularExpressionValidator(loginRegEx);

    ui->nameLineEdit->setValidator(nameValidator);
    ui->lastnameLineEdit->setValidator(nameValidator);
    ui->middleNameLineEdit->setValidator(nameValidator);
    ui->phoneNumberLineEdit->setValidator(phoneValidator);
    ui->emailLineEdit->setValidator(emailValidator);
    ui->passwordLineEdit->setValidator(passwordValidator);
    ui->loginLineEdit->setValidator(loginValidator);*/
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

    //form json and send request
    Requester* requester = Session::getRequester();
    requester->sendRequest("add/user", Requester::Type::POST, getNewUserJson());

}

void AdminPanelFormWidget::userAddResult(bool success)
{
    if(success)
        ui->statusLabel->setText("Пользователь добавлен");
    else
        ui->statusLabel->setText("Не удалось добавить пользователя");
}

QByteArray AdminPanelFormWidget::getNewUserJson()
{
    QString password = QString(QCryptographicHash::hash(ui->passwordLineEdit->text().toUtf8(), QCryptographicHash::Md5).toHex());
    int roleIndex =  ui->roleComboBox->currentIndex();
    QString role = "a";
    if(roleIndex == 1) role = "i";
    else if (roleIndex == 2) role = "s";

    QJsonObject obj {{"token", Session::getInstance()->getToken()}, {"name", ui->nameLineEdit->text()},
                     {"middle_name", ui->middleNameLineEdit->text()}, {"last_name", ui->lastNameLineEdit->text()},
                     {"login", ui->loginLineEdit->text()}, {"password", password},
                     {"phone_number", ui->phoneNumberLineEdit->text()}, {"email", ui->emailLineEdit->text()},
                     {"pass", ui->passLineEdit->text()}, {"role",  role}};
    qDebug() << obj;
    return QJsonDocument(obj).toJson();
}
