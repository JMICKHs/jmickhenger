#include "custominputforms.h"


CustomInputForms::CustomInputForms(QWidget *parent)
    :QLineEdit(parent)
{
    this->setStyleSheet("QLineEdit{background-color: rgb(230,230,230);}"
                         "QLineEdit{border-style: solid;}"
                         "QLineEdit{border-width: 1px;}"
                         "QLineEdit{border-radius: 9px;}"
                         "QLineEdit{border-color: rgb(220,220,220);}"
                         );
    this->setAutoFillBackground(true);
}
