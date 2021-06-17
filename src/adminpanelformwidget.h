#ifndef ADMINPANELFORMWIDGET_H
#define ADMINPANELFORMWIDGET_H

#include <QWidget>
#include "QRegularExpression"
#include "QRegularExpressionValidator"
#include "QByteArray"
#include "session.h"
#include <QInputDialog>

namespace Ui {
class AdminPanelFormWidget;
}

class AdminPanelFormWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdminPanelFormWidget(QWidget *parent = nullptr);
    ~AdminPanelFormWidget();

private slots:
    void on_addUserPushButton_clicked();
    void userAddResult(bool success);

    void on_pickUsersTabWidget_currentChanged(int index);
    void on_receivedAllUsersArray(QJsonArray arr);
    void on_receivedAdminsArray(QJsonArray arr);
    void on_receivedInstructorsArray(QJsonArray arr);
    void on_receivedStudentsArray(QJsonArray arr);
    void on_receivedGroupsArray(QJsonArray arr);
    void on_receivedCarsArray(QJsonArray arr);
    void on_receivedRoomsArray(QJsonArray arr);
    void addStudent(QStringList groups);

    void on_addCarPushButton_clicked();

    void on_addUserFromViewPushButton_clicked();

private:
    Ui::AdminPanelFormWidget *ui;

    [[nodiscard]] QByteArray getNewUserJson(QString group = "");
};

#endif // ADMINPANELFORMWIDGET_H
