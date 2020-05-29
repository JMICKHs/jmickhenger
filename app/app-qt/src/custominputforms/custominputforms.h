#ifndef CUSTOMINPUTFORMS_H
#define CUSTOMINPUTFORMS_H

#include <QLineEdit>
class CustomInputForms : public QLineEdit
{
     Q_OBJECT
public:
    explicit CustomInputForms(QWidget *parent = nullptr);
};

#endif // CUSTOMINPUTFORMS_H
