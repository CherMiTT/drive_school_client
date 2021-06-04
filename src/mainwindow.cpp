/*!
* \file
* \brief Code file for the main window of the program
* \author CherMiTT
* \date	07.04.2021
* \version 1.0
*/

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    currentForm = new WelcomeFormWidget();
    connect(currentForm, SIGNAL(showLoginForm(Forms)), this, SLOT(on_changeForm(Forms)));
    connect(currentForm, SIGNAL(showRegisterForm(Forms)), this, SLOT(on_changeForm(Forms)));

    vLayout = new QVBoxLayout();
    //vLayout->addStretch();
    vLayout->addWidget(currentForm);
    //vLayout->addStretch();

    hLayout = new QHBoxLayout();
    //hLayout->addStretch();
    hLayout->addLayout(vLayout);
    //hLayout->addStretch();

    centralWidget = new QWidget();
    centralWidget->setLayout(hLayout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_changeForm(Forms form)
{
    qDebug() << "Changing form to " << (int)form;

    switch (form)
    {
    case Forms::ENTER_FORM:
    {
        replaceFormInHLayout(new EnterFormWidget());
        connect(currentForm, SIGNAL(showRestorePasswordForm(Forms)), this, SLOT(on_changeForm(Forms)));
        connect(currentForm, SIGNAL(showMenuForm(Forms)), this, SLOT(on_changeForm(Forms)));
        connect(Requester::getInstance(), SIGNAL(wrongAuthorizationData()), currentForm, SLOT(wrongLoginOrPassword()));
        connect(Requester::getInstance(), SIGNAL(successfullyAuthorized()), currentForm, SLOT(authorized()));
        connect(Requester::getInstance(), SIGNAL(successfullyGotUserInfo()), currentForm, SLOT(changeWidget()));
        break;
    }
    case Forms::REGISTER_FORM:
    {
        break;
    }
    case Forms::RESTORE_PASSWORD_FORM:
    {
        break;
    }
    case Forms::WELCOME_FORM:
    {
        replaceFormInHLayout(new WelcomeFormWidget());
        connect(currentForm, SIGNAL(showLoginForm(Forms)), this, SLOT(on_changeForm(Forms)));
        connect(currentForm, SIGNAL(showRegisterForm(Forms)), this, SLOT(on_changeForm(Forms)));
        break;
    }
    case Forms::MENU_FORM:
    {
        replaceFormInHLayout(new MenuFormWidget());
        break;
    }
    case Forms::ADMIN_PANEL_FORM:
    {
        replaceFormInHLayout(new AdminPanelFormWidget());
        connect(Requester::getInstance(), SIGNAL(addUserResult(bool)), currentForm, SLOT(userAddResult(bool)));
        break;
    }
    default:
    {
        break;
    }
    }
}

void MainWindow::replaceFormInHLayout(QWidget* form)
{
    clearLayout(vLayout);
    currentForm = form;
    //vLayout->addStretch();
    vLayout->addWidget(currentForm);
    //vLayout->addStretch();
}


void MainWindow::clearLayout(QLayout* layout)
{
    QLayoutItem* item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
           delete item->widget();
        }
        delete item;
    }
}
