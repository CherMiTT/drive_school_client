#ifndef ADDLESSONDIALOG_H
#define ADDLESSONDIALOG_H

#include <QDialog>

namespace Ui {
class AddLessonDialog;
}

class AddLessonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddLessonDialog(QWidget *parent = nullptr);
    ~AddLessonDialog();

private slots:
    void on_buttonBox_accepted();
    void showGroups(QStringList list);
    void showInstructors(QStringList list);
    void showRooms(QStringList list);

private:
    Ui::AddLessonDialog *ui;
};

#endif // ADDLESSONDIALOG_H
