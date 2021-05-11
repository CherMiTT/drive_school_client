/*!
* \file
* \brief Header file for the main window of the program
* \author CherMiTT
* \date	07.04.2021
* \version 1.0
*/


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

#include "welcomeformwidget.h"
#include "enterformwidget.h"
#include "forms.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
 * \brief Class of the main window
 *
 * \extends QMainWindow
 */

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_changeForm(Forms);

private:
    Ui::MainWindow *ui;

    //Forms:
    QWidget* currentForm;
    QWidget* centralWidget;

    //Layouts:
    QVBoxLayout* vLayout;
    QHBoxLayout* hLayout;

    void replaceFormInHLayout(QWidget*);
    void clearLayout(QLayout*);
};
#endif // MAINWINDOW_H
