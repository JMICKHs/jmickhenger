#include "menuwidget.h"
#include <QDebug>

MenuWidget::MenuWidget(QFrame *parent, const QSize size)
    :QFrame(parent)

{
    this->setWindowFlags(Qt::SplashScreen);
    this->setFrameShape(QFrame::StyledPanel);
    this->setFrameShadow(QFrame::Raised);
   vLayout = new QVBoxLayout;
   topLayout = new QVBoxLayout;
   QSize buttonSize(250,60);
   QSize avatarSize(90,90);
   QRect rect(0,0,80,80);
   QRegion region(rect, QRegion::Ellipse);
   label = new QLabel("AccountName");
   avatar = new CustomButton();
   avatar->setMaximumSize(avatarSize);
   avatar->setMask(region);
   QIcon icon;
   icon.addFile("G://download//iconfinder_menu-alt_134216.png");
   avatar->setStyleSheet("QPushButton{background: transparent;}"
                         );
   avatar->setIcon(icon);

   settings = new CustomButton("Настройки",buttonSize);
   createGroup = new CustomButton("Создать группу",buttonSize);
   friends = new CustomButton("Контакты",buttonSize);
   topWidget = new QWidget(this);
   topLayout->addWidget(avatar);
   topLayout->addWidget(label);
   topWidget->setLayout(topLayout);

   vLayout->addWidget(topWidget);
   vLayout->addWidget(createGroup);
   vLayout->addWidget(friends);
   vLayout->addWidget(settings);
    vLayout->setSpacing(0);
   height = size.height();

   this->setLayout(vLayout);
   this->setGeometry(QCursor::pos().x(), QCursor::pos().y(), 300, height);
   this->setFixedWidth(300);
}

void MenuWidget::setPosition()
{
    this->raise();
}
