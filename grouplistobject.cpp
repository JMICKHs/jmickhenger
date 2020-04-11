#include "grouplistobject.h"



GroupListObject::GroupListObject(QWidget *parent)
    :QListWidget(parent)
{
    QListWidgetItem *item = new QListWidgetItem;
    item->setText("kek");
    this->setStyleSheet(
                        "QListWidget{ outline: 0;}"

                        "QListWidget::item:hover{   background-color:  rgb(240, 240, 243);selection-color: transperent;}"
                        "QListWidget::item:selected{ background-color:  rgb(235, 235, 248);selection-color: transperent;}"


                       );
    this->addItem(item);
}
