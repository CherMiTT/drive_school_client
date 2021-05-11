/*!
* \file
* \brief Code file for main function
* \author CherMiTT
* \date	07.04.2021
* \version 1.0
*/

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
