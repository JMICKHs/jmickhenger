#include "messageitemwidget.h"
#include "ui_messageitemwidget.h"

MessageItemWidget::MessageItemWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageItemWidget)
{
    ui->setupUi(this);
}

MessageItemWidget::MessageItemWidget(const QModelIndex &index, QWidget *parent)
    : QWidget(parent),
      ui(new Ui::MessageItemWidget)
{
      ui->setupUi(this);
    this->setMinimumHeight(50);
    this->setMaximumWidth(300);
    this->setLayout(ui->mainLayout);
}

MessageItemWidget::~MessageItemWidget()
{
    delete ui;
}

void MessageItemWidget::setTest(const QString &message)
{
    ui->message->setText(message);
}
