#ifndef ADMINPANELFORMWIDGET_H
#define ADMINPANELFORMWIDGET_H

#include <QWidget>
#include "QRegularExpression"
#include "QRegularExpressionValidator"
#include "QByteArray"
#include "session.h"

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

private:
    Ui::AdminPanelFormWidget *ui;

    [[nodiscard]] QByteArray getNewUserJson();
};

#endif // ADMINPANELFORMWIDGET_H
