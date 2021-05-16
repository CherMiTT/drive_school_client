#ifndef MAINMENUFORMWIDGET_H
#define MAINMENUFORMWIDGET_H

#include <QWidget>

namespace Ui {
class MainMenuFormWidget;
}

class MainMenuFormWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuFormWidget(QWidget *parent = nullptr);
    ~MainMenuFormWidget();

private:
    Ui::MainMenuFormWidget *ui;
};

#endif // MAINMENUFORMWIDGET_H
