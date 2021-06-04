/*!
* \file
* \brief Header file for entering (loging in) form
* \author CherMiTT
* \date	07.04.2021
* \version 1.0
*/


#ifndef ENTERFORMWIDGET_H
#define ENTERFORMWIDGET_H

#include <QWidget>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include "forms.h"

namespace Ui {
class EnterFormWidget;
}

/*!
 * \brief Class of entering (loging in) form
 *
 *  Form provides input fields for login and password, buttons to log in and to restore password
 * \extends QWidget
 */
class EnterFormWidget : public QWidget
{
    Q_OBJECT

    friend class tst_EnterFormTest; //test

public:
    explicit EnterFormWidget(QWidget *parent = nullptr);
    ~EnterFormWidget();

private slots:
    void on_loginButton_clicked();
    void on_forgotPasswordButton_clicked();
    void wrongLoginOrPassword();
    void authorized();
    void changeWidget();

public:
signals:
    void showRestorePasswordForm(Forms);
    void showMenuForm(Forms);

private:
    QByteArray formLogInJsonByteArr(const QString&, const QString&);
    Ui::EnterFormWidget *ui;
};

#endif // ENTERFORMWIDGET_H
