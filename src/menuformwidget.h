#ifndef MENUFORMWIDGET_H
#define MENUFORMWIDGET_H

#include <QWidget>

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

private:
    Ui::MenuFormWidget *ui;
};

#endif // MENUFORMWIDGET_H
