#include "datashowwidget.h"

DataShowWidget::DataShowWidget(QWidget *parent)
    : QWidget(parent)
{

}

ProfileData DataShowWidget::getData()
{
  return data;
}


void DataShowWidget::GetUserProfile(const ProfileData &data)
{
    this->data = data;
    this->show();
}
