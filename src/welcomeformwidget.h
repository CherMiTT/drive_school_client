/*!
* \file
* \brief Header file for welcome form
* \author CherMiTT
* \date	07.04.2021
* \version 1.0
*/

#ifndef WELCOMEFORMWIDGET_H
#define WELCOMEFORMWIDGET_H

#pragma once

#include <QWidget>
#include "forms.h"

namespace Ui {
class WelcomeFormWidget;
}

/*!
 * \brief Class of welcome form
 *
 *  Form provides buttons to log in or register
 * \extends QWidget
 */
class WelcomeFormWidget : public QWidget
{
    Q_OBJECT

    friend class tst_WelcomeFormtest;

public:
    explicit WelcomeFormWidget(QWidget *parent = nullptr);
    ~WelcomeFormWidget();

private slots:
    void on_enterPushButton_clicked();
    void on_registerPushButton_clicked();

signals:
    void showLoginForm(Forms);
    void showRegisterForm(Forms);

private:
    Ui::WelcomeFormWidget *ui;
};

#endif // WELCOMEFORMWIDGET_H
