#include "menuwidget.h"
#include "ui_menuwidget.h"

MenuWidget::MenuWidget(QWidget *parent)
    :QFrame(parent),
    ui(new Ui::MenuWidget)
{
    ui->setupUi(this);
    this->setLayout(ui->mainLayout);
    this->setWindowFlags(Qt::Popup);
    this->setFrameShadow(QFrame::Raised);
    this->setMinimumWidth(260);
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
}

MenuWidget::~MenuWidget()
{
    delete ui;
}

void MenuWidget::setPosition()
{
    this->setFocus();
    this->raise();
}

void MenuWidget::setName(const QString &name)
{
    ui->nickName->setText(name);
}

void MenuWidget::on_nickname_rename(const QString &nick)
{
    ui->nickName->setText(nick);
}
