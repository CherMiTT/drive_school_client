#ifndef MENUFORMWIDGET_H
#define MENUFORMWIDGET_H

#include <QWidget>
#include "QJsonArray"
#include "QJsonObject"
#include "QJsonDocument"

namespace Ui {
class MenuFormWidget;
}

class MenuFormWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MenuFormWidget(QWidget *parent = nullptr);
    ~MenuFormWidget();

private slots:
    void on_tabWidget_currentChanged(int index);
    void on_receivedLessonsArray(QJsonArray arr);
    void on_receivedGroupArray(QJsonObject arr);
    void on_receivedTestIds(QStringList list);

    void on_watchTest_clicked();

private:
    Ui::MenuFormWidget *ui;
};

#endif // MENUFORMWIDGET_H
