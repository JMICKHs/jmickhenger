#include "addfriendwidget.h"
#include "ui_addfriendwidget.h"

addFriendWidget::addFriendWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addFriendWidget)
{
    ui->setupUi(this);
    this->setFixedSize(200,200);
    this->setWindowFlag(Qt::Popup);
    this->setLayout(ui->verticalLayout);
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
}

addFriendWidget::~addFriendWidget()
{
    delete ui;
}

void addFriendWidget::on_addFriendButton_clicked()
{
    close();
    emit friendAddSignal(ui->loginInput->text().toInt());
}
