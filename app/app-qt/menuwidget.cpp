#include "menuwidget.h"
#include "ui_menuwidget.h"

MenuWidget::MenuWidget(QWidget *parent)
    :QFrame(parent),
    ui(new Ui::MenuWidget)
{
    ui->setupUi(this);
    this->setLayout(ui->mainLayout);
    this->setWindowFlags(Qt::SplashScreen);
    this->setFrameShape(QFrame::StyledPanel);
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

CustomButton* MenuWidget::getCreateButton()
{

}

void MenuWidget::setPosition()
{
    this->raise();
}
