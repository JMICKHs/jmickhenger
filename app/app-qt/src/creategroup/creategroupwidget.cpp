#include "creategroupwidget.h"
#include "ui_creategroupwidget.h"

CreateGroupWidget::CreateGroupWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateGroupWidget)
{
    ui->setupUi(this);
}

CreateGroupWidget::~CreateGroupWidget()
{
    delete ui;
}
