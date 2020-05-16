#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>
#include <QString>

class CustomButton : public QPushButton
{
    Q_OBJECT
private:
    int id;

public:
    explicit CustomButton(QWidget *parent = nullptr);
    CustomButton(const char* name,QSize size, QWidget *parent = nullptr);

    CustomButton(int id, QWidget *parent = nullptr);
    void setButtonIcon(const QIcon &icon);
    void setButtonRect(const QRect &rect);
};

#endif // CUSTOMBUTTON_H
