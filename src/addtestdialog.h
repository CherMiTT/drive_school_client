#ifndef ADDTESTDIALOG_H
#define ADDTESTDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QBuffer>

namespace Ui {
class AddTestDialog;
}

class AddTestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddTestDialog(QWidget *parent = nullptr);
    ~AddTestDialog();

private slots:
    void on_imagePushButton_clicked();

    void on_buttonBox_accepted();

private:
    Ui::AddTestDialog *ui;
    QImage image;
};

#endif // ADDTESTDIALOG_H
