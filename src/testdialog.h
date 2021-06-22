#ifndef TESTDIALOG_H
#define TESTDIALOG_H

#include <QDialog>
#include "QJsonObject"
#include "QJsonDocument"

namespace Ui {
class TestDialog;
}

class TestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TestDialog(QWidget *parent = nullptr);
    ~TestDialog();

private slots:
    void on_buttonBox_accepted();
    void showTest(QJsonObject o);

    void on_answerButton_clicked();

private:
    Ui::TestDialog *ui;
    int answer;
};

#endif // TESTDIALOG_H
