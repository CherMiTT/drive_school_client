#include "menuformwidget.h"
#include "ui_menuformwidget.h"
#include "session.h"

MenuFormWidget::MenuFormWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuFormWidget)
{
    ui->setupUi(this);

}

MenuFormWidget::~MenuFormWidget()
{
    delete ui;
}
