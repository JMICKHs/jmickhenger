#ifndef AVATARBUTTON_H
#define AVATARBUTTON_H

#include <QWidget>
#include <QPushButton>

class AvatarButton : public QPushButton
{
    Q_OBJECT
public:
    explicit AvatarButton(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
signals:

};

#endif // AVATARBUTTON_H
